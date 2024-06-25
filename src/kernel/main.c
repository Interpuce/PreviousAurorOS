// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// If you want to learn how kernel works, use documentation.
// The code can be unreadable in some moments.

// Include kernel API (from /includes/kernel.h)
#include <auror/kernel.h>

// The main kernel function. Here kernel starts working and uses functions from the kernel API (in the future).
int main() {
    init(1);
    return 0; // Return 0 by default (success)
}