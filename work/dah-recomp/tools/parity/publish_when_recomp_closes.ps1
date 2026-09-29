param(
    [Parameter(Mandatory = $true)][int]$TargetProcessId,
    [Parameter(Mandatory = $true)][string]$Source,
    [Parameter(Mandatory = $true)][string]$Destination,
    [Parameter(Mandatory = $true)][string]$LogPath
)

$ErrorActionPreference = 'Stop'
$sourcePath = [IO.Path]::GetFullPath($Source)
$destinationPath = [IO.Path]::GetFullPath($Destination)

while (Get-Process -Id $TargetProcessId -ErrorAction SilentlyContinue) {
    Start-Sleep -Seconds 2
}

for ($attempt = 1; $attempt -le 120; ++$attempt) {
    try {
        Copy-Item -LiteralPath $sourcePath -Destination $destinationPath -Force
        $hash = (Get-FileHash -LiteralPath $destinationPath -Algorithm SHA256).Hash
        "published=$([DateTime]::UtcNow.ToString('o')) sha256=$hash" |
            Set-Content -LiteralPath $LogPath -Encoding ascii
        exit 0
    } catch {
        if ($attempt -eq 120) {
            "failed=$([DateTime]::UtcNow.ToString('o')) message=$($_.Exception.Message)" |
                Set-Content -LiteralPath $LogPath -Encoding ascii
            exit 1
        }
        Start-Sleep -Seconds 1
    }
}
