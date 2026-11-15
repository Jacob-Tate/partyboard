@echo off
rem Usage: determinism-test.bat "C:\path\to\Mario Party 4 (USA) (Rev 1).rvz"
if "%~1"=="" (
    echo Usage: %~nx0 "C:\path\to\Mario Party 4 (USA) (Rev 1).rvz"
    exit /b 1
)
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0determinism-test.ps1" -Iso "%~1"
pause
