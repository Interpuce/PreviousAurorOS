// ======================================================================
//                           AurorOS Bootloader
// ======================================================================

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

// Writes a error line to the console
void writeError(const char* message) {
    set_text_color(0x04);

    print_string("[Error] ");

    set_text_color(0x07);

    print_string(message);
}