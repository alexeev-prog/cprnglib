#include "stdint.h"

uint32_t jsf32_state[4] = {0x12345678, 0x9ABCDEF0, 0x13579BDF, 0x2468ACE0};

typedef struct {
    uint32_t a, b, c, d;
} jsf32_state_t;

static jsf32_state_t jsf32_global = {0x12345678, 0x9ABCDEF0, 0x13579BDF, 0x2468ACE0};

uint32_t jsf32() {
    jsf32_state_t* s = &jsf32_global;
    uint32_t e = s->a - ((s->b << 27) | (s->b >> 5));
    s->a = s->b ^ ((s->c << 17) | (s->c >> 15));
    s->b = s->c + s->d;
    s->c = s->d + e;
    s->d = e + s->a;
    return s->d;
}
