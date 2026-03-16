#ifndef ROMUDUO_H
#define ROMUDUO_H

#include <stdint.h>

static uint64_t ROMO_DUO_STATE1 = 0x1234567890abcdef;
static uint64_t ROMO_DUO_STATE2 = 0xfedcba0987654321;

static inline uint64_t romu_duo(void) {
    uint64_t xp = ROMO_DUO_STATE1;
    ROMO_DUO_STATE1 = 15241094284759029579U * ROMO_DUO_STATE2;
    ROMO_DUO_STATE2 = ROMO_DUO_STATE2 - xp;
    ROMO_DUO_STATE2 = (ROMO_DUO_STATE2 << 32) | (ROMO_DUO_STATE2 >> 32);
    return xp;
}

#endif    // !ROMUDUO_H
