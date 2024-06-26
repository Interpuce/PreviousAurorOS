// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This is a basic VGA detecting driver. This will check if the system
// needs to load an another VGA driver in console mode or skip it.

// ISSUE: If there any VGA monitor, the system will mark the first
//        found VGA monitor to a default monitor.

// Include INT types
#include <stdint.h>

// A function that detects VGA screens.
int vga_check_monitor_presence() {
    volatile uint16_t *video_memory = (volatile uint16_t *)0xB8000;

    // The default value for VGA
    uint16_t default_value = 0x0700;

    // The first byte of memory
    uint16_t saved_value = *video_memory;

    // Save the default value
    *video_memory = default_value;

    // Read the value
    uint16_t read_value = *video_memory;

    // Fix the changed value
    *video_memory = saved_value;

    // The final check
    return (read_value == default_value);
}