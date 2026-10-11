param(
    [string]$BuildDirectory = "build-ninja",
    [string]$Target = "DestroyAllHumans",
    [switch]$Configure
)

$ErrorActionPreference = 'Stop'
$dahSource = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$dahVswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
if (!(Test-Path -LiteralPath $dahVswhere)) {
    throw 'Visual Studio Installer (vswhere.exe) was not found.'
}
$dahVs = & $dahVswhere -latest -products '*' `
    -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
    -requires Microsoft.VisualStudio.Component.Windows11SDK.26100 `
    -property installationPath
if (!$dahVs) {
    # Accept another installed Windows 10/11 SDK version; the file checks below
    # still prove that the selected developer environment is complete.
    $dahVs = & $dahVswhere -latest -products '*' `
        -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
        -property installationPath
}
if (!$dahVs) {
    throw 'Install Visual Studio C++ Build Tools and a Windows 10/11 SDK.'
}

& (Join-Path $dahVs 'Common7\Tools\Launch-VsDevShell.ps1') `
    -Arch amd64 -HostArch amd64 -SkipAutomaticLocation

$dahStdint = $env:INCLUDE -split ';' | Where-Object {
    $_ -and (Test-Path -LiteralPath (Join-Path $_ 'stdint.h'))
} | Select-Object -First 1
$dahD3D11 = $env:LIB -split ';' | Where-Object {
    $_ -and (Test-Path -LiteralPath (Join-Path $_ 'd3d11.lib'))
} | Select-Object -First 1
if (!$dahStdint) { throw 'MSVC stdint.h was not found after loading VsDevShell.' }
if (!$dahD3D11) { throw 'Windows SDK d3d11.lib was not found after loading VsDevShell.' }

$dahCmake = Join-Path $dahVs 'Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe'
$dahNinja = Join-Path $dahVs 'Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe'
$dahBuild = [IO.Path]::GetFullPath((Join-Path $dahSource $BuildDirectory))
$dahCache = Join-Path $dahBuild 'CMakeCache.txt'
if ($Configure -or !(Test-Path -LiteralPath $dahCache)) {
    & $dahCmake -S $dahSource -B $dahBuild -G Ninja `
        "-DCMAKE_MAKE_PROGRAM=$dahNinja" -DCMAKE_BUILD_TYPE=Release
    if ($LASTEXITCODE -ne 0) { throw 'CMake configuration failed.' }
}
& $dahCmake --build $dahBuild --parallel 4 --target $Target
if ($LASTEXITCODE -ne 0) { throw 'Release build failed.' }
