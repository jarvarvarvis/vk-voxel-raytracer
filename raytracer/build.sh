#!/bin/bash
MODE=$1

mkdir -p build/
cd build/

if [[ $MODE = "release" ]]; then
    mkdir -p release/
    cd release/
    cmake ../..
    make
elif [[ $MODE = "debug" ]]; then
    mkdir -p debug/
    cd debug/
    cmake ../.. -DDEBUGGING=ON
    make
fi
