@echo off

REM Qt build script for Super Mario (Qt UI)
REM Update QT_PATH below to point to your Qt installation root (contains bin folder)

set QT_PATH=C:\msys64\mingw64
set MINGW_PATH=C:\msys64\mingw64

set BUILD_TYPE="MinGW Makefiles"
set BUILD_SUFFIX=qt

chcp 65001

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=src

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% -DCMAKE_PREFIX_PATH="%QT_PATH%" -DBUILD_QT_UI=ON ..\%SOURCE_FOLDER%
cmake --build .

cd ..
