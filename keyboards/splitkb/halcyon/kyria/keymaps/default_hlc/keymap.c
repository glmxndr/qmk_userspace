#include QMK_KEYBOARD_H

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

#define LEADER QK_LEAD

#define _____ KC_TRANSPARENT

#define TO_BAS TO(_BASE)
#define TO_SYM TO(_SYMBOLS)
#define TO_ARR TT(_ARROWS)
#define TO_MSE TT(_MOUSE)
#define I3_MENU LT(_I3WM,KC_MENU)

#define ARR_TAB LT(_ARROWS, KC_TAB)
#define MOU_SPC LT(_MOUSE, KC_SPC)
#define PAD_ENT LT(_NUMBERS, KC_ENT)
#define SYM_ESC LT(_SYMBOLS, KC_ESC)
#define NUM_RGHT LT(_NUMBERS, KC_RIGHT)
#define SYM_BSP LT(_SYMBOLS, KC_BSPC)
#define MED_ESC LT(_MEDIA, KC_ESC)
#define SPE_LFT LT(_SPECIAL, KC_LEFT)


#define S_A  SFT_T(KC_A)
#define G_S  GUI_T(KC_S)
#define A_D  ALT_T(KC_D)
#define C_F  CTL_T(KC_F)

#define S_SC  SFT_T(KC_SCLN)
#define G_L  GUI_T(KC_L)
#define A_K  ALT_T(KC_K)
#define C_J  CTL_T(KC_J)

#define S_RBKT SFT_T(KC_RBRACKET)
#define G_LBKT GUI_T(KC_LBRACKET)
#define A_DOT  ALT_T(KC_DOT)
#define C_COMM CTL_T(KC_COMMA)

#define G_F4  GUI_T(KC_F4)
#define A_F5  ALT_T(KC_F5)
#define C_F6  CTL_T(KC_F6)

#define S_MINS SFT_T(KC_MINS)
#define G_3    GUI_T(KC_3)
#define A_2    ALT_T(KC_2)
#define C_1    CTL_T(KC_1)

#define S_INS LSFT(KC_INSERT)
#define C_INS LCTL(KC_INSERT)

#define G_GRV GUI_T(KC_GRV)
#define A_QUOT ALT_T(KC_QUOT)
#define C_EQL CTL_T(KC_EQL)
#define C_RBRC CTL_T(KC_RBRC)
#define A_SLSH ALT_T(KC_SLSH)
#define G_BSLS GUI_T(KC_BSLS)

#define WM_1 LGUI(KC_F1)
#define WM_2 LGUI(KC_F2)
#define WM_3 LGUI(KC_F3)
#define WM_4 LGUI(KC_F4)
#define WM_5 LGUI(KC_F5)
#define WM_6 LGUI(KC_F6)
#define WM_7 LGUI(KC_F7)
#define WM_8 LGUI(KC_F8)
#define WM_9 LGUI(KC_F9)
#define WM_0 LGUI(KC_F10)
#define WM_S1 SGUI(KC_F1)
#define WM_S2 SGUI(KC_F2)
#define WM_S3 SGUI(KC_F3)
#define WM_S4 SGUI(KC_F4)
#define WM_S5 SGUI(KC_F5)
#define WM_S6 SGUI(KC_F6)
#define WM_S7 SGUI(KC_F7)
#define WM_S8 SGUI(KC_F8)
#define WM_S9 SGUI(KC_F9)
#define WM_S0 SGUI(KC_F10)

#define WM_LEFT LGUI(KC_LEFT)
#define WM_RGHT LGUI(KC_RGHT)
#define WM_UP   LGUI(KC_UP)
#define WM_DOWN LGUI(KC_DOWN)
#define WM_SLEFT SGUI(KC_LEFT)
#define WM_SRGHT SGUI(KC_RGHT)
#define WM_SUP   SGUI(KC_UP)
#define WM_SDOWN SGUI(KC_DOWN)

#define WM_ENT LGUI(KC_ENT)
#define WM_SPC LGUI(KC_SPC)

#define WM_H LGUI(KC_H)
#define WM_V LGUI(KC_V)
#define WM_Z LGUI(KC_Z)
#define WM_E LGUI(KC_E)
#define WM_S LGUI(KC_S)
#define WM_D LGUI(KC_D)
#define WM_F SGUI(KC_F)

#define WM_SE SGUI(KC_E)
#define WM_SR SGUI(KC_R)
#define WM_SC SGUI(KC_C)
#define WM_SQ SGUI(KC_Q)
#define WM_SA SGUI(KC_A)
#define WM_SV SGUI(KC_V)
#define WM_SSPC SGUI(KC_SPC)

#define S_1 SFT_T(KC_1)
#define G_2 GUI_T(KC_2)
#define A_3 ALT_T(KC_3)
#define C_4 CTL_T(KC_4)
#define S_0 SFT_T(KC_0)
#define G_9 GUI_T(KC_9)
#define A_8 ALT_T(KC_8)
#define C_7 CTL_T(KC_7)

#define G_GRV GUI_T(KC_GRV)
#define A_QUOT ALT_T(KC_QUOT)
#define C_EQL CTL_T(KC_EQL)
#define C_RBRC CTL_T(KC_RBRC)
#define A_SLSH ALT_T(KC_SLSH)
#define G_BSLS GUI_T(KC_BSLS)

#define G_F4 GUI_T(KC_F4)
#define A_F5 ALT_T(KC_F5)
#define C_F6 CTL_T(KC_F6)
#define C_P4 CTL_T(KC_P4)
#define A_P5 ALT_T(KC_P5)
#define G_P6 GUI_T(KC_P6)
#define S_PMNS SFT_T(KC_PMNS)

#define A_LEFT LALT(KC_LEFT)
#define A_RGHT LALT(KC_RIGHT)
#define C_TAB LCTL(KC_TAB)
#define SC_TAB LCTL(LSFT(KC_TAB))

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
      _______, KC_PERC, KC_TILD, KC_DQUO, KC_PLUS, KC_ASTR,                                          KC_LPRN, KC_RPRN, KC_UNDS, KC_PIPE, KC_LT,   KC_NO,
      _______, KC_CIRC, G_GRV,   A_QUOT,  C_EQL,   KC_MINS,                                          KC_LBRC, C_RBRC,  A_SLSH,  G_BSLS,  KC_GT,   KC_NO,
      _______, _______, KC_AMPR, KC_DLR,  KC_AT,   KC_HASH, _______, _______,      _______, _______, KC_LCBR, KC_RCBR, KC_QUES, KC_EXLM, KC_NO,   KC_NO,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
                                 KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [_NUMBERS] = LAYOUT_split_3x6_5_hlc(
      _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_NO,
      _______, S_1,     G_2,     A_3,     C_4,     KC_5,                                             KC_6,    C_7,     A_8,     G_9,     S_0,     KC_NO,
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______, _______,      _______, _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                 _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______,
                                 KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    [_ARROWS] = LAYOUT_split_3x6_5_hlc(
      _______, KC_PASTE,KC_NO,   KC_CUT,  KC_COPY, KC_NO,                                            KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_NO,
      _______, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,                                            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,
      _______, KC_NO,   KC_NO,   KC_NO,   KC_NO  , QK_BOOT, _______, _______,      _______, _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
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