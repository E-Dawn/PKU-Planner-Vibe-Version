@echo off
rem -------------------------------------------------
rem Clean build + unit-test for Course-Helper
rem -------------------------------------------------

rem 1. Delete old build directory
if exist build (
    echo Removing old build directory ...
    rmdir /s /q build
)

rem 2. Recreate build directory and cd into it
mkdir build
cd build

rem 3. CMake configuration (using VS2022 NMake generator)
cmake -S ".." -B . -G "NMake Makefiles"
if errorlevel 1 (
    echo [ERROR] CMake configuration failed
    exit /b 1
)

rem 4. Build Release target
cmake --build . --config Release
if errorlevel 1 (
    echo [ERROR] Build failed
    exit /b 1
)

rem 5. Run unit tests (ctest will discover DataStoreTest)
ctest -C Release --output-on-failure
if errorlevel 1 (
    echo [ERROR] Some tests failed
    exit /b 1
)

echo -------------------------------------------------
echo Build and test succeeded.
echo -------------------------------------------------