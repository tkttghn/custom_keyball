/* SPDX-License-Identifier: GPL-2.0-or-later */
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include "config.h"
#include "pointer_accel.h"

static void reset(void) {
    conductor_pointer_accel_set_bypass(true);
    conductor_pointer_accel_set_bypass(false);
}

static void expect(int16_t x, int16_t y, bool left, int8_t expected_x, int8_t expected_y) {
    int8_t out_x, out_y;
    conductor_pointer_accel_apply(x, y, left, &out_x, &out_y);
    assert(out_x == expected_x);
    assert(out_y == expected_y);
}

static int8_t original_clip(int16_t value) {
    return value < -127 ? -127 : value > 127 ? 127 : value;
}

int main(void) {
    // Original conversion is exact when bypassed, for every int16_t input.
    conductor_pointer_accel_set_bypass(true);
    for (int32_t value = INT16_MIN; value <= INT16_MAX; ++value) {
        expect(value, -value - 1, false, original_clip(value), original_clip(-value - 1));
    }
    reset();
#if CONDUCTOR_POINTER_ACCEL_ENABLE
    expect(4, 0, false, 4, 0);       // Start threshold: unity.
    expect(8, 0, false, 8, 0);       // 1.1x, fractional count retained.
    reset();
    expect(12, 0, false, 14, 0);     // 1.2x.
    reset();
    expect(20, 0, false, 28, 0);     // Upper threshold: exactly 1.4x.
    expect(40, 0, false, 56, 0);     // Gain stops at 1.4x.
    reset();
    expect(-20, 0, false, -28, 0);
    expect(0, -20, false, 0, -28);
    reset();
    expect(10, 10, false, 14, 14);   // One shared gain, diagonal preserved.
    reset();
    expect(200, 100, false, 127, 63); // Saturation preserves 2:1 direction.
    expect(0, 0, false, 0, 0);       // No delayed saturated excess.

    // Sub-count acceleration must accumulate instead of being rounded away.
    reset();
    int total = 0;
    for (int i = 0; i < 8; ++i) {
        int8_t x, y;
        conductor_pointer_accel_apply(5, 0, false, &x, &y);
        total += x;
        assert(y == 0);
    }
    assert(total == 41);             // 8 * 5 * 1.025, exactly.
    expect(0, 0, false, 0, 0);

    // No-ball reports on the opposite side must not consume fractional motion.
    reset();
    for (int i = 0; i < 7; ++i) {
        expect(5, 0, false, 5, 0);
        expect(0, 0, true, 0, 0);
    }
    expect(5, 0, false, 6, 0);

    // Scroll/gesture entry drops pointer fractions; exit starts clean.
    reset();
    for (int i = 0; i < 7; ++i) {
        expect(5, 0, false, 5, 0);
    }
    conductor_pointer_accel_set_bypass(true);
    expect(20, 0, false, 20, 0);
    conductor_pointer_accel_set_bypass(false);
    expect(5, 0, false, 5, 0);

    // Even int16_t extrema must not overflow intermediate arithmetic.
    reset();
    expect(INT16_MIN, INT16_MIN, false, -127, -127);
    expect(INT16_MAX, INT16_MAX, true, 127, 127);

    // Positive and negative motions are symmetric, including rounding.
    for (int value = 0; value < 256; ++value) {
        int8_t pos_x, pos_y, neg_x, neg_y;
        reset();
        conductor_pointer_accel_apply(value, value / 3, false, &pos_x, &pos_y);
        reset();
        conductor_pointer_accel_apply(-value, -(value / 3), false, &neg_x, &neg_y);
        assert(pos_x == -neg_x && pos_y == -neg_y);
    }
#else
    // Build-time OFF must exactly reproduce the original clipping as well.
    for (int32_t value = INT16_MIN; value <= INT16_MAX; ++value) {
        expect(value, -value - 1, false, original_clip(value), original_clip(-value - 1));
    }
#endif
    puts("pointer acceleration: all checks passed");
    return 0;
}
