#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifdef MACCEL_ENABLE
    #include "maccel/maccel.h"
#endif

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
    SYM,
    NUM,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define NUMER MO(NUM)
#define SYMER MO(SYM)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE


// Left-hand home row mods
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K LCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)

#define SHIFTENTER LSFT(KC_ENT)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_PSCR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_LSFT,   KC_A,    HOME_S,  HOME_D,  HOME_F,  KC_G,       KC_H,    HOME_J,  HOME_K,  HOME_L,  KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_LCTL,   PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, KC_LALT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                       NUMER, KC_SPC, KC_BSPC,     SYMER, RAISE,
                                              LOWER,  KC_TAB,      KC_DEL
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       RGB_TOG, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PEQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PDOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______,
                                           XXXXXXX, XXXXXXX,    XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────╯
),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MNXT, XXXXXXX, KC_HOME, KC_UP,   KC_END,  XXXXXXX,    XXXXXXX, KC_HOME, KC_UP, KC_END, XXXXXXX, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPLY, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,    SHIFTENTER, KC_LEFT, KC_DOWN,   KC_RGHT, KC_ENT, KC_MUTE,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_MPRV, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,    XXXXXXX, KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, KC_PSCR,    _______, XXXXXXX,
                                           _______, _______,    XXXXXXX
  //                       x     ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,  QK_BOOT,    QK_BOOT, EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX, KC_PWR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_RGUI, _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, KC_RGUI,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1,
                                           KC_BTN1, KC_BTN2,    KC_BTN2
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
  [SYM] = LAYOUT(
    // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_NO,  KC_GRV,   KC_LT,   KC_GT,   KC_AT,   KC_PDOT,     KC_EXLM, KC_AMPR, KC_LBRC, KC_RBRC, KC_UNDS,   KC_NO,
    // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_NO,  KC_DQUO,  KC_PMNS, KC_PPLS, KC_EQL,  KC_HASH,     KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_PERC, KC_NO,
    // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_NO,  KC_QUOT,  KC_PSLS, KC_ASTR, KC_CIRC, KC_NO,       KC_TILD, KC_DLR,  KC_LCBR, KC_RCBR, KC_NO,   KC_NO,
    // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX,
                                             XXXXXXX, XXXXXXX,     XXXXXXX
    //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
  [NUM] = LAYOUT(
    // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,
    // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,   KC_7,   KC_8,   KC_9,   KC_NO,    KC_NO,
    // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,   KC_4,   KC_5,   KC_6,   KC_NO,    KC_NO,
    // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_0,    KC_1,   KC_2,   KC_3,   KC_NO,    KC_NO,
    // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_0,
                                              KC_NO,    KC_NO,    KC_NO
    //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // ...
#ifdef MACCEL_ENABLE
    return pointing_device_task_maccel(mouse_report);
#endif
}

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif


#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    const uint8_t layer = get_highest_layer(layer_state);

    switch (layer) {
        case 0:
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
        case 1:
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case 2:
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case 3:
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        case 4:
            rgblight_sethsv_noeeprom(HSV_CYAN);
            break;
        case 5:
            rgblight_sethsv_noeeprom(HSV_WHITE);
            break;
        case 6:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            break;
        default:
            break;
    }

    HSV hsv = rgb_matrix_get_hsv();

    if (hsv.v > rgb_matrix_get_val()) {
            hsv.v = MIN(rgb_matrix_get_val() + 22, 255);
    }

    const RGB rgb = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i <= led_max; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return false;
}

#endif
