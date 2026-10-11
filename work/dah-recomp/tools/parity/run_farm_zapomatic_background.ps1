param(
    [ValidateRange(30, 600)][int]$Seconds = 240,
    [ValidatePattern('^[A-Za-z0-9-]+$')][string]$Run = 'current'
)

$ErrorActionPreference = 'Stop'
$repo = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $repo 'build-ninja'
$exe = Join-Path $build 'dah_recomp_working.exe'
$inputScript = Join-Path $PSScriptRoot 'farm_zapomatic_fire_probe.txt'
$diagnosticRoot = Join-Path $env:LOCALAPPDATA 'Temp\dah-zapomatic-runs'
$saveDir = Join-Path $diagnosticRoot "saves-zapomatic-$Run"
$logPath = Join-Path $diagnosticRoot "zapomatic-$Run.log"
$statePath = Join-Path $diagnosticRoot "zapomatic-$Run-state.jsonl"
$captureTrigger = Join-Path $diagnosticRoot "zapomatic-$Run.trigger"

if (!(Test-Path -LiteralPath $exe)) { throw "Missing build: $exe" }
if (Test-Path -LiteralPath $saveDir) { throw "Run already exists: $saveDir" }
New-Item -ItemType Directory -Path $diagnosticRoot -Force | Out-Null
New-Item -ItemType Directory -Path $saveDir | Out-Null
Set-Content -LiteralPath $captureTrigger -Value 'armed'

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
    # Farm's tutorial repeatedly selects Cortex Scan/PK. Re-equip Zap between
    # those retail switches so at least one controller firing window exercises
    # Zap without patching guest state or calling the weapon implementation.
    DAH_CONSOLE_AUTO_WEAPON_SEQUENCE = 'zapomatic,zapomatic,zapomatic,zapomatic,zapomatic,zapomatic'
    DAH_CONSOLE_AUTO_WEAPON_INTERVAL = '1200'
    DAH_PARITY_STATE_TRACE = $statePath
    # Weapon detail makes each JSON record large.  Keep the trace tightly
    # around the firing window so diagnostics do not change route timing.
    DAH_PARITY_STATE_INTERVAL = '5'
    DAH_PARITY_STATE_START = '9000'
    DAH_PARITY_STATE_END = '16000'
    DAH_PARITY_WEAPON_DETAIL = '1'
    DAH_FRAME_CAPTURE = '0'
    DAH_FRAME_CAPTURE_TRIGGER = $captureTrigger
    DAH_PB_CAPTURE = '0'
    DAH_KPCR_WATCH = '0'
    DAH_ACTIVE_ICALL_TRACE = '1'
}
foreach ($name in $settings.Keys) { $start.EnvironmentVariables[$name] = $settings[$name] }

$process = [Diagnostics.Process]::Start($start)
Write-Output "ZAPOMATIC_START pid=$($process.Id) run=$Run seconds=$Seconds"
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
Write-Output "ZAPOMATIC_LOG $logPath"
Write-Output "ZAPOMATIC_STATE $statePath"
