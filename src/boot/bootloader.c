// ======================================================================
//                           AurorOS Bootloader
// ======================================================================

#include <stdbool.h>
#include <../console/api.c>

void stage2_main() {
    print_string("Hello from C bootloader!\r\n");

    writeError("This is an error message.\r\n");

    while (1);
}