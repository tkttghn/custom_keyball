/*
This is the c configuration file for the keymap

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

// インクルードガード
#pragma once

// LED利用する場合(RGBLIGHT_ENABLEが未定義で無効化)
#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_EFFECT_BREATHING
#   define RGBLIGHT_EFFECT_RAINBOW_MOOD
#   define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#   define RGBLIGHT_EFFECT_SNAKE
#   define RGBLIGHT_EFFECT_KNIGHT
#   define RGBLIGHT_EFFECT_CHRISTMAS
#   define RGBLIGHT_EFFECT_STATIC_GRADIENT
#   define RGBLIGHT_EFFECT_RGB_TEST
#   define RGBLIGHT_EFFECT_ALTERNATING
#   define RGBLIGHT_EFFECT_TWINKLE
#endif

//
#define TAP_CODE_DELAY 5

//VIA(REMAP)で認識するレイヤー数を変更
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

// Tap Danceの設定
//#define TAPPING_TERM 175

// Automatic Mouse Layer(AML)の有効化
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// AMLで切り替えるマウスレイヤー番号
#define AUTO_MOUSE_DEFAULT_LAYER 4
// 元のレイヤーに戻るまでの時間(ms)
#define AUTO_MOUSE_TIME 400

// スクロールスナップモードを有効化
#define KEYBALL_SCROLLSNAP_ENABLE 2

// スクロール反転(1で有効)
#define KEYBALL_SCROLL_INV 0

// JIS->US設定の有効化(1で有効)
#define JIS2US_ENABLE 0

// Conductor tap-preferred keys; middle-click/scroll has a per-key hold policy.
// QMK 0.22.14 defaults: TAPPING_TERM=200, QUICK_TAP_TERM=TAPPING_TERM.
#define QUICK_TAP_TERM_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_TERM_PER_COMBO

// Pointer acceleration: raw counts per 8ms report, from 1.0x to 1.4x.
// Set ENABLE to 0 for the original pointer conversion.
#ifndef CONDUCTOR_POINTER_ACCEL_ENABLE
#    define CONDUCTOR_POINTER_ACCEL_ENABLE 1
#endif
#define CONDUCTOR_POINTER_ACCEL_MAX_MILLI 1400
#define CONDUCTOR_POINTER_ACCEL_THRESHOLD 4
#define CONDUCTOR_POINTER_ACCEL_RANGE 16

// Vertical scrolling starts immediately; threshold applies only to axis choice.
// Conductor's threshold 6 follows a 1/2 scaler, hence 12 raw Keyball counts.
#define CONDUCTOR_SCROLL_ACTIVATE_THRESHOLD 12
#define CONDUCTOR_SCROLL_RELEASE_MS 200

// These use Keyball report units; CPI and scroll scaling remain unchanged.
#define CONDUCTOR_GESTURE_THRESHOLD 120
#define CONDUCTOR_GESTURE_TIMEOUT 180
#define CONDUCTOR_GESTURE_COOLDOWN 220
#define CONDUCTOR_GESTURE_TAP 30
