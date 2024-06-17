// ======================================================================
//                            AurorOS Kernel
// ======================================================================

// => The AurorOS kernel.
//       This file is basically an system loading from the kernel
//       and inplementation of console commands.

// Include C basics
#include <string.h>

// Get kernel functions
#include "functions.h"

// Get console API
#include "../console/api.h"

// Reset to default color
set_text_color(0x07);

// Write AurorOS version
print_version_line();

// Say that kernel parts has been included
write_OK("Loaded: Console API\n");
write_OK("Loaded: AFS driver\n");
write_OK("Loaded: NTFS driver\n");