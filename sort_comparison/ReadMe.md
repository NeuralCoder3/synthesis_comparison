Here, we compare fixed-sized sort functions that were synthesized.

Sources:
- [AlphaDev](https://github.com/google-deepmind/alphadev)
- [Shorter and faster than Sort3AlphaDev](https://export.arxiv.org/pdf/2307.14503v1)
    - https://github.com/cassioneri/sort3
- [Mimicry-ai](https://github.com/mimicry-ai/sort)
- Std


Languages:
- C
- C++
    - `g++ -S -O0 custom.cpp -o custom_g++_O0.s`
    - `g++ -S -O3 custom.cpp -o custom_g++_O3.s`
    - `clang++ -S -O0 custom.cpp -o custom_clang++_O0.s`
    - `clang++ -S -O3 custom.cpp -o custom_clang++_O3.s`
- Rust
    - `cargo rustc --release -- --emit asm`


Our baseline is the default C/Rust sort function with and without branches.

Resources:
- [measure instructions](https://stackoverflow.com/questions/13313510/quick-way-to-count-number-of-instructions-executed-in-a-c-program)
- 