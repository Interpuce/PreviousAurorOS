// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This is an substitute to default <stdbool.h> library file,
// which was deleted by Makefile

// Some files needs this file so it was rewritted 
// to be helpful in these files.

#pragma once // Use new `pragma once` instead of checking if the constant is defined.

#define bool _Bool
#define true 1
#define false 0