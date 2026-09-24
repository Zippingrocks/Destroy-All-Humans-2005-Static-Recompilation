param(
    [ValidateRange(1, 3600)][int]$Seconds = 30,
    [ValidateRange(0, 128)][int]$CaptureCount = 8,
    [ValidateRange(1, 1000000)][int]$CaptureInterval = 30,
    [ValidateRange(0, 64)][int]$PushbufferCaptures = 4,
    [ValidateRange(0, 1000000)][int]$StartDelay = 6,
    [ValidateRange(0, 1000000)][int]$CaptureStart = 0,
    [switch]$NonblockingMovie,
    [switch]$EnterMenu,
    [switch]$ForceUiRender,
    [switch]$ForceUiChild,
    [switch]$MatrixTrace,
    [switch]$Watchdog,
    [ValidateRange(1, 1000000)][int]$MenuStartDelay = 1050
)
$ErrorActionPreference = 'Stop'
$dahInternal = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\build-internal'))
$dahExecutable = Join-Path $dahInternal 'DestroyAllHumans.exe'
if (!(Test-Path -LiteralPath $dahExecutable)) { throw 'Build build-internal first.' }
$dahExisting = Get-Process -Name DestroyAllHumans -ErrorAction SilentlyContinue |
    Where-Object { $_.Path -eq $dahExecutable }
if ($dahExisting) { throw "An internal test is already running: $($dahExisting.Id -join ', ')" }

# The executable resolves its own directory. Data, saves and diagnostics are
# independent of build-ninja. Hidden mode disables desktop/input/audio effects.
# Configure only the child's inherited environment. Running this script in
# an existing shell must not make the user's next launch hidden or scripted.
$dahStartInfo = New-Object System.Diagnostics.ProcessStartInfo
$dahStartInfo.FileName = $dahExecutable
$dahStartInfo.WorkingDirectory = $dahInternal
$dahStartInfo.UseShellExecute = $false
$dahStartInfo.CreateNoWindow = $true
$dahStartInfo.WindowStyle = [Diagnostics.ProcessWindowStyle]::Hidden
$dahChildSettings = @{
    DAH_INTERNAL_RUN = '1'
    DAH_FPS = '30'
    DAH_HOST_FRAME = '0'
    DAH_MOVIE_NONBLOCK = $(if ($NonblockingMovie) { '1' } else { '0' })
    DAH_DIAGNOSTIC_OVERLAY = '0'
    DAH_AUTOSTART = '1'
    DAH_AUTOSTART_DELAY = [string]$StartDelay
    DAH_FRAME_CAPTURE = [string]$CaptureCount
    DAH_FRAME_CAPTURE_INTERVAL = [string]$CaptureInterval
    DAH_FRAME_CAPTURE_START = [string]$CaptureStart
    DAH_PB_CAPTURE = [string]$PushbufferCaptures
    DAH_WATCHDOG = $(if ($Watchdog) { '1' } else { '0' })
    DAH_KPCR_WATCH = '0'
}
foreach ($dahSetting in $dahChildSettings.Keys) {
    $dahStartInfo.EnvironmentVariables[$dahSetting] = $dahChildSettings[$dahSetting]
}
foreach ($dahDisabledSetting in @('DAH_FORCE_UI_RENDER', 'DAH_FORCE_UI_CHILD', 'DAH_MATRIX_TRACE', 'DAH_AUTOSTART2', 'DAH_AUTOA')) {
    $dahStartInfo.EnvironmentVariables.Remove($dahDisabledSetting)
}
if ($ForceUiRender) { $dahStartInfo.EnvironmentVariables['DAH_FORCE_UI_RENDER'] = '1' }
if ($ForceUiChild) { $dahStartInfo.EnvironmentVariables['DAH_FORCE_UI_CHILD'] = '1' }
if ($MatrixTrace) { $dahStartInfo.EnvironmentVariables['DAH_MATRIX_TRACE'] = '1' }
if ($EnterMenu) {
    # A logical-pad START only, after the title has had time to load. Never
    # send desktop/controller input or select a gameplay/save menu item.
    $dahStartInfo.EnvironmentVariables['DAH_AUTOSTART2'] = '1'
    $dahStartInfo.EnvironmentVariables['DAH_AUTOSTART2_DELAY'] = [string]$MenuStartDelay
}

$dahLaunchTime = [DateTime]::UtcNow
$dahRun = [Diagnostics.Process]::Start($dahStartInfo)
$dahExitFailure = $null
Write-Output "INTERNAL_START pid=$($dahRun.Id) seconds=$Seconds path=$dahExecutable"
try {
    $dahDeadline = [DateTime]::UtcNow.AddSeconds($Seconds)
    while ([DateTime]::UtcNow -lt $dahDeadline -and !$dahRun.HasExited) {
        Start-Sleep -Seconds 1
        $dahRun.Refresh()
    }
    if ($dahRun.HasExited) {
        Write-Output "INTERNAL_EXIT pid=$($dahRun.Id) code=$($dahRun.ExitCode)"
        if ($dahRun.ExitCode -ne 0) { $dahExitFailure = $dahRun.ExitCode }
    } else {
        Write-Output "INTERNAL_BOUND_REACHED pid=$($dahRun.Id) cpu=$($dahRun.CPU)"
    }
} finally {
    $dahRun.Refresh()
    if (!$dahRun.HasExited) {
        # Stop only the Process object created by this invocation.
        $dahRun.Kill()
        $dahRun.WaitForExit()
    }
    $dahLogSource = if ($env:DAH_LOG_PATH) { $env:DAH_LOG_PATH } else { Join-Path $dahInternal 'recomp.log' }
    $dahArchive = Join-Path ([IO.Path]::GetDirectoryName($dahLogSource)) "recomp-internal-$($dahRun.Id).log"
    if (Test-Path -LiteralPath $dahLogSource) {
        Copy-Item -LiteralPath $dahLogSource -Destination $dahArchive
        Write-Output "INTERNAL_LOG $dahArchive"
    }
    $dahCrashSource = Join-Path $dahInternal 'recomp_crash.log'
    if ((Test-Path -LiteralPath $dahCrashSource) -and
        (Get-Item -LiteralPath $dahCrashSource).LastWriteTimeUtc -ge $dahLaunchTime) {
        $dahCrashArchive = Join-Path $dahInternal "recomp-crash-$($dahRun.Id).log"
        Copy-Item -LiteralPath $dahCrashSource -Destination $dahCrashArchive
        Write-Output "INTERNAL_CRASH_LOG $dahCrashArchive"
    }
}
if ($null -ne $dahExitFailure) { throw "Internal game process exited with code $dahExitFailure; see its archived logs." }
