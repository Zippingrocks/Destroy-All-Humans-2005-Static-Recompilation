param(
    [string]$OutputDirectory = "dist"
)

$ErrorActionPreference = 'Stop'
$dahSource = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$dahOutput = [IO.Path]::GetFullPath((Join-Path $dahSource $OutputDirectory))
$dahNormalStage = Join-Path $dahOutput 'Destroy-All-Humans-Recomp-Normal'
$dahReporterStage = Join-Path $dahOutput 'Destroy-All-Humans-Recomp-Debug-Reporter'

& (Join-Path $PSScriptRoot 'build_release.ps1') -Configure
if ($LASTEXITCODE -ne 0) { throw 'Normal release build failed.' }
& (Join-Path $PSScriptRoot 'build_release.ps1') `
    -BuildDirectory 'build-reporter' -Reporter -Configure
if ($LASTEXITCODE -ne 0) { throw 'Debug-Reporter release build failed.' }

& python (Join-Path $PSScriptRoot 'test_reporting_separation.py') `
    --normal (Join-Path $dahSource 'build-ninja\dah_recomp_working.exe') `
    --reporter (Join-Path $dahSource 'build-reporter\dah_recomp_debug_reporter.exe')
if ($LASTEXITCODE -ne 0) { throw 'Reporter privacy separation test failed.' }

if (Test-Path -LiteralPath $dahOutput) {
    Remove-Item -LiteralPath $dahOutput -Recurse -Force
}
New-Item -ItemType Directory -Force -Path $dahNormalStage | Out-Null
New-Item -ItemType Directory -Force -Path $dahReporterStage | Out-Null

Copy-Item -LiteralPath (Join-Path $dahSource 'build-ninja\dah_recomp_working.exe') `
    -Destination (Join-Path $dahNormalStage 'DestroyAllHumans.exe')
Copy-Item -LiteralPath (Join-Path $dahSource 'build-reporter\dah_recomp_debug_reporter.exe') `
    -Destination (Join-Path $dahReporterStage 'DestroyAllHumans.exe')
Copy-Item -LiteralPath (Join-Path $dahSource 'docs\PUBLIC_REPORTING.md') `
    -Destination (Join-Path $dahReporterStage 'REPORTING.md')

$dahNormalNotice = @'
Destroy All Humans! Recomp — Normal release

This build has no public bug-reporting or telemetry feature compiled into it.
It performs no reporting network requests. Supply legally obtained game data
as described in the project README.
'@
$dahNormalNotice | Set-Content -LiteralPath (Join-Path $dahNormalStage 'README.txt')

$dahReporterNotice = @'
Destroy All Humans! Recomp — Debug-Reporter release

This build offers optional, privacy-safe reporting on first launch. Reporting
is disabled unless you choose Yes. See REPORTING.md for the exact allowlist and
the console commands that change your choice.
'@
$dahReporterNotice | Set-Content -LiteralPath (Join-Path $dahReporterStage 'README.txt')

Compress-Archive -Path (Join-Path $dahNormalStage '*') `
    -DestinationPath (Join-Path $dahOutput 'Destroy-All-Humans-Recomp-Normal.zip') -Force
Compress-Archive -Path (Join-Path $dahReporterStage '*') `
    -DestinationPath (Join-Path $dahOutput 'Destroy-All-Humans-Recomp-Debug-Reporter.zip') -Force

Write-Output "NORMAL_RELEASE $(Join-Path $dahOutput 'Destroy-All-Humans-Recomp-Normal.zip')"
Write-Output "DEBUG_REPORTER_RELEASE $(Join-Path $dahOutput 'Destroy-All-Humans-Recomp-Debug-Reporter.zip')"
