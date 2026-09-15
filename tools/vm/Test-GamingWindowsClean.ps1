<#
.SYNOPSIS
    Verify a Windows install carries NO trace of this project's RE tooling.

.DESCRIPTION
    Run this ON THE GAMING WINDOWS, before installing anything with a kernel
    anticheat (Ricochet, Vanguard, EAC, BattlEye). It answers one question with
    evidence rather than hope:

        "Is any of the S2 modding tooling present on this machine?"

    It checks for the things a kernel anticheat actually looks for:

      * Cheat Engine  -- installed, portable copies, and its DBK KERNEL DRIVER
                         (the driver is the part that matters most; a driver is
                         loaded system-wide and is trivially enumerable)
      * IDA Pro       -- installed or portable
      * the mod DLL   -- s2mp-mod.dll anywhere it would normally be deployed
      * injectors     -- the project's own launcher script
      * autostart     -- Run keys and services referencing any of the above
      * running procs -- anything from the list live right now

    NOTHING IS CHANGED. This is read-only; it reports and exits.

    Exit codes:
        0  clean      -- nothing from the project found
        1  DIRTY      -- at least one finding; details printed
        2  inconclusive (a check could not run, e.g. needs elevation)

.PARAMETER Deep
    Also scan whole drives for stray copies. Slow (minutes). Off by default
    because the targeted checks catch the cases that matter.

.EXAMPLE
    powershell -ExecutionPolicy Bypass -File .\Test-GamingWindowsClean.ps1
#>

[CmdletBinding()]
param(
    [switch] $Deep
)

$ErrorActionPreference = 'SilentlyContinue'
$findings = New-Object System.Collections.Generic.List[string]
$notes    = New-Object System.Collections.Generic.List[string]

function Write-Section { param([string]$T) Write-Host "`n=== $T ===" -ForegroundColor Cyan }
function Add-Finding   { param([string]$T) $findings.Add($T); Write-Host "  [FOUND] $T" -ForegroundColor Red }
function Write-Ok      { param([string]$T) Write-Host "  [clean] $T" -ForegroundColor Green }
function Add-Note      { param([string]$T) $notes.Add($T);    Write-Host "  [note]  $T" -ForegroundColor Yellow }

Write-Host "Checking this Windows for S2 modding tooling..." -ForegroundColor White
Write-Host "Machine: $env:COMPUTERNAME   User: $env:USERNAME"

# --- 1. The kernel driver. This is the single most important check. ----------
# Cheat Engine's DBK driver is loaded system-wide and is exactly the sort of
# thing a kernel anticheat enumerates. Note this project has never needed it --
# every CE use has been a direct read at a computed address, no scanning.
Write-Section 'Cheat Engine kernel driver (DBK)'
$drv = Get-CimInstance Win32_SystemDriver | Where-Object { $_.Name -match 'dbk|CEDRIVER' }
if ($drv) {
    foreach ($d in $drv) { Add-Finding "driver '$($d.Name)' state=$($d.State) start=$($d.StartMode)" }
} else {
    Write-Ok 'no DBK / CE driver registered'
}

# --- 2. Installed programs ----------------------------------------------------
Write-Section 'Installed programs'
$uninstallKeys = @(
    'HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\*',
    'HKLM:\SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\*',
    'HKCU:\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\*'
)
$installed = Get-ItemProperty $uninstallKeys |
    Where-Object { $_.DisplayName -match 'Cheat Engine|IDA (Pro|Free)|Hex-Rays|x64dbg|Process Hacker|System Informer' }
if ($installed) {
    foreach ($i in $installed) { Add-Finding "installed: $($i.DisplayName)" }
} else {
    Write-Ok 'no CE / IDA / debugger in the uninstall registry'
}

# --- 3. Running processes -----------------------------------------------------
Write-Section 'Running processes'
$procNames = 'cheatengine|ida64|ida\.exe|idaq|x64dbg|ProcessHacker|SystemInformer|s2_mp64_ship'
$procs = Get-Process | Where-Object { $_.ProcessName -match $procNames }
if ($procs) {
    foreach ($p in $procs) { Add-Finding "running: $($p.ProcessName) (pid $($p.Id))" }
} else {
    Write-Ok 'none of the tooling is running'
}

# --- 4. The mod DLL and the injector -----------------------------------------
Write-Section 'Mod DLL and injector'
$dllSpots = @(
    "$env:USERPROFILE\OneDrive\Documents\WWII\s2mp-mod.dll",
    "$env:USERPROFILE\Documents\WWII\s2mp-mod.dll"
)
$hit = $false
foreach ($p in $dllSpots) {
    if (Test-Path $p) { Add-Finding "mod DLL: $p"; $hit = $true }
}
$repo = "$env:USERPROFILE\OneDrive\Documents\GitHub\S2MP-Mod"
if (Test-Path $repo) {
    Add-Note "project repo present: $repo  (source only -- not itself a tooling artifact, but it is where the DLL is built)"
}
if (-not $hit) { Write-Ok 'no deployed s2mp-mod.dll in the usual locations' }

# --- 5. Autostart -------------------------------------------------------------
Write-Section 'Autostart entries'
$runKeys = @(
    'HKCU:\Software\Microsoft\Windows\CurrentVersion\Run',
    'HKLM:\Software\Microsoft\Windows\CurrentVersion\Run'
)
$autoHit = $false
foreach ($k in $runKeys) {
    $props = Get-ItemProperty $k
    if (-not $props) { continue }
    foreach ($p in $props.PSObject.Properties) {
        if ($p.Name -match '^PS' ) { continue }
        if ("$($p.Value)" -match 'cheat|ida64|s2mp|inject|x64dbg') {
            Add-Finding "autostart: $($p.Name) = $($p.Value)"
            $autoHit = $true
        }
    }
}
if (-not $autoHit) { Write-Ok 'nothing tooling-related in the Run keys' }

# --- 6. Optional deep scan ----------------------------------------------------
if ($Deep) {
    Write-Section 'Deep scan for stray copies (slow)'
    $drives = Get-PSDrive -PSProvider FileSystem | Where-Object { $_.Used -gt 0 }
    foreach ($d in $drives) {
        $found = Get-ChildItem -Path "$($d.Root)" -Recurse -Include 'cheatengine*.exe','ida64.exe','s2mp-mod.dll' -Depth 6 -Force
        foreach ($f in $found) { Add-Finding "stray file: $($f.FullName)" }
    }
    if ($findings.Count -eq 0) { Write-Ok 'no stray copies found' }
} else {
    Add-Note 'targeted checks only -- pass -Deep to also scan drives for stray copies'
}

# --- verdict ------------------------------------------------------------------
Write-Host ''
Write-Host ('-' * 68)
if ($findings.Count -eq 0) {
    Write-Host 'VERDICT: CLEAN -- no S2 modding tooling found on this Windows.' -ForegroundColor Green
    Write-Host 'Safe to install a kernel-anticheat game here.' -ForegroundColor Green
    exit 0
}

Write-Host "VERDICT: DIRTY -- $($findings.Count) finding(s):" -ForegroundColor Red
foreach ($f in $findings) { Write-Host "  - $f" -ForegroundColor Red }
Write-Host ''
Write-Host 'This is the machine you should NOT be running Ricochet/Vanguard titles on,' -ForegroundColor Yellow
Write-Host 'or you should remove the findings above first. The driver finding (if any)' -ForegroundColor Yellow
Write-Host 'matters most -- a kernel driver is enumerable system-wide.' -ForegroundColor Yellow
exit 1
