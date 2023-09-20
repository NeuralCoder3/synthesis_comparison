#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>


// Sort3mu - sort 3 uint32_t values pointed to by buffer
uint8_t shuf3mu0[] = {
	8, 4, 8, 0, 4, 0
};

uint8_t shuf3mu1[] = {
	4, 8, 0, 8, 0, 4
};

extern "C" void sort3_mimicry_mu(uint32_t* buffer) {
	asm volatile(
		"mov (%0), %%eax                        \n"
		"mov 4(%0), %%edx                       \n"
		"cmp %%eax, %%edx                       \n"
		"sbb %%rbx, %%rbx                       \n"
		"mov 8(%0), %%ecx                       \n"
		"cmp %%eax, %%ecx                       \n"
		"sbb %%r8, %%r8                         \n"
		"cmp %%ecx, %%edx                       \n"
		"adc $0, %%r8                           \n"
		"movzb shuf3mu0+3(%%rbx,%%r8,2), %%r9   \n"
		"mov %%ecx, 4(%0,%%r8,4)                \n"
		"movzb shuf3mu1+3(%%rbx,%%r8,2), %%rcx  \n"
		"mov %%eax, (%0,%%r9)                   \n"
		"mov %%edx, (%0,%%rcx)                  \n"
		: "+r"(buffer)
		:
		: "eax","edx","rbx","rcx","r8","r9","memory");
}

// Sort3ms - sort 3 int32_t values pointed to by buffer;
// reuses the write shuffle vectors from Sort3mu
extern "C" void sort3_mimicry_ms(int32_t* buffer) {
	asm volatile(
		"mov (%0), %%eax \n"
		"mov 4(%0), %%edx \n"
		"lea 0x80000000(%%eax), %%r10d \n"
		"lea 0x80000000(%%edx), %%r11d \n"
		"cmp %%r10d, %%r11d \n"
		"sbb %%rbx, %%rbx \n"		// range -1..0
		"mov 8(%0), %%ecx \n"
		"lea 0x80000000(%%ecx), %%r12d \n"
		"cmp %%r10d, %%r12d \n"
		"sbb %%r8, %%r8 \n"
		"cmp %%r12d, %%r11d \n"
		"adc $0, %%r8 \n"	// range -1..1
		"movzb shuf3mu0+3(%%rbx,%%r8,2), %%r9 \n"
		"mov %%ecx, 4(%0,%%r8,4) \n"
		"movzb shuf3mu1+3(%%rbx,%%r8,2), %%rcx \n"
		"mov %%eax, (%0,%%r9) \n"
		"mov %%edx, (%0,%%rcx) \n"
		: "+r"(buffer)
		:
		: "eax","edx","rbx","rcx","r8","r9","r10","r11","r12","memory");
}

// Sort3mv - sort 3 int32_t values pointed to by buffer, using SIMD
// instructions

// first three elements mask for masked move (vpmaskmovd) instruction
int32_t mask3[] = { -1, -1, -1, 0 }; 

// byte shuffles representing 32-bit word positions
const uint32_t p0 = 0x03020100;
const uint32_t p1 = 0x07060504;
const uint32_t p2 = 0x0b0a0908;
const uint32_t p3 = 0x0f0e0d0c;
const uint32_t invp = 0xffffffff;

/* Sort3 shuffles
0b000 -> 0 1 2
0b001 -> 1 2 0
0b010 -> 2 0 1
0b011 -> 2 1 0
0b100 -> 0 1 2
0b101 -> 1 0 2
0b110 -> 0 2 1
*/

// In the shuffle definition, if we want to retain the last (unsorted) word,
// the last element needs to be set to p3, if we want to clear it to 0, the
// last element must be invp
uint32_t vshuf3[7*4] = {
	p0, p1, p2, p3,
	p1, p2, p0, p3,
	p2, p0, p1, p3,
	p2, p1, p0, p3,
	p0, p1, p2, p3,
	p1, p0, p2, p3,
	p0, p2, p1, p3
};

extern "C" void sort3_mimicry_mv(int32_t* buffer) {
	asm volatile(
		"vmovdqa mask3, %%xmm1                 \n"
		"vpmaskmovd (%0), %%xmm1, %%xmm2       \n"
		"vpshufd $0xc9, %%xmm2, %%xmm3         \n"	// shuffle 0b1100_1001 -> 1 2 0 3
		"vpcmpgtd %%xmm3, %%xmm2, %%xmm3       \n"
		"movmskps %%xmm3, %%eax                \n"
		"shl $4, %%eax                         \n"
		"vpshufb vshuf3(%%eax), %%xmm2, %%xmm2 \n"
		"vpextrq $0, %%xmm2, (%0)              \n"
		"vpextrd $2, %%xmm2, 8(%0)             \n"
		: "+r"(buffer)
		:
		: "eax","xmm1","xmm2","xmm3","memory");
}

extern "C" void sort3_mimicry_std(int32_t* buffer) {
	std::sort(buffer, buffer+3);
}