// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This is an substitute to default <string.h> library file,
// which was deleted by Makefile

// Some files needs this file so it was rewritted 
// to be helpful in these files.

#ifndef _STRINGH
#define _STRINGH 1

#include <stddef.h>

// This function returns the lenght of the string
static inline size_t strlen(const char *str) {
    size_t len = 0;

    while (*str++) len++;

    return len;
}

// This function is used to copy string
static inline char *strcpy(char *dest, const char *src) {
    char *d = dest;

    while ((*d++ = *src++));

    return dest;
}

// Other string functions
static inline char *strcat(char *dest, const char *src) {
    char *d = dest;

    while (*d) d++;
    while ((*d++ = *src++));

    return dest;
}
static inline int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

#endif