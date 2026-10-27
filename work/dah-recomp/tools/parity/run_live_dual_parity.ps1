param(
    [ValidateRange(1024, 65535)][int]$GdbPort = 1236,
    [ValidateRange(1024, 65535)][int]$QmpPort = 4446,
    [string]$ReplayRequest,
    [string]$ReplayBarrier,
    [switch]$SkipWindowLayout,
    [switch]$SkipWatchers,
    [switch]$Start
)
$ErrorActionPreference = 'Stop'
Import-Module 'C:\Windows\System32\WindowsPowerShell\v1.0\Modules\Microsoft.PowerShell.Utility\Microsoft.PowerShell.Utility.psd1' -Force
if ([bool]$ReplayRequest -ne [bool]$ReplayBarrier) {
    throw 'ReplayRequest and ReplayBarrier must be supplied together'
}

$xemuSource = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\xemu-previous.exe'
$bootrom = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\Boot ROM image\mcpx_1.0.bin'
$bios = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\BIOS\Complex_4627v1.03.bin'
$hdd = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\Xemu Halo 2 E3 2003 Map Test 8-8-26\xbox_hdd.qcow2'
$xbe = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\ROMs\Destroy All Humans! (USA).xiso\default.xbe'
$xiso = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\ROMs\Destroy All Humans! (USA).xiso.iso'
$sourceEeprom = 'C:\Users\Bilbo\AppData\Roaming\xemu\xemu\eeprom.bin'
$userConfig = 'C:\Users\Bilbo\AppData\Roaming\xemu\xemu\xemu.toml'
$expectedXbeHash = 'B9491B30EAEE82AF6C805D9B0036EC1119059B0660A0923803EBDB6219FA02EB'
$expectedXisoHash = 'DA61C36C235EAB4111DD540FB237EAC01DB5B2138451FA422B74E6AA9147C9B5'
$expectedXemuHash = '7DA537938EA2AC09F894186BA793C9AE51DFF37C95903B0002273B8D363818B7'

$workspace = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..\..\..'))
$recomp = Join-Path $workspace 'DestroyAllHumans.exe'
$runtime = Join-Path ([IO.Path]::GetTempPath()) 'DAH1-live-parity'
$privateXemu = Join-Path $runtime 'xemu.exe'
$template = Join-Path $PSScriptRoot 'xemu-live-parity.toml'
$isolatedConfig = Join-Path $runtime 'xemu.toml'
$isolatedEeprom = Join-Path $runtime 'eeprom.bin'
$stdoutLog = Join-Path $runtime 'xemu.stdout.log'
$stderrLog = Join-Path $runtime 'xemu.stderr.log'
$launchStamp = [DateTime]::UtcNow.ToString('yyyyMMddTHHmmssfffZ')
$nativeLog = Join-Path $runtime "native-live-$launchStamp.log"

foreach ($required in @($xemuSource, $recomp, $bootrom, $bios, $hdd, $xbe, $xiso, $sourceEeprom, $userConfig, $template)) {
    if (!(Test-Path -LiteralPath $required)) { throw "Missing live-parity dependency: $required" }
}

$actualXbeHash = (Get-FileHash -LiteralPath $xbe -Algorithm SHA256).Hash
$actualXisoHash = (Get-FileHash -LiteralPath $xiso -Algorithm SHA256).Hash
$actualXemuHash = (Get-FileHash -LiteralPath $xemuSource -Algorithm SHA256).Hash
if ($actualXbeHash -ne $expectedXbeHash) {
    throw "Refusing mismatched XBE: expected $expectedXbeHash, got $actualXbeHash"
}
if ($actualXisoHash -ne $expectedXisoHash) {
    throw "Refusing mismatched XISO: expected $expectedXisoHash, got $actualXisoHash"
}
if ($actualXemuHash -ne $expectedXemuHash) {
    throw "Refusing unreviewed xemu executable: expected $expectedXemuHash, got $actualXemuHash"
}

$userConfigText = Get-Content -LiteralPath $userConfig -Raw
$controllerMatch = [regex]::Match($userConfigText, '(?m)^\s*port1\s*=\s*[''\"]([0-9A-Za-z]+)[''\"]\s*$')
if (!$controllerMatch.Success) {
    throw 'No physical xemu port1 controller binding was found in the normal xemu config'
}
$controllerId = $controllerMatch.Groups[1].Value

foreach ($port in @($GdbPort, $QmpPort)) {
    if (Get-NetTCPConnection -State Listen -LocalPort $port -ErrorAction SilentlyContinue) {
        throw "TCP port $port is already in use"
    }
}

$arguments = @(
    '-config_path', $isolatedConfig,
    '-snapshot',
    '-net', 'none',
    '-gdb', "tcp:127.0.0.1:$GdbPort",
    '-qmp', "tcp:127.0.0.1:$QmpPort,server=on,wait=off"
)

Write-Output "REFERENCE_XBE_SHA256 $actualXbeHash"
Write-Output "REFERENCE_XISO_SHA256 $actualXisoHash"
Write-Output "XEMU_SHA256 $actualXemuHash"
Write-Output "CONTROLLER $controllerId"
Write-Output 'INPUT_MODE one physical controller; native XInput plus xemu background capture'
Write-Output 'LIMITATION live physical input is not frame-scheduled; use scripted replay for proof'
Write-Output "RECOMP $recomp"
Write-Output "XEMU_SOURCE $xemuSource"
Write-Output "XEMU_PRIVATE $privateXemu"
Write-Output "GDB 127.0.0.1:$GdbPort"
Write-Output "QMP 127.0.0.1:$QmpPort"
if (!$Start) {
    Write-Output 'DRY_RUN_ONLY pass -Start to launch both visible instances'
    return
}

New-Item -ItemType Directory -Path $runtime -Force | Out-Null
Copy-Item -LiteralPath $xemuSource -Destination $privateXemu -Force
if ((Get-FileHash -LiteralPath $privateXemu -Algorithm SHA256).Hash -ne $expectedXemuHash) {
    throw 'Private xemu copy failed hash verification'
}
Copy-Item -LiteralPath $sourceEeprom -Destination $isolatedEeprom -Force
$configText = Get-Content -LiteralPath $template -Raw
$configText = $configText.Replace('__CONTROLLER_ID__', $controllerId)
$configText = $configText.Replace('__EEPROM_PATH__', $isolatedEeprom)
Set-Content -LiteralPath $isolatedConfig -Value $configText -Encoding utf8

$argumentString = (($arguments | ForEach-Object {
    if ($_ -match '[\s"]') { '"' + ($_ -replace '(\\*)"', '$1$1\"' -replace '(\\+)$', '$1$1') + '"' }
    else { $_ }
}) -join ' ')

$previousAppData = $env:APPDATA
try {
    $env:APPDATA = $runtime
    $xemuProcess = Start-Process -FilePath $privateXemu -ArgumentList $argumentString `
        -WorkingDirectory $runtime `
        -RedirectStandardOutput $stdoutLog -RedirectStandardError $stderrLog -PassThru
} finally {
    $env:APPDATA = $previousAppData
}

$existingRecomp = Get-Process -Name 'DestroyAllHumans' -ErrorAction SilentlyContinue |
    Where-Object { $_.MainWindowHandle -ne 0 } |
    Select-Object -First 1
if ($existingRecomp -and $ReplayRequest) {
    throw 'A coordinated replay requires a fresh recomp process with its request channel configured'
}
$recompProcess = if ($existingRecomp) {
    $existingRecomp
} else {
    $previousParityInput = $env:DAH_PARITY_BACKGROUND_INPUT
    $previousPhaseControl = $env:DAH_PARITY_PHASE_CONTROL
    $previousInputTrace = $env:DAH_INPUT_TRACE
    $previousLogPath = $env:DAH_LOG_PATH
    $previousReplayRequest = $env:DAH_PLAYER_REPLAY_REQUEST
    $previousReplayBarrier = $env:DAH_PLAYER_REPLAY_BARRIER
    try {
        $env:DAH_PARITY_BACKGROUND_INPUT = '1'
        $env:DAH_PARITY_PHASE_CONTROL = '1'
        $env:DAH_INPUT_TRACE = '1'
        $env:DAH_LOG_PATH = $nativeLog
        if ($ReplayRequest) {
            $env:DAH_PLAYER_REPLAY_REQUEST = [IO.Path]::GetFullPath($ReplayRequest)
            $env:DAH_PLAYER_REPLAY_BARRIER = [IO.Path]::GetFullPath($ReplayBarrier)
        }
        Start-Process -FilePath $recomp -WorkingDirectory $workspace -PassThru
    } finally {
        $env:DAH_PARITY_BACKGROUND_INPUT = $previousParityInput
        $env:DAH_PARITY_PHASE_CONTROL = $previousPhaseControl
        $env:DAH_INPUT_TRACE = $previousInputTrace
        $env:DAH_LOG_PATH = $previousLogPath
        $env:DAH_PLAYER_REPLAY_REQUEST = $previousReplayRequest
        $env:DAH_PLAYER_REPLAY_BARRIER = $previousReplayBarrier
    }
}

$xemuOwnerPid = $null
$deadline = [DateTime]::UtcNow.AddSeconds(20)
do {
    $listener = Get-NetTCPConnection -State Listen -LocalPort $GdbPort -ErrorAction SilentlyContinue |
        Select-Object -First 1
    if ($listener) {
        $xemuOwnerPid = $listener.OwningProcess
        break
    }
    Start-Sleep -Milliseconds 250
} while ([DateTime]::UtcNow -lt $deadline)

if (!$xemuOwnerPid) {
    $exitDetail = if ($xemuProcess.HasExited) { "exited with code $($xemuProcess.ExitCode)" } else { 'remained alive without opening GDB' }
    $stderrText = if (Test-Path -LiteralPath $stderrLog) { Get-Content -LiteralPath $stderrLog -Raw } else { '' }
    throw "Live parity xemu $exitDetail. $stderrText"
}
$liveXemu = Get-Process -Id $xemuOwnerPid -ErrorAction Stop
if ([IO.Path]::GetFullPath($liveXemu.Path) -ne [IO.Path]::GetFullPath($privateXemu)) {
    throw "GDB port $GdbPort belongs to unexpected executable: $($liveXemu.Path)"
}
if ($recompProcess.HasExited) {
    throw "DAH1 recomp exited with code $($recompProcess.ExitCode)"
}

if (!$SkipWindowLayout) {
    $layoutTool = Join-Path $PSScriptRoot 'normalize_live_windows.py'
    & python $layoutTool --reference-pid $xemuOwnerPid --native-pid $recompProcess.Id
    if ($LASTEXITCODE -ne 0) { throw 'Unable to establish equal 640x480 client areas.' }
}

Write-Output "LIVE_PARITY_READY xemu_pid=$xemuOwnerPid recomp_pid=$($recompProcess.Id)"
if ($existingRecomp) {
    Write-Output 'INPUT_WARNING existing recomp reused; background-input parity mode cannot be verified until it is relaunched by this script.'
} else {
    Write-Output 'Both games receive controller 1 even when only one window has focus.'
}
Write-Output "NATIVE_LOG $nativeLog"
if (!$SkipWatchers) {
    & (Join-Path $PSScriptRoot 'start_live_dual_watch.ps1') `
        -XemuPid $xemuOwnerPid -NativePid $recompProcess.Id
    if ($LASTEXITCODE -ne 0) { throw 'Unable to start live parity watchers.' }
}
Write-Output ("REFERENCE_STOP Stop-Process -Id {0}" -f $xemuOwnerPid)
