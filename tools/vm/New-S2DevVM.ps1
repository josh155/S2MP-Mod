<#
.SYNOPSIS
    Provision a Hyper-V VM for the S2MP-Mod TOOLING (IDA, MSBuild, the Python tools).

.DESCRIPTION
    ⚠ READ docs/ISOLATION-SETUP.md FIRST. This VM is deliberately for the half of the
    work that needs NO GPU. The GAME cannot usefully run in a VM on this machine:

        Hyper-V GPU-P   does not work on AMD (your RX 9070 XT). NVIDIA/Intel only.
        Hyper-V DDA     Windows Server only, not Windows 11 Pro.
        KVM passthrough needs a Linux host AND a second GPU.

    So this gets IDA and the build environment off your gaming Windows -- which is
    most of the persistent anticheat footprint -- while the game itself stays on a
    normal install (ideally a separate Windows; see Option 1 in the doc).

    ⚠ Enabling the Hyper-V role also puts your HOST under a hypervisor. VBS is already
    doing that here so it changes little, but some anticheats treat a hypervisor as
    suspicious. That is a trade, not a free win.

    The script is IDEMPOTENT and NON-DESTRUCTIVE: it refuses to touch an existing VM
    or overwrite an existing disk. It never enables Windows features for you -- it
    tells you the command to run, because that needs elevation and a reboot.

.PARAMETER Name
    VM name. Default 'S2-Dev'.

.PARAMETER VhdPath
    Where the virtual disk lives. Default puts it on E:, which has the most room.

.PARAMETER IsoPath
    Windows 11 installation ISO. Required unless -SkipIso.

.PARAMETER MemoryGB / CpuCount / DiskGB
    Sizing. Defaults are tuned for IDA on a 1.3 GB database.

.PARAMETER SharePath
    Host folder the VM will save work back into. The script creates it and prints
    the SMB share command; Sync-Workspace.ps1 inside the VM writes here.

.EXAMPLE
    .\New-S2DevVM.ps1 -IsoPath D:\iso\Win11.iso -WhatIf

.EXAMPLE
    .\New-S2DevVM.ps1 -IsoPath D:\iso\Win11.iso
#>
[CmdletBinding(SupportsShouldProcess)]
param(
    [string] $Name       = 'S2-Dev',
    [string] $VhdPath    = 'E:\Hyper-V\S2-Dev\S2-Dev.vhdx',
    [string] $IsoPath,
    [switch] $SkipIso,
    [ValidateRange(4, 64)]  [int] $MemoryGB = 12,
    [ValidateRange(2, 32)]  [int] $CpuCount = 8,
    [ValidateRange(60, 2000)][int] $DiskGB  = 200,
    [string] $SharePath  = 'E:\S2-Workspace-Backup',
    [string] $SwitchName
)

$ErrorActionPreference = 'Stop'
function Say  { param($t) Write-Host "  $t" }
function Ok   { param($t) Write-Host "  [ok]   $t"   -ForegroundColor Green }
function Bad  { param($t) Write-Host "  [stop] $t"   -ForegroundColor Red }
function Note { param($t) Write-Host "  [note] $t"   -ForegroundColor Yellow }

Write-Host "`nS2-Dev VM provisioning" -ForegroundColor White
Write-Host "(tooling only -- see docs/ISOLATION-SETUP.md for why the game stays out)`n"

# ---- preconditions, checked before anything is created ------------------
$fail = $false

if (-not ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()
        ).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Bad 'Not elevated. Hyper-V management needs an Administrator PowerShell.'
    $fail = $true
}

if (-not (Get-Module -ListAvailable Hyper-V)) {
    Bad 'The Hyper-V role is not installed.'
    Say 'Install it (elevated), then REBOOT, then re-run this script:'
    Write-Host '      Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Hyper-V-All -All' -ForegroundColor Cyan
    $fail = $true
}

if (-not $SkipIso) {
    if (-not $IsoPath)                        { Bad 'No -IsoPath given (or pass -SkipIso to attach one later).'; $fail = $true }
    elseif (-not (Test-Path -LiteralPath $IsoPath)) { Bad "ISO not found: $IsoPath"; $fail = $true }
}

$vhdDir = Split-Path -Parent $VhdPath
$drive  = (Split-Path -Qualifier $VhdPath).TrimEnd(':')
$vol    = Get-Volume -DriveLetter $drive -ErrorAction SilentlyContinue
if ($vol) {
    $freeGB = [math]::Round($vol.SizeRemaining / 1GB, 0)
    if ($freeGB -lt ($DiskGB + 20)) {
        Bad "Only $freeGB GB free on ${drive}: but the disk needs up to $DiskGB GB."
        $fail = $true
    } else { Ok "$freeGB GB free on ${drive}: (disk is dynamic, so it grows as used)" }
} else { Note "Could not read free space on ${drive}:" }

if ($fail) { Write-Host "`nNothing was changed.`n" -ForegroundColor Red; exit 1 }

if (Get-VM -Name $Name -ErrorAction SilentlyContinue) {
    Note "A VM called '$Name' already exists. Nothing to do -- delete it first, or pass -Name."
    exit 0
}
if (Test-Path -LiteralPath $VhdPath) {
    Bad "A disk already exists at $VhdPath. Refusing to overwrite it."
    exit 1
}

# ---- network ------------------------------------------------------------
if (-not $SwitchName) {
    $ext = Get-VMSwitch -ErrorAction SilentlyContinue | Where-Object SwitchType -eq 'External' | Select-Object -First 1
    if ($ext) { $SwitchName = $ext.Name; Ok "using external switch '$SwitchName'" }
    else {
        $def = Get-VMSwitch -ErrorAction SilentlyContinue | Where-Object Name -like '*Default*' | Select-Object -First 1
        if ($def) { $SwitchName = $def.Name; Note "using '$SwitchName' (NAT). Fine for IDA/build; no inbound connections." }
        else      { Note 'No virtual switch found -- the VM will have no network. Add one in Hyper-V Manager.' }
    }
}

# ---- create -------------------------------------------------------------
if ($PSCmdlet.ShouldProcess($Name, 'create VM')) {
    New-Item -ItemType Directory -Path $vhdDir -Force | Out-Null

    $p = @{
        Name               = $Name
        MemoryStartupBytes = ($MemoryGB * 1GB)
        Generation         = 2
        NewVHDPath         = $VhdPath
        NewVHDSizeBytes    = ($DiskGB * 1GB)
    }
    if ($SwitchName) { $p.SwitchName = $SwitchName }
    New-VM @p | Out-Null
    Ok "VM '$Name' created ($MemoryGB GB RAM, $CpuCount vCPU, $DiskGB GB dynamic disk)"

    Set-VMProcessor  -VMName $Name -Count $CpuCount
    # Fixed memory: IDA on a 1.3 GB IDB behaves badly when ballooning takes memory
    # back mid-analysis.
    Set-VMMemory     -VMName $Name -DynamicMemoryEnabled $false
    Set-VM           -VMName $Name -AutomaticCheckpointsEnabled $false -CheckpointType Production
    Ok 'fixed memory, automatic checkpoints off (they corrupt a live IDB)'

    # Gen2 needs Secure Boot configured for a Windows guest; a TPM lets Win11 install
    # without a workaround.
    Set-VMFirmware -VMName $Name -EnableSecureBoot On -SecureBootTemplate 'MicrosoftWindows'
    try {
        Set-VMKeyProtector -VMName $Name -NewLocalKeyProtector
        Enable-VMTPM      -VMName $Name
        Ok 'Secure Boot + vTPM enabled (Windows 11 requires both)'
    } catch {
        Note "vTPM could not be enabled: $($_.Exception.Message)"
        Note 'Windows 11 setup may refuse to install without it.'
    }

    if (-not $SkipIso -and $IsoPath) {
        Add-VMDvdDrive -VMName $Name -Path $IsoPath
        $dvd = Get-VMDvdDrive -VMName $Name
        Set-VMFirmware -VMName $Name -FirstBootDevice $dvd
        Ok "boot ISO attached: $IsoPath"
    }

    if (-not (Test-Path -LiteralPath $SharePath)) {
        New-Item -ItemType Directory -Path $SharePath -Force | Out-Null
    }
    Ok "host folder for work products: $SharePath"
}

# ---- what to do next ----------------------------------------------------
Write-Host "`nNext steps" -ForegroundColor White
Say "1. Share the work-product folder so the VM can write to it (elevated, on the HOST):"
Write-Host "      New-SmbShare -Name S2Backup -Path '$SharePath' -FullAccess `$env:USERNAME" -ForegroundColor Cyan
Say "2. Start the VM and install Windows:"
Write-Host "      Start-VM -Name $Name ; vmconnect.exe localhost $Name" -ForegroundColor Cyan
Say '3. Inside the VM install: IDA Pro, Visual Studio 2026 (v145 toolset), Python, git.'
Say '4. Clone/copy the repo into the VM, then after each session run, INSIDE the VM:'
Write-Host "      .\tools\vm\Sync-Workspace.ps1 -Destination \\<HOSTNAME>\S2Backup" -ForegroundColor Cyan
Say '   That copies the repo, the IDB (with its stale-.i64 check), demos and logs back.'
Write-Host ''
Note 'The GAME is not part of this VM. On an AMD GPU there is no working passthrough,'
Note 'so run WWII on a separate Windows install -- Option 1 in docs/ISOLATION-SETUP.md.'
Write-Host ''
