This test code is based on the work of Cassioneri.

To check correctness, just build test_correct.cpp (e.g. via `g++ -O3 test_correct.cpp ../rust_sort/target/release/libsort_rust.a`).

To benchmark, build with cmake:
```
mkdir build
cd build
cmake --preset clang.release.make ..
cd clang.release.make/
make
./bin/bench
```

Or short:
```
cmake --preset [preset]
cmake --build build/[preset]
./build/[preset]/bin/bench
```

To build the assembly files:
```
cd build/[preset]
make test_correct.s
```
The assembly file is located in `CMakeFiles/test.dir/test_correct.cpp.s`.

Useful presets (`compiler.mode.builder`):
- `gcc.debug.make`
- `gcc.release.make`
- `clang.debug.make`
- `clang.release.make`
- `gcc.release-symbols.make`
- `clang.release-symbols.make`

List all presets with `cmake --list-presets`.
