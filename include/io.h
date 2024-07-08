// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This IO file is used to put or get something from the
// devices ports. It can be used by the system to manage various
// devices.

// Use pragma once to prevent using this file multiply
#pragma once

// Prototypes of internal functions
static inline unsigned char inb(unsigned short port);
static inline void outb(unsigned short port, unsigned char value);

// Use assembly to put something to the device
static inline void outb(unsigned short port, unsigned char value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Use assembly to get something to the device
static inline unsigned char inb(unsigned short port) {
    unsigned char value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}
