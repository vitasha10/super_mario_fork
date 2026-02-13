@echo off
REM ================================================
REM Build script for Super Mario Qt Application
REM Requires: MSYS2 with MinGW64 and Qt5 installed
REM   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-qt5-base
REM ================================================

echo ================================================
echo Super Mario Qt Build Script
echo ================================================

REM Set paths - adjust to your MSYS2/MinGW installation
set QT_PATH=C:\msys64\mingw64
set MINGW_PATH=C:\msys64\mingw64

REM Add Qt and MinGW to PATH
set PATH=%QT_PATH%\bin;%MINGW_PATH%\bin;%PATH%

REM Create build directory
if not exist "build" mkdir build
cd build

echo.
echo [1/3] Running CMake configuration...
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="%QT_PATH%" ..\src

if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

echo.
echo [2/3] Building the project...
mingw32-make -j4

if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo [3/3] Copying Qt DLLs for deployment...
windeployqt super_mario.exe

echo.
echo ================================================
echo Build completed successfully!
echo Executable: build\super_mario.exe
echo ================================================
echo.
echo Press any key to run the application...
pause >nul

super_mario.exe
