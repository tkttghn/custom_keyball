/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "quantum.h"
#include <stdlib.h>
#include "pointer_accel.h"
#include "scroll_axis.h"

// Keep custom_for_mac's relative layer order; omit its QWERTY and empty layers.
enum layers { MAC, NUM, FN, EMACS, AML, SCROLL, SETTINGS, GESTURE };

#define SCROLL_MB3 LT(SCROLL, KC_BTN3)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC] = LAYOUT_universal(
        KC_Q,           KC_L,    KC_U,    KC_COMM,         KC_DOT,                                               KC_F,          KC_W,    KC_R,    KC_Y,    KC_P,
        LT(EMACS,KC_E), KC_I,    KC_A,    KC_O,            KC_MINS,                                              KC_K,          KC_T,    KC_N,    KC_S,    KC_H,
        LSFT_T(KC_Z),   KC_X,    KC_C,    KC_V,            KC_SCLN,                                              KC_G,          KC_D,    KC_M,    KC_J,    RSFT_T(KC_B),
        KC_LGUI,        KC_LALT, KC_LCTL, LGUI_T(KC_LNG2), LT(NUM,KC_SPC), LT(SCROLL,KC_LNG1),   RSFT_T(KC_TAB), LT(FN,KC_ENT), XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC
    ),

    [NUM] = LAYOUT_universal(
        KC_1,    KC_2,       KC_3,       KC_4,       KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_BSLS, LSFT(KC_2), LSFT(KC_8), LSFT(KC_1), LSFT(KC_SLSH),                     KC_EQL,  KC_BTN1, KC_BTN3, KC_BTN2, LSFT(KC_SLSH),
        KC_LSFT, _______,    LSFT(KC_9), LSFT(KC_0), LSFT(KC_3),                        KC_GRV,  KC_QUOT, KC_LBRC, KC_RBRC, RSFT_T(KC_SLSH),
        _______, _______,    _______,    _______,    _______,       _______,   _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______
    ),

    [FN] = LAYOUT_universal(
        KC_F1,   KC_F2,         KC_F3,      KC_F4,         KC_F5,                                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_F11,  KC_F12,        LCTL(KC_F), XXXXXXX,       XXXXXXX,                                    KC_BSPC, KC_BTN1, KC_UP,   KC_BTN2, XXXXXXX,
        KC_LSFT, LCTL(KC_LEFT), LCAG(KC_N), LCTL(KC_RGHT), LCTL(LSFT(LGUI(KC_4))),                     KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_RSFT,
        _______, _______,       _______,    _______,       _______,                _______,   _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______
    ),

    [EMACS] = LAYOUT_universal(
        _______, _______,    LCTL(KC_E), _______, _______,                     _______, _______,    _______,    _______,    KC_UP,
        _______, LCTL(KC_A), KC_DEL,     KC_RGHT, _______,                     KC_BSPC, LCTL(KC_J), LCTL(KC_K), LCTL(KC_L), LCTL(KC_SCLN),
        _______, _______,    _______,    _______, KC_LEFT,                     KC_DOWN, KC_ENT,     _______,    _______,    _______,
        _______, _______,    _______,    _______, _______, _______,   _______, _______, XXXXXXX,    XXXXXXX,    XXXXXXX,    _______
    ),

    [AML] = LAYOUT_universal(
        TG(AML), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_BTN5, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_BTN4, KC_BTN1, KC_BTN3,  KC_BTN2,  XXXXXXX,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, SCRL_MO, SCRL_MOV, SCRL_MOH, KC_RSFT,
        _______, _______, _______, _______, _______, _______,   _______, _______, XXXXXXX, XXXXXXX,  XXXXXXX,  _______
    ),

    [SCROLL] = LAYOUT_universal(
        KC_BRID, KC_BRIU, XXXXXXX, LGUI(KC_MINS), LSFT(LGUI(KC_EQL)),                     KC_BTN5,       XXXXXXX, XXXXXXX,    XXXXXXX,    LCAG(KC_UP),
        KC_VOLD, KC_VOLU, KC_MUTE, LCAG(KC_RGHT), XXXXXXX,                                KC_BTN4,       XXXXXXX, LCAG(KC_N), LCAG(KC_L), _______,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX,       LCAG(KC_LEFT),                          LCAG(KC_DOWN), XXXXXXX, LCAG(KC_M), XXXXXXX,    KC_RSFT,
        _______, _______, _______, _______,       MO(SETTINGS),       _______,   _______, _______,       XXXXXXX, XXXXXXX,    XXXXXXX,    _______
    ),

    [SETTINGS] = LAYOUT_universal(
        CPI_D100, CPI_I100, SCRL_DVI, SCRL_DVD, KBC_SAVE,                     XXXXXXX, SSNP_FRE, SSNP_VRT, SSNP_HOR, XXXXXXX,
        _______,  _______,  _______,  _______,  _______,                      XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  AML_TO,
        _______,  _______,  AML_D50,  AML_I50,  _______,                      XXXXXXX, XXXXXXX,  SCRL_MOV, SCRL_MOH, _______,
        _______,  _______,  _______,  _______,  _______,  _______,   _______, _______, XXXXXXX,  XXXXXXX,  XXXXXXX,  _______
    ),

    [GESTURE] = LAYOUT_universal(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX,       LCTL(KC_DOWN), XXXXXXX,       XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, LCTL(KC_RGHT), XXXXXXX,       LCTL(KC_LEFT), XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX,       LCTL(KC_UP),   XXXXXXX,       XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX
    ),
};
// clang-format on

_Static_assert(ARRAY_SIZE(keymaps) == 8, "Keep this VIA keymap within eight layers");
_Static_assert(AUTO_MOUSE_DEFAULT_LAYER == AML, "AML layer must match config.h");

enum combos { CLICK_LEFT, CLICK_MIDDLE_SCROLL, CLICK_RIGHT, HOLD_GESTURE };
const uint16_t PROGMEM click_left[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM click_middle_scroll[] = {KC_N, KC_S, COMBO_END};
const uint16_t PROGMEM click_right[] = {KC_S, KC_H, COMBO_END};
const uint16_t PROGMEM hold_gesture[] = {KC_R, KC_Y, COMBO_END};

combo_t key_combos[] = {
    [CLICK_LEFT] = COMBO(click_left, KC_BTN1),
    [CLICK_MIDDLE_SCROLL] = COMBO(click_middle_scroll, SCROLL_MB3),
    [CLICK_RIGHT] = COMBO(click_right, KC_BTN2),
    [HOLD_GESTURE] = COMBO(hold_gesture, MO(GESTURE)),
};

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    (void)combo;
    return index == HOLD_GESTURE ? 50 : 25;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    return keycode == SCROLL_MB3;
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    return keycode == SCROLL_MB3 ? 0 : QUICK_TAP_TERM;
}

static int16_t gesture_x, gesture_y;
static uint16_t gesture_started, gesture_cooldown_started, gesture_key_started;
static uint16_t gesture_key;
static bool gesture_pending, gesture_cooling;

static void gesture_release_key(void) {
    if (gesture_key) {
        unregister_code16(gesture_key);
        gesture_key = 0;
    }
}

static void gesture_reset(void) {
    gesture_x = gesture_y = 0;
    gesture_pending = false;
}

static uint8_t momentary_scroll;

void keyball_on_apply_motion_to_mouse_move(keyball_motion_t *motion, report_mouse_t *report, bool is_left) {
    conductor_pointer_accel_set_bypass(layer_state_is(GESTURE) || keyball_get_scroll_mode());
    // Preserve Keyball39's axis swap and left-ball orientation.
    conductor_pointer_accel_apply(motion->y, motion->x, is_left, &report->x, &report->y);
    if (is_left) {
        report->x = -report->x;
        report->y = -report->y;
    }
    motion->x = motion->y = 0;
}

void keyball_on_apply_motion_to_mouse_scroll(keyball_motion_t *motion, report_mouse_t *report, bool is_left) {
    conductor_scroll_apply(motion->y, motion->x, is_left, timer_read(),
                           keyball_get_scrollsnap_mode(), keyball_get_scroll_div(), &report->h, &report->v);
    // Preserve Keyball39's orientation and configured scroll inversion.
    report->v = -report->v;
    if (is_left) {
        report->h = -report->h;
        report->v = -report->v;
    }
#if KEYBALL_SCROLL_INV
    report->h = -report->h;
    report->v = -report->v;
#endif
    motion->x = motion->y = 0;
}

static void update_scroll_mode(layer_state_t state) {
    // Preserve held SCRL_MO/MOV/MOH across AML and other layer changes.
    bool gesture = layer_state_cmp(state, GESTURE);
    bool scrolling = !gesture && (layer_state_cmp(state, SCROLL) || momentary_scroll);
    keyball_set_scroll_mode(scrolling);
    conductor_pointer_accel_set_bypass(gesture || scrolling);
    if (!scrolling) {
        conductor_scroll_reset();
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // The original AML sits above NUM/FN/EMACS. Keep that numbering order,
    // but let explicit Conductor layers take precedence over automatic AML.
    const layer_state_t manual_layers = (1UL << NUM) | (1UL << FN) | (1UL << EMACS) |
                                        (1UL << SCROLL) | (1UL << SETTINGS) | (1UL << GESTURE);
    if (state & manual_layers) {
        state = remove_auto_mouse_layer(state, true);
    }
    update_scroll_mode(state);
    if (!layer_state_cmp(state, GESTURE)) {
        gesture_release_key();
        gesture_reset();
        gesture_cooling = false;
    }
    return state;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mask;
    switch (keycode) {
        case SCRL_MO:  mask = 1; break;
        case SCRL_MOV: mask = 2; break;
        case SCRL_MOH: mask = 4; break;
        default: return;
    }
    if (record->event.pressed) {
        momentary_scroll |= mask;
    } else {
        momentary_scroll &= ~mask;
    }
    // Keyball's handler sets scroll=false on release; restore any layer owner.
    update_scroll_mode(layer_state);
}

report_mouse_t pointing_device_task_user(report_mouse_t report) {
    if (!layer_state_is(GESTURE)) {
        return report;
    }

    int16_t x = report.x, y = report.y;
    // Gestures consume motion but leave button state/release reports intact.
    report.x = report.y = report.h = report.v = 0;
    if (gesture_cooling) {
        if (timer_elapsed(gesture_cooldown_started) < CONDUCTOR_GESTURE_COOLDOWN) {
            return report;
        }
        gesture_cooling = false;
    }
    if (gesture_pending && timer_elapsed(gesture_started) > CONDUCTOR_GESTURE_TIMEOUT) {
        gesture_reset();
    }
    if (!x && !y) {
        return report;
    }
    if (!gesture_pending) {
        gesture_started = timer_read();
        gesture_pending = true;
    }
    gesture_x += x;
    gesture_y += y;
    if (abs(gesture_x) < CONDUCTOR_GESTURE_THRESHOLD && abs(gesture_y) < CONDUCTOR_GESTURE_THRESHOLD) {
        return report;
    }

    // Resolve the four Conductor gesture positions through the QMK keymap,
    // so VIA edits to GESTURE also change the trackball's output.
    keypos_t position;
    if (abs(gesture_y) >= abs(gesture_x)) {
        position = gesture_y < 0 ? (keypos_t){.row = 4, .col = 2}
                                 : (keypos_t){.row = 6, .col = 2};
    } else {
        position = gesture_x < 0 ? (keypos_t){.row = 5, .col = 3}
                                 : (keypos_t){.row = 5, .col = 1};
    }
    uint16_t keycode = keymap_key_to_keycode(GESTURE, position);
    gesture_reset();
    gesture_cooling = true;
    gesture_cooldown_started = timer_read();
    // Layer/tap-hold/Keyball custom actions require an event dispatcher rather
    // than register_code16. Reject them instead of sending a truncated keycode.
    if (keycode <= KC_TRNS || !(IS_QK_BASIC(keycode) || IS_QK_MODS(keycode))) {
        return report;
    }
    gesture_release_key();
    gesture_key = keycode;
    register_code16(gesture_key);
    gesture_key_started = timer_read();
    return report;
}

void matrix_scan_user(void) {
    // Release asynchronously; a gesture must not block key scanning for 30ms.
    if (gesture_key && timer_elapsed(gesture_key_started) >= CONDUCTOR_GESTURE_TAP) {
        gesture_release_key();
    }
}

#ifdef OLED_ENABLE
#    include "lib/oledkit/oledkit.h"
void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}
#endif
