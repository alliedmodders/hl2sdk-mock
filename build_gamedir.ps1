#!/usr/bin/env pwsh

param(
    [Parameter(Position = 0, Mandatory = $true)]
    [string] $GameDir,
    [Parameter(Position = 1, Mandatory = $true)]
    [string] $SourceDir
)

$sourceRoot = (Resolve-Path -LiteralPath $SourceDir -ErrorAction Stop).Path
$gameRoot = [System.IO.Path]::GetFullPath($GameDir)

New-Item -ItemType Directory -Path $gameRoot -Force | Out-Null

Get-ChildItem -LiteralPath $sourceRoot -Recurse -Force | ForEach-Object {
    $relativePath = $_.FullName.Substring($sourceRoot.Length).TrimStart('\', '/')
    $destination = Join-Path $gameRoot $relativePath

    if ($_.PSIsContainer) {
        New-Item -ItemType Directory -Path $destination -Force | Out-Null
    } elseif (-not (Test-Path -LiteralPath $destination -PathType Leaf) -and
              -not (Test-Path -LiteralPath $destination -PathType Container)) {
        $destinationParent = Split-Path -Parent $destination
        New-Item -ItemType Directory -Path $destinationParent -Force | Out-Null
        try {
            & cmd.exe /c mklink $destination $_.FullName | Out-Null
            if ($LASTEXITCODE -ne 0) {
                throw "mklink exited with code $LASTEXITCODE"
            }
        } catch {
            throw "Could not create symlink '$destination'. Enable Windows Developer Mode or run PowerShell as Administrator, then retry. $($_.Exception.Message)"
        }
    }
}
