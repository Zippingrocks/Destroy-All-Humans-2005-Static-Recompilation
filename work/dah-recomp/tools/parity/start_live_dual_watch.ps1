param(
    [Parameter(Mandatory)][int]$XemuPid,
    [Parameter(Mandatory)][int]$NativePid,
    [ValidateRange(1,120)][double]$StateHz = 20,
    [ValidateRange(0.1,30)][double]$VisualHz = 1,
    [ValidateRange(0.1,30)][double]$BurstVisualHz = 4,
    [ValidateRange(0,30)][double]$VisualBurstSeconds = 2,
    [ValidateRange(1,50)][int]$MaxVisualIncidents = 8,
    [ValidateRange(60,2000)][double]$PhaseHz = 500,
    [ValidateRange(1,30)][double]$PhaseWindowSeconds = 5
)
$ErrorActionPreference = 'Stop'
Import-Module 'C:\Windows\System32\WindowsPowerShell\v1.0\Modules\Microsoft.PowerShell.Utility\Microsoft.PowerShell.Utility.psd1' -Force
if ($BurstVisualHz -lt $VisualHz) {
    throw 'BurstVisualHz must be greater than or equal to VisualHz'
}

$xemu = Get-Process -Id $XemuPid -ErrorAction Stop
$native = Get-Process -Id $NativePid -ErrorAction Stop
if ($xemu.ProcessName -ne 'xemu') { throw "PID $XemuPid is not xemu" }
if ($native.ProcessName -ne 'DestroyAllHumans') { throw "PID $NativePid is not DestroyAllHumans" }

$workspace = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..\..\..'))
$expectedNative = [IO.Path]::GetFullPath((Join-Path $workspace 'DestroyAllHumans.exe'))
$nativePath = [IO.Path]::GetFullPath($native.Path)
if ($nativePath -ne $expectedNative) {
    throw "Refusing a non-root recomp executable: $nativePath"
}
$rootExecutables = @(Get-ChildItem -LiteralPath $workspace -File -Filter '*.exe')
if ($rootExecutables.Count -ne 1 -or $rootExecutables[0].Name -ne 'DestroyAllHumans.exe') {
    throw 'Exact parity requires exactly one root executable named DestroyAllHumans.exe'
}
$expectedXemuHash = '7DA537938EA2AC09F894186BA793C9AE51DFF37C95903B0002273B8D363818B7'
$xemuHash = (Get-FileHash -LiteralPath $xemu.Path -Algorithm SHA256).Hash
if ($xemuHash -ne $expectedXemuHash) {
    throw "Refusing unreviewed xemu executable: expected $expectedXemuHash, got $xemuHash"
}
$nativeHash = (Get-FileHash -LiteralPath $nativePath -Algorithm SHA256).Hash

$xbe = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\ROMs\Destroy All Humans! (USA).xiso\default.xbe'
$expectedXbeHash = 'B9491B30EAEE82AF6C805D9B0036EC1119059B0660A0923803EBDB6219FA02EB'
if (!(Test-Path -LiteralPath $xbe)) { throw "Missing retail XBE: $xbe" }
$actualXbeHash = (Get-FileHash -LiteralPath $xbe -Algorithm SHA256).Hash
if ($actualXbeHash -ne $expectedXbeHash) {
    throw "Refusing mismatched XBE: expected $expectedXbeHash, got $actualXbeHash"
}

$stamp = [DateTime]::UtcNow.ToString('yyyyMMddTHHmmssfffZ')
$root = Join-Path ([IO.Path]::GetTempPath()) "DAH1-live-parity\watches\$stamp"
$visualRoot = Join-Path $root 'visual'
$stateLog = Join-Path $root 'dual-state.jsonl'
$stateStatus = Join-Path $root 'current-alignment.json'
$phaseLog = Join-Path $root 'dual-phase.jsonl'
$phaseStatus = Join-Path $root 'current-phase.json'
New-Item -ItemType Directory -Path $visualRoot -Force | Out-Null

$stateTool = Join-Path $PSScriptRoot 'live_dual_state_watch.py'
$visualTool = Join-Path $PSScriptRoot 'live_visual_parity_watch.py'
$stateArguments = '"' + $stateTool + '" --xemu-pid ' + $XemuPid +
    ' --native-pid ' + $NativePid + ' --xbe "' + $xbe + '" --out "' +
    $stateLog + '" --status-out "' + $stateStatus + '" --hz ' + ([string]$StateHz)
$stateProcess = Start-Process -FilePath 'python' -ArgumentList $stateArguments `
    -WindowStyle Hidden -RedirectStandardOutput (Join-Path $root 'state.stdout.log') `
    -RedirectStandardError (Join-Path $root 'state.stderr.log') -PassThru

$visualArguments = '"' + $visualTool + '" --reference-pid ' + $XemuPid +
    ' --native-pid ' + $NativePid + ' --out-dir "' + $visualRoot +
    '" --state-log "' + $stateLog + '" --state-status "' + $stateStatus +
    '" --phase-status "' + $phaseStatus +
    '" --hz ' + ([string]$VisualHz) + ' --burst-hz ' + ([string]$BurstVisualHz) +
    ' --burst-seconds ' + ([string]$VisualBurstSeconds) +
    ' --max-incidents ' + $MaxVisualIncidents
$visualProcess = Start-Process -FilePath 'python' -ArgumentList $visualArguments `
    -WindowStyle Hidden -RedirectStandardOutput (Join-Path $root 'visual.stdout.log') `
    -RedirectStandardError (Join-Path $root 'visual.stderr.log') -PassThru

$phaseTool = Join-Path $PSScriptRoot 'live_dual_phase_watch.py'
$phaseArguments = '"' + $phaseTool + '" --xemu-pid ' + $XemuPid +
    ' --native-pid ' + $NativePid + ' --xbe "' + $xbe + '" --out "' +
    $phaseLog + '" --state-status "' + $stateStatus + '" --hz ' + ([string]$PhaseHz) +
    ' --window-seconds ' + ([string]$PhaseWindowSeconds) +
    ' --status-out "' + $phaseStatus + '"'
$phaseProcess = Start-Process -FilePath 'python' -ArgumentList $phaseArguments `
    -WindowStyle Hidden -RedirectStandardOutput (Join-Path $root 'phase.stdout.log') `
    -RedirectStandardError (Join-Path $root 'phase.stderr.log') -PassThru

$manifest = [ordered]@{
    schema = 1
    startedAt = [DateTime]::UtcNow.ToString('o')
    xemuPid = $XemuPid
    nativePid = $NativePid
    stateWatcherPid = $stateProcess.Id
    visualWatcherPid = $visualProcess.Id
    phaseWatcherPid = $phaseProcess.Id
    stateHz = $StateHz
    visualHz = $VisualHz
    burstVisualHz = $BurstVisualHz
    visualBurstSeconds = $VisualBurstSeconds
    maxVisualIncidents = $MaxVisualIncidents
    phaseHz = $PhaseHz
    phaseWindowSeconds = $PhaseWindowSeconds
    xemuPath = $xemu.Path
    xemuSha256 = $xemuHash
    nativePath = $nativePath
    nativeSha256 = $nativeHash
    xbeSha256 = $actualXbeHash
    root = $root
    stateLog = $stateLog
    stateStatus = $stateStatus
    phaseLog = $phaseLog
    phaseStatus = $phaseStatus
    visualLog = (Join-Path $visualRoot 'visual-incidents.jsonl')
    retention = 'temporary; compact state incidents plus bounded deduplicated visual evidence'
}
$manifest | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $root 'manifest.json') -Encoding utf8
$manifest | ConvertTo-Json
