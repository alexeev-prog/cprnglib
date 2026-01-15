#ifndef MURMUR3_H
#    include <stdint.h>

#    include "utils.h"

typedef struct {
    uint64_t seed;
    uint64_t counter;
} murmur3_prng_t;

void murmur3_prng_init(murmur3_prng_t* prng, uint64_t seed) {
    prng->seed = seed;
    prng->counter = 0;
}

uint64_t murmur3_prng_next(murmur3_prng_t* prng) {
    uint64_t h1 = prng->seed;
    uint64_t k1 = prng->counter++;

    const uint64_t c1 = 0x87c37b91114253d5ULL;
    const uint64_t c2 = 0x4cf5ad432745937fULL;

    k1 *= c1;
    k1 = rotl64(k1, 31);
    k1 *= c2;

    h1 ^= k1;
    h1 = rotl64(h1, 27);
    h1 = h1 * 5 + 0x52dce729;

    h1 ^= 4;
    h1 = fmix64(h1);

    return h1;
}

#endif    // !MURMUR3_H
