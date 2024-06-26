// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// If you want to learn how kernel works, use documentation.
// The code can be unreadable in some moments.

// The current AurorOS version
#define OS_VERSION "1.0.0"

// The success code.
#define CODE_SUCCESS 0

// The invalid code
#define CODE_INVALID -1

// Initializes kernel subsystems.
int init(int start_code) {
    if (start_code == 1) {
        // Initializes kernel subsystems (in the future)
        return CODE_SUCCESS; // Returns success
    } else {
        return CODE_INVALID; // The start code is invalid
    }
}

// The update loop executed after system loop
int loop_update() {
    return CODE_SUCCESS;
}

// The system loop
int loop_system() {
    return CODE_SUCCESS;
}