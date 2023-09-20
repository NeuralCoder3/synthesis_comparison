#!/bin/sh


compiler=("gcc" "clang")
mode=("debug" "release")
# compiler=("gcc")
# mode=("release-symbols")
build=("make")

for c in "${compiler[@]}"
do
    for m in "${mode[@]}"
    do
        for b in "${build[@]}"
        do
            preset="$c.$m.$b"
            echo "Generating $preset"
            cmake --preset="$preset" > /dev/null
            echo "Building $preset"
            cmake --build build/"$preset" > /dev/null
            mkdir -p ./out/"$preset"
            echo "Running $preset"
            ./build/"$preset"/bin/bench > ./out/"$preset"/time.txt 2>&1
            cd ./build/"$preset"/
            echo "Generating assembly for $preset"
            make test_correct.s > /dev/null
            cd ../../
            cp ./build/"$preset"/CMakeFiles/test.dir/test_correct.cpp.s ./out/"$preset"/
            echo ""
        done
    done
done
