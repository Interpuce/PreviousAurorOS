// ======================================================================
//                            AurorOS Kernel
// ======================================================================

// => The AurorOS kernel.
//       This file is basically a system loader for the kernel
//       and implementation of console commands.

// Include C basics
#include <string.h>
#include <stdbool.h>

// Get kernel functions
#include "functions.h"

// Get console API
#include "../console/api.h"

// Function executes before multitasking cycle
int system_loop() {
    return 0; // No errors
}

// Function to use multitasking in AurorOS
int multitasking_loop() {
    return 0; // No errors
}

// Function to initialize kernel subsystems
int init() {
    return 0;
}

int main() {
    // Reset to default color
    set_text_color(0x07);

    // Write AurorOS version
    print_version_line();

    // Say that kernel parts have been included
    write_OK("Loaded: AurorOS kernel\n");

    // Initialize kernel subsystems
    init();

    // The main kernel loop
    while (true) {
        // Execute system loop
        system_loop();
        // Execute multitasking loop
        multitasking_loop();
    }

    return 0;
}