param(
    [ValidateRange(30, 600)][int]$Seconds = 330,
    [ValidatePattern('^[A-Za-z0-9-]+$')][string]$Run = 'current'
)

$ErrorActionPreference = 'Stop'
$repo = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $repo 'build-ninja'
$exe = Join-Path $build 'dah_recomp_working.exe'
$inputScript = Join-Path $PSScriptRoot 'farm_cortex_cow_gameplay_probe.txt'
$saveDir = Join-Path $build "saves-cortex-cow-$Run"
$logPath = Join-Path $build "cortex-cow-$Run.log"
$statePath = Join-Path $build "cortex-cow-$Run-state.jsonl"

if (!(Test-Path -LiteralPath $exe)) { throw "Missing build: $exe" }
if (!(Test-Path -LiteralPath $inputScript)) { throw "Missing route: $inputScript" }
if (Test-Path -LiteralPath $saveDir) { throw "Run already exists: $saveDir" }
New-Item -ItemType Directory -Path $saveDir | Out-Null

$start = [Diagnostics.ProcessStartInfo]::new()
$start.FileName = $exe
$start.WorkingDirectory = $build
$start.UseShellExecute = $false
$start.CreateNoWindow = $true
$start.WindowStyle = [Diagnostics.ProcessWindowStyle]::Hidden

# Do not inherit a caller's test switches. This route deliberately uses the
# retail movie scheduler and changes only host pacing after gameplay begins.
@($start.EnvironmentVariables.Keys) |
    Where-Object { $_ -like 'DAH_*' } |
    ForEach-Object { $start.EnvironmentVariables.Remove($_) }

$settings = @{
    DAH_INTERNAL_RUN = '1'
    DAH_TEST_WINDOW_HIDDEN = '1'
    DAH_FRAME_TURBO = '1'
    DAH_DIAGNOSTIC_OVERLAY = '0'
    DAH_AUTOSTART = '0'
    DAH_FRAME_CAPTURE = '0'
    DAH_PB_CAPTURE = '0'
    DAH_KPCR_WATCH = '0'
    DAH_INPUT_SCRIPT = $inputScript
    DAH_SAVE_DIR = $saveDir
    DAH_LOG_PATH = $logPath
    DAH_PARITY_STATE_TRACE = $statePath
    DAH_PARITY_STATE_INTERVAL = '1'
    DAH_ACTIVE_ICALL_TRACE = '1'
    DAH_ACTIVE_SCRIPT_CALL_TRACE = '1'
}
foreach ($name in $settings.Keys) {
    $start.EnvironmentVariables[$name] = $settings[$name]
}

$process = [Diagnostics.Process]::Start($start)
Write-Output "CORTEX_COW_START pid=$($process.Id) run=$Run seconds=$Seconds"
try {
    $deadline = [DateTime]::UtcNow.AddSeconds($Seconds)
    while ([DateTime]::UtcNow -lt $deadline -and !$process.HasExited) {
        Start-Sleep -Seconds 1
        $process.Refresh()
    }
    if ($process.HasExited) {
        Write-Output "CORTEX_COW_EXIT pid=$($process.Id) code=$($process.ExitCode)"
        if ($process.ExitCode -ne 0) { throw "Game exited with code $($process.ExitCode)" }
    } else {
        Write-Output "CORTEX_COW_BOUND pid=$($process.Id)"
    }
} finally {
    $process.Refresh()
    if (!$process.HasExited) {
        $process.Kill()
        $process.WaitForExit()
    }
}

Write-Output "CORTEX_COW_LOG $logPath"
Write-Output "CORTEX_COW_STATE $statePath"
