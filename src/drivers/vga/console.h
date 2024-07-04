// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// VGA driver header file

#pragma once // Use new `pragma once` instead of checking if the constant is defined.

// Video ports addresses (VGA registers)
#define VGA_CTRL_REG 0x3D4
#define VGA_DATA_REG 0x3D5

// Text mode screen dimensions (width and height in lines)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Character color attributes
#define VGA_COLOR_BLACK 0
#define VGA_COLOR_WHITE 15

// Global variables to track cursor position and attribute for primary monitor
uint8_t vga_cursorx = 0;
uint8_t vga_cursory = 0;
uint8_t vga_cursorattr = VGA_COLOR_WHITE;