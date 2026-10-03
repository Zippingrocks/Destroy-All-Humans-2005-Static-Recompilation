param(
    [Parameter(Mandatory)][ValidatePattern('^[A-Za-z0-9-]+$')][string]$Run,
    [ValidateRange(30, 300)][int]$Seconds = 120,
    [string]$SeedSaveDir = ''
)

$ErrorActionPreference = 'Stop'
$project = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$build = Join-Path $project 'build-ninja'
$exe = Join-Path $build 'dah_recomp_working.exe'
$prefix = Join-Path $build "new-game-slot1-$Run"
$route = "$prefix-input.txt"
$statePath = "$prefix-state.jsonl"
$saveDir = "$prefix-saves"

foreach ($path in @($route, $statePath, $saveDir, "$prefix.log")) {
    if (Test-Path -LiteralPath $path) { throw "Run already exists: $path" }
}
if (!(Test-Path -LiteralPath $exe -PathType Leaf)) { throw "Missing build: $exe" }
New-Item -ItemType Directory -Path $saveDir | Out-Null
if ($SeedSaveDir) {
    $seedRoot = [IO.Path]::GetFullPath($SeedSaveDir)
    if (!(Test-Path -LiteralPath $seedRoot -PathType Container)) { throw "Missing seed save directory: $seedRoot" }
    Get-ChildItem -LiteralPath $seedRoot -Force | Copy-Item -Destination $saveDir -Recurse -Force
}
Set-Content -LiteralPath $route -Value "@frame`n1200 6 10 0 0 0 0 0 0`n"

$start = [Diagnostics.ProcessStartInfo]::new()
$start.FileName = $exe
$start.WorkingDirectory = $build
$start.UseShellExecute = $false
$start.CreateNoWindow = $true
$start.WindowStyle = [Diagnostics.ProcessWindowStyle]::Hidden
@($start.EnvironmentVariables.Keys) | Where-Object { $_ -like 'DAH_*' } |
    ForEach-Object { $start.EnvironmentVariables.Remove($_) }
$settings = @{
    DAH_INTERNAL_RUN = '1'; DAH_TEST_WINDOW_HIDDEN = '1'; DAH_FRAME_TURBO = '1'
    DAH_HOST_FRAME = '0'; DAH_DIAGNOSTIC_OVERLAY = '0'; DAH_AUTOSTART = '0'
    DAH_INPUT_SCRIPT = $route; DAH_SAVE_DIR = $saveDir; DAH_LOG_PATH = "$prefix.log"
    DAH_PARITY_STATE_TRACE = $statePath; DAH_PARITY_STATE_INTERVAL = '5'
    DAH_PARITY_STATE_START = '0'; DAH_PARITY_STATE_END = '12000'
    DAH_SAVE_TRACE = '1'; DAH_FRAME_CAPTURE = '0'; DAH_PB_CAPTURE = '0'; DAH_KPCR_WATCH = '0'
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
    Add-Content -LiteralPath $route -Value "`n@frame`n$frame 6 0 255 0 0 0 0 0`n"
    Write-Output "SLOT1_INPUT label=$label frame=$frame"
}
function Add-FrameUp([uint64]$frame, [string]$label) {
    Add-Content -LiteralPath $route -Value "`n@frame`n$frame 6 1 0 0 0 0 0 0`n"
    Write-Output "SLOT1_INPUT label=$label frame=$frame"
}

$process = [Diagnostics.Process]::Start($start)
$process.PriorityClass = [Diagnostics.ProcessPriorityClass]::BelowNormal
$deadline = [DateTime]::UtcNow.AddSeconds($Seconds)
$startStable = 0; $profileStable = 0; $askStable = 0
$newGameFrame = 0; $slotFrame = 0; $confirmFrame = 0; $result = ''
Write-Output "SLOT1_START pid=$($process.Id) run=$Run"
try {
    while ([DateTime]::UtcNow -lt $deadline -and !$process.HasExited) {
        Start-Sleep -Milliseconds 200
        $state = Get-LatestState
        if ($null -eq $state) { continue }
        if (Test-ActiveUi $state 'readerror') {
            $result = 'readerror'; break
        } elseif (!$newGameFrame) {
            $startStable = if (Test-ActiveUi $state 'startmenu') { $startStable + 1 } else { 0 }
            if ($startStable -ge 3) {
                # With existing profiles retail initially highlights Load Game.
                # Move to New Game before accepting it.
                if ($SeedSaveDir) {
                    $newGameFrame = [uint64]$state.loop + 105
                    Add-FrameUp ([uint64]$state.loop + 45) 'select-new-game'
                } else { $newGameFrame = [uint64]$state.loop + 45 }
                Add-FrameA $newGameFrame 'new-game'
            }
        } elseif (!$slotFrame) {
            $profileStable = if (Test-ActiveUi $state 'selectprofile') { $profileStable + 1 } else { 0 }
            # selectprofile becomes active near the start of its entrance animation;
            # retail input is accepted only once that transition has settled.
            if ($profileStable -ge 3) { $slotFrame = [uint64]$state.loop + 600; Add-FrameA $slotFrame 'slot-1' }
        } elseif (!$confirmFrame) {
            $askStable = if (Test-ActiveUi $state 'ask') { $askStable + 1 } else { 0 }
            if ($askStable -ge 3) { $confirmFrame = [uint64]$state.loop + 45; Add-FrameA $confirmFrame 'confirm-save' }
            elseif ([uint64]$state.loop -gt $slotFrame + 1200) { $result = 'completed-no-error'; break }
        } elseif ($state.movie -ne 0 -or (Test-ActiveUi $state 'tthubMain')) {
            $result = 'success'; break
        } elseif ([uint64]$state.loop -gt $slotFrame + 1200) {
            $result = 'completed-no-error'; break
        }
    }
    if ($process.HasExited -and $process.ExitCode -ne 0) { throw "Game exited with code $($process.ExitCode)" }
} finally {
    $process.Refresh()
    if (!$process.HasExited) { $process.Kill(); $process.WaitForExit() }
}
Write-Output "SLOT1_DONE result=$result newGame=$newGameFrame slot=$slotFrame confirm=$confirmFrame"
Write-Output "SLOT1_LOG $prefix.log"
Write-Output "SLOT1_STATE $statePath"
