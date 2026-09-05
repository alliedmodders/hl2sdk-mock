#!/usr/bin/env pwsh

param(
    [Parameter(Position = 0, Mandatory = $true)]
    [string] $ObjDir
)

$sourceDir = Join-Path $ObjDir 'lib'
$destinationDir = 'lib'

if (-not (Test-Path -LiteralPath $sourceDir -PathType Container)) {
    throw "Library directory not found: $sourceDir"
}

New-Item -ItemType Directory -Path $destinationDir -Force | Out-Null
Get-ChildItem -LiteralPath $sourceDir -Force | ForEach-Object {
    Copy-Item -LiteralPath $_.FullName -Destination $destinationDir -Recurse -Force
}
