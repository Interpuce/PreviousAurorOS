// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// The console implementation. It has basic console init implementation
// and the console commands.

// Include the functions declarations
#include <kerdef.h>

// Use the booleans
#include <stdbool.h>

// Use the kernel headers
#include "../../kernel/kernel.h"

// VGA console mode and detection driver are included 
// using linking feature during the compilation process

bool isVGApresent;

// The main console function
int cm_init(void) {
    // Detect VGA
    if (vga_check_monitor_presence()) {
        // VGA is detected, set the variable that VGA is present
        isVGApresent = true;
    
        // Exit for now
        return CODE_SUCCESS;
    } else {
        // Set the variable that VGA is not present
        isVGApresent = false;

        // Just exit the function, because it is useless (for now)
        return CODE_EXIT;
    }

    // Return -1 (the kernel cannot probably go here)
    return CODE_INVALID;
}

// The function that writes string on the screen
void cm_write_string(char* write) {
    if (isVGApresent == false) {
        return; // The VGA is not present and for now there isn't a way to display character on the screen
    } else {
        // VGA is present, display characters
        vga_print_string(write);
    }
}