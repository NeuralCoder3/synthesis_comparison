#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

#include "../functions.h"

// equalValues - are two arrays pointed to by p and q equal for len elements
template<typename T, size_t len>
bool equalValues(T* p, T* q) {
	for (auto i = len; i > 0; i--) {
		if (p[i-1] != q[i-1]) {
			return false;
		}
	}
	return true;
}

// isSorted - return whether the array pointed to by p of size len is sorted
template<typename T, size_t len>
bool isSorted(T* p) {
	T sp[len];		// temporary buffer for a sorted copy
	std::copy(p, p+len, sp);
	std::sort(std::begin(sp), std::end(sp));
	return equalValues<T, len>(p, sp);
}

// slice is a helper for outputting slices
template<typename T>
struct slice {
	T* p;
	size_t l;
	slice(T* buf, size_t len) { p = buf; l = len; }
};

template<typename T>
std::ostream& operator<<(std::ostream& o, slice<T> sl) {
	o << "[";
	for (size_t i = 0; i < sl.l-1; i++) {
		o << sl.p[i] << ",";
	}
	o << sl.p[sl.l-1] << "]";
	return o;
}

// powUint calculates x^y, without overflow check
uint64_t powUint(uint64_t x, uint64_t y) {
	uint64_t res = 1, pot = x;
	while (y > 0) {
		if ((y&1) == 1) res *= pot;
		pot *= pot;
		y >>= 1;
	}
	return res;
}

// rshuffle implements a read shuffle; shuf includes n positions like a
// digit in a base-n number
template<typename T, size_t n>
void rshuffle(T src[], T dest[], uint64_t shuf) {
	for (size_t i = 0; i < n; i++) {
		dest[i] = src[shuf%n];
		shuf /= n;
	}
}

// checkSortFunction determines all permutations of array v including
// repetitions of individual elements (of which there are len^len), sorts
// them, and checks whether the array is the sorted copy of the original
// permutation; outputs failures and returns whether it was able to sort
// all permutations
template<typename T, size_t len>
bool checkSortFunction(void f(T*), T v[]) {
	bool failed = false;
	auto nofPerm = powUint(len, len);		// number of permutations with repetitions
	for (size_t shuf = 0; shuf < nofPerm; shuf++) {
		T org[len], work[len];
		rshuffle<T, len>(v, org, shuf);
		std::copy(org, org+len, work);
		f(work);
		if (!isSorted<T, len>(work)) {
			failed = true;
			std::cout << "failed to sort " << slice<T>(org, len) << ", result " << slice<T>(work, len) << "\n";
		}
	}
	return !failed;
}

int main() {

	// correctness checking
	int32_t vs[] = { -10, 0, 10, 20 };
	// uint32_t vu[] = { 0, 5, 10, 15 };
    int32_t vu[] = { 0, 5, 10, 15 };


    std::cout << "Testing signed correctness...\n";
    for (auto& function : functions) {
        std::cout << "testing " << function.name << "\n";
        checkSortFunction<int32_t, 3>(function.func, vs);
    }

    std::cout << std::endl;

    std::cout << "Testing unsigned correctness...\n";
    for (auto& function : functions) {
        std::cout << "testing " << function.name << "\n";
        checkSortFunction<int32_t, 3>(function.func, vu);
    }

	return 0;
}
