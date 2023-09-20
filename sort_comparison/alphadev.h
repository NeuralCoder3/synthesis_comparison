#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

#if defined(__clang__)

extern "C" void sort3_alphadev(int* buffer) {
  asm volatile(
      "mov 0x4(%0), %%eax            \n"
      "mov 0x8(%0), %%ecx            \n"
      "cmp %%eax, %%ecx              \n"
      "mov %%eax, %%edx              \n"
      "cmovl %%ecx, %%edx            \n"
      "mov (%0), %%r8d               \n"
      "cmovg %%ecx, %%eax            \n"
      "cmp %%r8d, %%eax              \n"
      "mov %%r8d, %%ecx              \n"
      "cmovl %%eax, %%ecx            \n"
      "cmovle %%r8d, %%eax           \n"
      "mov %%eax, 0x8(%0)            \n"
      "cmp %%ecx, %%edx              \n"
      "cmovle %%edx, %%r8d           \n"
      "mov %%r8d, (%0)               \n"
      "cmovg %%edx, %%ecx            \n"
      "mov %%ecx, 0x4(%0)            \n"
      : "+r"(buffer)
      :
      : "eax", "ecx", "edx", "r8d", "memory");
}

#else

// Adapted from [1] for gcc. ("rd8" is replaced with "esi" for the compilation to succeed.)
extern "C" void sort3_alphadev(int* buffer) {
  asm volatile(
      "mov 0x4(%0), %%eax            \n"
      "mov 0x8(%0), %%ecx            \n"
      "cmp %%eax, %%ecx              \n"
      "mov %%eax, %%edx              \n"
      "cmovl %%ecx, %%edx            \n"
      "mov (%0), %%esi               \n"
      "cmovg %%ecx, %%eax            \n"
      "cmp %%esi, %%eax              \n"
      "mov %%esi, %%ecx              \n"
      "cmovl %%eax, %%ecx            \n"
      "cmovle %%esi, %%eax           \n"
      "mov %%eax, 0x8(%0)            \n"
      "cmp %%ecx, %%edx              \n"
      "cmovle %%edx, %%esi           \n"
      "mov %%esi, (%0)               \n"
      "cmovg %%edx, %%ecx            \n"
      "mov %%ecx, 0x4(%0)            \n"
      : "+r"(buffer)
      :
      : "eax", "ecx", "edx", "esi", "memory");
}
#endif