# Cheat Engine MCP bridge setup for S2MP-Mod
# Run once: powershell -ExecutionPolicy Bypass -File tools/cheatengine-mcp/setup.ps1

$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent $MyInvocation.MyCommand.Path
$Base = "https://raw.githubusercontent.com/sudohakan/cheatengine-mcp-bridge/main/MCP_Server"

New-Item -ItemType Directory -Force -Path $Root | Out-Null

foreach ($file in @("mcp_cheatengine.py", "ce_mcp_bridge.lua", "requirements.txt")) {
    $dest = Join-Path $Root $file
    Write-Host "Downloading $file ..."
    Invoke-WebRequest -Uri "$Base/$file" -OutFile $dest -UseBasicParsing
}

Write-Host "Installing Python dependencies ..."
python -m pip install -r (Join-Path $Root "requirements.txt")

Write-Host ""
Write-Host "Done. Next steps:"
Write-Host "  1. CE -> Settings -> Extra -> disable 'Query memory region routines'"
Write-Host "  2. Attach CE to s2_mp64_ship.exe"
Write-Host "  3. Memory View -> Tools -> Lua Script -> open:"
Write-Host "     $Root\ce_mcp_bridge.lua"
Write-Host "  4. Execute script (expect: Bridge started)"
Write-Host "  5. Restart Cursor to load .cursor/mcp.json"
