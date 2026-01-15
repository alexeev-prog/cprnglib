#include <stdint.h>

uint32_t sfc32_state[4] = {0x12345678, 0x9ABCDEF0, 0x13579BDF, 0x2468ACE0};

uint32_t sfc32() {
    uint32_t result = sfc32_state[0] + sfc32_state[1] + sfc32_state[3]++;
    sfc32_state[0] = sfc32_state[1] ^ (sfc32_state[1] >> 9);
    sfc32_state[1] = sfc32_state[2] + (sfc32_state[2] << 3);
    sfc32_state[2] = ((sfc32_state[2] << 21) | (sfc32_state[2] >> 11)) + result;
    return result;
}
