// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// The console implementation. It has basic running implementation
// and the console commands.

// Use the booleans
#include <stdbool.h>

// Use the kernel headers
#include <auror/kernel.h>

// VGA detection driver
#include "../vga/detect.h"

// VGA console mode driver (runned only if VGA is detected)
#include "../vga/console.h"

// The main console function
int cm_init() {
    // Detect VGA
    if (vga_check_monitor_presence()) {
        // VGA is detected, initialize the VGA console mode driver
        vga_print_string("Hello world!");
        while (true) {
            // For now, prevent the function from returning 0
        }
    } else {
        // Just exit the kernel, because it is useless (for now)
        return 0;
    }

    // Return 0 (the kernel cannot probably go here)
    return 0;
}