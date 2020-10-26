:: Carbon Engine build script
:: -> Debug mode, validation layers ENABLED

@echo off

echo Building Carbon Engine in Debug mode ..

:: create 'build' directory if it does not already exist
if not exist "build" mkdir build

:: pull any submodules
git submodule update --init --recursive

:: run CMake
cmake . -B build -A x64
