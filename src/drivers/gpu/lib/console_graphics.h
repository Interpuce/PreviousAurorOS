#ifndef CONSOLE_GRAPHICS_H
#define CONSOLE_GRAPHICS_H

#include <stdint.h>
#include <stddef.h>

// Console graphics context structure
typedef struct {
    uint32_t width;     // Width of the console display
    uint32_t height;    // Height of the console display
    uint32_t bpp;       // Bits per pixel (color depth)
    uint8_t *framebuffer; // Framebuffer pointer
    int in_use;         // Flag to track if the device is in use
} console_graphics_t;

// Function declarations
int console_graphics_init(uint32_t width, uint32_t height, uint32_t bpp);
int console_graphics_shutdown();
int console_graphics_write_pixel(uint32_t x, uint32_t y, uint32_t color);
uint32_t console_graphics_read_pixel(uint32_t x, uint32_t y);
void console_graphics_clear(uint32_t color);

#endif