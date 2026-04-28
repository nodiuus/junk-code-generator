#pragma once
#include <cstdint>

constexpr uint64_t get_seed() {
	uint64_t seed = 0;
	for (const char* c = __TIME__; *c; c++) {
		seed = (seed << 8) + *c;
	}

	return seed;
}

constexpr uint64_t get_random(uint64_t n) {
	return (get_seed() + n * 6364136223846793005ULL) + 1442695040888963407ULL;
}

template <int N>
struct generator {
	__forceinline static void generate_junk() {
		constexpr int branch = get_random(N) % 5;

    // you can add as many branches as you want with garbage
		if constexpr (branch == 0) {
			volatile int counter = 0;
			constexpr int loop_limit = get_random(N) % 50;

			for (int i = 0; i < loop_limit; i++) {
				counter += i;
			}
		}
		else if constexpr (branch == 1) {
            volatile int fibonacci[6] = { 1, 1, 2, 3, 5, 8 };
            constexpr int idx = get_random(N + 5) % 6;
            fibonacci[idx] ^= idx * 31;
		}
		else if constexpr (branch == 2) {
			volatile char buffer[16];
			buffer[0] = static_cast<char>(get_random(N + 2) % 256);
		} 
        else if constexpr (branch == 3) {
            volatile uint32_t x = static_cast<uint32_t>(get_random(N + 6));
            x = (x << 7) | (x >> 25);
            x ^= 0x9E3779B9u;
        }
        else if constexpr (branch == 4) {
            volatile int x = static_cast<int>(get_random(N + 7));
            volatile int y = x;

            y ^= 0xABCD;
            y ^= 0xABCD; // y == x again
            y += 13;
            y -= 13;
        } 

		generator<N - 1>::generate_junk();
	}
};

template <>
struct generator<0> {
	__forceinline static void generate_junk() {
		// base case: do nothing
	}
};
