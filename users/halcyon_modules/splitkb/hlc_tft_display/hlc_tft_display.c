// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <string.h>
#include <stdio.h>

#include "halcyon.h"
#include "hlc_tft_display.h"

#include "hardware/structs/rosc.h"

// Fonts mono2
#include "graphics/fonts/tiny-12.qff.h"

// Numbers mono2
#include "graphics/numbers/undef.qgf.h"


static const char *caps =        "Caps";
static const char *num =         "Num";
static const char *scroll =      "Scroll";

static painter_font_handle_t dafont;
static painter_image_handle_t layer_number;

static uint8_t lcd_surface_fb[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(135, 240, 16)];

int color_value = 0;

painter_device_t lcd;
painter_device_t lcd_surface;

led_t last_led_usb_state = {0};
layer_state_t last_layer_state = {0};


// Helper to pad/truncate to 3 chars
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

#define GRID_LIGH 0x0, 0x0, 0xC0
#define GRID_DARK 0x0, 0x30, 0x30

void draw_keymap_row(
    int y,
    const char *keys[],     // array of strings
    size_t key_count,
    bool invert
) {
    char buf[4]; // 3 chars + null
    int spacing = 3 * 7; // adjust spacing depending on font width

    for (size_t i = 0; i < key_count; i++) {
        pad_to_width(keys[i], buf);
        if (i % 2 == 0) {
            if (invert) {
                qp_drawtext_recolor(lcd_surface, 5 + i * spacing, y, dafont, buf, HSV_BLACK, GRID_LIGH);
            }
            else {
                qp_drawtext_recolor(lcd_surface, 5 + i * spacing, y, dafont, buf, HSV_WHITE, GRID_DARK);
            }
            
        } else {
            if (invert) {
                qp_drawtext_recolor(lcd_surface, 5 + i * spacing, y, dafont, buf, HSV_WHITE, GRID_DARK);
            }
            else {
                qp_drawtext_recolor(lcd_surface, 5 + i * spacing, y, dafont, buf, HSV_BLACK, GRID_LIGH);
            }
        }
    }
}


// Table: layers × (left+right rows) × columns
static const char *keymaps[MAX_LAYERS][LEFT_ROWS + RIGHT_ROWS][RIGHT_COLS] = {
    // Layer 0 - BASE
    {
        { "Q", "W", "E", "R", "T" },                   // left row1
        { "A", "S", "D", "F", "G" },                   // left row2
        { "Z", "X", "C", "V", "B" },                   // left row3
        { "Y", "U", "I", "O", "P", "`" },              // right row1
        { "H", "J", "K", "L", ":", "'" },              // right row2
        { "N", "M", ",", ".", "/", "^" },              // right row3
    },

    // Layer 1 - SYMBOLS
    {
        { "!", "@", "#", "$", "%" },
        { "`", ";", ",", ".", "?" },
        { "~", ":", "<", ">", "!" },
        { "^", "&", "*", "( )", "_" },
        { "=", "[", "]", "\\", "/", "-" },
        { "+", "(", ")", "{", "}", "\"" },
    },

    // Layer 2 - NUMPAD
    {
        { "F12", "F11", "F10", "F9", "%" },
        { "F8",  "F7",  "F6",  "F5", "0" },
        { "F4",  "F3",  "F2",  "F1", "," },
        { "<", "7", "8", "9", "+", "*" },
        { "0", "4", "5", "6", ".", "-" },
        { ">", "1", "2", "3", "=", "/" },
    },

    // Layer 3 - NUMBERS
    {
        { "!", "@", "#", "$", "%" },
        { "1", "2", "3", "4", "5" },
        { "F1", "F2", "F3", "F4", "F5" },
        { "^", "&", "*", "(", ")", "_" },
        { "6", "7", "8", "9", "0", "F12" },
        { "F6", "F7", "F8", "F9", "F10", "F11" },
    },

    // Layer 4 - ARROWS
    {
        { "C-V", "", "C-X", "C-C", "" },
        { "SFT", "GUI", "ALT", "CTL", "" },
        { "", "", "", "", "BUT" },
        { "", "<=", "^", "=>", "P^" },
        { "", "<-", "v", ">", "Pv", "" },
        { "", "", "", "", "", "" },
    },

    // Layer 5 - MOUSE
    {
        { "", "", "", "", "" },
        { "", "", "", "", "" },
        { "", "", "", "", "" },
        { "", "", "", "", "", "" },
        { "", "", "", "", "", "" },
        { "", "", "", "", "", "" },
    },

    // Layer 6 - MEDIA
    {
        { "", "", "", "", "" },
        { "", "", "", "", "" },
        { "", "", "", "", "" },
        { "", "", "", "", "", "" },
        { "", "", "", "", "", "" },
        { "", "", "", "", "", "" },
    },

    // Layer 7 - SPECIAL
    {
        { "", "", "", "", "" },
        { "", "", "", "", "" },
        { "", "", "", "", "" },
        { "", "", "", "", "", "" },
        { "", "", "", "", "", "" },
        { "", "", "", "", "", "" },
    }
};

void update_display(void) {
    static bool first_run_led = false;
    static bool first_run_layer = false;

    if( first_run_layer == false) {
        // Load fonts
        dafont = qp_load_font_mem(font_tiny_12);
    }
    int line_height = dafont->line_height;

    if(last_led_usb_state.raw != host_keyboard_led_state().raw || first_run_led == false) {
        led_t led_usb_state = host_keyboard_led_state();

        led_usb_state.caps_lock   
            ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - dafont->line_height * 3 - 15, dafont, caps,   HSV_CAPS_ON,   HSV_BLACK) 
            : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - dafont->line_height * 3 - 15, dafont, caps,   HSV_CAPS_OFF,   HSV_BLACK);
        led_usb_state.num_lock    
            ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - dafont->line_height * 2 - 10, dafont, num,    HSV_NUM_ON,    HSV_BLACK) 
            : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - dafont->line_height * 2 - 10, dafont, num,    HSV_NUM_OFF,    HSV_BLACK);
        led_usb_state.scroll_lock 
            ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - dafont->line_height - 5,      dafont, scroll, HSV_SCROLL_ON, HSV_BLACK) 
            : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - dafont->line_height - 5,      dafont, scroll, HSV_SCROLL_OFF, HSV_BLACK);

        last_led_usb_state = led_usb_state;
        first_run_led = true;
    }

    if(last_layer_state != layer_state || first_run_layer == false) {
        
        layer_number = qp_load_image_mem(gfx_undef);
        qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_BLACK, HSV_BLACK);
        qp_close_image(layer_number);
        
        switch (get_highest_layer(layer_state|default_layer_state)) {
        case 0: {
            qp_drawtext_recolor(lcd_surface, 5 , line_height, dafont, "LAYER - 0 BASE", HSV_WHITE, HSV_BLACK);

            const char *base_lft_row1[] = { "Q", "W", "E", "R", "T" };
            const char *base_lft_row2[] = { "A", "S", "D", "F", "G" };
            const char *base_lft_row3[] = { "Z", "X", "C", "V", "B" };

            const char *base_rgt_row1[] = { "Y", "U", "I", "O", "P", "`" };
            const char *base_rgt_row2[] = { "H", "J", "K", "L", ":", "'" };
            const char *base_rgt_row3[] = { "N", "M", ",", ".", "/", "^" };

            draw_keymap_row(LCD_HEIGHT - 10 * line_height, base_lft_row1, 5, false);
            draw_keymap_row(LCD_HEIGHT -  9 * line_height, base_lft_row2, 5, true);
            draw_keymap_row(LCD_HEIGHT -  8 * line_height, base_lft_row3, 5, false);

            draw_keymap_row(LCD_HEIGHT -  6 * line_height, base_rgt_row1, 6, true);
            draw_keymap_row(LCD_HEIGHT -  5 * line_height, base_rgt_row2, 6, false);
            draw_keymap_row(LCD_HEIGHT -  4 * line_height, base_rgt_row3, 6, true);

            break; 
        }
        case 1: { // symbols
            qp_drawtext_recolor(lcd_surface, 5, line_height, dafont, "LAYER - 1 SYMBOLS", COLOR_SYMBOLS, HSV_BLACK);
            
            const char *base_lft_row1[] = { "!", "@", "#", "$", "%" };
            const char *base_lft_row2[] = { "`", ";", ",", ".", "?" };
            const char *base_lft_row3[] = { "~", ":", "<", ">", "!" };

            const char *base_rgt_row1[] = { "^", "&", "*", "( )", "_" };
            const char *base_rgt_row2[] = { "=", "[", "]", "\\", "/", "-" };
            const char *base_rgt_row3[] = { "+", "(", ")", "{", "}", "\"" };

            draw_keymap_row(LCD_HEIGHT - 10 * line_height, base_lft_row1, 5, false);
            draw_keymap_row(LCD_HEIGHT -  9 * line_height, base_lft_row2, 5, true);
            draw_keymap_row(LCD_HEIGHT -  8 * line_height, base_lft_row3, 5, false);

            draw_keymap_row(LCD_HEIGHT -  6 * line_height, base_rgt_row1, 6, true);
            draw_keymap_row(LCD_HEIGHT -  5 * line_height, base_rgt_row2, 6, false);
            draw_keymap_row(LCD_HEIGHT -  4 * line_height, base_rgt_row3, 6, true);

            break;
        }
        case 2: // numpad
            qp_drawtext_recolor(lcd_surface, 5, line_height, dafont, "LAYER - 2 NUMPAD", COLOR_NUMPAD, HSV_BLACK);

            const char *base_lft_row1[] = { "F12", "F11", "F10", "F9", "%" };
            const char *base_lft_row2[] = { "F8", "F7", "F6", "F5", "0" };
            const char *base_lft_row3[] = { "F4", "F3", "F2", "F1", "," };

            const char *base_rgt_row1[] = { "<", "7", "8", "9", "+", "*" };
            const char *base_rgt_row2[] = { "0", "4", "5", "6", ".", "-" };
            const char *base_rgt_row3[] = { ">", "1", "2", "3", "=", "/" };

            draw_keymap_row(LCD_HEIGHT - 10 * line_height, base_lft_row1, 5, false);
            draw_keymap_row(LCD_HEIGHT -  9 * line_height, base_lft_row2, 5, true);
            draw_keymap_row(LCD_HEIGHT -  8 * line_height, base_lft_row3, 5, false);

            draw_keymap_row(LCD_HEIGHT -  6 * line_height, base_rgt_row1, 6, true);
            draw_keymap_row(LCD_HEIGHT -  5 * line_height, base_rgt_row2, 6, false);
            draw_keymap_row(LCD_HEIGHT -  4 * line_height, base_rgt_row3, 6, true);
            break;
        case 3: // numbers
            qp_drawtext_recolor(lcd_surface, 5, line_height, dafont, "LAYER - 3 NUMBERS", COLOR_NUMBERS, HSV_BLACK);

            const char *base_lft_row1[] = { "!", "@", "#", "$", "%" };
            const char *base_lft_row2[] = { "1", "2", "3", "4", "5" };
            const char *base_lft_row3[] = { "F1", "F2", "F3", "F4", "F5" };

            const char *base_rgt_row1[] = { "^", "&", "*", "(", ")", "_" };
            const char *base_rgt_row2[] = { "6", "7", "8", "9", "0", "F12" };
            const char *base_rgt_row3[] = { "F6", "F7", "F8", "F9", "F10", "F11" };

            draw_keymap_row(LCD_HEIGHT - 10 * line_height, base_lft_row1, 5, false);
            draw_keymap_row(LCD_HEIGHT -  9 * line_height, base_lft_row2, 5, true);
            draw_keymap_row(LCD_HEIGHT -  8 * line_height, base_lft_row3, 5, false);

            draw_keymap_row(LCD_HEIGHT -  6 * line_height, base_rgt_row1, 6, true);
            draw_keymap_row(LCD_HEIGHT -  5 * line_height, base_rgt_row2, 6, false);
            draw_keymap_row(LCD_HEIGHT -  4 * line_height, base_rgt_row3, 6, true);

            break;
        case 4:
            qp_drawtext_recolor(lcd_surface, 5, line_height, dafont, "LAYER - 4 ARROWS", COLOR_ARROWS, HSV_BLACK);

            const char *base_lft_row1[] = { "C-V", "", "C-X", "C-C", "" };
            const char *base_lft_row2[] = { "SFT", "GUI", "ALT", "CTL", "" };
            const char *base_lft_row3[] = { "", "", "", "", "BUT" };

            const char *base_rgt_row1[] = { "", "<=", "^", "=>", "P^" };
            const char *base_rgt_row2[] = { "", "<-", "v", ">", "Pv", "" };
            const char *base_rgt_row3[] = { "", "", "", "", "", "" };

            draw_keymap_row(LCD_HEIGHT - 10 * line_height, base_lft_row1, 5, false);
            draw_keymap_row(LCD_HEIGHT -  9 * line_height, base_lft_row2, 5, true);
            draw_keymap_row(LCD_HEIGHT -  8 * line_height, base_lft_row3, 5, false);

            draw_keymap_row(LCD_HEIGHT -  6 * line_height, base_rgt_row1, 6, true);
            draw_keymap_row(LCD_HEIGHT -  5 * line_height, base_rgt_row2, 6, false);
            draw_keymap_row(LCD_HEIGHT -  4 * line_height, base_rgt_row3, 6, true);

            break;
        case 5:
            qp_drawtext_recolor(lcd_surface, 5, line_height, dafont, "LAYER - 5 MOUSE", COLOR_MOUSE, HSV_BLACK);


            const char *base_lft_row1[] = { "", "", "", "", "" };
            const char *base_lft_row2[] = { "", "", "", "", "" };
            const char *base_lft_row3[] = { "", "", "", "", "" };

            const char *base_rgt_row1[] = { "", "", "", "", "", "" };
            const char *base_rgt_row2[] = { "", "", "", "", "", "" };
            const char *base_rgt_row3[] = { "", "", "", "", "", "" };

            draw_keymap_row(LCD_HEIGHT - 10 * line_height, base_lft_row1, 5, false);
            draw_keymap_row(LCD_HEIGHT -  9 * line_height, base_lft_row2, 5, true);
            draw_keymap_row(LCD_HEIGHT -  8 * line_height, base_lft_row3, 5, false);

            draw_keymap_row(LCD_HEIGHT -  6 * line_height, base_rgt_row1, 6, true);
            draw_keymap_row(LCD_HEIGHT -  5 * line_height, base_rgt_row2, 6, false);
            draw_keymap_row(LCD_HEIGHT -  4 * line_height, base_rgt_row3, 6, true);

            break;
        case 6:
            qp_drawtext_recolor(lcd_surface, 5, line_height, dafont, "LAYER - 6 MEDIA", COLOR_MEDIA, HSV_BLACK);

            const char *base_lft_row1[] = { "", "", "", "", "" };
            const char *base_lft_row2[] = { "", "", "", "", "" };
            const char *base_lft_row3[] = { "", "", "", "", "" };

            const char *base_rgt_row1[] = { "", "", "", "", "", "" };
            const char *base_rgt_row2[] = { "", "", "", "", "", "" };
            const char *base_rgt_row3[] = { "", "", "", "", "", "" };

            draw_keymap_row(LCD_HEIGHT - 10 * line_height, base_lft_row1, 5, false);
            draw_keymap_row(LCD_HEIGHT -  9 * line_height, base_lft_row2, 5, true);
            draw_keymap_row(LCD_HEIGHT -  8 * line_height, base_lft_row3, 5, false);

            draw_keymap_row(LCD_HEIGHT -  6 * line_height, base_rgt_row1, 6, true);
            draw_keymap_row(LCD_HEIGHT -  5 * line_height, base_rgt_row2, 6, false);
            draw_keymap_row(LCD_HEIGHT -  4 * line_height, base_rgt_row3, 6, true);

            break;
        case 7:
            qp_drawtext_recolor(lcd_surface, 5, line_height, dafont, "LAYER - 7 SPECIAL", COLOR_SPECIAL, HSV_BLACK);

            const char *base_lft_row1[] = { "", "", "", "", "" };
            const char *base_lft_row2[] = { "", "", "", "", "" };
            const char *base_lft_row3[] = { "", "", "", "", "" };

            const char *base_rgt_row1[] = { "", "", "", "", "", "" };
            const char *base_rgt_row2[] = { "", "", "", "", "", "" };
            const char *base_rgt_row3[] = { "", "", "", "", "", "" };

            draw_keymap_row(LCD_HEIGHT - 10 * line_height, base_lft_row1, 5, false);
            draw_keymap_row(LCD_HEIGHT -  9 * line_height, base_lft_row2, 5, true);
            draw_keymap_row(LCD_HEIGHT -  8 * line_height, base_lft_row3, 5, false);

            draw_keymap_row(LCD_HEIGHT -  6 * line_height, base_rgt_row1, 6, true);
            draw_keymap_row(LCD_HEIGHT -  5 * line_height, base_rgt_row2, 6, false);
            draw_keymap_row(LCD_HEIGHT -  4 * line_height, base_rgt_row3, 6, true);

            break;
        }
        
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
