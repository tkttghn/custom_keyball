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
#define TAP_CODE_DELAY (5)

//VIA(REMAP)で認識するレイヤー数を変更
#define DYNAMIC_KEYMAP_LAYER_COUNT (7)

// Automatic Mouse Layer(AML)の有効化
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// 切り替えるマウスレイヤー番号
#define AUTO_MOUSE_DEFAULT_LAYER (5)
// 元のレイヤーに戻るまでの時間(ms)
#define AUTO_MOUSE_TIME (500)