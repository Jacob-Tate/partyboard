<#
.SYNOPSIS
    Cross-machine determinism test for Party Board.

.DESCRIPTION
    Plays the same seeded all-CPU game on each board and compares every frame's checksum
    against reference logs recorded on another PC with the same build. Any difference means
    the two machines would desync in online play.

    Results go to .\results\<timestamp>\. Zip that folder and send it back if anything fails.

.EXAMPLE
    powershell -ExecutionPolicy Bypass -File determinism-test.ps1 -Iso "D:\Games\Mario Party 4 (USA) (Rev 1).rvz"
#>
param(
    [Parameter(Mandatory = $true)][string]$Iso,
    [int[]]$Boards = @(0, 1, 2, 3, 4, 5),
    # These must match the settings the reference logs were recorded with.
    [int]$Turns = 3,
    [int]$Seed = 1234,
    [int]$CpuLevel = 1,
    [int]$HangSeconds = 60,
    [int]$TimeoutSeconds = 900
)

$ErrorActionPreference = 'Stop'
$here = Split-Path -Parent $MyInvocation.MyCommand.Path
$exe = Join-Path $here 'partyboard.exe'
$refDir = Join-Path $here 'reference'
$outDir = Join-Path $here ('results\' + (Get-Date -Format 'yyyyMMdd-HHmmss'))
$boardNames = @("Toad's Midway Madness", "Goomba's Greedy Gala", "Shy Guy's Jungle Jam",
                "Boo's Haunted Bash", "Koopa's Seaside Soiree", "Bowser's Gnarly Party")

if (-not (Test-Path $exe)) { throw "partyboard.exe not found next to this script ($here)" }
if (-not (Test-Path -LiteralPath $Iso)) { throw "Disc image not found: $Iso" }
New-Item -ItemType Directory -Force -Path $outDir | Out-Null

function Read-Checksums([string]$path) {
    # Frame lines only; '#' lines are comments (overlay changes, game end markers).
    $rows = New-Object System.Collections.Generic.List[string]
    if (Test-Path $path) {
        foreach ($line in [System.IO.File]::ReadLines($path)) {
            if ($line.Length -gt 0 -and $line[0] -ne '#') { $rows.Add($line) }
        }
    }
    return ,$rows
}

$summary = @()
foreach ($b in $Boards) {
    $name = $boardNames[$b]
    $log = Join-Path $outDir "board$b.checksums"
    $stdout = Join-Path $outDir "board$b.stdout.txt"
    Write-Host ("Board {0} ({1}): playing {2} turns..." -f $b, $name, $Turns) -NoNewline

    $argList = @('--quickstart', '--board', $b, '--turns', $Turns, '--seed', $Seed, '--cpu-level', $CpuLevel,
                 '--fast', '--iso', "`"$Iso`"", '--checksum-log', "`"$log`"",
                 '--config-dir', "`"$(Join-Path $outDir "board$b.config")`"")
    $proc = Start-Process -FilePath $exe -ArgumentList $argList -WorkingDirectory $here -PassThru `
        -RedirectStandardOutput $stdout -RedirectStandardError "$stdout.err"
    # Windows PowerShell 5.1 only records ExitCode if the handle is opened while the process runs.
    $null = $proc.Handle

    $start = Get-Date; $lastSize = -1; $lastGrowth = Get-Date; $status = 'ok'
    while (-not $proc.HasExited) {
        Start-Sleep -Milliseconds 500
        $size = if (Test-Path $log) { (Get-Item $log).Length } else { 0 }
        if ($size -ne $lastSize) { $lastSize = $size; $lastGrowth = Get-Date }
        elseif (((Get-Date) - $lastGrowth).TotalSeconds -gt $HangSeconds) { $status = 'hang'; break }
        if (((Get-Date) - $start).TotalSeconds -gt $TimeoutSeconds) { $status = 'timeout'; break }
    }
    if (-not $proc.HasExited) { $proc.Kill(); $proc.WaitForExit() }
    else {
        $proc.WaitForExit()
        if ($proc.ExitCode -ne 0) { $status = "crash (exit $($proc.ExitCode))" }
    }
    $secs = [int]((Get-Date) - $start).TotalSeconds

    $mine = Read-Checksums $log
    $ref = Read-Checksums (Join-Path $refDir "board$b.checksums")
    $result = ''
    if ($ref.Count -eq 0) {
        $result = 'NO REFERENCE LOG'
    } else {
        $n = [Math]::Min($mine.Count, $ref.Count)
        $diffAt = -1
        for ($i = 0; $i -lt $n; $i++) {
            if ($mine[$i] -ne $ref[$i]) { $diffAt = $i; break }
        }
        if ($diffAt -ge 0) {
            $result = "MISMATCH at frame $($mine[$diffAt].Split(' ')[0])`n      this PC:  $($mine[$diffAt])`n      ref PC:   $($ref[$diffAt])"
        } elseif ($mine.Count -ne $ref.Count) {
            $result = "MISMATCH: this PC stopped at $($mine.Count) frames, reference has $($ref.Count)"
        } else {
            $result = "MATCH ($($mine.Count) frames)"
        }
    }
    Write-Host (" {0}, {1}s - {2}" -f $status, $secs, $result)
    $summary += "board $b ($name): $status, $secs s - $result"
}

$summaryPath = Join-Path $outDir 'summary.txt'
$summary | Set-Content -Path $summaryPath
Write-Host ''
Write-Host "Summary written to $summaryPath"
if ($summary -match 'MISMATCH|crash|hang|timeout|NO REFERENCE') {
    Write-Host 'Some boards did not match. Zip this folder and send it back:' -ForegroundColor Yellow
    Write-Host "  $outDir"
} else {
    Write-Host 'All boards match this PC frame for frame.' -ForegroundColor Green
}
