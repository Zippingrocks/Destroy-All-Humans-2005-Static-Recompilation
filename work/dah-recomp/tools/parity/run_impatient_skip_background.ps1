param(
    [Parameter(Mandatory)][ValidatePattern('^[A-Za-z0-9-]+$')][string]$Run,
    [ValidateSet('absolute', 'phase', 'barrage')][string]$Route = 'absolute',
    [ValidateRange(30, 600)][int]$Seconds = 150
)

$ErrorActionPreference = 'Stop'
$project = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $project 'build-ninja'
$exe = Join-Path $build 'dah_recomp_working.exe'
$inputName = switch ($Route) {
    'phase' { 'impatient_skip_phase_stress_probe.txt' }
    'barrage' { 'impatient_cinematic_barrage_probe.txt' }
    default { 'impatient_skip_stress_probe.txt' }
}
$inputPath = Join-Path $PSScriptRoot $inputName
$prefixName = if ($Route -eq 'absolute') { "impatient-skip-$Run" } else { "impatient-skip-$Route-$Run" }
$prefix = Join-Path $build $prefixName
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
    DAH_INPUT_SCRIPT = $inputPath
    DAH_SAVE_DIR = $saveDir
    DAH_LOG_PATH = "$prefix.log"
    DAH_PARITY_STATE_TRACE = "$prefix-state.jsonl"
    DAH_PARITY_STATE_INTERVAL = '5'
    DAH_PARITY_STATE_START = '0'
    DAH_PARITY_STATE_END = '20000'
    DAH_FRAME_CAPTURE = '0'
    DAH_PB_CAPTURE = '0'
    DAH_KPCR_WATCH = '0'
}
foreach ($name in $settings.Keys) { $start.EnvironmentVariables[$name] = $settings[$name] }

$process = [Diagnostics.Process]::Start($start)
$process.PriorityClass = [Diagnostics.ProcessPriorityClass]::BelowNormal
Write-Output "IMPATIENT_SKIP_START pid=$($process.Id) run=$Run route=$Route seconds=$Seconds"
try {
    $deadline = [DateTime]::UtcNow.AddSeconds($Seconds)
    while ([DateTime]::UtcNow -lt $deadline -and !$process.HasExited) {
        Start-Sleep -Seconds 1
        $process.Refresh()
    }
    if ($process.HasExited -and $process.ExitCode -ne 0) {
        throw "Game exited with code $($process.ExitCode)"
    }
} finally {
    $process.Refresh()
    if (!$process.HasExited) {
        $process.Kill()
        $process.WaitForExit()
    }
}
Write-Output "IMPATIENT_SKIP_LOG $prefix.log"
Write-Output "IMPATIENT_SKIP_STATE $prefix-state.jsonl"
