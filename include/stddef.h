// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This is an substitute to default <stddef.h> library file,
// which was deleted by Makefile

// Some files needs this file so it was rewritted 
// to be helpful in these files.

#ifndef _STDDEF
#define _STDDEF 1

typedef unsigned long size_t;

#ifndef NULL
    #define NULL ((void*)0)
#endif

typedef long ptrdiff_t;

#endif