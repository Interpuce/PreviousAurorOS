// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// The console implementation. It has basic console init implementation
// and the console commands.

// Use the booleans
#include <stdbool.h>

// Use the kernel headers
#include "../../kernel/kernel.h"

// VGA detection driver
#include "../vga/detect.h"

// VGA console mode driver are included in compilation

bool isVGApresent;

// The main console function
int cm_init() {
    // Detect VGA
    if (vga_check_monitor_presence()) {
        // VGA is detected, set the variable that VGA is present
        isVGApresent = true;
    
        // Exit for now
        return CODE_SUCCESS;
    } else {
        // Set the variable that VGA is not present
        isVGApresent = false;

        // Just exit the kernel, because it is useless (for now)
        return CODE_SUCCESS;
    }

    // Return -1 (the kernel cannot probably go here)
    return CODE_INVALID;
}