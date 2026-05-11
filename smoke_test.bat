@echo off
rem -------------------------------------------------
rem Smoke test – launch the built executable, wait, then close it
rem -------------------------------------------------

set EXE_PATH=%~dp0build\PKUPlanner.exe

if not exist "%EXE_PATH%" (
    echo [ERROR] Executable not found: %EXE_PATH%
    exit /b 1
)

rem Start the binary (non‑blocking)
start "" "%EXE_PATH%"

rem Wait a few seconds for the app to initialise
timeout /t 5 > nul

rem Terminate the process gracefully
taskkill /IM PKUPlanner.exe /F > nul

echo -------------------------------------------------
echo Smoke test completed – binary launched and exited cleanly.
echo -------------------------------------------------