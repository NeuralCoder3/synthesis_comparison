#include <cstdint>


extern "C" void sort3_cassioneri_14(int* buffer) {
  int a, b, c;
  asm volatile (
    "mov (%[p]), %[a]           \n\t" // int a = buffer[0];
    "mov 4(%[p]), %[b]          \n\t" // int b = buffer[1];
    "loop_start%=:              \n\t" // for(;;) {
    "mov %[a], %[c]             \n\t" //   int c = a;
    "cmp %[b], %[a]             \n\t" //   bool flag = b < a;
    "cmovg %[b], %[a]           \n\t" //   a = flag ? b : a;
    "cmovg %[c], %[b]           \n\t" //   b = flag ? c : b;
    "cmp 8(%[p]), %[b]          \n\t" //   flag = buffer[2] < b;
    "jle loop_end%=             \n\t" //   if (!flag) break;
    "mov %[b], %[c]             \n\t" //   c = b;
    "mov 8(%[p]), %[b]          \n\t" //   b = buffer[2];
    "mov %[c], 8(%[p])          \n\t" //   buffer[2] = c;
    "jmp loop_start%=           \n\t" // }
    "loop_end%=:                \n\t" //
    "mov %[a], (%[p])           \n\t" // buffer[0] = a;
    "mov %[b], 4(%[p])              " // buffer[1] = b;
    : [a]"=r"(a), [b]"=r"(b), [c]"=r"(c), [p]"+r"(buffer)
    : : "memory");
}

char dest[] = {
  1, 2, 9, 2, 0, 9, 0, 1,
  0, 0, 9, 1, 1, 9, 2, 2,
  2, 1, 9, 0, 2, 9, 1, 0
};

// Precondition: buffer[0] >= 0 && buffer[1] >= 0 && buffer[2] >= 0.
extern "C" void sort3_cassioneri_15(int* buffer) {
  int a, b, c;
  int64_t i, j;
  asm volatile (
    "mov (%[p]), %[a]           \n\t" // int a = buffer[0];
    "mov 4(%[p]), %[b]          \n\t" // int b = buffer[1];
    "mov 8(%[p]), %[c]          \n\t" // int c = buffer[2];
    "cmp %[a], %[b]             \n\t" // bool flag = b < a;
    "sbb %[i], %[i]             \n\t" // int i = flag ? -1 : 0;
    "cmp %[b], %[c]             \n\t" // flag = c < b;
    "adc %[i], %[i]             \n\t" // i = 2 * i + flag;
    "cmp %[a], %[c]             \n\t" // flag = c < a;
    "adc %[i], %[i]             \n\t" // i = 2 * i + flag;
    "movsb dest+4(%[i]), %[j]   \n\t" // int j = dest[i + 4];
    "mov %[a], (%[p],%[j],4)    \n\t" // buffer[j] = a;
    "movsb dest+12(%[i]), %[j]  \n\t" // j = dest[i + 12];
    "mov %[b], (%[p],%[j],4)    \n\t" // buffer[j] = b;
    "movsb dest+20(%[i]), %[j]  \n\t" // j = dest[i + 20];
    "mov %[c], (%[p],%[j],4)        " // buffer[j] = c;
    : [a]"=r"(a), [b]"=r"(b), [c]"=r"(c), [i]"=r"(i), [j]"=r"(j),
    [p]"+r"(buffer) : "g"(dest) : "memory");
  return;
}

// Precondition: buffer[0] >= 0 && buffer[1] >= 0 && buffer[2] >= 0.
// Faster than the Sort3_15, this implementation also does not use a look-up
// table and thus, compiler switches "-fno-pie -no-pie" are unnecessary.
extern "C" void sort3_cassioneri_15_v2(int* buffer) {
  int a, b, c;
  int64_t i, j;
  asm volatile (
    "mov (%[p]), %[a]         \n\t" // int a = buffer[0];
    "mov 4(%[p]), %[b]        \n\t" // int b = buffer[1];
    "mov 8(%[p]), %[c]        \n\t" // int c = buffer[2];
    "cmp %[a], %[b]           \n\t" // int flag = b < a;
    "sbb %[j], %[j]           \n\t" // int j = -flag;       // = - (b < a)
    "blsi %[j], %[i]          \n\t" // int i = -j;          // = (b < a)
    "cmp %[a], %[c]           \n\t" // flag = c < a;
    "adc $0, %[i]             \n\t" // i = i + (0 + flag);  // = (b < a) + (c < a)
    "mov %[a], (%[p],%[i],4)  \n\t" // buffer[i] = a;
    "cmp %[c], %[b]           \n\t" // flag = b < c;
    "sbb $-2, %[j]            \n\t" // j = j - (-2 + flag); // = 2 - (b < a) - (b < c) = (a <= b) + (c <= b)
    "mov %[b], (%[p],%[j],4)  \n\t" // buffer[j] = b;
    "add %[j], %[i]           \n\t" // i = i + j;
    "xor $3, %[i]             \n\t" // i = 3 - i;
    "mov %[c], (%[p],%[i],4)      " // buffer[i] = c;
    : [a]"=r"(a), [b]"=r"(b), [c]"=r"(c), [i]"=r"(i), [j]"=r"(j),
    [p]"+r"(buffer) : : "memory");
  return;
}

extern "C" void sort3_cassioneri_faster(int* buffer) {

  int a = buffer[0];
  int b = buffer[1];
  int c = buffer[2];

  bool flag = c < b;
  int d = b;
  b = flag ? c : b;
  c = flag ? d : c;

  flag = c < a;
  d = a;
  a = flag ? c : a;
  c = flag ? d : c;
  buffer[2] = c;

  flag = b < a;
  d = a;
  a = flag ? b : a;
  b = flag ? d : b;
  buffer[0] = a;
  buffer[1] = b;

  return;
}