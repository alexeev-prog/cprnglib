#include "stdint.h"

uint64_t ROMO_DUO_STATE1 = 0x1234567890abcdef;
uint64_t ROMO_DUO_STATE2 = 0xfedcba0987654321;

uint64_t romu_duo() {
    uint64_t xp = ROMO_DUO_STATE1;
    ROMO_DUO_STATE1 = 15241094284759029579u * ROMO_DUO_STATE2;
    ROMO_DUO_STATE2 = ROMO_DUO_STATE2 - xp;
    ROMO_DUO_STATE2 = (ROMO_DUO_STATE2 << 32) | (ROMO_DUO_STATE2 >> 32);
    return xp;
}
