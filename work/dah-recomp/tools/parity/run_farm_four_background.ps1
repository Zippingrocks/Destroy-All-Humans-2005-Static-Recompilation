param(
    [Parameter(Mandatory)][ValidatePattern('^[0-9]{3}$')][string]$Run,
    [ValidateRange(1,3600)][int]$Seconds = 520
)
$ErrorActionPreference = 'Stop'
$project = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $project 'build-internal'
$env:DAH_INPUT_SCRIPT = Join-Path $PSScriptRoot 'farm_entry_four_direction_probe.txt'
$env:DAH_SAVE_DIR = Join-Path $build "parity-farm-four-saves-20260927-$Run"
$env:DAH_LOG_PATH = Join-Path $build "parity-farm-four-20260927-$Run.log"
$env:DAH_PARITY_STATE_TRACE = Join-Path $build "parity-farm-four-20260927-$Run.jsonl"
$env:DAH_PARITY_STATE_INTERVAL = '1'
$env:DAH_FRAME_CAPTURE_TRIGGER = Join-Path $build "parity-farm-four-20260927-$Run.trigger"
$env:DAH_MOVEMENT_PRECOMPAT_TRACE = '1'
foreach ($setting in @(
    'DAH_PLAYER_MOVEMENT_COMPAT', 'DAH_FARM_PRESENTATION_HOLD',
    'DAH_RENDERDOC_FRAME', 'DAH_RENDERDOC_PATH', 'DAH_HUD_DRAW_TRACE_START'
)) {
    Remove-Item "Env:$setting" -ErrorAction SilentlyContinue
}
& (Join-Path $project 'tools\run_internal.ps1') -Seconds $Seconds `
    -UseRetailFps -UseMovieDefault -CaptureCount 80 -CaptureStart 2800 `
    -CaptureInterval 100 -PushbufferCaptures 0
