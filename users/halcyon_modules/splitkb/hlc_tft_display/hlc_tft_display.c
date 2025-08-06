// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "halcyon.h"
#include "hlc_tft_display.h"

#include "hardware/structs/rosc.h"

// Fonts mono2
#include "graphics/fonts/tiny-18.qff.h"

static const char *caps =        "Caps";
static const char *num =         "Num";
static const char *scroll =      "Scroll";

static painter_font_handle_t dafont;

static uint8_t lcd_surface_fb[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(135, 240, 16)];

int color_value = 0;

painter_device_t lcd;
painter_device_t lcd_surface;

led_t last_led_usb_state = {0};
layer_state_t last_layer_state = {0};

void update_display(void) {
    static bool first_run_led = false;
    static bool first_run_layer = false;

    if( first_run_layer == false) {
        // Load fonts
        // dafont = qp_load_font_mem(font_atkinson_12);
        dafont = qp_load_font_mem(font_tiny_18);
    }
    int line_height = dafont->line_height;

    if(last_led_usb_state.raw != host_keyboard_led_state().raw || first_run_led == false) {
        led_t led_usb_state = host_keyboard_led_state();

        led_usb_state.caps_lock   
            ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 3 * line_height, dafont, caps,   HSV_CAPS_ON,   HSV_BLACK) 
            : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 3 * line_height, dafont, caps,   HSV_CAPS_OFF,   HSV_BLACK);
        led_usb_state.num_lock    
            ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 2 * line_height, dafont, num,    HSV_NUM_ON,    HSV_BLACK) 
            : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 2 * line_height, dafont, num,    HSV_NUM_OFF,    HSV_BLACK);
        led_usb_state.scroll_lock 
            ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 1 * line_height, dafont, scroll, HSV_SCROLL_ON, HSV_BLACK) 
            : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 1 * line_height, dafont, scroll, HSV_SCROLL_OFF, HSV_BLACK);

        last_led_usb_state = led_usb_state;
        first_run_led = true;
    }

    if(last_layer_state != layer_state || first_run_layer == false) {
        qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 10 * line_height, dafont, " Q W E R T",   HSV_LAYER_0,   HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 10 * line_height, dafont, "Q W E R T",   HSV_LAYER_0,   HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 9  * line_height, dafont, "A S D F G",   HSV_LAYER_0,   HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 8  * line_height, dafont, "Z X C V B",   HSV_LAYER_0,   HSV_BLACK);

        qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 6  * line_height, dafont, " Y U I O P '",   HSV_LAYER_0,   HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 5  * line_height, dafont, " H J K L ; '",   HSV_LAYER_0,   HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - 4  * line_height, dafont, " N M , , / ^",   HSV_LAYER_0,   HSV_BLACK);
        /*
        switch (get_highest_layer(layer_state|default_layer_state)) {
        case 0:
            
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            break;
        }
        */
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
