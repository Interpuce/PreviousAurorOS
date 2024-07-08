// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This is a default keyboard driver.

// This is unfinished version of the driver.
// It needs some improvments.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/io.h>
#include <signal.h>
#include <fcntl.h>

#define KBD_DATA_PORT 0x60
#define KBD_STATUS_PORT 0x64
#define KBD_IRQ 1

// Scan code to ASCII map
unsigned char keymap[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '-', '=', '\b', /* Backspace */
    '\t', /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0, /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
    '\'', '`',   0, /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
    'm', ',', '.', '/',   0, /* Right shift */
    '*',
    0,  /* Alt */
    ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
    '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
    '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0, 0, 0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

// Interrupt handler function
void keyboard_interrupt_handler(int sig) {
    unsigned char scancode;

    // Read the scan code from the keyboard data port
    scancode = inb(KBD_DATA_PORT);

    if (scancode & 0x80) {
        // Key Released
        // Idk what to put here
    } else {
        // Key pressed
        // Idk what to put here too
    }
}

int main() {
    // Gain access to the I/O ports
    if (ioperm(KBD_DATA_PORT, 1, 1) != 0 || ioperm(KBD_STATUS_PORT, 1, 1) != 0) {
        perror("ioperm");
        exit(1);
    }

    // Set up the interrupt handler
    if (signal(SIGINT, keyboard_interrupt_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    printf("Press Ctrl+C to exit\n");

    // Main loop of the driver
    while (1) {
        pause(); // Wait for an interrupt...
    }

    return 0;
}