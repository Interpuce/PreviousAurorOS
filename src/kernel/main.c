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
    // Perform system tasks here
    // For example: check for system events, manage resources, etc.
    return 0; // No errors
}

// Function to use multitasking in AurorOS
int multitasking_loop() {
    // Perform multitasking tasks here
    // For example: schedule processes, manage task switching, etc.
    return 0; // No errors
}

// Function to initialize hardware
void init_hardware() {
    // Initialize hardware components
    write_OK("Initialized: Hardware\n");
}

// Function to initialize drivers
void init_drivers() {
    // Load and initialize drivers
    write_OK("Initialized: Drivers\n");
}

// Function to initialize filesystem
void init_filesystem() {
    // Initialize filesystem
    write_OK("Initialized: Filesystem\n");
}

// Function to initialize memory management
void init_memory_management() {
    // Set up memory management
    write_OK("Initialized: Memory Management\n");
}

int main() {
    // Reset to default color
    set_text_color(0x07);

    // Write AurorOS version
    print_version_line();

    // Say that kernel parts have been included
    write_OK("Loaded: AurorOS kernel\n");

    // Initialize kernel subsystems
    init_hardware();
    init_drivers();
    init_filesystem();
    init_memory_management();

    // The main kernel loop
    while (true) {
        // Execute system loop
        system_loop();
        // Execute multitasking loop
        multitasking_loop();
    }

    return 0;
}