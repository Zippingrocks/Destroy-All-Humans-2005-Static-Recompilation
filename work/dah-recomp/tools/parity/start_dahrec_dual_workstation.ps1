param(
    [Parameter(Mandatory)][string]$Recording,
    [string]$MatchMyRecomp = 'D:\MatchMyRecomp',
    [ValidateRange(1024,65535)][int]$GdbPort = 1236,
    [ValidateRange(1024,65535)][int]$QmpPort = 4446,
    [switch]$ReplaceRunningRecomp,
    [switch]$Start
)
$ErrorActionPreference = 'Stop'
Import-Module 'C:\Windows\System32\WindowsPowerShell\v1.0\Modules\Microsoft.PowerShell.Utility\Microsoft.PowerShell.Utility.psd1' -Force

$recordingPath = [IO.Path]::GetFullPath($Recording)
$recordingName = [IO.Path]::GetFileNameWithoutExtension($recordingPath)
if ($recordingName -notmatch '^[A-Za-z0-9_-]{1,48}$') {
    throw 'Recording filename must be a 1-48 character replay name'
}
$recordingRoot = [IO.Path]::GetFullPath((Join-Path $env:LOCALAPPDATA 'DestroyAllHumansRecomp\recordings'))
if ([IO.Path]::GetDirectoryName($recordingPath) -ne $recordingRoot) {
    throw "Recording must be in the native recording directory: $recordingRoot"
}
if (!(Test-Path -LiteralPath $recordingPath -PathType Leaf)) { throw "Missing recording: $recordingPath" }
$matchScript = Join-Path $MatchMyRecomp 'scripts\run-dah-live.ps1'
if (!(Test-Path -LiteralPath $matchScript -PathType Leaf)) { throw "Missing MatchMyRecomp launcher: $matchScript" }

$stamp = [DateTime]::UtcNow.ToString('yyyyMMddTHHmmssfffZ')
$run = Join-Path ([IO.Path]::GetTempPath()) "DAH1-live-parity\replays\$stamp"
$route = Join-Path $run 'validated-fallback-route.txt'
$request = Join-Path $run 'native-replay.request'
$barrier = Join-Path $run 'dual-replay.release'
$ready = Join-Path $run 'xemu-adapter.ready'
$startFile = Join-Path $run 'dual-replay.start'
$trace = Join-Path $run 'xemu-replay.json'
$status = Join-Path $run 'replay-status.json'
$converter = Join-Path $PSScriptRoot 'dahrec_to_route.py'
$launcher = Join-Path $PSScriptRoot 'run_live_dual_parity.ps1'
$coordinator = Join-Path $PSScriptRoot 'coordinate_dahrec_replay.py'

Write-Output "RECORDING $recordingPath"
Write-Output "REPLAY_NAME $recordingName"
Write-Output "RUN $run"
Write-Output 'MODE shared DAHREC1 packets at the retail XInputGetState boundary'
Write-Output 'ARM_RULE same Farm backend, presentation-aligned state, and recorded Crypto position'
if (!$Start) {
    Write-Output 'DRY_RUN_ONLY pass -Start to launch xemu, recomp, watchers, and MatchMyRecomp'
    return
}

New-Item -ItemType Directory -Path $run -Force | Out-Null
& python $converter $recordingPath $route
if ($LASTEXITCODE -ne 0) { throw 'Recording validation/conversion failed' }

$running = @(Get-Process -Name 'DestroyAllHumans' -ErrorAction SilentlyContinue)
if ($running.Count) {
    if (!$ReplaceRunningRecomp) {
        throw 'DestroyAllHumans is already running; pass -ReplaceRunningRecomp to relaunch it with the replay request channel'
    }
    $running | Stop-Process -Force
    $running | Wait-Process -Timeout 10 -ErrorAction SilentlyContinue
}

$launchOutput = @(& $launcher -GdbPort $GdbPort -QmpPort $QmpPort `
    -ReplayRequest $request -ReplayBarrier $barrier -Start)
$launchOutput | Write-Output
$readyLine = $launchOutput | Where-Object { $_ -match '^LIVE_PARITY_READY ' } | Select-Object -Last 1
if (!$readyLine -or $readyLine -notmatch 'xemu_pid=(\d+) recomp_pid=(\d+)') {
    throw 'Live pair launcher returned no process identity'
}
$xemuPid = [int]$Matches[1]
$nativePid = [int]$Matches[2]

$watchRoot = Join-Path ([IO.Path]::GetTempPath()) 'DAH1-live-parity\watches'
$session = $null
$deadline = [DateTime]::UtcNow.AddSeconds(15)
do {
    foreach ($candidate in @(Get-ChildItem -LiteralPath $watchRoot -Directory -ErrorAction SilentlyContinue |
            Sort-Object LastWriteTime -Descending)) {
        $manifestPath = Join-Path $candidate.FullName 'manifest.json'
        if (!(Test-Path -LiteralPath $manifestPath)) { continue }
        $candidateManifest = Get-Content -LiteralPath $manifestPath -Raw | ConvertFrom-Json
        if ($candidateManifest.xemuPid -eq $xemuPid -and $candidateManifest.nativePid -eq $nativePid) {
            $session = $candidate.FullName
            break
        }
    }
    if (!$session) { Start-Sleep -Milliseconds 100 }
} while (!$session -and [DateTime]::UtcNow -lt $deadline)
if (!$session) { throw 'Watcher manifest for the launched pair did not appear' }

$manifestPath = Join-Path $session 'manifest.json'
$manifest = Get-Content -LiteralPath $manifestPath -Raw | ConvertFrom-Json
$manifest | Add-Member -NotePropertyName inputStatus -NotePropertyValue $status -Force
$manifest | Add-Member -NotePropertyName replayRecording -NotePropertyValue $recordingPath -Force
$manifest | Add-Member -NotePropertyName replayChecksumValidated -NotePropertyValue $true -Force
$manifest | ConvertTo-Json -Depth 8 | Set-Content -LiteralPath $manifestPath -Encoding utf8

$coordinatorArguments = @(
    $coordinator, '--recording', $recordingPath, '--recording-name', $recordingName,
    '--session', $session, '--request', $request, '--barrier', $barrier,
    '--ready-file', $ready, '--start-file', $startFile, '--trace', $trace,
    '--status', $status, '--gdb-port', [string]$GdbPort, '--qmp-port', [string]$QmpPort
)
$coordinatorArgumentString = (($coordinatorArguments | ForEach-Object {
    $value = [string]$_
    if ($value -match '[\s"]') { '"' + ($value -replace '(\\*)"', '$1$1\"' -replace '(\\+)$', '$1$1') + '"' }
    else { $value }
}) -join ' ')
$coordinatorProcess = Start-Process -FilePath 'python' -ArgumentList $coordinatorArgumentString `
    -WorkingDirectory $PSScriptRoot -WindowStyle Hidden `
    -RedirectStandardOutput (Join-Path $run 'coordinator.stdout.log') `
    -RedirectStandardError (Join-Path $run 'coordinator.stderr.log') -PassThru

& $matchScript -Session $session
Write-Output "DAHREC_WORKSTATION_READY session=$session coordinator_pid=$($coordinatorProcess.Id)"
Write-Output 'Navigate both games with the shared controller. Replay arms only at the recorded Farm checkpoint.'
Write-Output "STATUS $status"
