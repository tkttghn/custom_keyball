/* SPDX-License-Identifier: GPL-2.0-or-later */
#include "config.h"
#include "pointer_accel.h"

static int8_t clip_report(int32_t value) {
    return value < -127 ? -127 : value > 127 ? 127 : (int8_t)value;
}

#if CONDUCTOR_POINTER_ACCEL_ENABLE
_Static_assert(CONDUCTOR_POINTER_ACCEL_MAX_MILLI >= 1000 && CONDUCTOR_POINTER_ACCEL_MAX_MILLI <= 4000,
               "Pointer acceleration must be between 1.0x and 4.0x");
_Static_assert(CONDUCTOR_POINTER_ACCEL_THRESHOLD >= 0 && CONDUCTOR_POINTER_ACCEL_THRESHOLD <= 32767,
               "Invalid pointer acceleration threshold");
_Static_assert(CONDUCTOR_POINTER_ACCEL_RANGE > 0 && CONDUCTOR_POINTER_ACCEL_RANGE <= 32767,
               "Invalid pointer acceleration range");

// Separate fractional counts for each physical ball; no floating point needed.
static int16_t remainders[2][2];
static bool accel_bypassed;

// At 1.4x over 16 counts the gain is exactly (40 + over) / 40.
// Reducing the fraction saves AVR instructions without changing any output.
#if CONDUCTOR_POINTER_ACCEL_MAX_MILLI == 1400 && CONDUCTOR_POINTER_ACCEL_RANGE == 16
#    define ACCEL_UNITY 40
#else
#    define ACCEL_UNITY 1000
#endif

void conductor_pointer_accel_set_bypass(bool bypass) {
    if (bypass != accel_bypassed) {
        for (uint8_t side = 0; side < 2; ++side) {
            remainders[side][0] = remainders[side][1] = 0;
        }
        accel_bypassed = bypass;
    }
}

static int32_t magnitude(int32_t value) {
    return value < 0 ? -value : value;
}

static int32_t scale_axis(int16_t value, uint16_t gain, int16_t *remainder) {
    int32_t scaled = (int32_t)value * gain + *remainder;
    int32_t whole = scaled / ACCEL_UNITY;
    *remainder = scaled - whole * ACCEL_UNITY;
    return whole;
}

void conductor_pointer_accel_apply(int16_t x, int16_t y, bool is_left, int8_t *out_x, int8_t *out_y) {
    if (accel_bypassed) {
        *out_x = clip_report(x);
        *out_y = clip_report(y);
        return;
    }

    // Keyball reports accumulated motion every 8ms by default. Use the current
    // frame's combined X/Y magnitude, so both axes always receive the same gain.
    int32_t over = magnitude(x) + magnitude(y) - CONDUCTOR_POINTER_ACCEL_THRESHOLD;
    if (over < 0) {
        over = 0;
    } else if (over > CONDUCTOR_POINTER_ACCEL_RANGE) {
        over = CONDUCTOR_POINTER_ACCEL_RANGE;
    }
#if ACCEL_UNITY == 40
    uint16_t gain = ACCEL_UNITY + over;
#else
    uint16_t gain = ACCEL_UNITY + (CONDUCTOR_POINTER_ACCEL_MAX_MILLI - 1000) * over / CONDUCTOR_POINTER_ACCEL_RANGE;
#endif
    int16_t *remainder = remainders[is_left ? 1 : 0];
    int32_t scaled_x = scale_axis(x, gain, &remainder[0]);
    int32_t scaled_y = scale_axis(y, gain, &remainder[1]);

    // Fit one HID report without changing the direction of a fast diagonal.
    // Discard saturated excess rather than emitting delayed movement at rest.
    int32_t peak = magnitude(scaled_x);
    if (magnitude(scaled_y) > peak) {
        peak = magnitude(scaled_y);
    }
    if (peak > 127) {
        scaled_x = scaled_x * 127 / peak;
        scaled_y = scaled_y * 127 / peak;
        remainder[0] = remainder[1] = 0;
    }
    *out_x = (int8_t)scaled_x;
    *out_y = (int8_t)scaled_y;
}
#else
void conductor_pointer_accel_set_bypass(bool bypass) {
    (void)bypass;
}

void conductor_pointer_accel_apply(int16_t x, int16_t y, bool is_left, int8_t *out_x, int8_t *out_y) {
    (void)is_left;
    *out_x = clip_report(x);
    *out_y = clip_report(y);
}
#endif
