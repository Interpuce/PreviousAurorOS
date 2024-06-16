// ======================================================================
//                            AurorOS Kernel
// ======================================================================

// => The AurorOS kernel functions.
//       This file is basically an kernel function inplementation.

// Import console API
#include "../console/api.h"

// Prints an AurorOS version
void print_version() {
    write_msg("AurorOS 1.0.0")
}

// Same as print_version but with line ending
void print_version_line() {
    set_text_color(0x07)
    print_line("AurorOS 1.0.0")
}