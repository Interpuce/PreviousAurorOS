// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This is a custom header file used to declare (not define) functions
// defined in various kernel-side C files.

#pragma once // Use new `pragma once` instead of checking if the constant is defined.
#include <stdint.h> // For types in functions

// Information for Visual Studio Code users: don't belive the information
//   from the editor that function is not defined. To disable this disgusting
//   error, open the tabs with files defining functions and close it.

// ---------------------------- drivers/vga/console.c ----------------------------

// Function to set cursor position for primary monitor
extern void vga_set_cursor_position(uint8_t x, uint8_t y);

// Function to set character attribute (color) for primary monitor
extern void set_char_attribute(uint8_t attr);

// Function to display a character on the screen of primary monitor
extern void vga_put_char(uint8_t c, uint8_t x, uint8_t y);

// Function to display a string on the screen of primary monitor
extern void vga_print_string(const char *str);

// Function to read from console (stdin) for primary monitor
extern char vga_read_console();

// Function to clear the screen of primary monitor
extern void vga_clear_screen();

// ---------------------------- drivers/vga/detect.c ----------------------------

// A function that detects VGA screen.
extern int vga_check_monitor_presence();

// ---------------------------- drivers/console/init.c ----------------------------

// The main console function
extern int cm_init(void);

// The function that writes string on the screen
extern void cm_write_string(char* write);

// ---------------------------- kernel/kernel.h ----------------------------

// The update loop executed after system loop
extern int loop_update();

// The system loop
extern int loop_system();

// Initializes kernel subsystems.
extern int init(int start_code);