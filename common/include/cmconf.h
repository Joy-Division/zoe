/*
 *【 LibCM 】ver.20200314
 * Copyright (C) 2019 2020 J.Ingram
 * All rights reserved.
 */
/* cmconf.h
 * Configuration Include
 */
#ifndef INCLUDED_CMCONF_H
#define INCLUDED_CMCONF_H

/*---------------------------------------------------------------------------*/
/* Target-Independent Defines                                                */
/*---------------------------------------------------------------------------*/

/* These provide the correct C data type primitive for a given width.
 * #undef and (re)#define below for any platforms/toolchains with different
 * implementations. For instance: sizeof(int)==2 or sizeof(long)==8 */
#define CM_TYPE_INT8     char
#define CM_TYPE_INT16    short
#define CM_TYPE_INT32    int
#define CM_TYPE_INT64    long long
#define CM_TYPE_FLOAT32  float
#define CM_TYPE_FLOAT64  double

/* Magic numbers for the two major byte orders; used to define and evaluate
 * the CM_ENDIANNESS and CM_BYTE_ORDER macros for conditional compilation. */
#define CM_LIL_ENDIAN  1234
#define CM_BIG_ENDIAN  4321

/*---------------------------------------------------------------------------*/
/* Target-Dependent Defines (Processor ISA)                                  */
/*---------------------------------------------------------------------------*/

/*---< Intel x86 (32-bit) >---*/

#if defined(__i386__)||defined(__i486__)\
||  defined(__i586__)||defined(__i686__)\
||  defined(_M_IX86)

#define CM_ENDIANNESS  CM_LIL_ENDIAN
#define CM_BYTE_ORDER  CM_ENDIANNESS

#if defined(__GNUC__)\
&&  defined(__i686__)
#  define CM_HAVE_MODEXF  (1)
#  define CM_HAVE_MODETF  (1)
#endif

/*---< AMD64 / x86-64 (64-bit) >---*/

#elif defined(__x86_64__)||defined(_M_X64)\
||    defined(__adm64__) ||defined(_M_AMD64)

#define CM_ENDIANNESS  CM_LIL_ENDIAN
#define CM_BYTE_ORDER  CM_ENDIANNESS

#if defined(__GNUC__)
#  define CM_HAVE_MODETI  (1)

/* Support added in 3.9.0 */
#if !((__clang_major__ <= 3)\
    &&(__clang_minor__ <= 8))

#  define CM_HAVE_MODETF  (1)

#endif /* clang >= 3.9.0 */
#endif /* __GNUC__ */

/*---< ARM >---*/

#elif defined(__arm__)||defined(_M_ARM)

#if defined(__ARMEB__)
#  define CM_ENDIANNESS  CM_BIG_ENDIAN
#  define CM_BYTE_ORDER  CM_ENDIANNESS
#else
#  define CM_ENDIANNESS  CM_LIL_ENDIAN
#  define CM_BYTE_ORDER  CM_ENDIANNESS
#endif

/*---< ARM Thumb Mode >---*/

#elif defined(__thumb__)||defined(_M_ARMT)

#if defined(__THUMBEB__)
#  define CM_ENDIANNESS  CM_BIG_ENDIAN
#  define CM_BYTE_ORDER  CM_ENDIANNESS
#else
#  define CM_ENDIANNESS  CM_LIL_ENDIAN
#  define CM_BYTE_ORDER  CM_ENDIANNESS
#endif

/*---< IBM PowerPC >---*/

#elif defined(__ppc__)||defined(__powerpc__)||defined(_M_PPC)\
||    defined(__PPC__)||defined(__POWERPC__)||defined(_M_PPCBE)

/* PowerPC is a bi-endian architecture, however, the default endian mode
 * is big-endian, and most systems are implemented in big-endian mode. */
#define CM_ENDIANNESS  CM_BIG_ENDIAN
#define CM_BYTE_ORDER  CM_ENDIANNESS

/*---< MIPS / MIPS64 >---*/

#elif defined(__mips__)||defined(__mips)\
||    defined(__MIPS__)||defined(__MIPS)

#if defined(_MIPSEB)
#  define CM_ENDIANNESS  CM_BIG_ENDIAN
#  define CM_BYTE_ORDER  CM_ENDIANNESS
#else
#  define CM_ENDIANNESS  CM_LIL_ENDIAN
#  define CM_BYTE_ORDER  CM_ENDIANNESS
#endif

#if defined(__GNUC__)\
&&  defined(__mips64)
#  define CM_HAVE_MODETI  (1)
#  define CM_HAVE_MODETF  (1)
#endif

/*---< Motorola 680000 >---*/

#elif defined(__m68k__)\
||    defined(__mc68000__)||defined(__MC68000__)\
||    defined(__mc68010__)||defined(__MC68010__)\
||    defined(__mc68020__)||defined(__MC68020__)\
||    defined(__mc68030__)||defined(__MC68030__)\
||    defined(__mc68040__)||defined(__MC68040__)\
||    defined(__mc68060__)||defined(__MC68060__)\
||    defined(_M_M68K)

#define CM_ENDIANNESS  CM_BIG_ENDIAN
#define CM_BYTE_ORDER  CM_ENDIANNESS

/*---< Hitachi SuperH >---*/

#elif defined(__sh__) ||defined(__SH__)\
||    defined(__sh1__)||defined(__SH1__)\
||    defined(__sh2__)||defined(__SH2__)\
||    defined(__sh3__)||defined(__SH3__)\
||    defined(__sh4__)||defined(__SH4__)\
||    defined(__sh5__)||defined(__SH5__)

/* SH-1 & SH-2 are big-endian, while SH-3 through SH-5 are bi-endian. */
/* For instance, the Sega Dreamcast (SH-4) works in little-endian mode. */

#if defined(__littleendian__)\
||  defined(__LITTLE_ENDIAN__)
#define CM_ENDIANNESS  CM_LIL_ENDIAN
#define CM_BYTE_ORDER  CM_ENDIANNESS
#else
#define CM_ENDIANNESS  CM_BIG_ENDIAN
#define CM_BYTE_ORDER  CM_ENDIANNESS
#endif

/*---< UNDEFINED >---*/

#else /* (DEFAULTS) */

#define CM_ENDIANNESS  CM_LIL_ENDIAN
#define CM_BYTE_ORDER  CM_ENDIANNESS

#endif /* (ARCH) */

/*---------------------------------------------------------------------------*/
/* Target-Dependent Defines (Platform/OS)                                    */
/*---------------------------------------------------------------------------*/

/*---< PlayStation 2 (Emotion Engine) >---*/

#if defined(__R5900__)||defined(__ee__)

#if defined(__GNUC__)
#  ifndef CM_HAVE_MODETI
#  define CM_HAVE_MODETI  (1)
#  endif

#  undef  CM_TYPE_INT64
#  define CM_TYPE_INT64 long
#endif

#endif /* (Emotion Engine) */

/*---< PlayStation Portable (ALLEGREX) >---*/

#if defined(__psp__)

#if defined(__GNUC__)\
||  defined(__MWERKS__)\
||  defined(__SNC__)

#  ifndef CM_HAVE_MODETI
#  define CM_HAVE_MODETI  (1)
#  endif

#endif

#if defined(__SCE__)

/* Check if "psptypes.h" has been included without having suppressed typedefs
 * which conflict with "cmtypes.h" and terminate the build process if so. */
#if defined(_SCE_PSPTYPES_H)\
&& !defined(SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE)
#error "SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE not in effect"
#endif

#ifndef SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE
#define SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE (1)
#endif

#endif /* __SCE__ */
#endif /* __psp__ */

/*---< PlayStation 3 (Cell Broadband Engine) >---*/

#if defined(__CELLOS_LV2__)\
||  defined(__PPU__)||defined(__SPU__)

#if defined(__GNUC__)\
&& !defined(__SNC__) /* Error:1103 */
#  ifndef CM_HAVE_MODETI
#  define CM_HAVE_MODETI  (1)
#  endif
#endif

#endif /* (CellBE/OS) */

#endif /* END OF FILE */
