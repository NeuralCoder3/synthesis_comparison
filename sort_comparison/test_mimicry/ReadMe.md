`g++ -O3 test_correct.cpp -L ../rust_sort/target/release/ -lsort_rust`
cp ../rust_sort/target/release/libsort_rust.so .

cp ../rust_sort/target/release/libsort_rust.a .
`g++ -O3 test_correct.cpp ../rust_sort/target/release/libsort_rust.a`