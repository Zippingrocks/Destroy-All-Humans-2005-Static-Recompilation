$ErrorActionPreference = 'Stop'
$cineVswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
$cineVs = & $cineVswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $cineVs) { throw 'Visual Studio C++ tools are required.' }
& (Join-Path $cineVs 'Common7\Tools\Launch-VsDevShell.ps1') -Arch amd64 -HostArch amd64 -SkipAutomaticLocation | Out-Null
$cineTestDir = Join-Path $env:TEMP ('dah-cinematic-observer-' + [Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $cineTestDir | Out-Null
$cineTestExe = Join-Path $cineTestDir 'observer.exe'
$cineTestObj = Join-Path $cineTestDir 'observer.obj'
& cl.exe /nologo /O2 /std:c11 /Gy /Gw "/Fo:$cineTestObj" "/Fe:$cineTestExe" (Join-Path $PSScriptRoot 'test_cinematic_state_native.c') /link /OPT:REF
if ($LASTEXITCODE -ne 0) { throw 'Cinematic observer fixture compilation failed.' }
& python.exe (Join-Path $PSScriptRoot 'test_cinematic_state_consistency.py') $cineTestExe
if ($LASTEXITCODE -ne 0) { throw 'Cinematic observer consistency failed.' }
