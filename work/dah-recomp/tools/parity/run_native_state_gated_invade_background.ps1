param(
    [Parameter(Mandatory)][ValidatePattern('^[A-Za-z0-9-]+$')][string]$Run,
    [ValidateRange(1, 1000)][int]$StateInterval = 5,
    [ValidateRange(0, 240)][int]$CaptureCount = 0,
    [ValidateRange(0, 50000)][int]$CaptureStart = 0,
    [ValidateRange(1, 1000)][int]$CaptureInterval = 10,
    [ValidateRange(90, 600)][int]$Seconds = 240
)

$ErrorActionPreference = 'Stop'
$project = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $project 'build-ninja'
$exe = Join-Path $build 'dah_recomp_working.exe'
$seed = Join-Path $PSScriptRoot 'mothership_hub_probe.txt'
$prefix = Join-Path $build "state-gated-invade-$Run"
$route = "$prefix-input.txt"
$statePath = "$prefix-state.jsonl"
$saveDir = "$prefix-saves"

foreach ($newPath in @($route, $statePath, $saveDir)) {
    if (Test-Path -LiteralPath $newPath) { throw "Run already exists: $newPath" }
}
if (!(Test-Path -LiteralPath $exe -PathType Leaf)) { throw "Missing build: $exe" }
Copy-Item -LiteralPath $seed -Destination $route
New-Item -ItemType Directory -Path $saveDir | Out-Null

$start = [Diagnostics.ProcessStartInfo]::new()
$start.FileName = $exe
$start.WorkingDirectory = $build
$start.UseShellExecute = $false
$start.CreateNoWindow = $true
$start.WindowStyle = [Diagnostics.ProcessWindowStyle]::Hidden
@($start.EnvironmentVariables.Keys) | Where-Object { $_ -like 'DAH_*' } |
    ForEach-Object { $start.EnvironmentVariables.Remove($_) }
$settings = @{
    DAH_INTERNAL_RUN = '1'; DAH_TEST_WINDOW_HIDDEN = '1'; DAH_HOST_FRAME = '0'
    DAH_DIAGNOSTIC_OVERLAY = '0'; DAH_AUTOSTART = '0'; DAH_INPUT_SCRIPT = $route
    DAH_SAVE_DIR = $saveDir; DAH_LOG_PATH = "$prefix.log"
    DAH_PARITY_STATE_TRACE = $statePath; DAH_PARITY_STATE_INTERVAL = [string]$StateInterval
    DAH_PARITY_STATE_START = '0'; DAH_PARITY_STATE_END = '20000'
    DAH_FRAME_CAPTURE = [string]$CaptureCount
    DAH_FRAME_CAPTURE_START = [string]$CaptureStart
    DAH_FRAME_CAPTURE_INTERVAL = [string]$CaptureInterval
    DAH_PB_CAPTURE = '0'; DAH_KPCR_WATCH = '0'
}
foreach ($name in $settings.Keys) { $start.EnvironmentVariables[$name] = $settings[$name] }

function Get-LatestState {
    if (!(Test-Path -LiteralPath $statePath)) { return $null }
    foreach ($text in @(Get-Content -LiteralPath $statePath -Tail 12)[-1..-12]) {
        try { return ($text | ConvertFrom-Json) } catch {}
    }
    return $null
}
function Test-ActiveUi($state, [string]$name) {
    return $null -ne ($state.ui | Where-Object { $_.active -eq 1 -and $_.name -eq $name } | Select-Object -First 1)
}
function Add-FrameA([uint64]$frame, [string]$label) {
    Add-Content -LiteralPath $route -Value "`n@frame`n$frame 3 0 255 0 0 0 0 0`n"
    Write-Output "STATE_GATED_INPUT label=$label frame=$frame"
}

$process = [Diagnostics.Process]::Start($start)
$process.PriorityClass = [Diagnostics.ProcessPriorityClass]::BelowNormal
$deadline = [DateTime]::UtcNow.AddSeconds($Seconds)
$hubStable = 0; $navicomStable = 0; $hangarFrame = 0; $invadeFrame = 0; $farmLoop = 0
Write-Output "STATE_GATED_START pid=$($process.Id) run=$Run seconds=$Seconds"
try {
    while ([DateTime]::UtcNow -lt $deadline -and !$process.HasExited) {
        Start-Sleep -Milliseconds 250
        $state = Get-LatestState
        if ($null -eq $state) { continue }
        if (!$hangarFrame) {
            # A startup-route press may already have entered Hangar on a faster
            # build. Treat that observed state as the completed first gate.
            if (Test-ActiveUi $state 'navicom') {
                $hangarFrame = [uint64]$state.loop
                Write-Output "STATE_GATED_OBSERVED label=hangar frame=$hangarFrame"
                continue
            }
            $hubStable = if ((Test-ActiveUi $state 'tthubMain') -and !(Test-ActiveUi $state 'navicom')) { $hubStable + 1 } else { 0 }
            if ($hubStable -ge 3) { $hangarFrame = [uint64]$state.loop + 45; Add-FrameA $hangarFrame 'enter-hangar' }
        } elseif (!$invadeFrame) {
            $navicomStable = if (Test-ActiveUi $state 'navicom') { $navicomStable + 1 } else { 0 }
            if ($navicomStable -ge 3) { $invadeFrame = [uint64]$state.loop + 45; Add-FrameA $invadeFrame 'invade-farm' }
        } elseif (!$farmLoop -and $state.backendName -eq 'blocks\sites\farm') {
            $farmLoop = [uint64]$state.loop
            Write-Output "STATE_GATED_FARM loop=$farmLoop invadeFrame=$invadeFrame"
        } elseif ($farmLoop -and [uint64]$state.loop -ge $farmLoop + 240) {
            break
        }
    }
    if ($process.HasExited -and $process.ExitCode -ne 0) { throw "Game exited with code $($process.ExitCode)" }
    if (!$invadeFrame -or !$farmLoop) { throw "State-gated route did not reach Farm (hangar=$hangarFrame invade=$invadeFrame farm=$farmLoop)" }
} finally {
    $process.Refresh()
    if (!$process.HasExited) { $process.Kill(); $process.WaitForExit() }
}
Write-Output "STATE_GATED_DONE hangarFrame=$hangarFrame invadeFrame=$invadeFrame farmLoop=$farmLoop"
Write-Output "STATE_GATED_STATE $statePath"
