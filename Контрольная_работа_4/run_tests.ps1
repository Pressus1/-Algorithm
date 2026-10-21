$ErrorActionPreference = 'Stop'
$compiler = 'C:\msys64\ucrt64\bin\g++.exe'
$sourceRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$testRoot = Join-Path 'C:\Temp' ('codex-c04-' + [guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $testRoot | Out-Null

$sources = @(
    'task4_min_coins.cpp',
    'task5_unique_paths.cpp',
    'task6_max_subarray.cpp'
)

foreach ($source in $sources) {
    Copy-Item -LiteralPath (Join-Path $sourceRoot $source) -Destination $testRoot
    $stem = [System.IO.Path]::GetFileNameWithoutExtension($source)
    & $compiler -std=c++17 -Wall -Wextra -Werror -pedantic `
        (Join-Path $testRoot $source) -o (Join-Path $testRoot ($stem + '.exe'))
    if ($LASTEXITCODE -ne 0) {
        throw "Compilation failed for $source"
    }
    Write-Output "COMPILED $source"
}

function Assert-Output {
    param(
        [string]$Name,
        [string]$Actual,
        [string]$Expected
    )
    if ($Actual.TrimEnd() -cne $Expected.TrimEnd()) {
        throw "$Name failed. Expected [$Expected], got [$Actual]"
    }
    Write-Output "PASS $Name"
}

$task4 = Join-Path $testRoot 'task4_min_coins.exe'
Assert-Output 'task4 reachable' (("3 11`n1 5 7" | & $task4) -join "`n") '3'
Assert-Output 'task4 impossible' (("2 3`n2 4" | & $task4) -join "`n") '-1'
Assert-Output 'task4 zero amount' (("2 0`n2 4" | & $task4) -join "`n") '0'

$task5 = Join-Path $testRoot 'task5_unique_paths.exe'
Assert-Output 'task5 3x4' (('3 4' | & $task5) -join "`n") '10'
Assert-Output 'task5 one row' (('1 8' | & $task5) -join "`n") '1'
Assert-Output 'task5 large exact integer' (('20 20' | & $task5) -join "`n") '35345263800'

$task6 = Join-Path $testRoot 'task6_max_subarray.exe'
Assert-Output 'task6 mixed' (("9`n-2 1 -3 4 -1 2 1 -5 4" | & $task6) -join "`n") '6'
Assert-Output 'task6 all negative' (("4`n-8 -3 -6 -2" | & $task6) -join "`n") '-2'
Assert-Output 'task6 one element' (("1`n42" | & $task6) -join "`n") '42'

Write-Output 'ALL C04 TESTS PASSED'
Write-Output "Temporary binaries: $testRoot"
