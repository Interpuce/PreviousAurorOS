// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// If you want to learn how kernel works, use documentation.
// The code can be unreadable in some moments.

// Include booleans
#include <stdbool.h>

// Include kernel API
#include "kernel.h"

// Include functions declarations
#include <kerdef.h>

// Initializes kernel subsystems.
int init(int start_code) {
    if (start_code == 1) {
        // Initialize console mode
        cm_init();

        return CODE_SUCCESS; // Returns success.
    } else {
        return CODE_INVALID; // The start code is probably invalid or not implemented.
    }
}

// The update loop executed after system loop.
// It will be used for multitasking in the future, now it is only placeholder.
int loop_update() {
    return CODE_SUCCESS;
}

// The system loop.
int loop_system() {
    return CODE_SUCCESS;
}

// The main kernel function. Here kernel starts working and uses functions from the kernel API (in the future).
void main() {
    // Init kernel subsystems
    init(1);

    // The main kernel loop
    while (true) {
        // Execute system loop
        loop_system();

        // Execute update loop
        loop_update();
    }

    // Exit from kernel
    return 0; // Return 0 by default (success)
}