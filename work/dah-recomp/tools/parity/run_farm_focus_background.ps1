param(
    [Parameter(Mandatory)][ValidatePattern('^[0-9]{3}$')][string]$Run,
    [ValidateRange(1,3600)][int]$Seconds = 240,
    [ValidateRange(0,10000000)][uint32]$Start = 0,
    [ValidateRange(0,10000000)][uint32]$End = 0
)

$ErrorActionPreference = 'Stop'
$project = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $project 'build-internal'
$prefix = Join-Path $build "parity-farm-four-20260927-$Run"

$env:DAH_INPUT_SCRIPT = Join-Path $PSScriptRoot 'farm_entry_four_direction_probe.txt'
$env:DAH_SAVE_DIR = "$prefix-saves"
$env:DAH_LOG_PATH = "$prefix.log"
$env:DAH_PARITY_STATE_TRACE = "$prefix.jsonl"
$env:DAH_PARITY_STATE_INTERVAL = '1'
$env:DAH_PHYSICS_QUAT_TRACE = "$prefix-physics-quat.jsonl"
$env:DAH_QUAT_CONSTRUCTOR_TRACE = "$prefix-constructor.jsonl"
$env:DAH_VELOCITY_TRACE = "$prefix-velocity.jsonl"
$env:DAH_VELOCITY_SOURCE_TRACE = "$prefix-velocity-source.jsonl"
$env:DAH_VELOCITY_STAGE_TRACE = "$prefix-velocity-stage.jsonl"
$env:DAH_PARITY_STATE_START = [string]$Start
$env:DAH_PARITY_STATE_END = [string]$End

foreach ($setting in @(
    'DAH_PLAYER_MOVEMENT_COMPAT', 'DAH_FARM_PRESENTATION_HOLD',
    'DAH_RENDERDOC_FRAME', 'DAH_RENDERDOC_PATH', 'DAH_HUD_DRAW_TRACE_START',
    'DAH_FRAME_CAPTURE_TRIGGER', 'DAH_MOVEMENT_PRECOMPAT_TRACE'
)) {
    Remove-Item "Env:$setting" -ErrorAction SilentlyContinue
}

& (Join-Path $project 'tools\run_internal.ps1') -Seconds $Seconds `
    -UseRetailFps -UseMovieDefault -CaptureCount 0 -PushbufferCaptures 0
