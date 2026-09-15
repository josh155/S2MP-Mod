<#
.SYNOPSIS
    Launch Call of Duty: WWII with s2mp-mod injected, without the S2MP Launcher.

.DESCRIPTION
    Replicates what S2MP-Launcher.exe does -- its imports show the standard
    sequence: CreateProcessW, VirtualAllocEx, WriteProcessMemory,
    CreateRemoteThread -> LoadLibraryW.

    This script does the same via P/Invoke:

        1. start s2_mp64_ship.exe SUSPENDED, so nothing runs before the DLL is in
        2. VirtualAllocEx a buffer in the target and write the DLL path (wide)
        3. CreateRemoteThread at LoadLibraryW with that buffer as the argument
        4. wait for the loader thread, check it returned a non-null HMODULE
        5. ResumeThread so the game starts with the mod already loaded

    Injecting while SUSPENDED matters: it is why the mod's hooks are installed
    before the engine initialises, which is what the console log's ordering
    (Functions::init, ArxanPatches::init, ...) depends on.

    kernel32.dll is loaded at the same base in every process on a given boot, so
    LoadLibraryW's address here is valid in the target. That is what makes the
    classic technique work without a full loader.

.PARAMETER GamePath
    Folder containing s2_mp64_ship.exe.

.PARAMETER DllPath
    The mod to inject. Defaults to the deploy location.

.PARAMETER Args
    Extra command line passed to the game.

.PARAMETER WaitForExit
    Block until the game exits (useful when scripting a check run).

.EXAMPLE
    .\Launch-S2.ps1

.EXAMPLE
    # Launch and immediately arm the automatic force-host check.
    .\Launch-S2.ps1 -Args '+set fh_autotest_pending 1'
#>
[CmdletBinding()]
param(
    [string] $GamePath = 'E:\SteamLibrary\steamapps\common\Call of Duty WWII',
    [string] $DllPath  = 'C:\Users\joshu\OneDrive\Documents\WWII\s2mp-mod.dll',
    [string] $Args     = '',
    [switch] $WaitForExit
)

$ErrorActionPreference = 'Stop'

$exe = Join-Path $GamePath 's2_mp64_ship.exe'
foreach ($p in @($exe, $DllPath)) {
    if (-not (Test-Path -LiteralPath $p)) { throw "not found: $p" }
}
$DllPath = (Resolve-Path $DllPath).Path

if (Get-Process s2_mp64_ship -ErrorAction SilentlyContinue) {
    throw 'WWII is already running. Close it first (injection happens at launch).'
}

Add-Type -Namespace S2 -Name Native -MemberDefinition @'
[StructLayout(LayoutKind.Sequential)] public struct STARTUPINFO {
    public int cb; public string r1, desktop, title;
    public int x, y, xs, ys, xCount, yCount, fill, flags;
    public short showWindow, r2; public IntPtr r3, hStdIn, hStdOut, hStdErr; }
[StructLayout(LayoutKind.Sequential)] public struct PROCESS_INFORMATION {
    public IntPtr hProcess, hThread; public int pid, tid; }

[DllImport("kernel32.dll", SetLastError=true, CharSet=CharSet.Unicode)]
public static extern bool CreateProcessW(string app, string cmd, IntPtr pa, IntPtr ta,
    bool inherit, uint flags, IntPtr env, string dir,
    ref STARTUPINFO si, out PROCESS_INFORMATION pi);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern IntPtr VirtualAllocEx(IntPtr p, IntPtr a, uint size, uint type, uint prot);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern bool WriteProcessMemory(IntPtr p, IntPtr a, byte[] buf, uint n, out UIntPtr w);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern IntPtr CreateRemoteThread(IntPtr p, IntPtr sa, uint stack,
    IntPtr start, IntPtr param, uint flags, IntPtr tid);
[DllImport("kernel32.dll", SetLastError=true, CharSet=CharSet.Unicode)]
public static extern IntPtr GetModuleHandleW(string n);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern IntPtr GetProcAddress(IntPtr h, string n);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern uint WaitForSingleObject(IntPtr h, uint ms);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern bool GetExitCodeThread(IntPtr h, out uint code);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern uint ResumeThread(IntPtr h);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern bool TerminateProcess(IntPtr h, uint code);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern bool CloseHandle(IntPtr h);
[DllImport("kernel32.dll", SetLastError=true)]
public static extern bool VirtualFreeEx(IntPtr p, IntPtr a, uint size, uint type);
'@

$CREATE_SUSPENDED = 0x4
$MEM_COMMIT_RESERVE = 0x3000
$MEM_RELEASE = 0x8000
$PAGE_READWRITE = 0x4

Write-Host "launching  : $exe"
Write-Host "injecting  : $DllPath"

$si = New-Object S2.Native+STARTUPINFO
$si.cb = [Runtime.InteropServices.Marshal]::SizeOf($si)
$pi = New-Object S2.Native+PROCESS_INFORMATION

$cmd = '"' + $exe + '"'
if ($Args) { $cmd += ' ' + $Args }

if (-not [S2.Native]::CreateProcessW($exe, $cmd, [IntPtr]::Zero, [IntPtr]::Zero, $false,
        $CREATE_SUSPENDED, [IntPtr]::Zero, $GamePath, [ref]$si, [ref]$pi)) {
    throw "CreateProcessW failed: $([ComponentModel.Win32Exception]::new([Runtime.InteropServices.Marshal]::GetLastWin32Error()).Message)"
}
Write-Host "  process created suspended, pid $($pi.pid)"

$injected = $false
try {
    $bytes = [Text.Encoding]::Unicode.GetBytes($DllPath + "`0")
    $remote = [S2.Native]::VirtualAllocEx($pi.hProcess, [IntPtr]::Zero, [uint32]$bytes.Length,
        $MEM_COMMIT_RESERVE, $PAGE_READWRITE)
    if ($remote -eq [IntPtr]::Zero) { throw 'VirtualAllocEx failed' }

    $written = [UIntPtr]::Zero
    if (-not [S2.Native]::WriteProcessMemory($pi.hProcess, $remote, $bytes, [uint32]$bytes.Length, [ref]$written)) {
        throw 'WriteProcessMemory failed'
    }

    # Valid in the target: kernel32 is at the same base in every process this boot.
    $loadLib = [S2.Native]::GetProcAddress([S2.Native]::GetModuleHandleW('kernel32.dll'), 'LoadLibraryW')
    if ($loadLib -eq [IntPtr]::Zero) { throw 'could not resolve LoadLibraryW' }

    $thread = [S2.Native]::CreateRemoteThread($pi.hProcess, [IntPtr]::Zero, 0, $loadLib, $remote, 0, [IntPtr]::Zero)
    if ($thread -eq [IntPtr]::Zero) { throw 'CreateRemoteThread failed' }

    if ([S2.Native]::WaitForSingleObject($thread, 15000) -ne 0) { throw 'the loader thread did not finish in 15 s' }

    # LoadLibraryW returns the HMODULE. Zero means the DLL failed to load, and
    # resuming a game with no mod in it would silently look like success.
    $code = 0
    [void][S2.Native]::GetExitCodeThread($thread, [ref]$code)
    if ($code -eq 0) { throw 'LoadLibraryW returned NULL - the DLL did not load (missing dependency, or wrong architecture)' }

    Write-Host "  [ok] injected, HMODULE low32 = 0x$('{0:X}' -f $code)" -ForegroundColor Green
    [void][S2.Native]::VirtualFreeEx($pi.hProcess, $remote, 0, $MEM_RELEASE)
    [void][S2.Native]::CloseHandle($thread)
    $injected = $true
}
finally {
    if (-not $injected) {
        # Never leave a suspended, un-modded process lying around.
        Write-Host '  injection failed - terminating the suspended process' -ForegroundColor Red
        [void][S2.Native]::TerminateProcess($pi.hProcess, 1)
    }
}

[void][S2.Native]::ResumeThread($pi.hThread)
Write-Host '  resumed' -ForegroundColor Green
[void][S2.Native]::CloseHandle($pi.hThread)

Write-Host "`nGame is starting with the mod loaded. F9 / Insert for the UI."
Write-Host "Force-host check: Host tab -> 'Start check', or console: fh_autotest 300 0`n"

if ($WaitForExit) {
    Write-Host 'waiting for the game to exit...'
    (Get-Process -Id $pi.pid).WaitForExit()
    $report = Join-Path $GamePath 's2mp_forcehost_report.txt'
    if (Test-Path $report) { Write-Host "`n--- force-host report ---"; Get-Content $report }
}
[void][S2.Native]::CloseHandle($pi.hProcess)
