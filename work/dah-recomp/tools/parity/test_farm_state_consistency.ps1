$ErrorActionPreference = 'Stop'
$farmVswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
$farmVs = & $farmVswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $farmVs) { throw 'Visual Studio C++ tools are required.' }
& (Join-Path $farmVs 'Common7\Tools\Launch-VsDevShell.ps1') -Arch amd64 -HostArch amd64 -SkipAutomaticLocation
$farmTestDir = Join-Path $env:TEMP ('dah-farm-observer-' + [Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $farmTestDir | Out-Null
$farmTestExe = Join-Path $farmTestDir 'observer.exe'
$farmTestObj = Join-Path $farmTestDir 'observer.obj'
& cl.exe /nologo /O2 /std:c11 /Gy /Gw "/Fo:$farmTestObj" "/Fe:$farmTestExe" (Join-Path $PSScriptRoot 'test_farm_state_native.c') /link /OPT:REF
if ($LASTEXITCODE -ne 0) { throw 'Farm observer fixture compilation failed.' }
& python.exe (Join-Path $PSScriptRoot 'test_farm_state_consistency.py') --native $farmTestExe
if ($LASTEXITCODE -ne 0) { throw 'Farm observer field consistency failed.' }
