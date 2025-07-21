#include QMK_KEYBOARD_H

#include "shortcuts.h"

enum layers {
    _BASE = 0,
    _SYMBOLS,
    _NUMBERS,
    _ARROWS,
    _MOUSE,
    _MEDIA,
    _SPECIAL,
    _I3WM,
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_split_3x6_5_hlc(
      KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRAVE,
      KC_RCTL, S_A,     G_S,     A_D,     C_F,     KC_G,                                             KC_H,    C_J,     A_K,     G_L,     S_SC,    KC_QUOT,
      QK_LEAD, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    QK_LOCK, TO_BAS,       KC_UP,   KC_DOWN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_CIRC,
                                 I3_MENU, ARR_TAB, MOU_SPC, PAD_ENT, MED_ESC,      SPE_LFT, NUM_RGHT,SYM_BSP, KC_DEL,  KC_INS,
                                 KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [_SYMBOLS] = LAYOUT_split_3x6_5_hlc(
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR , KC_PERC,                                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
      _______, S_GRV,   G_SC,    A_COMM,  C_DOT,   KC_QUES,                                          KC_EQL,  C_LBRC,  A_RBRC,  G_BSLS,  S_SLSH,  KC_MINS,
      _______, KC_TILD, KC_COLN, KC_LT,   KC_GT,   KC_EXLM, _______, _______,      _______, _______, KC_PLUS, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_DQUO,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
                                 KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [_NUMBERS] = LAYOUT_split_3x6_5_hlc(
      _______, KC_F12,  KC_F11,  KC_F10,  KC_F9,   KC_PERC,                                          KC_LT, KC_7,    KC_8,    KC_9,    KC_PLUS, KC_ASTR,
      _______, S_F8,    G_F7,    A_F6,    C_F5,    KC_0,                                             KC_0,  C_4,     A_5,     G_6,     S_DOT,   KC_MINS,
      _______, KC_F4,   KC_F3,   KC_F2,   KC_F1,   KC_COMM, _______, _______,      _______, _______, KC_GT, KC_1,    KC_2,    KC_3,    KC_EQL,  KC_SLSH,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
                                 KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [_ARROWS] = LAYOUT_split_3x6_5_hlc(
      _______, KC_PASTE,KC_NO,   KC_CUT,  KC_COPY, KC_NO,                                            KC_NO,   KC_PGUP, KC_UP,   KC_END,  KC_NO,   KC_NO,
      _______, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,                                            KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  KC_NO,
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO  , QK_BOOT, _______, _______,      _______, _______, KC_NO,   KC_PGDN, KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
                                 KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [_MOUSE] = LAYOUT_split_3x6_5_hlc(
      _______, S_INS,   KC_NO,   KC_NO,   C_INS,   KC_NO,                                            KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_ACL0, KC_NO,
      _______, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,                                            KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_ACL0, KC_NO,
      _______, KC_ACL0, KC_ACL0, KC_ACL0, KC_ACL0, KC_NO,   _______, _______,      _______, _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_ACL0, KC_NO,
                                 _______, _______, _______, _______, _______,      _______, KC_BTN3, KC_BTN1, KC_BTN2, _______,
                                 KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [_MEDIA] = LAYOUT_split_3x6_5_hlc(
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                            KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_VOLU, KC_NO,
      _______, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,                                            A_LEFT,  C_TAB,   SC_TAB,  A_RGHT,  KC_MUTE, KC_NO,
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, _______,      _______, _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_VOLD, KC_NO,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
                                 KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [_SPECIAL] = LAYOUT_split_3x6_5_hlc(
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                            KC_INS,  KC_LNUM, KC_LCAP, KC_LSCR, KC_PAUSE,_______,
      _______, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,                                            KC_TAB,  KC_SPC,  KC_ENT,  KC_BSPC, KC_DEL,  _______,
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, _______,      _______, _______, KC_PSCR, KC_MENU, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
                                 KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [_I3WM] = LAYOUT_split_3x6_5_hlc(
      _______, WM_S1,   WM_S2,   WM_S3,   WM_S4,   WM_S5,                                            WM_SUP,  WM_SLEFT,WM_UP,  WM_SRGHT,WM_SSPC, WM_SQ,
      _______, WM_1,    WM_2,    WM_3,    WM_4,    WM_5,                                             WM_SDOWN,WM_LEFT, WM_DOWN,WM_RGHT, WM_SPC,  WM_SA,
      _______, WM_SE,   WM_SR,   WM_SC,   WM_SV,   KC_NO,   _______, _______,      _______, _______, WM_H,    WM_V,    WM_Z,   WM_E,    WM_ENT,  WM_D,
                                 _______, _______, _______, _______, _______,      _______, KC_LSFT, KC_LSFT, KC_LSFT, _______,
                                 KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO
    )
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT_split_3x6_5_hlc(
//       _______, _______, _______, _______, _______, _______,                                          _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                          _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
//                                  KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO
//     ),
};

//#ifdef LEADER_ENABLE
void leader_start_user(void) {}

void leader_end_user(void) {
    if (leader_sequence_three_keys(KC_L, KC_G, KC_L)) {
        SEND_STRING("glmxndr");
    }
}

//#endif

//#ifdef RGB_MATRIX_ENABLE
#define _BASE_COLOR          0x00, 0x00, 0x00  // Black
#define _BASE_COLOR_DIM      0x44, 0x44, 0x44  // Light gray

#define _SYMBOLS_COLOR       0xFF, 0x66, 0x00  // Bright orange
#define _SYMBOLS_COLOR_DIM   0x7F, 0x33, 0x00

#define _NUMBERS_COLOR       0x00, 0x99, 0xCC  // Medium cyan blue
#define _NUMBERS_COLOR_DIM   0x00, 0x4C, 0x66

#define _ARROWS_COLOR        0x66, 0xCC, 0x33  // Lime green
#define _ARROWS_COLOR_DIM    0x33, 0x66, 0x19

#define _MOUSE_COLOR         0xCC, 0x33, 0x99  // Magenta pink
#define _MOUSE_COLOR_DIM     0x66, 0x19, 0x4C

#define _MEDIA_COLOR         0x33, 0x99, 0x66  // Teal green
#define _MEDIA_COLOR_DIM     0x19, 0x4C, 0x33

#define _SPECIAL_COLOR       0xFF, 0xCC, 0x00  // Gold/yellow
#define _SPECIAL_COLOR_DIM   0x7F, 0x66, 0x00

#define _I3WM_COLOR          0x66, 0x66, 0xFF  // Soft blue-violet
#define _I3WM_COLOR_DIM      0x33, 0x33, 0x7F

bool rgb_matrix_indicators_user(void) {
    uint8_t current_layer = get_highest_layer(layer_state);
    switch (current_layer) {
        case _BASE:
            rgb_matrix_set_color_all(_BASE_COLOR_DIM);
            break;
        case _SYMBOLS:
            rgb_matrix_set_color_all(_SYMBOLS_COLOR_DIM);
            break;
        case _NUMBERS:
            rgb_matrix_set_color_all(_NUMBERS_COLOR_DIM);
            break;
        case _ARROWS:
            rgb_matrix_set_color_all(_ARROWS_COLOR_DIM);
            break;
        case _MOUSE:
            rgb_matrix_set_color_all(_MOUSE_COLOR_DIM);
            break;
        case _MEDIA:
            rgb_matrix_set_color_all(_MEDIA_COLOR_DIM);
            break;
        case _SPECIAL:
            rgb_matrix_set_color_all(_SPECIAL_COLOR_DIM);
            break;
        case _I3WM:
            rgb_matrix_set_color_all(_I3WM_COLOR_DIM);
            break;
        default:
            break;
    }
    return false;
}
//#endif