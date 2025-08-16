// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPLIT_TRANSACTION_IDS_KB MODULE_SYNC

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
#define LEADER_NO_TIMEOUT

#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_COMBINED

#define HLC_BACKLIGHT_TIMEOUT 120000

#define BACKLIGHT_PWM_DRIVER PWMD5
#define BACKLIGHT_LEVELS 10
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_B

//// Keyboard redefines

// Always the same
#define BACKLIGHT_PIN GP2 //NOT CONNECTED
#define POINTING_DEVICE_CS_PIN GP2 //NOT CONNECTED
#define HLC_ENCODER_A NO_PIN
#define HLC_ENCODER_B NO_PIN

#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_LAYER_STATE_ENABLE

// Kyria
#undef ENCODER_A_PINS
#define ENCODER_A_PINS { GP23, HLC_ENCODER_A }
#undef ENCODER_B_PINS
#define ENCODER_B_PINS { GP22, HLC_ENCODER_B }

#undef MATRIX_ROWS
#define MATRIX_ROWS 10

#define LAYOUT_split_3x6_5_hlc( \
    k0G, k0F, k0E, k0D, k0C, k0B,                                k5B, k5C, k5D, k5E, k5F, k5G, \
    k1G, k1F, k1E, k1D, k1C, k1B,                                k6B, k6C, k6D, k6E, k6F, k6G, \
    k2G, k2F, k2E, k2D, k2C, k2B,    k3D, k2A,      k7A, k8D,    k7B, k7C, k7D, k7E, k7F, k7G, \
                      k3E, k3C, k3B, k3F, k3A,      k8A, k8F, k8B, k8C, k8E \
) { \
    {KC_NO, k0B,   k0C,   k0D,   k0E,   k0F,   k0G}, \
    {KC_NO, k1B,   k1C,   k1D,   k1E,   k1F,   k1G}, \
    {k2A,   k2B,   k2C,   k2D,   k2E,   k2F,   k2G}, \
    {k3A,   k3B,   k3C,   k3D,   k3E,   k3F,   KC_NO}, \
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO}, \
    {KC_NO, k5B,   k5C,   k5D,   k5E,   k5F,   k5G}, \
    {KC_NO, k6B,   k6C,   k6D,   k6E,   k6F,   k6G}, \
    {k7A,   k7B,   k7C,   k7D,   k7E,   k7F,   k7G}, \
    {k8A,   k8B,   k8C,   k8D,   k8E,   k8F,   KC_NO}, \
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO} \
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

#define COLOR_I3WM          0x00, 0xCC, 0xFF  // Green blue
#define COLOR_I3WM_DIM      0x00, 0x66, 0x7F
