#!/bin/bash

# Carbon Engine build script
# -> Debug mode, validation layers ENABLED

echo Building Carbon Engine in Debug mode ..

# create 'build' directory if it does not already exist
mkdir -p build

# pull any submodules
git submodule update --init --recursive

# run CMake
cmake . -B build
