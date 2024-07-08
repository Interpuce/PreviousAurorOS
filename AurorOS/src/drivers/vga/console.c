// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This is a basic VGA console driver. 

// NOTE: For making it simple, many things are really To-DO.
// We are going to make this driver really useful in the future.

// Include the INT types.
#include <stdint.h>

// Include the header file
#include "console.h"

// Declare these functions
#include <kerdef.h>

// Function to set cursor position for primary monitor
void vga_set_cursor_position(uint8_t x, uint8_t y) {
    uint16_t position = y * VGA_WIDTH + x;

    // Send high byte of the position to VGA controller
    outb(VGA_CTRL_REG, 14);
    outb(VGA_DATA_REG, position >> 8);
    // Send low byte of the position to VGA controller
    outb(VGA_CTRL_REG, 15);
    outb(VGA_DATA_REG, position & 0xFF);

    vga_cursorx = x;
    vga_cursory = y;
}

// Function to set character attribute (color) for primary monitor
void set_char_attribute(uint8_t attr) {
    vga_cursorattr = attr;
}

// Function to display a character on the screen of primary monitor
void vga_put_char(uint8_t c, uint8_t x, uint8_t y) {
    volatile uint16_t *video_memory = (volatile uint16_t *)0xB8000;
    uint16_t offset = y * VGA_WIDTH + x;
    video_memory[offset] = (vga_cursorattr << 8) | c;
}

// Function to display a string on the screen of primary monitor
void vga_print_string(const char *str) {
    uint8_t x = vga_cursorx;
    uint8_t y = vga_cursory;

    while (*str != '\0') {
        if (*str == '\n') {
            x = 0;
            y++;
        } else {
            vga_put_char(*str, x, y);
            x++;
            if (x >= VGA_WIDTH) {
                x = 0;
                y++;
            }
        }

        if (y >= VGA_HEIGHT) {
            // To-DO: Implement scrolling.
            break;
        }

        str++;
    }

    // Set the text cursor position
    vga_set_cursor_position(x, y);
}

// Function to read from console (stdin) for primary monitor
char vga_read_console() {
    // It will probably need a keyboard driver, so for making it simple just return X
    // Yes, I can simply return X without the variable.
    char input = 'X';
    return input;
}

// Function to clear the screen of primary monitor
void vga_clear_screen() {
    volatile uint16_t *video_memory = (volatile uint16_t *)0xB8000;

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
        video_memory[i] = ' ' | (vga_cursorattr << 8);
    }
    
    vga_set_cursor_position(0, 0);
}