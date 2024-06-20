// ======================================================================
//                            AurorOS Kernel
// ======================================================================

// => The AurorOS kernel functions.
//       This file is basically a kernel function implementation.

// Imports basic features in C
#include <string.h>

// Import console API
#include "../console/api.h"

// Get AurorOS filesystem API
#include "../drivers/fs/arfs.h"

// Get NTFS-3 filesystem API
#include "../drivers/fs/ntfs3.h"

// Defines an AurorOS version
#define OS_VERSION "1.0.0"

// Prints an AurorOS version
void print_version() {
    write_msg("AurorOS ");
    print_line(OS_VERSION);
}

// Same as print_version but with line ending
void print_version_line() {
    set_text_color(0x07);
    print_string("AurorOS ");
    print_line(OS_VERSION);
}