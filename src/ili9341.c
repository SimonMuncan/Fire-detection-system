#include "ili9341.h"
#include "peripheral/gpio/plib_gpio.h"
#include "peripheral/coretimer/plib_coretimer.h"

volatile uint16_t DISPLAY_HEIGHT = ILI9341_HEIGHT;
volatile uint16_t DISPLAY_WIDTH = ILI9341_WIDTH;

static void swap(uint16_t *x, uint16_t *y) {
    uint16_t temp = *x;
    *x = *y;
    *y = temp;
}

int16_t min(int16_t a, int16_t b) {
    return (a < b) ? a : b;
}

int16_t max(int16_t a, int16_t b) {
    return (a > b) ? a : b;
}

static void set_data_bus(uint8_t data)
{
    if (data & 0x01) 
        D0_Set();
    else
        D0_Clear();
    if (data & 0x02)
        D1_Set();
    else
        D1_Clear();
    if (data & 0x04)
        D2_Set();
    else
        D2_Clear();
    if (data & 0x08)
        D3_Set();
    else
        D3_Clear();
    if (data & 0x10)
        D4_Set();
    else
        D4_Clear();
    if (data & 0x20)
        D5_Set();
    else
        D5_Clear();
    if (data & 0x40)
        D6_Set();
    else
        D6_Clear();
    if (data & 0x80)
        D7_Set();    
    else
        D7_Clear();
}

// Function to send a command to the ILI9341
static void ili9341_send_command(uint8_t command)
{
    // Set D/C pin low to indicate a command
    RS_Clear();
    
    // Set CS pin low to select the ILI9341
    CS_Clear();
    
    // Write the command to the data bus
    set_data_bus(command);

    
    // Pulse the WR pin to write the command to the ILI9341
    WR_Clear();
    WR_Set();
    
    // Set CS pin high to deselect the ILI9341
    CS_Set();
}

// Function to send data to the ILI9341
static void ili9341_send_data(uint8_t data)
{
    // Set D/C pin high to indicate data
    RS_Set();
    
    // Set CS pin low to select the ILI9341
    CS_Clear();
    
    // Write the data to the data bus
    set_data_bus(data);
    
    // Pulse the WR pin to write the data to the ILI9341
    WR_Clear();
    WR_Set();
    
    // Set CS pin high to deselect the ILI9341
    CS_Set();
}


// Function to reset the ILI9341
void ili9341_reset()
{   
    // Set RST pin low to reset the ILI9341
    RST_Clear();
    
    // Wait for some time
    CORETIMER_DelayMs(20);
    
    // Set RST pin high to release from reset
    RST_Set();
    
    // Wait for some time
    CORETIMER_DelayMs(100);
}

void ili9341_init()
{
    CS_Set();
    WR_Set();
    RD_Set();
    
    ili9341_reset();

    // Power Control A
	ili9341_send_command(0xcb); 
	ili9341_send_data(0x39);
	ili9341_send_data(0x2c);
	ili9341_send_data(0x00);
	ili9341_send_data(0x34);
	ili9341_send_data(0x02);
    
    // Power Control B
    ili9341_send_command(0xcf); 
	ili9341_send_data(0x00);
	ili9341_send_data(0xc1);
	ili9341_send_data(0x30);
	
    // Driver Timing Control A
	ili9341_send_command(0xe8); 
	ili9341_send_data(0x85);
	ili9341_send_data(0x10);
	ili9341_send_data(0x78);//0x79

    // Driver Timing Control B
	ili9341_send_command(0xea); 
	ili9341_send_data(0x00);
	ili9341_send_data(0x00);
    
    // Power On Sequence Control
	ili9341_send_command(0xed); 
	ili9341_send_data(0x64);
	ili9341_send_data(0x03);
	ili9341_send_data(0x12);
	ili9341_send_data(0x81);
	
    // Pump Ratio Control
	ili9341_send_command(0xF7);
	ili9341_send_data(0x20);

    // Power control 1
	ili9341_send_command(0xC0); 
	ili9341_send_data(0x23);
	
    // Power control 2
	ili9341_send_command(0xC1);
	ili9341_send_data(0x10);
	
	// VCM Control
	ili9341_send_command(0xC5);
	ili9341_send_data(0x3E);
	ili9341_send_data(0x28);
	
    // VCM Control 2
    ili9341_send_command(0xc7); 
	ili9341_send_data(0x86);

    // Memory Access Control
	ili9341_send_command(0x36); 
    ili9341_send_data(0x48);	
    
    // Pixel Format
    ili9341_send_command(0x3A); 
	ili9341_send_data(0x55);
    
    // Frame Rate Control
	ili9341_send_command(0xB1); 
	ili9341_send_data(0x00);
	ili9341_send_data(0x18);
    
    // Display Function Control
    ili9341_send_command(0xB6); 
	ili9341_send_data(0x0a);
	ili9341_send_data(0xa2);
    
    // 3Gamma Function Disable
	ili9341_send_command(0xF2); 
	ili9341_send_data(0x00);
    
	// Gamma Curve Selected
    ili9341_send_command(0x26);    
    ili9341_send_data(0x01);

    // Positive Gamma Correction
    ili9341_send_command(0xE0);
	ili9341_send_data(0x0F);
	ili9341_send_data(0x31);
	ili9341_send_data(0x2B);
	ili9341_send_data(0x0C);
	ili9341_send_data(0x0E);
	ili9341_send_data(0x08);
	ili9341_send_data(0x4E);
	ili9341_send_data(0xF1);
	ili9341_send_data(0x37);
	ili9341_send_data(0x07);
	ili9341_send_data(0x10);
	ili9341_send_data(0x03);
	ili9341_send_data(0x0E);
	ili9341_send_data(0x09);
	ili9341_send_data(0x00);
	
    // Negative Gamma Correction
	ili9341_send_command(0xE1);
	ili9341_send_data(0x00);
	ili9341_send_data(0x0E);
	ili9341_send_data(0x14);
	ili9341_send_data(0x03);
	ili9341_send_data(0x11);
	ili9341_send_data(0x07);
	ili9341_send_data(0x31);
	ili9341_send_data(0xC1);
	ili9341_send_data(0x48);
	ili9341_send_data(0x08);
	ili9341_send_data(0x0F);
	ili9341_send_data(0x0C);
	ili9341_send_data(0x31);
	ili9341_send_data(0x36);
	ili9341_send_data(0x0F);
    
    // Exit Sleep
	ili9341_send_command(0x11); 
	CORETIMER_DelayMs(80);
    // Turn On Display
	ili9341_send_command(0x29);
    
    ili9341_set_rotation(SCREEN_ROT_0);
    
}

void ili9341_set_rotation(screen_rot_t rot)
{
    // Memory Access Control
    ili9341_send_command(0x36);
    
    switch(rot)
    {
        // Vertical
        case SCREEN_ROT_90:
            ili9341_send_data(0x48);
            DISPLAY_WIDTH = 240;
            DISPLAY_HEIGHT = 320;
            break;
        // Horizontal
        case SCREEN_ROT_0:
            ili9341_send_data(0x28);
            DISPLAY_WIDTH = 320;
            DISPLAY_HEIGHT = 240;
            break;
        // Vertical 2
        case SCREEN_ROT_270:
            ili9341_send_data(0x88);
            DISPLAY_WIDTH = 240;
            DISPLAY_HEIGHT = 320;
            break;
        // Horizontal 2
        case SCREEN_ROT_180:
            ili9341_send_data(0xE8);
            DISPLAY_WIDTH = 320;
            DISPLAY_HEIGHT = 240;
            break;
    }
}

void ili9341_set_address_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    // Column address set
    ili9341_send_command(0x2A);
    ili9341_send_data(x1 >> 8);
    ili9341_send_data(x1 & 0xFF);
    ili9341_send_data(x2 >> 8);
    ili9341_send_data(x2 & 0xFF);
    
    // Page Address Set
    ili9341_send_command(0x2B);
    ili9341_send_data(y1 >> 8);
    ili9341_send_data(y1 & 0xFF);
    ili9341_send_data(y2 >> 8);
    ili9341_send_data(y2 & 0xFF);
    
    // RAM Write
    ili9341_send_command(0x2C);
}


void ili9341_draw_pixel(uint16_t x, uint16_t y, uint16_t color) {
    ili9341_set_address_window(x, y, x+1, y+1);
    
    // Write pixel data (command 0x2C)
    ili9341_send_command(0x2C);
    ili9341_send_data(color >> 8);
    ili9341_send_data(color & 0xFF);
}

void ili9341_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color, uint8_t thickness) {
    int16_t dx = abs(x1 - x0);
    int16_t dy = abs(y1 - y0);
    int16_t sx = (x0 < x1) ? 1 : -1;
    int16_t sy = (y0 < y1) ? 1 : -1;
    int16_t err = dx - dy;
    int16_t e2 = 0;
    
    ili9341_draw_pixel(x0, y0, color);
    
    if (dx > dy) {
        e2 = (thickness << 8) / dx;
        for (int16_t i = 0; i < thickness; i++) {
            ili9341_draw_pixel(x0, y0 + i, color);
            ili9341_draw_pixel(x0, y0 - i, color);
        }
        while (x0 != x1) {
            err -= dy;
            if (err < 0) {
                y0 += sy;
                err += dx;
                for (int16_t i = 0; i < thickness; i++) {
                    ili9341_draw_pixel(x0, y0 + i, color);
                    ili9341_draw_pixel(x0, y0 - i, color);
                }
            }
            x0 += sx;
            for (int16_t i = 0; i < thickness; i++) {
                ili9341_draw_pixel(x0, y0 + i, color);
                ili9341_draw_pixel(x0, y0 - i, color);
            }
            e2 += (thickness << 8) / dx;
            if (e2 > 0xFF) {
                y0 += sy;
                e2 -= 0xFF;
            }
        }
    } else {
        e2 = (thickness << 8) / dy;
        for (int16_t i = 0; i < thickness; i++) {
            ili9341_draw_pixel(x0 + i, y0, color);
            ili9341_draw_pixel(x0 - i, y0, color);
        }
        while (y0 != y1) {
            err -= dx;
            if (err < 0) {
                x0 += sx;
                err += dy;
                for (int16_t i = 0; i < thickness; i++) {
                    ili9341_draw_pixel(x0 + i, y0, color);
                    ili9341_draw_pixel(x0 - i, y0, color);
                }
            }
            y0 += sy;
            for (int16_t i = 0; i < thickness; i++) {
                ili9341_draw_pixel(x0 + i, y0, color);
                ili9341_draw_pixel(x0 - i, y0, color);
            }
            e2 += (thickness << 8) / dy;
            if (e2 > 0xFF) {
                x0 += sx;
                e2 -= 0xFF;
            }
        }
    }
}


void ili9341_clear_display(uint16_t color) {
    ili9341_set_address_window(0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1);
    for (uint32_t i = 0; i < ILI9341_PIXEL_COUNT; i++) {
        ili9341_send_data(color>>8);
        ili9341_send_data(color&0xFF);
    }
}

void ili9341_draw_filled_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    uint32_t pixel_count = (width) * (height);
    ili9341_set_address_window(x, y, x+width-1, y+height-1);
    
    while (pixel_count--)
    {
        ili9341_send_data(color>>8);
        ili9341_send_data(color);
    }
}

// Midpoint circle algorithm to draw the circle as a series of pixels
void ili9341_draw_circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color, uint8_t thickness) {
        for (int t = 0; t < thickness; t++) {
        int x1 = 0, y1 = radius - t;
        int d = 3 - 2 * (radius - t);
        while (x1 <= y1) {
            ili9341_draw_pixel(x + x1, y - y1, color);
            ili9341_draw_pixel(x + y1, y - x1, color);
            ili9341_draw_pixel(x + y1, y + x1, color);
            ili9341_draw_pixel(x + x1, y + y1, color);
            ili9341_draw_pixel(x - x1, y + y1, color);
            ili9341_draw_pixel(x - y1, y + x1, color);
            ili9341_draw_pixel(x - y1, y - x1, color);
            ili9341_draw_pixel(x - x1, y - y1, color);

            if (d < 0) {
                d = d + 4 * x1 + 6;
            } else {
                d = d + 4 * (x1 - y1) + 10;
                y1--;
            }
            x1++;
        }
    }
}

void ili9341_draw_filled_circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color)
{
    int x1 = 0, y1 = radius;
    int d = 1 - radius;
    while (x1 <= y1) {
        for (int i = x - x1; i <= x + x1; i++) {
            ili9341_draw_pixel(i, y - y1, color);
            ili9341_draw_pixel(i, y + y1, color);
        }
        for (int i = x - y1; i <= x + y1; i++) {
            ili9341_draw_pixel(i, y - x1, color);
            ili9341_draw_pixel(i, y + x1, color);
        }
        if (d < 0) {
            d += 2 * x1 + 3;
        } else {
            d += 2 * (x1 - y1) + 5;
            y1--;
        }
        x1++;
    }
}

// Draw an empty rectangle with the specified top-left corner coordinates, width, height, and color
void ili9341_draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color, uint8_t thickness)
{
    for (uint8_t t = 0; t < thickness; t++) {
        // Draw horizontal lines for top and bottom edges
        ili9341_draw_hline(x, y + t, width, color,1);
        ili9341_draw_hline(x, y + height - t - 1, width, color,1);
        
        // Draw vertical lines for left and right edges
        ili9341_draw_vline(x + t, y, height, color,1);
        ili9341_draw_vline(x + width - t - 1, y, height, color,1);
    }
}

void ili9341_draw_vline(uint16_t x, uint16_t y, uint16_t h, uint16_t color, uint8_t thickness) {
    for (int t = 0; t < thickness; t++) {
        ili9341_set_address_window(x + t, y, x + t, y + h - 1);
        for (int i = 0; i < h; i++) {
            ili9341_send_data(color >> 8);
            ili9341_send_data(color & 0xFF);
        }
    }
}

void ili9341_draw_hline(uint16_t x, uint16_t y, uint16_t w, uint16_t color, uint8_t thickness) {
    for (int t = 0; t < thickness; t++) {
        ili9341_set_address_window(x, y + t, x + w - 1, y + t);
        for (int i = 0; i < w; i++) {
            ili9341_send_data(color >> 8);
            ili9341_send_data(color & 0xFF);
        }
    }
}

void ili9341_draw_triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t thickness, uint16_t color) {
    ili9341_draw_line(x0, y0, x1, y1, thickness, color);
    ili9341_draw_line(x1, y1, x2, y2, thickness, color);
    ili9341_draw_line(x2, y2, x0, y0, thickness, color);
}

void ili9341_draw_filled_triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    int16_t a, b, y, last;
    if (y0 > y1) {
        swap(&y0, &y1);
        swap(&x0, &x1);
    }
    if (y1 > y2) {
        swap(&y2, &y1);
        swap(&x2, &x1);
    }
    if (y0 > y1) {
        swap(&y0, &y1);
        swap(&x0, &x1);
    }

    if (y0 == y2) { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if (x1 < a) {
            a = x1;
        }
        else if (x1 > b) {
            b = x1;
        }
        if (x2 < a) {
            a = x2;
        }
        else if (x2 > b) {
            b = x2;
        }
        ili9341_draw_hline(a, y0, b - a + 1, color, 1);
        return;
    }

    int16_t dx01 = x1 - x0;
    int16_t dy01 = y1 - y0;
    int16_t dx02 = x2 - x0;
    int16_t dy02 = y2 - y0;
    int16_t dx12 = x2 - x1;
    int16_t dy12 = y2 - y1;
    int32_t sa = 0;
    int32_t sb = 0;

    if (y1 == y2) {
        last = y1; // Include y1 scanline
    }
    else {
        last = y1 - 1; // Skip it
    }

    for (y = y0; y <= last; y++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        if (a > b) {
            uint32_t temp = a;
            a = b;
            b = temp;
        }
        ili9341_draw_hline(a, y, b - a + 1, color, 1);
    }

    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        if (a > b) {
            uint32_t temp = a;
            a = b;
            b = temp;
        }
        ili9341_draw_hline(a, y, b - a + 1, color, 1);
    }
}

void ili9341_draw_raw_image(uint16_t x, uint16_t y, const uint8_t* data, uint16_t width, uint16_t height) {
    uint16_t pixel;

    // Set the address window
    ili9341_set_address_window(x, y, x + width - 1, y + height - 1);

    // Send the pixel data
    for (uint16_t row = height-1; row != 0xFFFF; row--) {
        for (uint16_t col = 0; col < width; col++) {
            pixel = ((const uint16_t*)data)[row * width + col];
            ili9341_send_data(pixel & 0xFF);
            ili9341_send_data(pixel >> 8);

        }
    }
}

void ili9341_write_char(uint16_t x, uint16_t y, char c, uint16_t color, font_t* font) {
    uint8_t i, j;
    uint8_t width_bytes = (font->width + 7) / 8;  // Round up to nearest multiple of 8 bits
    const uint8_t* char_bitmap = font->font + ((c - 32) * width_bytes * font->height);  // Calculate offset into font data for given character

    for (i = font->height; i > 0; i--) {
        for (j = 0; j < font->width; j++) {
            if (char_bitmap[((i - 1) * width_bytes) + (j / 8)] & (0x80 >> (j % 8))) {
                ili9341_draw_pixel(x + j, y + (font->height - i), color);
            }
        }
    }
}

void ili9341_write_text(uint16_t x, uint16_t y, const char* str, uint16_t color, font_t* font){
    uint16_t offset_x = x;
    uint16_t offset_y = y;
    char c = *str;
    while (c != '\0') {
        if (c == '\n') {
            offset_y -= (font->width +3);//font->height;
            offset_x = x;
        } else {
            ili9341_write_char(offset_x, offset_y, c, color, font);
            offset_x += font->width;
        }
        str++;
        c = *str;
    }
}