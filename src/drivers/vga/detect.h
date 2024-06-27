// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This is a basic VGA detecting driver. This will check if the system
// needs to load an another VGA driver in console mode or skip it.

// ISSUE: If there any VGA monitor, the system will mark the first
//        found VGA monitor as a default monitor.

// Include INT types
#include <stdint.h>

// A function that detects VGA screen.
int vga_check_monitor_presence() {
    // Pointer to the VGA text mode memory address
    volatile uint16_t *video_memory = (volatile uint16_t *)0xB8000;

    // Save the original value at the first position of video memory
    uint16_t saved_value = *video_memory;

    // Set a test value
    uint16_t test_value = 0xAA55;

    // Write the test value to video memory
    *video_memory = test_value;

    // Read back the value
    uint16_t read_value = *video_memory;

    // Restore the original value
    *video_memory = saved_value;

    // Check if the value read matches the value written
    return (read_value == test_value);
}