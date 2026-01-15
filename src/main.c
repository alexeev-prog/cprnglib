#include <stdint.h>
#include <stdio.h>

#include "../cprnglib/cprnglib.h"

int main() {
    uint64_t romu_duo_result = romu_duo();

    murmur3_prng_t prng;
    murmur3_prng_init(&prng, 42);

    uint64_t murmur3_result = murmur3_prng_next(&prng);

    uint32_t sfc32_result = sfc32();

    uint32_t jsf32_result = jsf32();

    printf("romu_duo: %lu\n", romu_duo_result);
    printf("murmur3: %lu\n", murmur3_result);
    printf("sfc32: %d\n", sfc32_result);
    printf("jsf32: %d\n", jsf32_result);

    return 0;
}
