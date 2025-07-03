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

// clang-format off

// 以下でデフォルトのキーマップを設定する
// 番号が各レイヤ
// キーコード詳細は -> https://docs.qmk.fm/keycodes
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Layer 0 (O24 keybind layer)
    [0] = LAYOUT_universal(
        KC_Q     , KC_L     , KC_U     , KC_COMM  , KC_DOT   ,                            KC_F     , KC_W     , KC_R     , KC_Y     , KC_P     ,
        LT(4,KC_E), KC_I    , KC_A     , KC_O     , KC_MINS  ,                            KC_K     , KC_T     , KC_N     , KC_S     , KC_H     ,
        LSFT_T(KC_Z), KC_X  , KC_C     , KC_V     , KC_SCLN  ,                            KC_G     , KC_D     , KC_M     , KC_J     , RSFT_T(KC_B),
        KC_LGUI  , KC_LALT  , KC_LCTL  , LALT_T(KC_LNG2),LT(2,KC_SPC),LT(7,KC_LNG1),      RSFT_T(KC_TAB),LT(3,KC_ENT),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_ESC
    ),
    
    // Layer 1 (Text input layer)
    [1] = LAYOUT_universal(
        KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
        LT(4,KC_A), KC_S    , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_ENT   ,
        LSFT_T(KC_Z), KC_X  , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , RSFT_T(KC_MINS),
        KC_LGUI  , KC_LALT  , KC_LCTL  , LALT_T(KC_LNG2),LT(2,KC_SPC),LT(7,KC_LNG1),RSFT_T(KC_TAB),LT(3,KC_SPC),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_ESC
    ),

    // Layer 2 (Symbols and numbers, mouse click layer)
    [2] = LAYOUT_universal(
        KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                            KC_6     , KC_7     , KC_8     , KC_9     , KC_0     ,
        KC_BSLS  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            KC_EQL   , KC_BTN1  , KC_BTN3  , KC_BTN2  , KC_SCLN  ,
        KC_LSFT  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            KC_GRV   , KC_QUOT  , KC_LBRC  , KC_RBRC  , RSFT_T(KC_SLSH),
        _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , LT(3,KC_ENT)  , _______  , _______  , _______  , _______
    ),

    // Layer 3 (Function layer)
    [3] = LAYOUT_universal(
        KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
        KC_F11   , KC_F12   , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            KC_BSPC  , KC_PGUP  , KC_UP    , KC_PGDN  , AML_TO   ,
        KC_LSFT  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            KC_DEL   , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_RSFT  ,
        _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
    ),

    // Layer 4 (Emacs keybind layer)
    [4] = LAYOUT_universal(
        XXXXXXX  , XXXXXXX  , LCTL(KC_E), XXXXXXX , LCTL(KC_T),                           LCTL(KC_Y), XXXXXXX , XXXXXXX  , LCTL(KC_O), KC_UP   ,
        XXXXXXX  ,  LCTL(KC_A), KC_DEL , KC_RGHT  , XXXXXXX  ,                            KC_BSPC  , LCTL(KC_J),LCTL(KC_K),LCTL(KC_L), LCTL(KC_SCLN) ,
        KC_LSFT  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_LEFT  ,                            KC_DOWN  , KC_ENT   , XXXXXXX  , XXXXXXX  , KC_RSFT  ,
        _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
    ),

    // Layer 5
    [5] = LAYOUT_universal(
        XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,
        XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,
        KC_LSFT  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_RSFT  ,
        _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
    ),

    // Layer 6 (Auto mouse layer)
    [6] = LAYOUT_universal(
        TG(6)    , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            KC_BTN5  , XXXXXXX , XXXXXXX  , XXXXXXX  , XXXXXXX  ,
        XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            KC_BTN4  , KC_BTN1  , KC_BTN3  , KC_BTN2  , XXXXXXX  ,
        KC_LSFT  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                            XXXXXXX  , SCRL_MO  , SCRL_MOV , SCRL_MOH , KC_RSFT  ,
        _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
    ),

    // Layer 7 (Scroll and settings layer)
    [7] = LAYOUT_universal(
        CPI_D100 , CPI_I100 , SCRL_DVI , SCRL_DVD , KBC_SAVE ,                            KC_BTN5  , SSNP_FRE , SSNP_VRT , SSNP_HOR , TG(1)  ,
        KC_VOLD  , KC_VOLU  , KC_MUTE  , LCAG(KC_RGHT), XXXXXXX  ,                        KC_BTN4  , XXXXXXX  , XXXXXXX  , LCAG(KC_L), AML_TO  ,
        KC_LSFT  , XXXXXXX  , AML_D50  , AML_I50  , LCAG(KC_LEFT) ,                      LCAG(KC_N), LCAG(KC_M), SCRL_MOV, SCRL_MOH  , KC_RSFT ,
        _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
    )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 7
    keyball_set_scroll_mode(get_highest_layer(state) == 7);
    return state;
}

#ifdef OLED_ENABLE
#   include "lib/oledkit/oledkit.h"
    void oledkit_render_info_user(void) {
        keyball_oled_render_keyinfo(); // キー情報を表示
        keyball_oled_render_ballinfo(); // トラックボール情報を表示
        keyball_oled_render_layerinfo(); // レイヤ情報を表示
    }
#endif

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    void pointing_device_init_user(void) {
        set_auto_mouse_enable(true);
    }
#endif