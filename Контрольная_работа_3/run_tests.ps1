$ErrorActionPreference = 'Stop'
$compiler = 'C:\msys64\ucrt64\bin\g++.exe'
$sourceRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$testRoot = Join-Path 'C:\Temp' ('codex-c03-' + [guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $testRoot | Out-Null

$sources = @(
    'task1_recursive_reverse.cpp',
    'task2_file_spaces.cpp',
    'task3_reformat_date.cpp'
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

$task1 = Join-Path $testRoot 'task1_recursive_reverse.exe'
Assert-Output 'task1 normal' (('recursion' | & $task1) -join "`n") 'noisrucer'
Assert-Output 'task1 empty' (('' | & $task1) -join "`n") ''

$task2 = Join-Path $testRoot 'task2_file_spaces.exe'
Push-Location $testRoot
Set-Content -LiteralPath 'input.txt' -Value "hello world`nsecond  line" -NoNewline -Encoding utf8
$task2Output = (& $task2) -join "`n"
Pop-Location
Assert-Output 'task2 spaces' $task2Output "hello_world`nsecond__line"

$task3 = Join-Path $testRoot 'task3_reformat_date.exe'
Assert-Output 'task3 leap day' (('29.02.2024' | & $task3) -join "`n") '2024-02-29'
Assert-Output 'task3 year boundary' (('01.01.2000' | & $task3) -join "`n") '2000-01-01'

Write-Output 'ALL C03 TESTS PASSED'
Write-Output "Temporary binaries: $testRoot"
