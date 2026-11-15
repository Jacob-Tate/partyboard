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
    # Games to run at once. Lower it on a slow PC.
    [int]$Jobs = 3,
    [int]$HangSeconds = 90,
    [int]$TimeoutSeconds = 1200
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
foreach ($b in $Boards) { if ($b -lt 0 -or $b -gt 5) { throw "Board must be 0-5, got $b" } }
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

# Launch games, keeping up to $Jobs running at once.
$queue = New-Object System.Collections.Queue
foreach ($b in $Boards) { $queue.Enqueue($b) }
$running = @{}
$finished = @{}
Write-Host ("Playing {0} board(s), {1} at a time. Game windows will open and close." -f $Boards.Count, $Jobs)
while ($queue.Count -gt 0 -or $running.Count -gt 0) {
    while ($queue.Count -gt 0 -and $running.Count -lt $Jobs) {
        $b = $queue.Dequeue()
        $log = Join-Path $outDir "board$b.checksums"
        $stdout = Join-Path $outDir "board$b.stdout.txt"
        $argList = @('--quickstart', '--board', $b, '--turns', $Turns, '--seed', $Seed, '--cpu-level', $CpuLevel,
                     '--fast', '--iso', "`"$Iso`"", '--checksum-log', "`"$log`"",
                     '--config-dir', "`"$(Join-Path $outDir "board$b.config")`"")
        $proc = Start-Process -FilePath $exe -ArgumentList $argList -WorkingDirectory $here -PassThru `
            -RedirectStandardOutput $stdout -RedirectStandardError "$stdout.err"
        # Windows PowerShell 5.1 only records ExitCode if the handle is opened while the process runs.
        $null = $proc.Handle
        $running[$b] = @{ Proc = $proc; Log = $log; Start = (Get-Date); LastSize = -1; LastGrowth = (Get-Date) }
        Write-Host ("  started board {0} ({1})" -f $b, $boardNames[$b])
    }
    Start-Sleep -Milliseconds 500
    foreach ($b in @($running.Keys)) {
        $r = $running[$b]
        $status = $null
        if ($r.Proc.HasExited) {
            $r.Proc.WaitForExit()
            $status = if ($r.Proc.ExitCode -ne 0) { "crash (exit $($r.Proc.ExitCode))" } else { 'ok' }
        } else {
            $size = if (Test-Path $r.Log) { (Get-Item $r.Log).Length } else { 0 }
            if ($size -ne $r.LastSize) { $r.LastSize = $size; $r.LastGrowth = Get-Date }
            elseif (((Get-Date) - $r.LastGrowth).TotalSeconds -gt $HangSeconds) { $status = 'hang' }
            if (((Get-Date) - $r.Start).TotalSeconds -gt $TimeoutSeconds) { $status = 'timeout' }
            if ($status) { $r.Proc.Kill(); $r.Proc.WaitForExit() }
        }
        if ($status) {
            $secs = [int]((Get-Date) - $r.Start).TotalSeconds
            $finished[$b] = @{ Status = $status; Secs = $secs }
            $running.Remove($b)
            Write-Host ("  finished board {0} ({1}): {2}, {3}s" -f $b, $boardNames[$b], $status, $secs)
        }
    }
}

Write-Host ''
$summary = @()
foreach ($b in $Boards) {
    $name = $boardNames[$b]
    $status = $finished[$b].Status
    $secs = $finished[$b].Secs
    $mine = Read-Checksums (Join-Path $outDir "board$b.checksums")
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
    $line = "board $b ($name): $status, $secs s - $result"
    Write-Host $line
    $summary += $line
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
