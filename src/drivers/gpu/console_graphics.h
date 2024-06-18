// ======================================================================
//                            AurorOS Driver
// ======================================================================

// => The AurorOS console graphics driver.
//      This file is basically an implementation of the AurorOS console
//      GPU driver.

#include "lib/console_graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static console_graphics_t console_graphics_device = {0};

// Function to initialize console graphics
int console_graphics_init(uint32_t width, uint32_t height, uint32_t bpp) {
    if (console_graphics_device.in_use) {
        return -1; // Device already in use
    }

    // Allocate framebuffer memory
    console_graphics_device.framebuffer = (uint8_t *)malloc(width * height * (bpp / 8));
    if (!console_graphics_device.framebuffer) {
        return -1; // Memory allocation failed
    }

    console_graphics_device.width = width;
    console_graphics_device.height = height;
    console_graphics_device.bpp = bpp;
    console_graphics_device.in_use = 1;

    // Clear framebuffer
    console_graphics_clear(0x00000000);

    return 0; // Initialization successful
}

// Function to shutdown console graphics
int console_graphics_shutdown() {
    if (!console_graphics_device.in_use) {
        return -1; // Device not in use
    }

    free(console_graphics_device.framebuffer);
    console_graphics_device.framebuffer = NULL;
    console_graphics_device.width = 0;
    console_graphics_device.height = 0;
    console_graphics_device.bpp = 0;
    console_graphics_device.in_use = 0;

    return 0; // Shutdown successful
}

// Function to write a pixel to the framebuffer
int console_graphics_write_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (!console_graphics_device.in_use) {
        return -1; // Device not in use
    }

    if (x >= console_graphics_device.width || y >= console_graphics_device.height) {
        return -1; // Coordinates out of bounds
    }

    uint32_t *pixel = (uint32_t *)(console_graphics_device.framebuffer + (y * console_graphics_device.width + x) * (console_graphics_device.bpp / 8));
    *pixel = color;

    return 0; // Pixel write successful
}

// Function to read a pixel from the framebuffer
uint32_t console_graphics_read_pixel(uint32_t x, uint32_t y) {
    if (!console_graphics_device.in_use) {
        return 0; // Device not in use
    }

    if (x >= console_graphics_device.width || y >= console_graphics_device.height) {
        return 0; // Coordinates out of bounds
    }

    uint32_t *pixel = (uint32_t *)(console_graphics_device.framebuffer + (y * console_graphics_device.width + x) * (console_graphics_device.bpp / 8));
    return *pixel;
}

// Function to clear the framebuffer with a specified color
void console_graphics_clear(uint32_t color) {
    if (!console_graphics_device.in_use) {
        return; // Device not in use
    }

    uint32_t *fb = (uint32_t *)console_graphics_device.framebuffer;
    uint32_t num_pixels = console_graphics_device.width * console_graphics_device.height;
    for (uint32_t i = 0; i < num_pixels; ++i) {
        fb[i] = color;
    }
}