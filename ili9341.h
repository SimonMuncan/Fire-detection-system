/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* 
 * File:   ili9341.h
 * Author: Djole
 *
 * Created on March 28, 2023, 7:44 PM
 */

#ifndef ILI9341_H
#define	ILI9341_H

#include "config/default/peripheral/gpio/plib_gpio.h"
#include "fonts.h"

typedef enum {SCREEN_ROT_0, SCREEN_ROT_90, SCREEN_ROT_180, SCREEN_ROT_270}screen_rot_t;

#define COLOR_BLACK         0x0000
#define COLOR_NAVY          0x000F
#define COLOR_DARKGREEN     0x03E0
#define COLOR_DARKCYAN      0x03EF
#define COLOR_MAROON        0x7800
#define COLOR_PURPLE        0x780F
#define COLOR_OLIVE         0x7BE0
#define COLOR_LIGHTGREY     0xC618
#define COLOR_DARKGREY      0x7BEF
#define COLOR_BLUE          0x001F
#define COLOR_GREEN         0x07E0
#define COLOR_CYAN          0x07FF
#define COLOR_RED           0xF800
#define COLOR_MAGENTA       0xF81F
#define COLOR_YELLOW        0xFFE0
#define COLOR_WHITE         0xFFFF


#define ILI9341_WIDTH  320
#define ILI9341_HEIGHT 240
#define ILI9341_PIXEL_COUNT 76800
#define ILI9341_COLUMN_ADDRESS_SET 0x2A
#define ILI9341_PAGE_ADDRESS_SET 0x2B

void ili9341_reset();
void ili9341_init();
void ili9341_set_rotation(screen_rot_t rot);
void ili9341_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void ili9341_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color, uint8_t thickness);
void ili9341_set_address_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void ili9341_clear_display(uint16_t color);
void ili9341_draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color, uint8_t thickness);
void ili9341_draw_filled_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void ili9341_draw_circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color, uint8_t thickness);
void ili9341_draw_filled_circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color);
void ili9341_draw_vline(uint16_t x, uint16_t y, uint16_t h, uint16_t color, uint8_t thickness);
void ili9341_draw_hline(uint16_t x, uint16_t y, uint16_t w, uint16_t color, uint8_t thickness);
void ili9341_draw_triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t thickness, uint16_t color);
void ili9341_draw_filled_triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ili9341_draw_raw_image(uint16_t x, uint16_t y, const uint8_t* data, uint16_t width, uint16_t height);
void ili9341_write_char(uint16_t x, uint16_t y, char c, uint16_t color, font_t* font);
void ili9341_write_text(uint16_t x, uint16_t y, const char* str, uint16_t color, font_t* font);
#endif	/* ILI9341_H */