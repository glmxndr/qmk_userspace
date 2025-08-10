#include QMK_KEYBOARD_H

#include "shortcuts.h"

enum layers {
    _BASE = 0,
    _SYMBOLS,
    _NUMPAD,
    _NUMBERS,
    _ARROWS,
    _MOUSE,
    _MEDIA,
    _SPECIAL,
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_split_3x6_5_hlc(
      KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRAVE,
      KC_RCTL, S_A,     G_S,     A_D,     C_F,     KC_G,                                             KC_H,    C_J,     A_K,     G_L,     S_SC,    KC_QUOT,
      QK_LEAD, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    QK_LOCK, TO_BAS,       KC_UP,   KC_DOWN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_CIRC,
                                 KC_MENU, MOU_TAB, ARR_SPC, KC_ENT,  MED_ESC,      SPE_LFT, NUM_RGHT,SYM_BSP, PAD_DEL, KC_INS
    ),

    [_SYMBOLS] = LAYOUT_split_3x6_5_hlc(
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR , KC_PERC,                                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
      _______, S_GRV,   G_SC,    A_COMM,  C_DOT,   KC_QUES,                                          KC_EQL,  C_LBRC,  A_RBRC,  G_BSLS,  S_SLSH,  KC_MINS,
      _______, KC_TILD, KC_COLN, KC_LT,   KC_GT,   KC_EXLM, _______, _______,      _______, _______, KC_PLUS, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_DQUO,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),
  
    [_NUMPAD] = LAYOUT_split_3x6_5_hlc(
      _______, KC_F12,  KC_F11,  KC_F10,  KC_F9,   KC_PERC,                                          KC_LT,   KC_7,    KC_8,    KC_9,    KC_PLUS, KC_ASTR,
      _______, S_F8,    G_F7,    A_F6,    C_F5,    KC_0,                                             KC_0,    C_4,     A_5,     G_6,     S_DOT,   KC_MINS,
      _______, KC_F4,   KC_F3,   KC_F2,   KC_F1,   KC_COMM, _______, _______,      _______, _______, KC_GT,   KC_1,    KC_2,    KC_3,    KC_EQL,  KC_SLSH,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),

    [_NUMBERS] = LAYOUT_split_3x6_5_hlc(
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR , KC_PERC,                                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______, S_1,     G_2,     A_3,     C_4,     KC_5,                                             KC_6,    C_7,     A_8,     G_9,     S_0,     KC_F12,
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______,      _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),
  
    [_ARROWS] = LAYOUT_split_3x6_5_hlc(
      _______, KC_PASTE,KC_NO,   KC_CUT,  KC_COPY, KC_NO,                                            KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_NO,
      _______, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,                                            KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_NO,
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO  , QK_BOOT, _______, _______,      _______, _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),

    [_MOUSE] = LAYOUT_split_3x6_5_hlc(
      _______, S_INS,   KC_NO,   KC_NO,   C_INS,   KC_NO,                                            KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_ACL0, KC_NO,
      _______, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,                                            KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_ACL0, KC_NO,
      _______, KC_ACL0, KC_ACL0, KC_ACL0, KC_ACL0, KC_NO,   _______, _______,      _______, _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_ACL0, KC_NO,
                                 _______, _______, _______, _______, _______,      _______, KC_BTN3, KC_BTN1, KC_BTN2, _______
    ),

    [_MEDIA] = LAYOUT_split_3x6_5_hlc(
      _______, KC_NO,   KC_NO,   KC_PASTE,KC_COPY, KC_CUT,                                           KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_VOLU, KC_NO,
      _______, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,                                            A_LEFT,  C_TAB,   SC_TAB,  A_RGHT,  KC_VOLD, KC_NO,
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, _______,      _______, _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MUTE, KC_NO,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
    ),

    [_SPECIAL] = LAYOUT_split_3x6_5_hlc(
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                            KC_INS,  KC_LNUM, KC_LCAP, KC_LSCR, KC_PAUSE,_______,
      _______, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,                                            KC_TAB,  KC_SPC,  KC_ENT,  KC_BSPC, KC_DEL,  _______,
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, _______,      _______, _______, KC_PSCR, KC_MENU, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
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

void leader_start_user(void) {}

void leader_end_user(void) {
    if (leader_sequence_three_keys(KC_L, KC_G, KC_L)) {
        SEND_STRING("glmxndr");
    }
    if (leader_sequence_four_keys(KC_W, KC_S, KC_E, KC_A)) {
        
    }
    
}

#define COLOR_BASE          0x00, 0x00, 0x00  // Black
#define COLOR_BASE_DIM      0x44, 0x44, 0x44  // Light gray

#define COLOR_SYMBOLS       0xFF, 0x66, 0x00  // Bright orange
#define COLOR_SYMBOLS_DIM   0x7F, 0x33, 0x00

#define COLOR_NUMPAD        0x66, 0x66, 0xFF  // Soft blue-violet
#define COLOR_NUMPAD_DIM    0x33, 0x33, 0x7F

#define COLOR_NUMBERS       0x00, 0x99, 0xCC  // Medium cyan blue
#define COLOR_NUMBERS_DIM   0x00, 0x4C, 0x66

#define COLOR_ARROWS        0x66, 0xCC, 0x33  // Lime green
#define COLOR_ARROWS_DIM    0x33, 0x66, 0x19

#define COLOR_MOUSE         0xCC, 0x33, 0x99  // Magenta pink
#define COLOR_MOUSE_DIM     0x66, 0x19, 0x4C

#define COLOR_MEDIA         0x33, 0x99, 0x66  // Teal green
#define COLOR_MEDIA_DIM     0x19, 0x4C, 0x33

#define COLOR_SPECIAL       0xFF, 0xCC, 0x00  // Gold/yellow
#define COLOR_SPECIAL_DIM   0x7F, 0x66, 0x00


bool rgb_matrix_indicators_user(void) {
    uint8_t current_layer = get_highest_layer(layer_state);
    switch (current_layer) {
        case _BASE:
            rgb_matrix_set_color_all(COLOR_BASE);
            break;
        case _SYMBOLS:
            rgb_matrix_set_color_all(COLOR_SYMBOLS_DIM);
            break;
        case _NUMBERS:
            rgb_matrix_set_color_all(COLOR_NUMBERS_DIM);
            break;
        case _ARROWS:
            rgb_matrix_set_color_all(COLOR_ARROWS_DIM);
            break;
        case _MOUSE:
            rgb_matrix_set_color_all(COLOR_MOUSE_DIM);
            break;
        case _MEDIA:
            rgb_matrix_set_color_all(COLOR_MEDIA_DIM);
            break;
        case _SPECIAL:
            rgb_matrix_set_color_all(COLOR_SPECIAL_DIM);
            break;
        default: 
            rgb_matrix_set_color_all(COLOR_BASE);
    }


    rgb_matrix_set_color(23, COLOR_BASE_DIM);
    rgb_matrix_set_color(22, COLOR_BASE_DIM);
    rgb_matrix_set_color(21, COLOR_BASE_DIM);
    rgb_matrix_set_color(20, COLOR_BASE_DIM);
    // === Left side
    #ifdef HLC_TFT_DISPLAY
        // To base
        rgb_matrix_set_color(11, COLOR_BASE_DIM);
        rgb_matrix_set_color(9, COLOR_MOUSE);
        rgb_matrix_set_color(8, COLOR_ARROWS);
        rgb_matrix_set_color(6, COLOR_MEDIA);
    #endif

    // === Right side
    #ifdef HLC_CIRQUE_TRACKPAD
        rgb_matrix_set_color(9, COLOR_SYMBOLS);
        rgb_matrix_set_color(8, COLOR_NUMBERS);
        rgb_matrix_set_color(7, COLOR_SPECIAL);
    #endif

    return false;
}
