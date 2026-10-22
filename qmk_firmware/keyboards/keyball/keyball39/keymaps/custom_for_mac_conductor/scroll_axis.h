/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once
#include <stdbool.h>
#include <stdint.h>

void conductor_scroll_reset(void);
void conductor_scroll_apply(int16_t h, int16_t v, bool is_left, uint16_t now,
                            uint8_t snap_mode, uint8_t divider, int8_t *out_h, int8_t *out_v);
