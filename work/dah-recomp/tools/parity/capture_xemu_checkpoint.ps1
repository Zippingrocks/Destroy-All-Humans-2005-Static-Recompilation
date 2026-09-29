param(
    [Parameter(Mandatory)][int]$XemuPid,
    [Parameter(Mandatory)][string]$Stem,
    [Parameter(Mandatory)][string]$Python,
    [UInt64]$RamBase = 0,
    [int]$Port = 4445
)
$ErrorActionPreference = 'Stop'
$dahReference = Get-Process -Id $XemuPid -ErrorAction Stop
$dahExpected = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..\build-parity-xemu\xemu.exe'))
if ($dahReference.Path -ne $dahExpected) { throw 'PID is not the private DAH1 reference executable.' }
$dahListener = Get-NetTCPConnection -LocalPort $Port -State Listen -ErrorAction Stop
if (!($dahListener | Where-Object { $_.OwningProcess -eq $XemuPid })) {
    throw 'QMP listener does not belong to the requested reference process.'
}
$dahStem = [IO.Path]::GetFullPath($Stem)
foreach ($dahSuffix in @('.checkpoint.json', '.ram.bin', '.ram.bin.json', '.state.json', '.png')) {
    if (Test-Path -LiteralPath ($dahStem + $dahSuffix)) { throw "Capture already exists: $dahStem$dahSuffix" }
}
if (!(Test-Path -LiteralPath $Python)) { throw 'Python runtime not found.' }
$dahPaused = $false
try {
    & node (Join-Path $PSScriptRoot 'xemu_capture_checkpoint.mjs') --port $Port --out ($dahStem + '.checkpoint.json')
    if ($LASTEXITCODE -ne 0) { throw 'Reference checkpoint failed.' }
    $dahPaused = $true
    $dahMeta = Get-Content -LiteralPath ($dahStem + '.checkpoint.json') -Raw | ConvertFrom-Json
    & (Join-Path $PSScriptRoot 'read_xemu_ram.ps1') -XemuPid $XemuPid -Out ($dahStem + '.ram.bin') -RamBase $RamBase -Cr3 $dahMeta.cr3
} finally {
    if ($dahPaused) {
        & node (Join-Path $PSScriptRoot 'xemu_qmp_control.mjs') --port $Port --execute cont
        if ($LASTEXITCODE -ne 0) { Write-Warning 'Reference resume failed; inspect its QMP state.' }
    }
}
& $Python (Join-Path $PSScriptRoot 'decode_xemu_ram.py') ($dahStem + '.ram.bin') --metadata ($dahStem + '.checkpoint.json') --out ($dahStem + '.state.json') --image ($dahStem + '.png')
if ($LASTEXITCODE -ne 0) { throw 'Reference capture decode failed.' }
