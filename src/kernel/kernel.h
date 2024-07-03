// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// If you want to learn how kernel works, use documentation.
// The code can be unreadable in some moments.

#ifndef _AUROR_KERNEL
#define _AUROR_KERNEL 1

// The current AurorOS version in the major:minor:patch format
#define OS_VERSION "0.0.1 Snapshot 1"

// The success code definition.
#define CODE_SUCCESS 0

// The invalid code definition.
#define CODE_INVALID -1

// Initializes kernel subsystems.
int init(int start_code) {
    if (start_code == 1) {
        // Initializes kernel subsystems (in the future)
        // For now AurorOS doesn't need any initialization

        return CODE_SUCCESS; // Returns success.
    } else {
        return CODE_INVALID; // The start code is probably invalid or not implemented.
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

#endif