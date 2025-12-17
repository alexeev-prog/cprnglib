#include <stdint.h>
#include <stdio.h>
#include "../cprnglib/romuduo.h"
#include "../cprnglib/murmur3.h"

int main() {
    uint64_t romu_duo_result = romu_duo();

    murmur3_prng_t prng;
    murmur3_prng_init(&prng, 42);

    uint64_t murmur3_result = murmur3_prng_next(&prng);

    printf("romu_duo: %lu\n", romu_duo_result);
    printf("murmur3: %lu\n", murmur3_result);

    return 0;
}
