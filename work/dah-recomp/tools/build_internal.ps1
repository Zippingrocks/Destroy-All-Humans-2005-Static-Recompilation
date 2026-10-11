param([switch]$ConfigureOnly, [string]$Target)
$ErrorActionPreference = 'Stop'
$dahSource = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
if (!(Test-Path (Join-Path $dahSource 'CMakeLists.txt'))) { throw 'Place this script in the game tools directory.' }
$dahVswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
$dahVs = & $dahVswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (!$dahVs) { throw 'Install Visual Studio C++ Build Tools with the Windows SDK and CMake.' }
& (Join-Path $dahVs 'Common7\Tools\Launch-VsDevShell.ps1') -Arch amd64 -HostArch amd64 -SkipAutomaticLocation
$dahCmake = Join-Path $dahVs 'Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe'
$dahNinja = Join-Path $dahVs 'Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe'
$dahBuild = Join-Path $dahSource 'build-internal'
$dahCache = Join-Path $dahBuild 'CMakeCache.txt'
if (Test-Path $dahCache) {
    $dahStamp = Get-Date -Format 'yyyyMMdd-HHmmss'
    Copy-Item -LiteralPath $dahCache -Destination "$dahCache.$dahStamp.backup"
}
& $dahCmake --fresh -S $dahSource -B $dahBuild -G Ninja "-DCMAKE_MAKE_PROGRAM=$dahNinja" -DCMAKE_BUILD_TYPE=Release -DDAH_INTERNAL_BUILD=ON
if ($LASTEXITCODE -ne 0) { throw 'CMake configuration failed.' }
if (!$ConfigureOnly) {
    if ($Target) {
        & $dahCmake --build $dahBuild --parallel 4 --target $Target
    } else {
        & $dahCmake --build $dahBuild --parallel 4
    }
    if ($LASTEXITCODE -ne 0) { throw 'Game build failed.' }
}
