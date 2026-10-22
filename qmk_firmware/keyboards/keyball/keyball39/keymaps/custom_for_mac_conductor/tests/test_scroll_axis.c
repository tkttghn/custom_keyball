/* SPDX-License-Identifier: GPL-2.0-or-later */
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include "scroll_axis.h"

enum { VERTICAL, HORIZONTAL, AUTO };
static int8_t h, v;

static void apply(int16_t x, int16_t y, bool left, uint16_t now, uint8_t mode, uint8_t divider) {
    conductor_scroll_apply(x, y, left, now, mode, divider, &h, &v);
    assert(h >= -127 && v >= -127);
    assert(h == 0 || v == 0); // Never leak a second axis.
}

int main(void) {
    conductor_scroll_reset();
    apply(1, 1, false, 0, AUTO, 4);
    assert(h == 0 && v == 0);
    apply(20, 20, false, 8, AUTO, 4);
    assert(h == 0 && v == 2); // Ties prefer vertical.

    // Small vertical motion must reach the wheel without a speed/dead-zone
    // threshold. The original scroll divider still retains sub-notch counts.
    conductor_scroll_reset();
    apply(0, 8, false, 0, AUTO, 4);
    assert(h == 0 && v == 1);
    conductor_scroll_reset();
    int total_v = 0;
    for (int i = 0; i < 16; ++i) {
        apply(1, 1, false, i * 8, AUTO, 4);
        assert(h == 0);
        total_v += v;
    }
    assert(total_v == 2); // Slow diagonal wobble remains vertical and linear.
    conductor_scroll_reset();
    total_v = 0;
    for (int i = 0; i < 8; ++i) {
        apply(0, -1, false, i * 8, AUTO, 4);
        total_v += v;
    }
    assert(total_v == -1);
    apply(0, 8, false, 256, AUTO, 4);
    assert(h == 0 && v == 1); // First small movement after 200ms idle.

    conductor_scroll_reset();
    for (uint16_t now = 16; now < 400; now += 8) {
        apply(3, 20, false, now, AUTO, 4);
        assert(h == 0 && v > 0); // Ongoing horizontal wobble stays suppressed.
    }
    bool switched = false;
    for (uint16_t now = 400; now < 480; now += 8) {
        apply(40, 0, false, now, AUTO, 4);
        if (h) switched = true;
    }
    assert(switched); // Deliberate horizontal motion can overcome a prior lock.

    conductor_scroll_reset();
    apply(20, 0, false, 0, AUTO, 4);
    assert(h == 1 && v == 0);
    apply(0, 20, false, 200, AUTO, 4);
    assert(h == 0 && v == 2); // 200ms idle permits a fresh axis choice.

    conductor_scroll_reset();
    apply(20, 0, false, 65530, AUTO, 4);
    apply(0, 20, false, 194, AUTO, 4);
    assert(h == 0 && v == 2); // Same timeout across timer rollover.

    conductor_scroll_reset();
    apply(200, 8, false, 0, VERTICAL, 4);
    assert(h == 0 && v == 1);
    apply(16, 200, false, 8, HORIZONTAL, 4);
    assert(h == 1 && v == 0); // Explicit axis keys override the automatic lock.

    conductor_scroll_reset();
    int total_h = 0;
    for (int i = 0; i < 16; ++i) {
        apply(1, 0, false, i * 8, HORIZONTAL, 4);
        total_h += h;
    }
    assert(total_h == 1); // Half horizontal sensitivity retains fractions.
    apply(0, 0, false, 136, HORIZONTAL, 4);
    assert(h == 0 && v == 0);

    conductor_scroll_reset();
    apply(8, 0, false, 0, HORIZONTAL, 4);
    assert(h == 0);
    apply(0, 0, false, 8, HORIZONTAL, 3);
    assert(h == 0);
    apply(8, 0, false, 16, HORIZONTAL, 3);
    assert(h == 1); // Divider changes don't release an old fractional count.

    conductor_scroll_reset();
    apply(0, 20, false, 0, AUTO, 4);
    apply(20, 0, true, 8, AUTO, 4);
    assert(h == 1 && v == 0); // Independent ball states.
    apply(3, 20, false, 16, AUTO, 4);
    assert(h == 0 && v > 0);

    conductor_scroll_reset();
    apply(INT16_MIN, INT16_MIN, false, 0, AUTO, 1);
    assert(h == 0 && v == -127);
    apply(INT16_MAX, INT16_MAX, false, 8, VERTICAL, 7);
    assert(h == 0 && v == 127);
    apply(INT16_MIN, 0, false, 16, HORIZONTAL, 1);
    assert(h == -127 && v == 0);
    apply(0, 0, false, 24, HORIZONTAL, 1);
    assert(h == 0 && v == 0); // No saturated excess drifts out later.

    puts("scroll axis: all checks passed");
    return 0;
}
