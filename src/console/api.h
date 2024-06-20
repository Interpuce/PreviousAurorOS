// ======================================================================
//                            AurorOS Kernel
// ======================================================================

// => The initial API for console writing.
//       This API is used to write text on the console, setting text color
//       and for displaying errors, warnings and notices

#include <stdbool.h>

// Prints a string to the console
void print_string(const char* str) {
    while (*str) {
        __asm__ volatile (
            "mov ah, 0x0E\n"
            "mov al, %[char]\n"
            "int 0x10\n"
            :
            : [char] "r" (*str)
        );
        str++;
    }
}

// Prints a line to the console
void print_line(const char* str) {
    print_string(str);
    print_string("\n");
}

// Sets up a color
void set_text_color(unsigned char color) {
    __asm__ volatile (
        "mov ah, 0x0B\n"
        "mov bh, 0x00\n"
        "mov bl, %[color]\n"
        "int 0x10\n"
            :
            : [color] "r" (color)
    );
}

// Writes a message
void write_msg(const char* message) {
    set_text_color(0x07); // Reset to default color
    print_string(message);
}

// Writes an error line to the console
void write_error(const char* message) {
    set_text_color(0x04); // Red color for error
    print_string("[Error] ");
    set_text_color(0x07); // Reset to default color
    print_string(message);
}

// Writes a warning line to the console
void write_warn(const char* message) {
    set_text_color(0x0E); // Yellow color for warning
    print_string("[Warning] ");
    set_text_color(0x07); // Reset to default color
    print_string(message);
}

// Writes a notice line to the console
void write_notice(const char* message) {
    set_text_color(0x03); // Cyan color for notice
    print_string("[Notice] ");
    set_text_color(0x07); // Reset to default color
    print_string(message);
}

// Writes an OK line to the console
void write_OK(const char* message) {
    set_text_color(0x02); // Green color for OK
    print_string("[OK] ");
    set_text_color(0x07); // Reset to default color
    print_string(message);
}

// Writes a skipped line to the console
void write_skipped(const char* message) {
    set_text_color(0x0E); // Yellow color for skipped
    print_string("[Skipped] ");
    set_text_color(0x07); // Reset to default color
    print_string(message);
}