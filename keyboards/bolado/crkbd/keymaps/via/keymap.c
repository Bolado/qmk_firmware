/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K LCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)


#define SHIFTENTER LSFT(KC_ENT)
#define LOWER MO(1)
#define RAISE MO(2)
#define ADJUST MO(3)
#define lowertab LT(LOWER, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    HOME_S,  HOME_D,  HOME_F,  KC_G,                         KC_H,    HOME_J,  HOME_K,  HOME_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          lowertab, KC_SPC,  KC_BSPC,     ADJUST, RAISE, KC_DEL
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,----XXXXXXX-------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      XXXXXXX, KC_7,   KC_8,   KC_9, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+-────────────────────+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_4,   KC_5,   KC_6, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+-────────────────────+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_1,   KC_2,   KC_3, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______,  XXXXXXX,     KC_0, _______, KC_DOT
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     XXXXXXX, KC_GRV,   KC_LT,   KC_GT,   KC_AT,   KC_PDOT,                      KC_EXLM, KC_AMPR, KC_LBRC, KC_RBRC, KC_UNDS,XXXXXXX,
  //|-------+-─────────────────────────────────────────────                    |-────────────────────────────────────────────-------+
     XXXXXXX, KC_DQUO,  KC_PMNS, KC_PPLS, KC_EQL,  KC_HASH,                      KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_PERC,XXXXXXX,
  //|-------+-─────────────────────────────────────────────                    |-────────────────────────────────────────────-------+
     XXXXXXX, KC_QUOT,  KC_PSLS, KC_ASTR, KC_CIRC, KC_NO,                        KC_TILD, KC_DLR,  KC_LCBR, KC_RCBR, KC_NO,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX,  XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //─────────────────────────────────────────────────────┤                       ├──────────────────────────────────────────────────────┤
     KC_MNXT, XXXXXXX, KC_HOME, KC_UP,   KC_END,  XXXXXXX,                        XXXXXXX, KC_HOME, KC_UP, KC_END, XXXXXXX, KC_VOLU,
  //─────────────────────────────────────────────────────┤                       ├──────────────────────────────────────────────────────┤
     KC_MPLY, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,                        SHIFTENTER, KC_LEFT, KC_DOWN,  KC_RGHT, KC_ENT, KC_MUTE,
  //─────────────────────────────────────────────────────┤                       ├──────────────────────────────────────────────────────┤
     KC_MPRV, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,                        XXXXXXX, KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_PSCR, _______, KC_PSCR,     KC_PSCR, _______, KC_PSCR
                                      //`--------------------------'  `--------------------------'
  )
};
