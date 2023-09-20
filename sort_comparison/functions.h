#include "alphadev.h"
#include "cassioneri.h"
#include "custom.h"
#include "mimicry.h"

#include <array>

using SortingFunction = void (*)(int*);

struct TestFunction {
    SortingFunction func;
    std::string name;
};

TestFunction functions[] = {
    { sort3_alphadev, "alphadev" },

    { sort3_cassioneri_14,     "cassioneri_14" },
    { sort3_cassioneri_15,     "cassioneri_15" },
    { sort3_cassioneri_15_v2,  "cassioneri_15_v2" },
    { sort3_cassioneri_faster, "cassioneri_faster" },

    { sort3_default,     "default" },
    { sort3_std,         "std" },
    { sort3_branchless,  "branchless" },
    { sort3_swap,        "swap" },
    { sort3_swap_inline, "swap_inline" },

    // { sort3_mimicry_mu, "sort3_mimicry_mu" },
    { sort3_mimicry_ms,  "mimicry_ms" },
    { sort3_mimicry_mv,  "mimicry_mv" },
    { sort3_mimicry_std, "mimicry_std" }
};