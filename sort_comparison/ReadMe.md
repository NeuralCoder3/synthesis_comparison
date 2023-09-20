Here, we compare fixed-sized sort functions that were synthesized.

Sources:
- [AlphaDev](https://github.com/google-deepmind/alphadev)
- [Shorter and faster than Sort3AlphaDev](https://export.arxiv.org/pdf/2307.14503v1)
    - https://github.com/cassioneri/sort3
- [Mimicry-ai](https://github.com/mimicry-ai/sort)
- Std

Languages:
- C++
- Rust
    - `cargo rustc --release -- --emit asm`

Our baseline is the default C/Rust sort function with and without branches.

Resources:
- [measure instructions](https://stackoverflow.com/questions/13313510/quick-way-to-count-number-of-instructions-executed-in-a-c-program)


Results: https://docs.google.com/spreadsheets/d/1KrTYNVt-A_0IoiN0O6RWO8vJDD5ZJGBcsyh7__rFS6o/edit?usp=sharing

In conclusion, alphadev is quite good and leads the benchmarks.
`cassioneri 15 v2` is also very fast but does not work on negative numbers.

The manual branchless approach (shown below) is competitive to the other implementations (with a slight slowdown compared to alphadev depending on the benchmark).
The std sort is surprisingly bad which might be due to an overhead (that would need partial evaluation to be resolved).

Branchless implementation:
```C
void sort3_branchless(int *buffer) {
  int a = buffer[0];
  int b = buffer[1];
  int c = buffer[2];
  int x = a > b;
  int y = a > c;
  int z = b > c;
  buffer[x+y] = a;
  buffer[1-x+z] = b;
  buffer[2-y-z] = c;
}
```