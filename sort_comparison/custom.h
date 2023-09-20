#include <stdlib.h>
#include <algorithm>

extern "C" void sort3_default(int *buffer) {
  int tmp;
  if (buffer[0] > buffer[1]) {
    tmp = buffer[0];
    buffer[0] = buffer[1];
    buffer[1] = tmp;
  }
  if (buffer[1] > buffer[2]) {
    tmp = buffer[1];
    buffer[1] = buffer[2];
    buffer[2] = tmp;
  }
  if (buffer[0] > buffer[1]) {
    tmp = buffer[0];
    buffer[0] = buffer[1];
    buffer[1] = tmp;
  }
}

extern "C" void sort3_default_size(int buffer[3]) {
  int tmp;
  if (buffer[0] > buffer[1]) {
    tmp = buffer[0];
    buffer[0] = buffer[1];
    buffer[1] = tmp;
  }
  if (buffer[1] > buffer[2]) {
    tmp = buffer[1];
    buffer[1] = buffer[2];
    buffer[2] = tmp;
  }
  if (buffer[0] > buffer[1]) {
    tmp = buffer[0];
    buffer[0] = buffer[1];
    buffer[1] = tmp;
  }
}

extern "C" void sort3_std(int *buffer) {
  std::sort(buffer, buffer + 3);
}

extern "C" void sort3_branchless(int *buffer) {
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

extern "C" void sort3_branchless_size(int buffer[3]) {
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

extern "C" void sort3_swap(int* buffer) {
    int a = buffer[0];
    int b = buffer[1];
    int c = buffer[2];
    
    if(c < b) {
        std::swap(c, b);
    }
    if(c < a) {
        std::swap(c, a);
    }
    if(b < a) {
        std::swap(b, a);
    }
    buffer[0] = a;
    buffer[1] = b;
    buffer[2] = c;
    return;
}

extern "C" void sort3_swap_inline(int* buffer) {
  if (buffer[0] > buffer[1]) {
    std::swap(buffer[0], buffer[1]);
  }
  if (buffer[1] > buffer[2]) {
    std::swap(buffer[1], buffer[2]);
  }
  if (buffer[0] > buffer[1]) {
    std::swap(buffer[0], buffer[1]);
  }
}