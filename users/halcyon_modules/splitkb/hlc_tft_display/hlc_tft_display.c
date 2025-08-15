// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <string.h>
#include <stdio.h>

#include "halcyon.h"
#include "hlc_tft_display.h"

#include "hardware/structs/rosc.h"

// Fonts mono2
#include "graphics/fonts/tiny-12.qff.h"
#define FONT_WIDTH 7

// Numbers mono2
#include "graphics/numbers/undef.qgf.h"

#define GRID_LIGH 0x0, 0x0, 0xC0
#define GRID_DARK 0x0, 0x30, 0x30
#define XOFFSET 0
#define MAX_LAYERS 8
#define LEFT_ROWS 3
#define RIGHT_ROWS 3
#define LEFT_COLS 5
#define RIGHT_COLS 6

static painter_font_handle_t dafont;

static uint8_t lcd_surface_fb[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(135, 240, 16)];

int color_value = 0;

painter_device_t lcd;
painter_device_t lcd_surface;

led_t last_led_usb_state = {0};
layer_state_t last_layer_state = {0};
uint8_t last_mods = 0;

// Table: layers × (left+right rows) × columns
static const char *keymaps[MAX_LAYERS][LEFT_ROWS + RIGHT_ROWS][RIGHT_COLS] = {
    // Layer 0 - BASE
    {
        { "Q",   "W",   "E",   "R",   "T" },
        { "A",   "S",   "D",   "F",   "G" },
        { "Z",   "X",   "C",   "V",   "B" },

        { "Y",   "U",   "I",   "O",   "P",   "`" },
        { "H",   "J",   "K",   "L",   ":",   "'" },
        { "N",   "M",   ",",   ".",   "/",   "^" },
    },
    // Layer 1 - SYMBOLS
    {
        { "!",   "@",   "#",   "$",   "%" },
        { "`",   ";",   ",",   ".",   "?" },
        { "~",   ":",   "<",   ">",   "!" },

        { "^",   "&",   "*",   "(",   ")",   "_" },
        { "=",   "[",   "]",   "\\",  "/",   "-" },
        { "+",   "(",   ")",   "{",   "}",   "\"" },
    },
    // Layer 2 - NUMPAD
    {
        { "F12",  "F11",  "F10",  "F9",  "%"   },
        { "F8",   "F7",   "F6",   "F5",  "0"   },
        { "F4",   "F3",   "F2",   "F1",  ","   },

        { "<",    "7",    "8",    "9",   "+",   "*" },
        { "0",    "4",    "5",    "6",   ".",   "-" },
        { ">",    "1",    "2",    "3",   "=",   "/" },
    },
    // Layer 3 - NUMBERS
    {
        { "!",   "@",   "#",   "$",   "%"   },
        { "1",   "2",   "3",   "4",   "5"   },
        { "F1",  "F2",  "F3",  "F4",  "F5"  },

        { "^",   "&",   "*",   "(",   ")",   "_"   },
        { "6",   "7",   "8",   "9",   "0",   "F12" },
        { "F6",  "F7",  "F8",  "F9",  "F10", "F11" },
    },
    // Layer 4 - ARROWS
    {
        { "C-V", "",    "C-X", "C-C", "" },
        { "SFT", "GUI", "ALT", "CTL", "" },
        { "",    "",    "",    "",    "" },

        { "",    "<=",  "^",   "=>",  "P^", "" },
        { "",    "<",   "v",   ">",   "Pv", "" },
        { "",    "",    "",    "",    "",   "" },
    },
    // Layer 5 - MOUSE
    {
        { "",    "",    "",    "",    "" },
        { "SFT", "GUI", "ALT", "CTL", "" },
        { "",    "Bn3", "Bn2", "Bn1", "" },

        { "W^",  "W<",  "^",   "W>",  "Ac2", "" },
        { "Wv",  "<",   "v",   ">",   "Ac1", "" },
        { "Bn4", "Bn1", "Bn2", "Bn3", "Ac0", "" },
    },
    // Layer 6 - MEDIA
    {
        { "",    "C-V", "C-C", "C-X", "" },
        { "SFT", "GUI", "ALT", "CTL", "" },
        { "",    "",    "",    "",    "" },
        { "prv", "ply", "stp", "nxt", "vo+", "" },
        { "a<",  "C<>", "",  "a>", "vo-", "" },
        { "",    "",    "",     "",   "mut", "" },
    },
    // Layer 7 - SPECIAL
    {
        { "",    "",    "MR2", "MR1", ""    },
        { "SFT", "GUI", "ALT", "CTL", "STP" },
        { "",    "",    "MP2", "MP1", ""    },

        { "ins", "nmL", "cpL", "scL", "POS", "BUT" },
        { "tab", "spc", "ent", "<=",  "del", ""    },
        { "psc", "men", "",    "",    "",    ""    },
    }
};

static void pad_to_width(const char *src, char *dest) {
    size_t len = strlen(src);
    if (len > 3) {
        strncpy(dest, src, 3);   // truncate
        dest[3] = '\0';
    } else {
        int left_pad = (3 - len) / 2;    // center text
        int right_pad = 3 - len - left_pad;
        int pos = 0;

        for (int i = 0; i < left_pad; i++) dest[pos++] = ' ';
        for (size_t i = 0; i < len; i++)  dest[pos++] = src[i];
        for (int i = 0; i < right_pad; i++) dest[pos++] = ' ';
        dest[3] = '\0';
    }
}

void draw_keymap_row(
    int y,
    const char *keys[],
    size_t key_count,
    bool invert
) {
    char buf[4];
    int spacing = 3 * FONT_WIDTH;
    for (size_t i = 0; i < key_count; i++) {
        pad_to_width(keys[i], buf);
        (i % 2 == 0)
            ? invert
                ? qp_drawtext_recolor(lcd_surface, XOFFSET + i * spacing, y, dafont, buf, HSV_BLACK, GRID_LIGH)
                : qp_drawtext_recolor(lcd_surface, XOFFSET + i * spacing, y, dafont, buf, HSV_WHITE, GRID_DARK)
            : invert
                ? qp_drawtext_recolor(lcd_surface, XOFFSET + i * spacing, y, dafont, buf, HSV_WHITE, GRID_DARK)
                : qp_drawtext_recolor(lcd_surface, XOFFSET + i * spacing, y, dafont, buf, HSV_BLACK, GRID_LIGH);
    }
}

void draw_layer(uint8_t layer) {
    int line_height = dafont->line_height;
    int y_positions[] = {
        LCD_HEIGHT - 10 * line_height,
        LCD_HEIGHT -  9 * line_height,
        LCD_HEIGHT -  8 * line_height,
        LCD_HEIGHT -  6 * line_height - 5,
        LCD_HEIGHT -  5 * line_height - 5,
        LCD_HEIGHT -  4 * line_height - 5
    };

    for (int row = 0; row < LEFT_ROWS + RIGHT_ROWS; row++) {
        int col_count = (row < LEFT_ROWS) ? LEFT_COLS : RIGHT_COLS;
        bool invert = (row % 2 == 1);
        draw_keymap_row(y_positions[row], keymaps[layer][row], col_count, invert);
    }
}

void update_display(void) {
    static bool first_run_led = false;
    static bool first_run_layer = false;
    static bool first_run_mods = false;

    if( first_run_layer == false) {
        dafont = qp_load_font_mem(font_tiny_12);
    }
    int line_height = dafont->line_height;

    if(last_led_usb_state.raw != host_keyboard_led_state().raw || first_run_led == false) {
        led_t led_usb_state = host_keyboard_led_state();
        qp_drawtext_recolor(lcd_surface, XOFFSET, 3 * line_height, dafont, "LCK ", HSV_WHITE, HSV_BLACK);
        led_usb_state.caps_lock
            ? qp_drawtext_recolor(lcd_surface, XOFFSET +  4 * FONT_WIDTH, 3 * line_height, dafont, "CAP", HSV_BLACK, HSV_WHITE)
            : qp_drawtext_recolor(lcd_surface, XOFFSET +  4 * FONT_WIDTH, 3 * line_height, dafont, "cap", HSV_WHITE, HSV_BLACK);
        led_usb_state.num_lock
            ? qp_drawtext_recolor(lcd_surface, XOFFSET +  8 * FONT_WIDTH, 3 * line_height, dafont, "NUM", HSV_BLACK, HSV_WHITE)
            : qp_drawtext_recolor(lcd_surface, XOFFSET +  8 * FONT_WIDTH, 3 * line_height, dafont, "num", HSV_WHITE, HSV_BLACK);
        led_usb_state.scroll_lock
            ? qp_drawtext_recolor(lcd_surface, XOFFSET + 12 * FONT_WIDTH, 3 * line_height, dafont, "SCR", HSV_BLACK, HSV_WHITE)
            : qp_drawtext_recolor(lcd_surface, XOFFSET + 12 * FONT_WIDTH, 3 * line_height, dafont, "scr", HSV_WHITE, HSV_BLACK);
        last_led_usb_state = led_usb_state;
        first_run_led = true;
    }

    const uint8_t mods = get_mods() | get_oneshot_mods();
    if(last_mods != mods || first_run_mods == false) {
        qp_drawtext_recolor(lcd_surface, XOFFSET, 2 * line_height, dafont, "MOD ", HSV_WHITE, HSV_BLACK);
        (mods & MOD_MASK_CTRL) > 0
            ? qp_drawtext_recolor(lcd_surface, XOFFSET +  4 * FONT_WIDTH, 2 * line_height, dafont, "CTL", HSV_BLACK, HSV_WHITE)
            : qp_drawtext_recolor(lcd_surface, XOFFSET +  4 * FONT_WIDTH, 2 * line_height, dafont, "ctl", HSV_WHITE, HSV_BLACK);
        (mods & MOD_MASK_ALT) > 0
            ? qp_drawtext_recolor(lcd_surface, XOFFSET +  8 * FONT_WIDTH, 2 * line_height, dafont, "ALT", HSV_BLACK, HSV_WHITE)
            : qp_drawtext_recolor(lcd_surface, XOFFSET +  8 * FONT_WIDTH, 2 * line_height, dafont, "alt", HSV_WHITE, HSV_BLACK);
        (mods & MOD_MASK_GUI) > 0
            ? qp_drawtext_recolor(lcd_surface, XOFFSET + 12 * FONT_WIDTH, 2 * line_height, dafont, "GUI", HSV_BLACK, HSV_WHITE)
            : qp_drawtext_recolor(lcd_surface, XOFFSET + 12 * FONT_WIDTH, 2 * line_height, dafont, "gui", HSV_WHITE, HSV_BLACK);
        (mods & MOD_MASK_SHIFT) > 0
            ? qp_drawtext_recolor(lcd_surface, XOFFSET + 16 * FONT_WIDTH, 2 * line_height, dafont, "SFT", HSV_BLACK, HSV_WHITE)
            : qp_drawtext_recolor(lcd_surface, XOFFSET + 16 * FONT_WIDTH, 2 * line_height, dafont, "sft", HSV_WHITE, HSV_BLACK);
        last_mods = mods;
        first_run_mods = true;
    }

    if(last_layer_state != layer_state || first_run_layer == false) {
        switch (get_highest_layer(layer_state|default_layer_state)) {
        case 0:
            qp_drawtext_recolor(lcd_surface, XOFFSET, line_height, dafont, "LAYER - 0 BASE      ", HSV_WHITE, HSV_BLACK);
            break; 
        case 1:
            qp_drawtext_recolor(lcd_surface, XOFFSET, line_height, dafont, "LAYER - 1 SYMBOLS   ", HSV_WHITE, HSV_BLACK);
            break;
        case 2:
            qp_drawtext_recolor(lcd_surface, XOFFSET, line_height, dafont, "LAYER - 2 NUMPAD    ", COLOR_NUMPAD, HSV_BLACK);
            break;
        case 3:
            qp_drawtext_recolor(lcd_surface, XOFFSET, line_height, dafont, "LAYER - 3 NUMBERS   ", COLOR_NUMBERS, HSV_BLACK);
            break;
        case 4:
            qp_drawtext_recolor(lcd_surface, XOFFSET, line_height, dafont, "LAYER - 4 ARROWS    ", COLOR_ARROWS, HSV_BLACK);
            break;
        case 5:
            qp_drawtext_recolor(lcd_surface, XOFFSET, line_height, dafont, "LAYER - 5 MOUSE     ", COLOR_MOUSE, HSV_BLACK);
            break;
        case 6:
            qp_drawtext_recolor(lcd_surface, XOFFSET, line_height, dafont, "LAYER - 6 MEDIA     ", COLOR_MEDIA, HSV_BLACK);
            break;
        case 7:
            qp_drawtext_recolor(lcd_surface, XOFFSET, line_height, dafont, "LAYER - 7 SPECIAL   ", COLOR_SPECIAL, HSV_BLACK);
            break;
        }
        draw_layer(get_highest_layer(layer_state | default_layer_state));
        
        last_layer_state = layer_state;
        first_run_layer = true;
    }
}

// Called from halcyon.c
void module_suspend_power_down_kb(void) {
    qp_power(lcd, false);
}

// Called from halcyon.c
void module_suspend_wakeup_init_kb(void) {
    qp_power(lcd, true);
}

// Called from halcyon.c
bool module_post_init_kb(void) {
    // Turn on backlight
    //backlight_enable();

    // Make the devices
    lcd = qp_st7789_make_spi_device(LCD_WIDTH, LCD_HEIGHT, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, LCD_SPI_MODE);
    lcd_surface = qp_make_rgb565_surface(LCD_WIDTH, LCD_HEIGHT, lcd_surface_fb);

    // Initialise the LCD
    qp_init(lcd, LCD_ROTATION);
    qp_set_viewport_offsets(lcd, LCD_OFFSET_X, LCD_OFFSET_Y);
    qp_clear(lcd);
    qp_rect(lcd, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, HSV_BLACK, true);
    qp_power(lcd, true);
    qp_flush(lcd);

    // Initialise the LCD surface
    qp_init(lcd_surface, LCD_ROTATION);
    qp_rect(lcd_surface, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, HSV_BLACK, true);
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    qp_flush(lcd);

    if(!module_post_init_user()) { return false; }

    return true;
}

// Called from halcyon.c
bool display_module_housekeeping_task_kb(bool second_display) {
    if(!display_module_housekeeping_task_user(second_display)) { return false; }

    update_display();

    // Move surface to lcd
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    qp_flush(lcd);

    return true;
}
