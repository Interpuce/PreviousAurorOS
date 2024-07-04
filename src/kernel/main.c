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

// Internal functions declaration

int loop_update(void);
int loop_system(void);
int init(int start_code);
int main(void);

// Initializes kernel subsystems.
int init(int start_code) {
    if (start_code == 1) {
        // Initialize console mode
        if (cm_init() == CODE_EXIT) {
            return CODE_EXIT; // The monitor cannot be detected
        }

        return CODE_SUCCESS; // Returns success.
    } else {
        return CODE_INVALID; // The start code is probably invalid or not implemented.
    }
}

// The update loop executed after system loop.
// It will be used for multitasking in the future, now it is only placeholder.
int loop_update(void) {
    return CODE_SUCCESS;
}

// The system loop.
int loop_system(void) {
    return CODE_SUCCESS;
}

/* The main kernel function. Here kernel starts working and uses functions from the kernel API (in the future). */
int main(void) {
    // Init kernel subsystems
    if (init(1) == CODE_EXIT) {
        // Exit the kernel, because initialization executed a problem
        return CODE_SUCCESS; // CODE_SUCCESS simply because this function must return 0
    }

    // The main kernel loop
    while (true) {
        // Execute system loop
        loop_system();

        // Execute update loop
        loop_update();
    }

    return CODE_SUCCESS; // The kernel cannot go here
}