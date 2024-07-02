// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This is a custom header file used to declare (not define) functions
// defined in various kernel-side C files.

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