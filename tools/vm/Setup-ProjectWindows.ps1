<#
.SYNOPSIS
    Provision a fresh "project Windows" for S2 work, so the gaming Windows never
    sees IDA, Cheat Engine, or an injector.

.DESCRIPTION
    Run this ON THE NEW (project) Windows install, once.

    THE POINT: your RX 9070 XT cannot pass through to a VM (Hyper-V GPU-P is
    NVIDIA/Intel only, DDA is Server only), so the game must run natively. A
    second Windows install is therefore the only arrangement that gives BOTH
    full isolation and a working game. See docs/ISOLATION-SETUP.md.

    THE BIG TIME-SAVER: the game does NOT need re-downloading. Steam can adopt
    an existing library folder, and E:\SteamLibrary already holds WWII plus --
    because they live inside the game directory -- your demos, botnames.txt,
    botkits.txt and the whole S2MP-Mod data folder. Point Steam at it and
    everything is there.

    WHAT THIS SCRIPT DOES
        * checks it is NOT being run on the machine that has the game+tooling
          already (so you cannot fire it at the wrong Windows by accident)
        * verifies the shared library and repo paths exist
        * installs the automatable toolchain via winget (git, python, VS build
          tools)
        * prints the short list of things that genuinely cannot be scripted

    WHAT IT DELIBERATELY DOES NOT DO
        * install Windows (obviously)
        * install IDA -- licensed, needs your own installer and key
        * install Cheat Engine -- deliberate: install it here, never on gaming
          Windows, and do NOT install its DBK kernel driver. This project has
          never needed it; every CE use has been a direct read at a computed
          address.

.PARAMETER SteamLibrary
    The EXISTING shared Steam library holding WWII. Not re-downloaded.

.PARAMETER RepoPath
    Where the repo should live on this install.

.PARAMETER SkipInstalls
    Verify and report only; install nothing.

.EXAMPLE
    powershell -ExecutionPolicy Bypass -File .\Setup-ProjectWindows.ps1
#>

[CmdletBinding()]
param(
    [string] $SteamLibrary = 'E:\SteamLibrary',
    [string] $RepoPath     = "$env:USERPROFILE\Documents\GitHub\S2MP-Mod",
    [switch] $SkipInstalls
)

$ErrorActionPreference = 'Stop'
$problems = New-Object System.Collections.Generic.List[string]

function Write-Section { param([string]$T) Write-Host "`n=== $T ===" -ForegroundColor Cyan }
function Write-Ok      { param([string]$T) Write-Host "  [ok]   $T" -ForegroundColor Green }
function Write-Warn    { param([string]$T) Write-Host "  [warn] $T" -ForegroundColor Yellow; $problems.Add($T) }
function Write-Info    { param([string]$T) Write-Host "  [info] $T" -ForegroundColor Gray }

Write-Host 'S2MP-Mod -- project Windows setup' -ForegroundColor White
Write-Host "Machine: $env:COMPUTERNAME   Windows: $((Get-CimInstance Win32_OperatingSystem).Caption)"

# --- 0. Refuse to run on the wrong machine ------------------------------------
# If IDA/CE are already installed here, this is very likely the machine you were
# trying to keep clean. Stop rather than make it worse.
Write-Section 'Sanity: is this the right Windows?'
$already = Get-ItemProperty 'HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\*',
                            'HKLM:\SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\*' `
           -ErrorAction SilentlyContinue |
           Where-Object { $_.DisplayName -match 'Cheat Engine|IDA (Pro|Free)|Hex-Rays' }
if ($already) {
    Write-Host ''
    Write-Host 'REFUSING: this Windows already has the RE tooling installed:' -ForegroundColor Red
    foreach ($a in $already) { Write-Host "    $($a.DisplayName)" -ForegroundColor Red }
    Write-Host 'That means it is your EXISTING install, not a fresh project one.' -ForegroundColor Red
    Write-Host 'Run this on the new Windows instead.' -ForegroundColor Red
    exit 2
}
Write-Ok 'no existing IDA/CE here -- looks like a fresh install'

# --- 1. The shared library ----------------------------------------------------
Write-Section 'Shared Steam library (no re-download)'
$game = Join-Path $SteamLibrary 'steamapps\common\Call of Duty WWII'
if (Test-Path $game) {
    Write-Ok "WWII found: $game"
    $modData = Join-Path $game 'S2MP-Mod'
    $demos   = Join-Path $game 'main\demo'
    if (Test-Path $modData) {
        $n = (Get-ChildItem $modData -File -ErrorAction SilentlyContinue).Count
        Write-Ok "mod data folder carries over ($n file(s)): $modData"
    } else {
        Write-Info 'S2MP-Mod data folder not present yet -- it is created on first run'
    }
    if (Test-Path $demos) {
        $n = (Get-ChildItem $demos -Filter *.demo -ErrorAction SilentlyContinue).Count
        Write-Ok "$n recorded demo(s) carry over: $demos"
    }
    Write-Host ''
    Write-Info 'In Steam: Settings > Storage > Add Drive > pick the folder above.'
    Write-Info 'Steam adopts the existing install; it will verify, not re-download.'
} else {
    Write-Warn "no WWII at $game -- check the drive letter on this install (-SteamLibrary)"
}

# --- 2. Toolchain -------------------------------------------------------------
Write-Section 'Toolchain'
$winget = Get-Command winget -ErrorAction SilentlyContinue
if (-not $winget) {
    Write-Warn 'winget not available -- install the toolchain manually'
} else {
    $pkgs = @(
        @{ Id = 'Git.Git';                                  Name = 'Git' },
        @{ Id = 'Python.Python.3.12';                       Name = 'Python 3.12' },
        @{ Id = 'Microsoft.VisualStudio.2022.BuildTools';   Name = 'VS Build Tools' }
    )
    foreach ($p in $pkgs) {
        if ($SkipInstalls) { Write-Info "would install $($p.Name) ($($p.Id))"; continue }
        Write-Info "installing $($p.Name) ..."
        & winget install --id $p.Id --silent --accept-source-agreements --accept-package-agreements | Out-Null
        if ($LASTEXITCODE -eq 0) { Write-Ok "$($p.Name) installed" }
        else { Write-Warn "$($p.Name) install returned $LASTEXITCODE -- may already be present" }
    }
    Write-Info 'NOTE: this project builds with Visual Studio 2026 (toolset v145).'
    Write-Info 'If the build complains about the toolset, install VS 2026 rather than 2022 Build Tools.'
}

# --- 3. The repo --------------------------------------------------------------
Write-Section 'Repository'
if (Test-Path $RepoPath) {
    Write-Ok "repo present: $RepoPath"
} else {
    Write-Info "not present at $RepoPath"
    Write-Info 'Either sign into OneDrive (the repo lives there and syncs for free),'
    Write-Info 'or copy it across with tools/vm/Sync-Workspace.ps1 from the old install.'
}

# --- 4. What cannot be scripted ----------------------------------------------
Write-Section 'Manual steps (deliberately not automated)'
Write-Host '  1. IDA Pro     -- licensed; run your own installer + key here.' -ForegroundColor White
Write-Host '  2. Cheat Engine-- install HERE only, never on gaming Windows.' -ForegroundColor White
Write-Host '                    Do NOT install the DBK kernel driver: this project' -ForegroundColor White
Write-Host '                    has never needed it (all reads are direct, at' -ForegroundColor White
Write-Host '                    computed addresses), and a driver is the single' -ForegroundColor White
Write-Host '                    most enumerable artifact a kernel anticheat sees.' -ForegroundColor White
Write-Host '  3. Steam       -- sign in, then add the existing library folder above.' -ForegroundColor White

# --- verdict ------------------------------------------------------------------
Write-Host ''
Write-Host ('-' * 68)
if ($problems.Count -eq 0) {
    Write-Host 'Setup checks passed. Finish the three manual steps and you are done.' -ForegroundColor Green
    Write-Host 'Afterwards, run Test-GamingWindowsClean.ps1 on your GAMING Windows' -ForegroundColor Green
    Write-Host 'to confirm it is clean before installing a kernel-anticheat game.' -ForegroundColor Green
    exit 0
}
Write-Host "$($problems.Count) thing(s) need attention:" -ForegroundColor Yellow
foreach ($p in $problems) { Write-Host "  - $p" -ForegroundColor Yellow }
exit 1
