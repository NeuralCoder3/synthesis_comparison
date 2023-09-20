#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <iomanip>

#include "../functions.h"

// workBody iterates sorting function F over the allocated array, changing
// the offset to obtain different alignments
template<typename T, void F(T*)>
void workBody(T work[], size_t offsetLen, size_t nofArrays) {
	for (size_t offset = 0; offset < offsetLen; offset++) {
		for (size_t i = 0; i < nofArrays; i++) {
			F(&work[offset+i*offsetLen]);
		}
	}
}

// benchSortFunction runs provided sort function on a provided array of
// random values. It sorts nofArrays subarrays,
// shifted by all offsets from 0 upto less than offsetLen, which provides
// for different alignments of the subarrays to be benchmarked. It executes
// the benchmark runs times, re-initializing the arrays to its initial state
// after each run. It returns the total number of nanoseconds performing
// sorting (and copying - see comments on measurements).
template<typename T, size_t len>
// std::chrono::nanoseconds benchSortFunction(void F(T*, size_t, size_t),
std::chrono::nanoseconds benchSortFunction(void F(T*),
																					T v[], size_t nofArrays, size_t offsetLen, size_t runs) {
	T work[(nofArrays+1)*offsetLen];
	// measure execution time as elapsed time (to be improved if needed)
	std::chrono::nanoseconds res(0);
	auto t0 = std::chrono::steady_clock::now();
	for (size_t r = 0; r < runs; r++) {
		std::copy(v, v+(nofArrays+1)*offsetLen, work);	// reset arrays

		// body to measure
		// F(work, offsetLen, nofArrays);

		for (size_t offset = 0; offset < offsetLen; offset++) {
			for (size_t i = 0; i < nofArrays; i++) {
				F(&work[offset+i*offsetLen]);
			}
		}

	}
	auto t1 = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
}

int main() {
	// benchmarking
	std::minstd_rand generator;
	size_t const n = 501*4;
	// 500 subarrays of length 4, one extra so we can have different alignment
	// by adding an offset
	std::vector<uint32_t> au;
	std::uniform_int_distribution<> udist(0, 10000);
	for (size_t i = 0; i < n; i++) {
		au.push_back((uint32_t)udist(generator));
	}
	std::vector<int32_t> as;
	std::uniform_int_distribution<> sdist(-10000, 10000);
	for (size_t i = 0; i < n; i++) {
		as.push_back(sdist(generator));
	}

	// size_t const nofRuns = 1000000;
	size_t const nofRuns = 100000;
	double const nofSorts = 500.0*4.0*nofRuns;

	std::cout << "Benchmark    Time\n";
	std::cout << "-----------------\n";

	for (auto& function : functions) {
		// void (*work)(int*, size_t, size_t) = workBody<int, function.func>;
		// work = workBody<int, function.func>;
		auto ns = benchSortFunction<int32_t, 3>(
		// auto ns = benchSortFunction<int, 3>(
			// work
			// workBody<int, function.func>,
			function.func, &as[0], 500, 4, nofRuns);
		auto nsPerSort = 1000000*double(ns.count())/nofSorts;
		std::cout << function.name << "   " << std::setprecision(0) << std::fixed << nsPerSort << " ns per sort\n";
	}


	return 0;
}
