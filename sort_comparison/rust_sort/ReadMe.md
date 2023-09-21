cargo rustc --release -- --emit asm


Needs cargo install cbindgen
$HOME/.cargo/bin/cbindgen --config cbindgen.toml --crate rust_sort --output ../rust.h


python ../extract_code.py ./target/release/deps/sort_rust.s | xclip -sel clip
