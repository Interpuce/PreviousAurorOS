// ======================================================================
//                            AurorOS Kernel
// ======================================================================

// => The AurorOS kernel.
//       This file is basically an system loading from the kernel
//       and inplementation of console commands.

// Get console API
#include <../console/api.c>

// Reset to default color
set_text_color(0x07);