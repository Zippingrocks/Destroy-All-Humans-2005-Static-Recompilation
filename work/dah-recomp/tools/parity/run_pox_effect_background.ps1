param(
    [Parameter(Mandatory)][ValidatePattern('^[A-Za-z0-9-]+$')][string]$Run,
    [ValidateRange(10, 300)][int]$Seconds = 90,
    [ValidateRange(0, 1000000)][uint32]$CaptureStart = 5600,
    [ValidateRange(1, 1000000)][uint32]$CaptureInterval = 10,
    [ValidateRange(0, 128)][uint32]$CaptureCount = 64,
    [ValidateRange(0, 1000000)][uint32]$RenderDocFrame = 6001
)

$ErrorActionPreference = 'Stop'
$project = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $project 'build-ninja'
$exe = Join-Path $build 'dah_recomp_working.exe'
$inputPath = Join-Path $PSScriptRoot 'pox_lab_effect_probe.txt'
$prefix = Join-Path $build "pox-effect-$Run"
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

$settings = @{
    DAH_INTERNAL_RUN = '1'
    DAH_TEST_WINDOW_HIDDEN = '1'
    DAH_FRAME_TURBO = '1'
    DAH_HOST_FRAME = '0'
    DAH_DIAGNOSTIC_OVERLAY = '0'
    DAH_AUTOSTART = '0'
    DAH_MOVIE_NONBLOCK = '1'
    DAH_KPCR_WATCH = '0'
    DAH_INPUT_SCRIPT = $inputPath
    DAH_SAVE_DIR = $saveDir
    DAH_LOG_PATH = "$prefix.log"
    DAH_PARITY_STATE_TRACE = "$prefix-state.jsonl"
    DAH_PARITY_STATE_INTERVAL = '1'
    DAH_PARITY_STATE_START = '5000'
    DAH_PARITY_STATE_END = '6800'
    DAH_FRAME_CAPTURE = [string]$CaptureCount
    DAH_FRAME_CAPTURE_INTERVAL = [string]$CaptureInterval
    DAH_FRAME_CAPTURE_START = [string]$CaptureStart
    DAH_PB_CAPTURE = '0'
    DAH_UI_ANIMATION_TRACE = '1'
    DAH_UI_ANIMATION_TRACE_START = '5000'
    DAH_FARM_MATERIAL_TRACE = '1'
    DAH_FARM_MATERIAL_TRACE_START = '5000'
}
if ($RenderDocFrame -gt 0) {
    $settings.DAH_RENDERDOC_FRAME = [string]$RenderDocFrame
    $settings.DAH_RENDERDOC_PATH = $prefix
}
foreach ($name in $settings.Keys) {
    $start.EnvironmentVariables[$name] = [string]$settings[$name]
}

$process = [Diagnostics.Process]::Start($start)
$process.PriorityClass = [Diagnostics.ProcessPriorityClass]::BelowNormal
Write-Output "POX_EFFECT_START pid=$($process.Id) run=$Run seconds=$Seconds"
try {
    $deadline = [DateTime]::UtcNow.AddSeconds($Seconds)
    while ([DateTime]::UtcNow -lt $deadline -and !$process.HasExited) {
        Start-Sleep -Seconds 1
        $process.Refresh()
    }
    if ($process.HasExited) {
        Write-Output "POX_EFFECT_EXIT pid=$($process.Id) code=$($process.ExitCode)"
        if ($process.ExitCode -ne 0) { throw "Game exited with code $($process.ExitCode)" }
    } else {
        Write-Output "POX_EFFECT_BOUND pid=$($process.Id)"
    }
} finally {
    $process.Refresh()
    if (!$process.HasExited) {
        $process.Kill()
        $process.WaitForExit()
    }
}

Write-Output "POX_EFFECT_LOG $prefix.log"
Write-Output "POX_EFFECT_STATE $prefix-state.jsonl"
