<#
.SYNOPSIS
    Versioned, verified snapshot of the S2 reverse-engineering project onto an
    archival drive.

.DESCRIPTION
    The archival drive is a PRESERVATION TARGET, not a working drive. This script
    is built around that:

      * DATED snapshots -- <root>\S2-RE-Snapshot\YYYY-MM-DD_HHmmss\ -- so nothing
        ever replaces an earlier one. Successive snapshots ARE the version history.
      * It NEVER deletes and NEVER overwrites. If the destination already exists it
        refuses and tells you, rather than merging into it.
      * Every file is hash-verified (SHA256) after copying and discrepancies are
        reported. A snapshot that does not verify is reported as FAILED, not as
        "done with warnings".
      * -WhatIf shows the full plan and payload size without writing anything.

    CLAUDE.md is untracked by git and has no version history, so it is ALSO copied
    into <root>\S2-RE-Snapshot\claude-md-history\CLAUDE.<timestamp>.md. That folder
    accumulates cheaply (~1 MB each) and survives even if whole snapshots are later
    pruned.

.PARAMETER Root
    Destination drive/folder, e.g. G:\ . If omitted, the script looks for exactly
    one REMOVABLE drive and refuses if there is not exactly one -- it will not
    guess, and it will not fall back to a fixed disk just because the label sounds
    like a backup.

.PARAMETER IncludeHistoricalIdbs
    Also copy the superseded IDBs under D:\WWII IDB (~4 GB). Off by default: they
    are superseded by the authoritative database, but they are genuine history.

.EXAMPLE
    powershell -ExecutionPolicy Bypass -File tools\Archive-S2.ps1 -WhatIf
    powershell -ExecutionPolicy Bypass -File tools\Archive-S2.ps1 -Root G:\

.NOTES
    SAVE EVERY OPEN IDB FIRST. IDA only repacks the .i64 on save, so an unsaved
    database archives stale. The script warns if an .i64 is older than its own
    loose .id0 working file, which is exactly that situation.
#>
[CmdletBinding(SupportsShouldProcess = $true)]
param(
    [string] $Root,
    [switch] $IncludeHistoricalIdbs
)

$ErrorActionPreference = 'Stop'
$repo = Split-Path -Parent $PSScriptRoot

# ---------------------------------------------------------------- destination --
# [System.IO.DriveInfo] rather than Get-CimInstance: CIM cmdlets do not accept
# -WhatIf, and merely importing CimCmdlets while $WhatIfPreference is set floods
# the output with "What if: Set Alias" lines that bury the actual plan.
if (-not $Root) {
    $removable = [System.IO.DriveInfo]::GetDrives() |
        Where-Object { $_.DriveType -eq 'Removable' -and $_.IsReady }
    if (-not $removable) {
        Write-Host "No removable drive is connected." -ForegroundColor Yellow
        Write-Host "Connect the archival USB, or pass -Root explicitly."
        Write-Host "Refusing to fall back to a fixed disk: E: is labelled 'Backup Hard"
        Write-Host "Drive' but hosts the live game install and the live IDB, which is"
        Write-Host "exactly the working-drive/preservation-target conflation to avoid."
        exit 1
    }
    if ($removable.Count -gt 1) {
        Write-Host "More than one removable drive is connected - pass -Root to choose:" -ForegroundColor Yellow
        $removable | ForEach-Object { "   {0}  {1}" -f $_.Name, $_.VolumeLabel }
        exit 1
    }
    $Root = $removable.Name          # DriveInfo.Name is already "G:\"
}
if (-not (Test-Path $Root)) { throw "Destination '$Root' is not reachable." }

$stamp    = Get-Date -Format 'yyyy-MM-dd_HHmmss'
$archive  = Join-Path $Root 'S2-RE-Snapshot'
$dest     = Join-Path $archive $stamp
$mdHistory = Join-Path $archive 'claude-md-history'

if (Test-Path $dest) { throw "Snapshot '$dest' already exists. Refusing to overwrite." }

# ------------------------------------------------------------------- payload --
# name, source, whether missing is acceptable
$items = @(
    @{ N='repo';            S=$repo;                                                                  Opt=$false }
    @{ N='idb-s2';          S='E:\SteamLibrary\steamapps\common\Call of Duty WWII';                   Opt=$false; Filter='s2x_dump.exe*' }
    @{ N='idb-s2-xbox';     S='F:\WWII XBOX Dump';                                                    Opt=$true }
    @{ N='ida-plugins';     S="$env:APPDATA\Hex-Rays\IDA Pro\plugins";                                Opt=$true }
    @{ N='ida-launchers';   S='F:\Coding\ida-launchers';                                              Opt=$true }
    @{ N='ce-mcp-bridge';   S='F:\Coding\cheatengine-mcp-bridge';                                     Opt=$true }
    @{ N='claude-global';   S="$env:USERPROFILE\.claude";                                             Opt=$true }
)
if ($IncludeHistoricalIdbs) { $items += @{ N='idb-historical'; S='D:\WWII IDB'; Opt=$true } }

# ---------------------------------------------------- pre-flight: stale IDBs --
Write-Host "`n=== pre-flight ===" -ForegroundColor Cyan
foreach ($i64 in @(
    'E:\SteamLibrary\steamapps\common\Call of Duty WWII\s2x_dump.exe.i64',
    'F:\WWII XBOX Dump\s2_mp64_ship_dump.exe.i64')) {
    $id0 = [IO.Path]::ChangeExtension($i64, '.id0')
    if ((Test-Path $i64) -and (Test-Path $id0)) {
        if ((Get-Item $id0).LastWriteTime -gt (Get-Item $i64).LastWriteTime.AddSeconds(2)) {
            Write-Host ("  STALE: {0}" -f (Split-Path $i64 -Leaf)) -ForegroundColor Yellow
            Write-Host "         its .id0 is newer - the database has unsaved work."
            Write-Host "         Save it in IDA (Ctrl+W) or via idb_save, then re-run."
        } else {
            Write-Host ("  ok: {0}" -f (Split-Path $i64 -Leaf)) -ForegroundColor Green
        }
    }
}

# ------------------------------------------------------------------ planning --
$plan = @()
foreach ($it in $items) {
    if (-not (Test-Path $it.S)) {
        if (-not $it.Opt) { throw "Required source missing: $($it.S)" }
        Write-Host ("  skip (absent): {0}" -f $it.S) -ForegroundColor DarkGray
        continue
    }
    $files = if ($it.Filter) {
        Get-ChildItem -Path $it.S -Filter $it.Filter -File -ErrorAction SilentlyContinue
    } else {
        Get-ChildItem -Path $it.S -Recurse -File -ErrorAction SilentlyContinue
    }
    $bytes = ($files | Measure-Object Length -Sum).Sum
    $plan += [pscustomobject]@{ Name=$it.N; Source=$it.S; Files=$files; Count=$files.Count; Bytes=[int64]$bytes }
}

Write-Host "`n=== plan ===" -ForegroundColor Cyan
$plan | ForEach-Object { "  {0,-16} {1,7:N0} files  {2,9:N2} GB   {3}" -f $_.Name, $_.Count, ($_.Bytes/1GB), $_.Source }
$total = ($plan | Measure-Object Bytes -Sum).Sum
$free  = ([System.IO.DriveInfo]::new((Split-Path $Root -Qualifier) + '\')).AvailableFreeSpace
"`n  TOTAL {0:N2} GB   destination free {1:N2} GB" -f ($total/1GB), ($free/1GB) | Write-Host
if ($free -and $total -gt ($free * 0.95)) { throw "Not enough free space on $Root." }
Write-Host "  -> $dest"

if ($WhatIfPreference) { Write-Host "`n-WhatIf: nothing written." -ForegroundColor Yellow; exit 0 }

# --------------------------------------------------------- copy then verify --
New-Item -ItemType Directory -Path $dest -Force | Out-Null
New-Item -ItemType Directory -Path $mdHistory -Force | Out-Null

$copied = 0; $bad = @()
foreach ($p in $plan) {
    Write-Host ("`ncopying {0} ({1:N0} files)..." -f $p.Name, $p.Count) -ForegroundColor Cyan
    $base = (Resolve-Path $p.Source).Path.TrimEnd('\')
    foreach ($f in $p.Files) {
        $rel = $f.FullName.Substring($base.Length).TrimStart('\')
        $out = Join-Path (Join-Path $dest $p.Name) $rel
        New-Item -ItemType Directory -Path (Split-Path $out -Parent) -Force | Out-Null
        Copy-Item $f.FullName $out -Force
        $copied++
        # Verify EVERY file. Hashing multi-GB IDBs is slow but this is a
        # preservation copy: an unverified archive is worth very little.
        $hs = (Get-FileHash $f.FullName -Algorithm SHA256).Hash
        $hd = (Get-FileHash $out       -Algorithm SHA256).Hash
        if ($hs -ne $hd) { $bad += [pscustomobject]@{ File=$rel; Src=$hs; Dst=$hd } }
        if (($copied % 200) -eq 0) { Write-Host ("    {0:N0} files..." -f $copied) }
    }
}

# CLAUDE.md also lands in the accumulating history folder (it is untracked by git,
# so these dated copies are the only version history that exists).
$md = Join-Path $repo 'CLAUDE.md'
if (Test-Path $md) {
    $mdOut = Join-Path $mdHistory ("CLAUDE.{0}.md" -f $stamp)
    Copy-Item $md $mdOut -Force
    if ((Get-FileHash $md -Algorithm SHA256).Hash -ne (Get-FileHash $mdOut -Algorithm SHA256).Hash) {
        $bad += [pscustomobject]@{ File='CLAUDE.md (history)'; Src='-'; Dst='MISMATCH' }
    }
}

# ------------------------------------------------------------------- report --
$manifest = Join-Path $dest 'MANIFEST.txt'
@(
    "S2 reverse-engineering snapshot"
    "created : $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')"
    "host    : $env:COMPUTERNAME"
    "source  : $repo"
    ""
    "files   : $copied"
    "bytes   : $total"
    "verified: SHA256, every file"
    "mismatch: $($bad.Count)"
    ""
    "contents:"
) + ($plan | ForEach-Object { "  {0,-16} {1,7:N0} files  {2,9:N2} GB  <- {3}" -f $_.Name, $_.Count, ($_.Bytes/1GB), $_.Source }) |
    Set-Content $manifest -Encoding utf8

Write-Host "`n=== result ===" -ForegroundColor Cyan
Write-Host ("  {0:N0} files copied, {1:N2} GB" -f $copied, ($total/1GB))
if ($bad.Count) {
    Write-Host ("  {0} FILE(S) FAILED VERIFICATION:" -f $bad.Count) -ForegroundColor Red
    $bad | ForEach-Object { "     $($_.File)" } | Write-Host
    Write-Host "  SNAPSHOT IS NOT TRUSTWORTHY - investigate before relying on it." -ForegroundColor Red
    exit 2
}
Write-Host "  all files verified (SHA256 source == destination)" -ForegroundColor Green
Write-Host "  manifest: $manifest"
Write-Host "  nothing existing was modified or deleted."
