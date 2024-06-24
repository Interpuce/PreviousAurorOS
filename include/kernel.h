// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// If you want to learn how kernel works, use documentation.
// The code can be unreadable in some moments.

// The success code.
#define CODE_SUCCESS 0

// Initializes kernel subsystems.
void init(int start_code) {
    if (start_code == 1) {
        // Initializes kernel subsystems (in the future)
        return CODE_SUCCESS; // Returns success
    } else {
        return -1; // The start code is invalid
    }
}