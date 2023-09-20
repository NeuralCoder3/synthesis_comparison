#!/bin/sh


compiler=("g++" "clang++")
mode=("O0" "O3")

mkdir -p ./build
mkdir -p ./out

for c in "${compiler[@]}"
do
    for m in "${mode[@]}"
    do
        OUT=./out/$c.$m
        BOUT=./build/$c.$m
        mkdir -p $OUT
        mkdir -p $BOUT
        echo "Generating $c $m assembly"
        $c -$m -S ./test_correct.cpp -o $OUT/test_correct.s ../rust_sort/target/release/libsort_rust.a
        echo "Building $c $m"
        $c -$m ./benchmark.cpp -o $BOUT/bench.out ../rust_sort/target/release/libsort_rust.a
        echo "Running $c $m"
        $BOUT/bench.out > $OUT/time.txt 2>&1
        echo ""
    done
done
