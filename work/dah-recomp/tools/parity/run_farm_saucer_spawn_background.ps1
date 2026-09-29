param(
    [ValidateRange(60, 600)][int]$Seconds = 420,
    [ValidatePattern('^[A-Za-z0-9-]+$')][string]$Run = 'current'
)

$ErrorActionPreference = 'Stop'
$repo = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $repo 'build-ninja'
$exe = Join-Path $build 'dah_recomp_working.exe'
$inputScript = Join-Path $PSScriptRoot 'farm_saucer_spawn_probe.txt'
$saveDir = Join-Path $build "saves-saucer-spawn-$Run"
$logPath = Join-Path $build "saucer-spawn-$Run.log"
$statePath = Join-Path $build "saucer-spawn-$Run-state.jsonl"

if (!(Test-Path -LiteralPath $exe)) { throw "Missing build: $exe" }
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
    DAH_AUTOSTART = '0'
    DAH_DIAGNOSTIC_OVERLAY = '0'
    DAH_INPUT_SCRIPT = $inputScript
    DAH_SAVE_DIR = $saveDir
    DAH_LOG_PATH = $logPath
    DAH_CONSOLE_AUTO_GRANT_SAUCER = '1'
    DAH_CONSOLE_AUTO_EQUIP_DELAY = '0'
    DAH_PARITY_STATE_TRACE = $statePath
    DAH_PARITY_STATE_INTERVAL = '100'
    DAH_PARITY_STATE_START = '0'
    DAH_PARITY_STATE_END = '99999999'
    DAH_PARITY_WEAPON_DETAIL = '1'
    DAH_FRAME_CAPTURE = '0'
    DAH_INPUT_EVENT_CAPTURE = '1'
    DAH_PB_CAPTURE = '0'
    DAH_KPCR_WATCH = '0'
    DAH_ACTIVE_ICALL_TRACE = '1'
    DAH_FOCUS_TRACE = '1'
}
foreach ($name in $settings.Keys) { $start.EnvironmentVariables[$name] = $settings[$name] }

$process = [Diagnostics.Process]::Start($start)
Write-Output "SAUCER_SPAWN_START pid=$($process.Id) run=$Run seconds=$Seconds"
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
Write-Output "SAUCER_SPAWN_LOG $logPath"
Write-Output "SAUCER_SPAWN_STATE $statePath"
