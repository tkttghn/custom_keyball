/*
 * Based on Conductor's input_processor_axis_lock.c.
 * Copyright (c) 2026 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "config.h"
#include "scroll_axis.h"

enum { VERTICAL, HORIZONTAL, AUTO };
typedef struct {
    uint16_t mag_h, mag_v, last_motion;
    int16_t remainder_h, remainder_v;
    uint8_t lock, setting;
} scroll_state_t;
static scroll_state_t states[2];

_Static_assert(CONDUCTOR_SCROLL_ACTIVATE_THRESHOLD > 0 && CONDUCTOR_SCROLL_ACTIVATE_THRESHOLD <= 7500,
               "Invalid scroll activation threshold");
_Static_assert(CONDUCTOR_SCROLL_RELEASE_MS > 0 && CONDUCTOR_SCROLL_RELEASE_MS < 32768,
               "Invalid scroll release interval");

void conductor_scroll_reset(void) {
    // Valid dividers are 1..7, so zero cannot match a live setting. Clear the
    // full state lazily on its next report rather than duplicating that code.
    states[0].setting = states[1].setting = 0;
}

static uint16_t recent_magnitude(uint16_t previous, int16_t delta) {
    // Unsigned subtraction also handles INT16_MIN without a 32-bit negate.
    uint16_t amount = delta < 0 ? 0U - (uint16_t)delta : (uint16_t)delta;
    uint16_t sum = previous + amount;
    if (sum > 10000) {
        sum = 10000;
    }
    return sum - sum / 4;
}

static int8_t scroll_count(int16_t delta, int16_t *remainder, uint16_t divisor) {
    int32_t total = (int32_t)delta + *remainder;
    // For divisors 1..128 the quotient fits int16_t: at divisor 1 the
    // remainder is zero, and larger divisors bound it below the input range.
    int16_t whole = total / divisor;
    *remainder = total % divisor;
    return whole < -127 ? -127 : whole > 127 ? 127 : (int8_t)whole;
}

void conductor_scroll_apply(int16_t h, int16_t v, bool is_left, uint16_t now,
                            uint8_t snap_mode, uint8_t divider, int8_t *out_h, int8_t *out_v) {
    scroll_state_t *s = &states[is_left ? 1 : 0];
    uint8_t setting = snap_mode | (divider << 2);
    if (s->setting != setting || (uint16_t)(now - s->last_motion) >= CONDUCTOR_SCROLL_RELEASE_MS) {
        s->mag_h = s->mag_v = 0;
        s->remainder_h = s->remainder_v = 0;
        // Start vertical immediately. Waiting for a movement threshold here
        // discarded every slow input, so its fractional counts never built up.
        s->lock = VERTICAL;
        s->setting = setting;
    }
    if (h || v) {
        s->last_motion = now;
    }

    uint8_t lock = snap_mode;
    if (snap_mode == AUTO) {
        // Decide after BOTH axes are available, with vertical winning ties.
        s->mag_h = recent_magnitude(s->mag_h, h);
        s->mag_v = recent_magnitude(s->mag_v, v);
        bool horizontal = s->mag_h > s->mag_v;
        uint16_t win = horizontal ? s->mag_h : s->mag_v;
        uint16_t lose = horizontal ? s->mag_v : s->mag_h;
        if (win >= CONDUCTOR_SCROLL_ACTIVATE_THRESHOLD && win >= lose * 2) {
            s->lock = horizontal ? HORIZONTAL : VERTICAL;
        }
        lock = s->lock;
    }
    if (lock != HORIZONTAL) {
        h = 0;
        s->remainder_h = 0;
    }
    if (lock != VERTICAL) {
        v = 0;
        s->remainder_v = 0;
    }
    uint16_t divisor = 1U << (divider - 1);
    *out_h = scroll_count(h, &s->remainder_h, divisor * 2);
    *out_v = scroll_count(v, &s->remainder_v, divisor);
}
