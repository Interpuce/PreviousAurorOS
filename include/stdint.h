// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This is an substitute to default <stdint.h> library file,
// which was deleted by Makefile

// Some files needs this file so it was rewritted 
// to be helpful in these files.

#ifndef _STDINT
#define _STDINT 1

// The types definitions

typedef signed char         int8_t;
typedef short               int16_t;
typedef int                 int32_t;
typedef long long           int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef signed char         int_least8_t;
typedef short               int_least16_t;
typedef int                 int_least32_t;
typedef long long           int_least64_t;

typedef unsigned char       uint_least8_t;
typedef unsigned short      uint_least16_t;
typedef unsigned int        uint_least32_t;
typedef unsigned long long  uint_least64_t;

typedef signed char         int_fast8_t;
typedef int                 int_fast16_t;
typedef int                 int_fast32_t;
typedef long long           int_fast64_t;

typedef unsigned char       uint_fast8_t;
typedef unsigned int        uint_fast16_t;
typedef unsigned int        uint_fast32_t;
typedef unsigned long long  uint_fast64_t;

typedef long long           intptr_t;
typedef unsigned long long  uintptr_t;

typedef long long           intmax_t;
typedef unsigned long long  uintmax_t;

// The various constants defines the minimum and maximum numbers
// of defined integer types

#define INT8_MIN            (-128)
#define INT16_MIN           (-32767-1)
#define INT32_MIN           (-2147483647-1)
#define INT64_MIN           (-__LONG_LONG_MAX__-1)

#define INT8_MAX            (127)
#define INT16_MAX           (32767)
#define INT32_MAX           (2147483647)
#define INT64_MAX           (__LONG_LONG_MAX__)

#define UINT8_MAX           (255)
#define UINT16_MAX          (65535)
#define UINT32_MAX          (4294967295U)
#define UINT64_MAX          (__LONG_LONG_MAX__ * 2ULL + 1ULL)

#define INT_LEAST8_MIN      INT8_MIN
#define INT_LEAST16_MIN     INT16_MIN
#define INT_LEAST32_MIN     INT32_MIN
#define INT_LEAST64_MIN     INT64_MIN

#define INT_LEAST8_MAX      INT8_MAX
#define INT_LEAST16_MAX     INT16_MAX
#define INT_LEAST32_MAX     INT32_MAX
#define INT_LEAST64_MAX     INT64_MAX

#define UINT_LEAST8_MAX     UINT8_MAX
#define UINT_LEAST16_MAX    UINT16_MAX
#define UINT_LEAST32_MAX    UINT32_MAX
#define UINT_LEAST64_MAX    UINT64_MAX

#define INT_FAST8_MIN       INT8_MIN
#define INT_FAST16_MIN      INT32_MIN
#define INT_FAST32_MIN      INT32_MIN
#define INT_FAST64_MIN      INT64_MIN

#define INT_FAST8_MAX       INT8_MAX
#define INT_FAST16_MAX      INT32_MAX
#define INT_FAST32_MAX      INT32_MAX
#define INT_FAST64_MAX      INT64_MAX

#define UINT_FAST8_MAX      UINT8_MAX
#define UINT_FAST16_MAX     UINT32_MAX
#define UINT_FAST32_MAX     UINT32_MAX
#define UINT_FAST64_MAX     UINT64_MAX

#define INTPTR_MIN          INT64_MIN
#define INTPTR_MAX          INT64_MAX
#define UINTPTR_MAX         UINT64_MAX

#define INTMAX_MIN          INT64_MIN
#define INTMAX_MAX          INT64_MAX
#define UINTMAX_MAX         UINT64_MAX

#define INTMAX_C(value)     (value ## LL)
#define UINTMAX_C(value)    (value ## ULL)

#define INT8_C(value)       value
#define INT16_C(value)      value
#define INT32_C(value)      value
#define INT64_C(value)      value ## LL

#define UINT8_C(value)      value ## U
#define UINT16_C(value)     value ## U
#define UINT32_C(value)     value ## U
#define UINT64_C(value)     value ## ULL

#endif