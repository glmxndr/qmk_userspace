// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "halcyon.h"
#include "hlc_tft_display.h"

#include "hardware/structs/rosc.h"

// Fonts mono2
#include "graphics/fonts/tiny-18.qff.h"

// Numbers mono2
#include "graphics/numbers/0.qgf.h"
#include "graphics/numbers/1.qgf.h"
#include "graphics/numbers/2.qgf.h"
#include "graphics/numbers/3.qgf.h"
#include "graphics/numbers/4.qgf.h"
#include "graphics/numbers/5.qgf.h"
#include "graphics/numbers/6.qgf.h"
#include "graphics/numbers/7.qgf.h"
#include "graphics/numbers/8.qgf.h"
#include "graphics/numbers/9.qgf.h"
#include "graphics/numbers/undef.qgf.h"

static const char *caps =        "Caps";
static const char *num =         "Num";
static const char *scroll =      "Scroll";

static painter_font_handle_t tiny_18;
static painter_image_handle_t layer_number;

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
        tiny_18 = qp_load_font_mem(font_tiny_18);
    }

    if(last_led_usb_state.raw != host_keyboard_led_state().raw || first_run_led == false) {
        led_t led_usb_state = host_keyboard_led_state();

        led_usb_state.caps_lock   
            ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - tiny_18->line_height * 3 - 15, tiny_18, caps,   HSV_CAPS_ON,   HSV_BLACK) 
            : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - tiny_18->line_height * 3 - 15, tiny_18, caps,   HSV_CAPS_OFF,   HSV_BLACK);
        led_usb_state.num_lock    
            ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - tiny_18->line_height * 2 - 10, tiny_18, num,    HSV_NUM_ON,    HSV_BLACK) 
            : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - tiny_18->line_height * 2 - 10, tiny_18, num,    HSV_NUM_OFF,    HSV_BLACK);
        led_usb_state.scroll_lock 
            ? qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - tiny_18->line_height - 5,      tiny_18, scroll, HSV_SCROLL_ON, HSV_BLACK) 
            : qp_drawtext_recolor(lcd_surface, 5, LCD_HEIGHT - tiny_18->line_height - 5,      tiny_18, scroll, HSV_SCROLL_OFF, HSV_BLACK);

        last_led_usb_state = led_usb_state;
        first_run_led = true;
    }

    if(last_layer_state != layer_state || first_run_layer == false) {
        switch (get_highest_layer(layer_state|default_layer_state)) {
        case 0:
            layer_number = qp_load_image_mem(gfx_0);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_0, HSV_BLACK);
            break;
        case 1:
            layer_number = qp_load_image_mem(gfx_1);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_1, HSV_BLACK);
            break;
        case 2:
            layer_number = qp_load_image_mem(gfx_2);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_2, HSV_BLACK);
            break;
        case 3:
            layer_number = qp_load_image_mem(gfx_3);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_3, HSV_BLACK);
            break;
        case 4:
            layer_number = qp_load_image_mem(gfx_4);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_4, HSV_BLACK);
            break;
        case 5:
            layer_number = qp_load_image_mem(gfx_5);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_5, HSV_BLACK);
            break;
        case 6:
            layer_number = qp_load_image_mem(gfx_6);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_6, HSV_BLACK);
            break;
        case 7:
            layer_number = qp_load_image_mem(gfx_7);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_7, HSV_BLACK);
            break;
        default:
            layer_number = qp_load_image_mem(gfx_undef);
            qp_drawimage_recolor(lcd_surface, 5, 5, layer_number, HSV_LAYER_UNDEF, HSV_BLACK);
        }
        qp_close_image(layer_number);
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
    backlight_enable();

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
