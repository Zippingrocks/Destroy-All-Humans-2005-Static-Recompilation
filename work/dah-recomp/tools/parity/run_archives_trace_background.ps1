param(
    [ValidateRange(30, 600)][int]$Seconds = 300,
    [ValidateRange(0, 1000000)][int]$CaptureStart = 8500,
    [ValidateRange(0, 1000000)][int]$SubmissionStart = 16800,
    [ValidateRange(0, 1000000)][int]$TraceStart = 16500,
    [string]$InputPath = '',
    [ValidateRange(0, 1000000)][int]$PixelTraceFirst = 0,
    [string]$PixelTraceXY = '',
    [switch]$PixelTraceAuto,
    [switch]$PixelTraceAnyTarget,
    [string]$ExePath = ''
)

$ErrorActionPreference = 'Stop'
$root = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $root 'build-ninja'
$exe = if ($ExePath) { [IO.Path]::GetFullPath($ExePath) } else {
    Join-Path $build 'dah_recomp_working.exe'
}
$input = if ($InputPath) { [IO.Path]::GetFullPath($InputPath) } else {
    Join-Path $PSScriptRoot 'archives_live_route_probe.txt'
}
$save = Join-Path $build 'archives-save-copy'
$log = Join-Path $build 'archives-route-trace.log'

if (!(Test-Path -LiteralPath $exe)) { throw "Missing diagnostic executable: $exe" }
if (!(Test-Path -LiteralPath $input)) { throw "Missing input route: $input" }
if (!(Test-Path -LiteralPath $save)) { throw "Missing isolated save copy: $save" }

$start = New-Object System.Diagnostics.ProcessStartInfo
$start.FileName = $exe
$start.WorkingDirectory = $build
$start.UseShellExecute = $false
$start.CreateNoWindow = $true
$start.WindowStyle = [Diagnostics.ProcessWindowStyle]::Hidden
$settings = @{
    DAH_INTERNAL_RUN = '1'
    DAH_FPS = '60'
    DAH_HOST_FRAME = '0'
    DAH_AUTOSTART = '0'
    DAH_MOVIE_NONBLOCK = '1'
    DAH_SAVE_DIR = $save
    DAH_INPUT_SCRIPT = $input
    DAH_FRAME_CAPTURE = '24'
    DAH_FRAME_CAPTURE_INTERVAL = '15'
    DAH_FRAME_CAPTURE_START = [string]$CaptureStart
    DAH_PB_CAPTURE = '64'
    DAH_PB_CAPTURE_START = [string]$SubmissionStart
    DAH_PB_REJECT_CAPTURE = '32'
    DAH_PB_REJECT_START = [string]$SubmissionStart
    DAH_SKIN_DUMP = '1'
    DAH_UI_ANIMATION_TRACE = '1'
    DAH_UI_ANIMATION_TRACE_START = [string]$TraceStart
    DAH_FOG_TRACE = '1'
    DAH_FARM_MATERIAL_TRACE = '1'
    DAH_FARM_MATERIAL_TRACE_START = [string]$TraceStart
    DAH_LOG_PATH = $log
}
foreach ($pair in $settings.GetEnumerator()) {
    $start.EnvironmentVariables[$pair.Key] = [string]$pair.Value
}
if ($PixelTraceFirst -gt 0) {
    $start.EnvironmentVariables['DAH_DRAW_PIXEL_TRACE'] = '1'
    $start.EnvironmentVariables['DAH_DRAW_PIXEL_TRACE_FIRST'] = [string]$PixelTraceFirst
}
if ($PixelTraceXY) {
    $start.EnvironmentVariables['DAH_DRAW_PIXEL_TRACE_XY'] = $PixelTraceXY
}
if ($PixelTraceAuto) {
    $start.EnvironmentVariables['DAH_DRAW_PIXEL_TRACE_AUTO'] = '1'
}
if ($PixelTraceAnyTarget) {
    $start.EnvironmentVariables['DAH_DRAW_PIXEL_TRACE_ANY_TARGET'] = '1'
}

$process = [Diagnostics.Process]::Start($start)
Write-Output "ARCHIVES_TEST_START pid=$($process.Id) nonblocking=1"
try {
    $deadline = [DateTime]::UtcNow.AddSeconds($Seconds)
    while ([DateTime]::UtcNow -lt $deadline -and !$process.HasExited) {
        Start-Sleep -Seconds 1
        $process.Refresh()
    }
    if ($process.HasExited) {
        Write-Output "ARCHIVES_TEST_EXIT pid=$($process.Id) code=$($process.ExitCode)"
    } else {
        Write-Output "ARCHIVES_TEST_BOUND pid=$($process.Id)"
    }
} finally {
    $process.Refresh()
    if (!$process.HasExited) {
        $process.Kill()
        $process.WaitForExit()
    }
}
