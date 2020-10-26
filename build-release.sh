#!/bin/bash

# Carbon Engine build script
# -> Release mode, validation layers DISABLED

echo Building Carbon Engine in Release mode ..

# create 'build' directory if it does not already exist
mkdir -p build

# pull any submodules
git submodule update --init --recursive

# run CMake
cmake . -B build -DIS_RELEASE=ON
