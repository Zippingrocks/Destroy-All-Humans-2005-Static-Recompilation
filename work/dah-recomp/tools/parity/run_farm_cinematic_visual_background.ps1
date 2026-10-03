param(
    [Parameter(Mandatory)][ValidatePattern('^[A-Za-z0-9-]+$')][string]$Run,
    [ValidateRange(30, 300)][int]$Seconds = 105,
    [ValidateRange(0, 1000000)][uint32]$CaptureStart = 3400,
    [ValidateRange(1, 1000000)][uint32]$CaptureInterval = 25,
    [ValidateRange(1, 256)][uint32]$CaptureCount = 128,
    [ValidateRange(0, 1000000)][uint32]$RenderDocFrame = 0,
    [ValidateRange(0, 120)][double]$RenderDocCinematicSeconds = 0,
    [ValidateRange(0, 1000000)][uint32]$RenderDocEffectSubmission = 0,
    [ValidateRange(0, 307200)][uint32]$RenderDocBlackPixels = 0,
    [ValidateRange(0, 307200)][uint32]$RenderDocBlackPixelsMax = 230399,
    [ValidateRange(0, 120)][double]$RenderDocBlackCinematicMinSeconds = 0,
    [switch]$SceneFlipTrace
)

$ErrorActionPreference = 'Stop'
$project = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $project 'build-ninja'
$exe = Join-Path $build 'dah_recomp_working.exe'
$inputPath = Join-Path $PSScriptRoot 'farm_cinematic_current_probe.txt'
$prefix = Join-Path $build "farm-cinematic-visual-$Run"
$saveDir = "$prefix-saves"

if (!(Test-Path -LiteralPath $exe -PathType Leaf)) { throw "Missing build: $exe" }
if (!(Test-Path -LiteralPath $inputPath -PathType Leaf)) { throw "Missing route: $inputPath" }
if (Test-Path -LiteralPath $saveDir) { throw "Run already exists: $saveDir" }
New-Item -ItemType Directory -Path $saveDir | Out-Null

$start = [Diagnostics.ProcessStartInfo]::new()
$start.FileName = $exe
$start.WorkingDirectory = $build
$start.UseShellExecute = $false
$start.CreateNoWindow = $true
$start.WindowStyle = [Diagnostics.ProcessWindowStyle]::Hidden

@($start.EnvironmentVariables.Keys) |
    Where-Object { $_ -like 'DAH_*' } |
    ForEach-Object { $start.EnvironmentVariables.Remove($_) }

$captureEnd = $CaptureStart + (($CaptureCount - 1u) * $CaptureInterval)
$settings = @{
    DAH_INTERNAL_RUN = '1'
    DAH_TEST_WINDOW_HIDDEN = '1'
    DAH_FRAME_TURBO = '1'
    DAH_HOST_FRAME = '0'
    DAH_DIAGNOSTIC_OVERLAY = '0'
    DAH_AUTOSTART = '0'
    DAH_KPCR_WATCH = '0'
    DAH_INPUT_SCRIPT = $inputPath
    DAH_SAVE_DIR = $saveDir
    DAH_LOG_PATH = "$prefix.log"
    DAH_PARITY_STATE_TRACE = "$prefix-state.jsonl"
    DAH_PARITY_STATE_INTERVAL = '1'
    DAH_PARITY_STATE_START = [string]$CaptureStart
    DAH_PARITY_STATE_END = [string]$captureEnd
    DAH_FRAME_CAPTURE = [string]$CaptureCount
    DAH_FRAME_CAPTURE_INTERVAL = [string]$CaptureInterval
    DAH_FRAME_CAPTURE_START = [string]$CaptureStart
    DAH_PB_CAPTURE = '0'
    DAH_UI_ANIMATION_TRACE = '1'
    DAH_UI_ANIMATION_TRACE_START = [string]$CaptureStart
    DAH_FARM_MATERIAL_TRACE = '1'
    DAH_FARM_MATERIAL_TRACE_START = [string]$CaptureStart
    DAH_MODEL_TRACE = '1'
    DAH_EFFECT_TEXTURE_OFFSET = '0x02493800'
    DAH_EFFECT_TEXTURE_DUMP = "$prefix-effect-02493800.bc3"
}
foreach ($name in $settings.Keys) {
    $start.EnvironmentVariables[$name] = [string]$settings[$name]
}
if ($SceneFlipTrace) {
    $start.EnvironmentVariables['DAH_SCENE_FLIP_TRACE'] = '1'
}
if ((@([bool]($RenderDocFrame -gt 0), [bool]($RenderDocCinematicSeconds -gt 0),
        [bool]($RenderDocEffectSubmission -gt 0), [bool]($RenderDocBlackPixels -gt 0)) | Where-Object { $_ }).Count -gt 1) {
    throw 'Choose one RenderDoc trigger: host frame, cinematic seconds, effect submission, or black-pixel detection.'
}
if ($RenderDocFrame -gt 0) {
    $start.EnvironmentVariables['DAH_RENDERDOC_FRAME'] = [string]$RenderDocFrame
    $start.EnvironmentVariables['DAH_RENDERDOC_PATH'] = $prefix
} elseif ($RenderDocCinematicSeconds -gt 0) {
    $start.EnvironmentVariables['DAH_RENDERDOC_CINEMATIC_SECONDS'] = $RenderDocCinematicSeconds.ToString([Globalization.CultureInfo]::InvariantCulture)
    $start.EnvironmentVariables['DAH_RENDERDOC_PATH'] = $prefix
} elseif ($RenderDocEffectSubmission -gt 0) {
    $start.EnvironmentVariables['DAH_RENDERDOC_FRAME'] = '999999'
    $start.EnvironmentVariables['DAH_RENDERDOC_EFFECT_SUBMISSION'] = [string]$RenderDocEffectSubmission
    $start.EnvironmentVariables['DAH_RENDERDOC_PATH'] = $prefix
} elseif ($RenderDocBlackPixels -gt 0) {
    $start.EnvironmentVariables['DAH_RENDERDOC_FRAME'] = '999999'
    $start.EnvironmentVariables['DAH_RENDERDOC_BLACK_PIXEL_THRESHOLD'] = [string]$RenderDocBlackPixels
    $start.EnvironmentVariables['DAH_RENDERDOC_BLACK_PIXEL_MAXIMUM'] = [string]$RenderDocBlackPixelsMax
    $start.EnvironmentVariables['DAH_RENDERDOC_BLACK_CINEMATIC_MIN_SECONDS'] = $RenderDocBlackCinematicMinSeconds.ToString([Globalization.CultureInfo]::InvariantCulture)
    $start.EnvironmentVariables['DAH_RENDERDOC_PATH'] = $prefix
}

$process = [Diagnostics.Process]::Start($start)
$process.PriorityClass = [Diagnostics.ProcessPriorityClass]::BelowNormal
Write-Output "FARM_CINEMATIC_VISUAL_START pid=$($process.Id) run=$Run seconds=$Seconds capture=$CaptureStart..$captureEnd"
try {
    $deadline = [DateTime]::UtcNow.AddSeconds($Seconds)
    while ([DateTime]::UtcNow -lt $deadline -and !$process.HasExited) {
        Start-Sleep -Seconds 1
        $process.Refresh()
    }
    if ($process.HasExited) {
        Write-Output "FARM_CINEMATIC_VISUAL_EXIT pid=$($process.Id) code=$($process.ExitCode)"
        if ($process.ExitCode -ne 0) { throw "Game exited with code $($process.ExitCode)" }
    } else {
        Write-Output "FARM_CINEMATIC_VISUAL_BOUND pid=$($process.Id)"
    }
} finally {
    $process.Refresh()
    if (!$process.HasExited) {
        $process.Kill()
        $process.WaitForExit()
    }
}

Write-Output "FARM_CINEMATIC_VISUAL_LOG $prefix.log"
Write-Output "FARM_CINEMATIC_VISUAL_STATE $prefix-state.jsonl"
