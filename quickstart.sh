#!/bin/bash
# Build runner
cd runner
sh build.sh

# Build raytracer
FIRST_ARG="$1"
shift

if [ ! $FIRST_ARG = "debug" ] && [ ! $FIRST_ARG = "release" ]; then
    echo "Build mode \"$FIRST_ARG\" is not supported!"
    echo "Supported build modes are: debug, release"
    exit
fi

./build/Runner --build --mode $FIRST_ARG $@
./build/Runner --mode $FIRST_ARG $@
