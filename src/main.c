#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../cprnglib/jsf32.h"
#include "../cprnglib/murmur3.h"
#include "../cprnglib/romuduo.h"
#include "../cprnglib/sfc32.h"

#define NUM_COUNT 100000000
#define BINS 256

typedef struct {
    const char* name;
    void (*init)(void);
    uint64_t (*next)(void);
} prng_t;

static void jsf32_init(void) {
    jsf32_global.a = 0x12345678;
    jsf32_global.b = 0x9ABCDEF0;
    jsf32_global.c = 0x13579BDF;
    jsf32_global.d = 0x2468ACE0;
}

static uint64_t jsf32_next(void) {
    return jsf32();
}

static void romu_duo_init(void) {
    ROMO_DUO_STATE1 = 0x1234567890abcdef;
    ROMO_DUO_STATE2 = 0xfedcba0987654321;
}

static uint64_t romu_duo_next(void) {
    return romu_duo();
}

static void sfc32_init(void) {
    sfc32_state[0] = 0x12345678;
    sfc32_state[1] = 0x9ABCDEF0;
    sfc32_state[2] = 0x13579BDF;
    sfc32_state[3] = 0x2468ACE0;
}

static uint64_t sfc32_next(void) {
    return sfc32();
}

static murmur3_prng_t murmur3_ctx;

static void murmur3_init(void) {
    murmur3_prng_init(&murmur3_ctx, 42);
}

static uint64_t murmur3_next(void) {
    return murmur3_prng_next(&murmur3_ctx);
}

static void chi_square_test(uint64_t* samples, size_t n, const char* name) {
    uint64_t bins[BINS] = {0};
    for (size_t i = 0; i < n; i++) {
        uint8_t byte = samples[i] >> 24;
        bins[byte]++;
    }
    double expected = (double)n / BINS;
    double chi2 = 0.0;
    for (int i = 0; i < BINS; i++) {
        double diff = bins[i] - expected;
        chi2 += diff * diff / expected;
    }
    double p_value = 1.0 - exp(-chi2 / 2);
    printf("%s: хи-квадрат = %.2f (число степеней свободы = 255, p-значение = ~%.4f)\n", name, chi2, p_value);
}

static void benchmark(prng_t* prng) {
    prng->init();
    uint64_t* samples = malloc(NUM_COUNT * sizeof(uint64_t));
    if (!samples) {
        return;
    }

    clock_t start = clock();
    for (size_t i = 0; i < NUM_COUNT; i++) {
        samples[i] = prng->next();
    }
    clock_t end = clock();

    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    double mln_per_sec = NUM_COUNT / seconds / 1e6;

    printf("%s: %.2f миллионов чисел в секунду\n", prng->name, mln_per_sec);
    chi_square_test(samples, NUM_COUNT, prng->name);
    printf("\n");

    free(samples);
}

int main(void) {
    prng_t generators[] = {{"jsf32", jsf32_init, jsf32_next},
                           {"romu_duo", romu_duo_init, romu_duo_next},
                           {"sfc32", sfc32_init, sfc32_next},
                           {"murmur3", murmur3_init, murmur3_next}};
    size_t num_generators = sizeof(generators) / sizeof(generators[0]);

    for (size_t i = 0; i < num_generators; i++) {
        benchmark(&generators[i]);
    }

    return 0;
}
