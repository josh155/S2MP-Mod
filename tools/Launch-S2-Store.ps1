<#
.SYNOPSIS
    Launch the Microsoft Store / Game Pass build of WWII with s2mp-mod injected,
    BEFORE the game executes a single instruction.

.DESCRIPTION
    WHY THE STEAM LAUNCHER CANNOT BE REUSED

    tools/Launch-S2.ps1 does CreateProcessW(CREATE_SUSPENDED) on the exe. That is
    impossible here, and the reason rules out a whole family of workarounds.
    Measured on this machine:

        exe              C:\Program Files\WindowsApps\38985CA0.CallofDutyWWIIPCMS_
                         2.0.18.0_x64_WW_5bkah9njm3e9g\s2_mp64_ship.exe
        Test-Path        True          the path is enumerable
        [IO.File]::Open  ACCESS DENIED

    WindowsApps is ACL'd to TrustedInstaller. CreateProcessW needs read+execute, so
    it fails outright. Even if it did not, a process created that way carries no
    package identity, which a GDK title checks for.

    An IFEO "Debugger" key does not rescue it either. IFEO is keyed on the image
    NAME, and the Store executable is called s2_mp64_ship.exe -- the SAME name as
    the Steam build, so one key would intercept both. And the stub it launched
    would still hit the same ACL.

    WHAT THIS USES INSTEAD

    IPackageDebugSettings::EnableDebugging is the documented mechanism packaged-app
    debuggers use. With a null debugger command line it tells the OS: next time this
    package is activated, start it SUSPENDED and wait. The OS performs the
    activation, so the process gets correct package identity, and we still get the
    "nothing has run yet" guarantee the Steam launcher depends on.

        EnableDebugging(pfn, null, null)      arm
        ActivateApplication(aumid) -> pid     the OS launches it, suspended
        inject                                CreateRemoteThread -> LoadLibraryW
        Resume(pfn)                           let it run
        DisableDebugging(pfn)                 ALWAYS, even on failure

.PARAMETER Dll
    The mod to inject. Defaults to the repo's Release build.

.PARAMETER SinglePlayer
    Launch GameSP instead of GameMP.

.PARAMETER NoResume
    Arm, activate and inject, then leave the game suspended so a debugger can be
    attached before anything runs.

.PARAMETER Disarm
    Do nothing but clear the debugging flag. Use this if a run died between arming
    and disarming -- otherwise every later launch hangs waiting for a debugger.

.NOTES
    VERIFIED on this machine, offline:
        the package is installed (38985CA0.CallofDutyWWIIPCMS 2.0.18.0)
        AUMID  38985CA0.CallofDutyWWIIPCMS_5bkah9njm3e9g!GameMP
        the exe is NOT readable, which is what rules out CreateProcessW
        IPackageDebugSettings QueryInterfaces and DisableDebugging actually runs

    NOT yet verified (needs a real launch): that EnableDebugging suspends this
    title, that OpenProcess succeeds against it, and that the mod survives GDK
    licensing. See docs/XBOX-PORT.md.
#>

[CmdletBinding()]
param(
    [string] $Dll = (Join-Path $PSScriptRoot '..\bin\Release\s2mp-mod.dll'),
    [switch] $SinglePlayer,
    [switch] $NoResume,
    [switch] $Disarm
)

$ErrorActionPreference = 'Stop'
$PackageName = '38985CA0.CallofDutyWWIIPCMS'
$AppId       = if ($SinglePlayer) { 'GameSP' } else { 'GameMP' }

function Info { param([string]$m) Write-Host "  [info] $m" -ForegroundColor Gray }
function Ok   { param([string]$m) Write-Host "  [ok]   $m" -ForegroundColor Green }
function Warn { param([string]$m) Write-Host "  [warn] $m" -ForegroundColor Yellow }
function Die  { param([string]$m) Write-Host "  [FAIL] $m" -ForegroundColor Red; exit 1 }

# Both COM interfaces are IUnknown-only, with no IDispatch. PowerShell can create
# the objects but cannot late-bind to their methods ("does not contain a method
# named ..."), so every call is made from C# where the cast is a real
# QueryInterface and the vtable call is static.
Add-Type -TypeDefinition @'
using System;
using System.Runtime.InteropServices;

namespace S2Store
{
    [ComImport, Guid("F27C3930-8029-4AD1-94E3-3DBA417810C1"),
     InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IPackageDebugSettings
    {
        // Declared in vtable order. Only the head of the interface is declared,
        // which is safe because nothing past TerminateAllProcesses is called.
        void EnableDebugging([MarshalAs(UnmanagedType.LPWStr)] string packageFullName,
                             [MarshalAs(UnmanagedType.LPWStr)] string debuggerCommandLine,
                             [MarshalAs(UnmanagedType.LPWStr)] string environment);
        void DisableDebugging([MarshalAs(UnmanagedType.LPWStr)] string packageFullName);
        void Suspend([MarshalAs(UnmanagedType.LPWStr)] string packageFullName);
        void Resume([MarshalAs(UnmanagedType.LPWStr)] string packageFullName);
        void TerminateAllProcesses([MarshalAs(UnmanagedType.LPWStr)] string packageFullName);
    }

    [ComImport, Guid("2E941141-7F97-4756-BA1D-9DECDE894A3D"),
     InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IApplicationActivationManager
    {
        void ActivateApplication([MarshalAs(UnmanagedType.LPWStr)] string appUserModelId,
                                 [MarshalAs(UnmanagedType.LPWStr)] string arguments,
                                 uint options, out uint processId);
    }

    public static class Pkg
    {
        static IPackageDebugSettings Dbg()
        {
            return (IPackageDebugSettings)Activator.CreateInstance(
                Type.GetTypeFromCLSID(new Guid("B1AEC16F-2383-4852-B0E9-8F0B1DC66B4D")));
        }
        static IApplicationActivationManager Aam()
        {
            return (IApplicationActivationManager)Activator.CreateInstance(
                Type.GetTypeFromCLSID(new Guid("45BA127D-10A8-46EA-8AB7-56EA9078943C")));
        }

        public static void Arm(string pfn)    { Dbg().EnableDebugging(pfn, null, null); }
        public static void Disarm(string pfn) { Dbg().DisableDebugging(pfn); }
        public static void Go(string pfn)     { Dbg().Resume(pfn); }

        public static uint Activate(string aumid)
        {
            uint pid;
            Aam().ActivateApplication(aumid, null, 0, out pid);   // 0 = AO_NONE
            return pid;
        }
    }
}
'@

Add-Type -Namespace S2Store -Name Native -MemberDefinition @'
    [DllImport("kernel32.dll", SetLastError=true)]
    public static extern IntPtr OpenProcess(uint access, bool inherit, uint pid);
    [DllImport("kernel32.dll", SetLastError=true)]
    public static extern IntPtr VirtualAllocEx(IntPtr h, IntPtr addr, IntPtr size, uint type, uint prot);
    [DllImport("kernel32.dll", SetLastError=true)]
    public static extern bool WriteProcessMemory(IntPtr h, IntPtr addr, byte[] buf, IntPtr size, out IntPtr written);
    [DllImport("kernel32.dll", SetLastError=true)]
    public static extern IntPtr CreateRemoteThread(IntPtr h, IntPtr sa, IntPtr stack, IntPtr start, IntPtr param, uint flags, IntPtr tid);
    [DllImport("kernel32.dll", SetLastError=true)]
    public static extern uint WaitForSingleObject(IntPtr h, uint ms);
    [DllImport("kernel32.dll", SetLastError=true)]
    public static extern bool GetExitCodeThread(IntPtr h, out uint code);
    [DllImport("kernel32.dll", SetLastError=true)]
    public static extern IntPtr GetModuleHandleW(string name);
    [DllImport("kernel32.dll", SetLastError=true)]
    public static extern IntPtr GetProcAddress(IntPtr mod, string name);
    [DllImport("kernel32.dll", SetLastError=true)]
    public static extern bool CloseHandle(IntPtr h);
'@

function LastError { [ComponentModel.Win32Exception]::new([Runtime.InteropServices.Marshal]::GetLastWin32Error()).Message }

Write-Host 'S2MP-Mod -- Microsoft Store launcher' -ForegroundColor White

$pkg = Get-AppxPackage $PackageName -ErrorAction SilentlyContinue
if (-not $pkg) { Die "$PackageName is not installed for this user" }
$pfn   = $pkg.PackageFullName
$aumid = "$($pkg.PackageFamilyName)!$AppId"

if ($Disarm) {
    [S2Store.Pkg]::Disarm($pfn)
    Ok "debugging cleared for $pfn"
    exit 0
}

$Dll = [IO.Path]::GetFullPath($Dll)
if (-not (Test-Path -LiteralPath $Dll)) { Die "mod not found: $Dll" }
Ok "mod: $Dll"
Ok "package: $pfn"
Ok "activating: $aumid"

$armed = $false
try {
    # 1. Arm. A null debugger command line means "launch suspended and wait".
    #    That is the whole point: it buys the Steam launcher's before-anything-runs
    #    guarantee without ever touching the ACL'd executable.
    [S2Store.Pkg]::Arm($pfn)
    $armed = $true
    Ok 'armed - the next activation starts suspended'

    # 2. Let the OS activate it, so it gets proper package identity.
    $gamePid = [S2Store.Pkg]::Activate($aumid)
    if ($gamePid -eq 0) { Die 'activation returned PID 0' }
    Ok "launched, pid $gamePid (suspended)"

    # 3. Inject, exactly as the Steam launcher does. kernel32 sits at the same
    #    base in every process on a given boot, so LoadLibraryW's address here is
    #    valid in the target.
    $PROCESS_ALL_ACCESS = 0x1F0FFF
    $h = [S2Store.Native]::OpenProcess($PROCESS_ALL_ACCESS, $false, $gamePid)
    if ($h -eq [IntPtr]::Zero) { Die "OpenProcess failed: $(LastError)" }

    $bytes = [Text.Encoding]::Unicode.GetBytes($Dll + [char]0)
    $mem = [S2Store.Native]::VirtualAllocEx($h, [IntPtr]::Zero, [IntPtr]$bytes.Length, 0x3000, 0x04)
    if ($mem -eq [IntPtr]::Zero) { Die "VirtualAllocEx failed: $(LastError)" }

    $written = [IntPtr]::Zero
    if (-not [S2Store.Native]::WriteProcessMemory($h, $mem, $bytes, [IntPtr]$bytes.Length, [ref]$written)) {
        Die "WriteProcessMemory failed: $(LastError)"
    }

    $loadLib = [S2Store.Native]::GetProcAddress([S2Store.Native]::GetModuleHandleW('kernel32.dll'), 'LoadLibraryW')
    if ($loadLib -eq [IntPtr]::Zero) { Die 'could not resolve LoadLibraryW' }

    $th = [S2Store.Native]::CreateRemoteThread($h, [IntPtr]::Zero, [IntPtr]::Zero, $loadLib, $mem, 0, [IntPtr]::Zero)
    if ($th -eq [IntPtr]::Zero) { Die "CreateRemoteThread failed: $(LastError)" }

    [void][S2Store.Native]::WaitForSingleObject($th, 15000)
    $code = 0
    [void][S2Store.Native]::GetExitCodeThread($th, [ref]$code)
    # LoadLibraryW returns the HMODULE, truncated to 32 bits by the thread exit
    # code. Zero means the DLL did not load at all -- a missing dependency, or the
    # wrong architecture.
    if ($code -eq 0) { Warn 'LoadLibraryW returned NULL - the mod did NOT load' }
    else { Ok ("mod injected (module low dword 0x{0:X})" -f $code) }

    [void][S2Store.Native]::CloseHandle($th)
    [void][S2Store.Native]::CloseHandle($h)

    # 4. Run.
    if ($NoResume) {
        Warn 'left SUSPENDED (-NoResume). Attach a debugger, then: -Disarm and resume it.'
    } else {
        [S2Store.Pkg]::Go($pfn)
        Ok 'resumed'
    }
}
catch {
    Write-Host "  [FAIL] $($_.Exception.Message)" -ForegroundColor Red
    exit 1
}
finally {
    # ALWAYS disarm. A package left in debugging mode makes every later launch --
    # including from the Xbox app -- hang waiting for a debugger that never comes.
    if ($armed) {
        try { [S2Store.Pkg]::Disarm($pfn); Info 'disarmed' }
        catch { Warn "DisableDebugging failed, run with -Disarm: $($_.Exception.Message)" }
    }
}
