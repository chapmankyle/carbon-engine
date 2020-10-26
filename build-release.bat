:: Carbon Engine build script
:: -> Release mode, validation layers DISABLED

@echo off

echo Building Carbon Engine in Release mode ..

:: create 'build' directory if it does not already exist
if not exist "build" mkdir build

:: pull any submodules
git submodule update --init --recursive

:: run CMake
cmake . -B build -A x64 -DIS_RELEASE=ON
