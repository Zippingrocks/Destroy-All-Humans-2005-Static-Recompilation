param(
    [Parameter(Mandatory)][ValidatePattern('^[0-9]{3}$')][string]$Run,
    [ValidateRange(1,3600)][int]$Seconds = 245,
    [ValidateRange(0,10000000)][uint32]$StateStart = 3750,
    [ValidateRange(0,10000000)][uint32]$StateEnd = 4200,
    [ValidateRange(0,10000000)][uint32]$CaptureStart = 3800,
    [ValidateRange(1,1000000)][uint32]$CaptureInterval = 5,
    [ValidateRange(0,128)][uint32]$CaptureCount = 80,
    [ValidateNotNullOrEmpty()][string]$InputScript = 'rockwell_holobob_close_probe.txt',
    [switch]$MaterialTrace,
    [ValidateRange(0,10000000)][uint32]$MaterialTraceStart = 8950
)

$ErrorActionPreference = 'Stop'
$project = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $project 'build-internal'
$prefix = Join-Path $build "rockwell-holobob-focus-$Run"

# This is an internal, hidden diagnostic path.  It keeps the desktop and the
# user's controller untouched while replaying the same logical Xbox input on
# every build.
$inputPath = Join-Path $PSScriptRoot $InputScript
if (!(Test-Path -LiteralPath $inputPath -PathType Leaf)) {
    throw "Rockwell input script not found: $inputPath"
}
$env:DAH_INPUT_SCRIPT = $inputPath
$env:DAH_SAVE_DIR = "$prefix-saves"
$env:DAH_LOG_PATH = "$prefix.log"
$env:DAH_PARITY_STATE_TRACE = "$prefix-state.jsonl"
$env:DAH_PARITY_STATE_INTERVAL = '1'
$env:DAH_PARITY_STATE_START = [string]$StateStart
$env:DAH_PARITY_STATE_END = [string]$StateEnd
$env:DAH_PARITY_WEAPON_DETAIL = '1'
$env:DAH_HOLOBOB_TRACE = '1'
$env:DAH_CONSOLE_AUTOLOAD_LEVEL = 'rockwell'
$env:DAH_CONSOLE_AUTO_EQUIP_WEAPON = 'holobob'
$env:DAH_CONSOLE_AUTO_EQUIP_DELAY = '40'

foreach ($setting in @(
    'DAH_PLAYER_MOVEMENT_COMPAT', 'DAH_FARM_PRESENTATION_HOLD',
    'DAH_RENDERDOC_FRAME', 'DAH_RENDERDOC_PATH', 'DAH_HUD_DRAW_TRACE_START',
    'DAH_FARM_MATERIAL_TRACE', 'DAH_FARM_MATERIAL_TRACE_START'
)) {
    Remove-Item "Env:$setting" -ErrorAction SilentlyContinue
}
if ($MaterialTrace) {
    $env:DAH_FARM_MATERIAL_TRACE = '1'
    $env:DAH_FARM_MATERIAL_TRACE_START = [string]$MaterialTraceStart
}

& (Join-Path $project 'tools\run_internal.ps1') -Seconds $Seconds `
    -UseRetailFps -UseMovieDefault -CaptureCount $CaptureCount `
    -CaptureInterval $CaptureInterval -CaptureStart $CaptureStart `
    -PushbufferCaptures 0
