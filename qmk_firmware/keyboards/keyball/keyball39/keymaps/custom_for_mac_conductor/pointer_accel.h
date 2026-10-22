/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include <stdbool.h>
#include <stdint.h>

void conductor_pointer_accel_set_bypass(bool bypass);
void conductor_pointer_accel_apply(int16_t x, int16_t y, bool is_left, int8_t *out_x, int8_t *out_y);
