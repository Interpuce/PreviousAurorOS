// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// If you want to learn how kernel works, use documentation.
// The code can be unreadable in some moments.

// Include booleans
#include <stdbool.h>

// Include kernel API (from /includes/kernel.h)
#include <auror/kernel.h>

// The main kernel function. Here kernel starts working and uses functions from the kernel API (in the future).
int main() {
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