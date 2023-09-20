#include "../functions.h"

#include <benchmark/benchmark.h>

#include <array>
#include <cstdint>
#include <iterator>
#include <random>

std::array<int , 3> const test_cases[] = {
  { 1, 2, 3 },
  { 1, 3, 2 },
  { 2, 1, 3 },
  { 2, 3, 1 },
  { 3, 1, 2 },
  { 3, 2, 1 },
  { 1, 1, 2 },
  { 1, 2, 1 },
  { 2, 1, 1 },
  { 2, 2, 1 },
  { 2, 1, 2 },
  { 1, 2, 2 },
  { 1, 1, 1 },
};

// random selectors
auto ns = [](){
  std::uniform_int_distribution<unsigned> uniform_dist(0, std::size(test_cases) - 1);
  std::mt19937 rng;
  std::array<int32_t, 32768> ns;
  for (auto& n : ns)
    n = uniform_dist(rng);
  return ns;
}();

// Benchmark function that takes a TestFunction as an argument
static void BenchmarkSortFunction(benchmark::State& state, const TestFunction& testFunc) {
    for (auto _ : state) {
        for (auto n : ns) {
            auto p = test_cases[n];
            testFunc.func(p.data());
            benchmark::DoNotOptimize(p.data());
        }
    }
}

// Register benchmarks for each sorting function
void RegisterSortBenchmarks(std::vector<TestFunction>& functions) {
    for (const auto& func : functions) {
        benchmark::RegisterBenchmark(
            func.name.c_str(),
            [testFunc = func](benchmark::State& state) {
                BenchmarkSortFunction(state, testFunc);
            });
    }
}

int main(int argc, char** argv) {
    ::benchmark::Initialize(&argc, argv);

    // Create a vector of test functions and register benchmarks
    std::vector<TestFunction> sortingFunctions(functions, functions + sizeof(functions) / sizeof(functions[0]));
    RegisterSortBenchmarks(sortingFunctions);

    ::benchmark::RunSpecifiedBenchmarks();
    return 0;
}