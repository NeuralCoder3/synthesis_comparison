#include "../functions.h"

#include <array>
#include <cstdint>
#include <cstdio>


void test_correct(void (*function)(int*), char const* name) {

  std::printf("Testing %s...\n", name);

  using test_case_t = std::array<int , 3>;

  test_case_t test_cases[][2] = {
    /* actual      expected    */
    { { 1, 2, 3 }, { 1, 2, 3 } },
    { { 1, 3, 2 }, { 1, 2, 3 } },
    { { 2, 1, 3 }, { 1, 2, 3 } },
    { { 2, 3, 1 }, { 1, 2, 3 } },
    { { 3, 1, 2 }, { 1, 2, 3 } },
    { { 3, 2, 1 }, { 1, 2, 3 } },
    { { 1, 1, 2 }, { 1, 1, 2 } },
    { { 1, 2, 1 }, { 1, 1, 2 } },
    { { 2, 1, 1 }, { 1, 1, 2 } },
    { { 2, 2, 1 }, { 1, 2, 2 } },
    { { 2, 1, 2 }, { 1, 2, 2 } },
    { { 1, 2, 2 }, { 1, 2, 2 } },
    { { 1, 1, 1 }, { 1, 1, 1 } },

    // including negative numbers
    { { -1, -2, -3 }, { -3, -2, -1 } },
    { { -1, -3, -2 }, { -3, -2, -1 } },
    { { -2, -1, -3 }, { -3, -2, -1 } },
    { { -2, -3, -1 }, { -3, -2, -1 } },
    { { -3, -1, -2 }, { -3, -2, -1 } },
    { { -3, -2, -1 }, { -3, -2, -1 } },
    { { -1, -1, -2 }, { -2, -1, -1 } },
    { { -1, -2, -1 }, { -2, -1, -1 } },
    { { -2, -1, -1 }, { -2, -1, -1 } },
    { { -2, -2, -1 }, { -2, -2, -1 } },
    { { -2, -1, -2 }, { -2, -2, -1 } },
    { { -1, -2, -2 }, { -2, -2, -1 } },
    { { -1, -1, -1 }, { -1, -1, -1 } },

    // mixed numbers
  };

  for (auto& test_case : test_cases) {
    test_case_t const& expected = test_case[1];
    test_case_t actual = test_case[0];
    function(actual.data());
    if (actual[0] != expected[0] || actual[1] != expected[1] || actual[2] != expected[2]) {
      std::puts("  FAIL");
      return;
    }
  }
  std::puts("  PASS");
}


int main() {

    printf("Testing correctness...\n");
    printf("\n");
    for (auto& function : functions) {
        test_correct(function.func, function.name.c_str());
    }

    // printf("\n");
    // printf("\n");
    // printf("\n");

    // printf("Benchmarking...\n");
    // printf("\n");

    return 0;
}