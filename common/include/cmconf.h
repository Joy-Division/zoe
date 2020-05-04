/*
 *【 LibCM 】ver.20200504
 * Copyright (C) 2019 2020 J.Ingram
 * All Rights Reserved.
 */
#ifndef INCLUDED_CMCONF_H
#define INCLUDED_CMCONF_H

/*===========================================================================*/
/* Target-Independent Defines                                                */
/*===========================================================================*/

#define LIBCM_VERSION_YYYY  0x2020
#define LIBCM_VERSION_MMDD  0x0504

#define LIBCM_VERSION \
	( ((LIBCM_VERSION_YYYY << 8) & 0xFFFF0000) \
	| ((LIBCM_VERSION_MMDD     ) & 0x0000FFFF) )

/* These provide the correct C data type primitive for a given width.
 * #undef and (re)#define below for any platforms/toolchains with different
 * implementations. For instance: sizeof(int)==2 or sizeof(long)==8
 */
#define CM_TYPE_INT8    char
#define CM_TYPE_INT16   short
#define CM_TYPE_INT32   int
#define CM_TYPE_INT64   long long
#define CM_TYPE_FLOAT32 float
#define CM_TYPE_FLOAT64 double

/* Magic numbers for the two major byte orders, primarily intended for use
 * in conditionals along with the CM_BYTE_ORDER flag. Decimal literals were
 * chosen to avoid misrepresentation if used as an attribute for binary data
 * formats stored with the opposite endiannes of the target machine.
 */
#define CM_LIL_ENDIAN   44332211    /* 0x02A474B3 */
#define CM_BIG_ENDIAN   11223344    /* 0x00AB4130 */

/*===========================================================================*/
/* Target-Dependent Defines (Processor ISA)                                  */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/*                        <<< Intel x86 (32-bit) >>>                         */
/*---------------------------------------------------------------------------*/
#if defined(__i386__)||defined(__i486__)\
||  defined(__i586__)||defined(__i686__)\
||  defined(_M_IX86)

#define CM_ARCH_X86 1

/* Little-Endian ONLY */
#define CM_BYTE_ORDER CM_LIL_ENDIAN

#if defined(__GNUC__)
#if defined(__i686__)

#  define CM_HAVE_MODEXF    1
#  define CM_SIZEOF_MODEXF  12

#  define CM_HAVE_MODETF    1
#  define CM_SIZEOF_MODETF  16

#endif /* __i686__ */
#endif /* __GNUC__ */

/*---------------------------------------------------------------------------*/
/*                      <<< AMD64 / x86-64 (64-bit) >>>                      */
/*---------------------------------------------------------------------------*/
#elif defined(__x86_64__)||defined(_M_X64)\
||    defined(__adm64__) ||defined(_M_AMD64)

#define CM_ARCH_AMD64   1
#define CM_ARCH_X86_64  1
#define CM_ARCH_X64     1

/* Little-Endian ONLY */
#define CM_BYTE_ORDER CM_LIL_ENDIAN

#if defined(__GNUC__)

#  define CM_HAVE_MODETI    1
#  define CM_SIZEOF_MODETI  16

#  define CM_HAVE_MODEXF    1
#  define CM_SIZEOF_MODEXF  16

/* GCC version 4.4.0 MINIMUM
 * Clang defines GNU C 4.2.1
 */
#if !((__GNUC__ <= 4)\
||   ((__GNUC__ == 4)&&(__GNUC_MINOR__ < 4)))
#  define CM_HAVE_MODETF    1
#  define CM_SIZEOF_MODETF  16
#endif

/* Clang version 3.9.0 MINIMUM */
#if !((__clang_major__ <= 3)\
||   ((__clang_major__ == 3)&&(__clang_minor__ <= 8)))
#  define CM_HAVE_MODETF    1
#  define CM_SIZEOF_MODETF  16
#endif

#endif /* __GNUC__ */

/*---------------------------------------------------------------------------*/
/*                                <<< ARM >>>                                */
/*---------------------------------------------------------------------------*/
#elif defined(__arm__)||defined(_M_ARM)

#define CM_ARCH_ARM 1

#if defined(__ARMEB__)\
||  defined(__BIG_ENDIAN__)
#  define CM_BYTE_ORDER CM_BIG_ENDIAN
#else
#  define CM_BYTE_ORDER CM_LIL_ENDIAN
#endif

/*---------------------------------------------------------------------------*/
/*                               <<< ARM64 >>>                               */
/*---------------------------------------------------------------------------*/
#elif defined(__arm64__)||defined(_M_ARM64)||defined(__aarch64__)

#define CM_ARCH_ARM64 1

#if defined(__AARCH64EB__)\
||  defined(__BIG_ENDIAN__)
#  define CM_BYTE_ORDER CM_BIG_ENDIAN
#else
#  define CM_BYTE_ORDER CM_LIL_ENDIAN
#endif

/*---------------------------------------------------------------------------*/
/*                          <<< ARM Thumb Mode >>>                           */
/*---------------------------------------------------------------------------*/
#elif defined(__thumb__)||defined(_M_ARMT)

#define CM_ARCH_THUMB 1

#if defined(__THUMBEB__)\
||  defined(__BIG_ENDIAN__)
#  define CM_BYTE_ORDER CM_BIG_ENDIAN
#else
#  define CM_BYTE_ORDER CM_LIL_ENDIAN
#endif

/*---------------------------------------------------------------------------*/
/*                            <<< IBM PowerPC >>>                            */
/*---------------------------------------------------------------------------*/
#elif defined(__ppc__)||defined(__powerpc__)\
||    defined(__PPC__)||defined(__POWERPC__)\
||    defined(_M_PPC) ||defined(_ARCH_PPC)

#define CM_ARCH_PPC 1

#if defined(__ppc64__)||defined(__powerpc64__)\
||  defined(__PPC64__)||defined(__POWERPC64__)\
||  defined(_M_PPC64) ||defined(_ARCH_PPC64)
#define CM_ARCH_PPC64 1
#endif

/* PowerPC is a bi-endian architecture, however, the default setting
 * is big-endian, and most systems operate in big-endian mode.
 */
#if defined(__LITTLE_ENDIAN__)
#  define CM_BYTE_ORDER CM_LIL_ENDIAN
#else
#  define CM_BYTE_ORDER CM_BIG_ENDIAN
#endif

/*---------------------------------------------------------------------------*/
/*                           <<< MIPS & MIPS64 >>>                           */
/*---------------------------------------------------------------------------*/
#elif defined(__mips__)||defined(__mips)\
||    defined(__MIPS__)||defined(__MIPS)

#define CM_ARCH_MIPS 1

#if defined(_MIPSEB)\
||  defined(__BIG_ENDIAN__)
#  define CM_BYTE_ORDER CM_BIG_ENDIAN
#else
#  define CM_BYTE_ORDER CM_LIL_ENDIAN
#endif

#if defined(__GNUC__)\
&&  defined(__mips64)
#  define CM_HAVE_MODETI    1
#  define CM_SIZEOF_MODETI  16
#  define CM_HAVE_MODETF    1
#  define CM_SIZEOF_MODETF  16
#endif

/*---------------------------------------------------------------------------*/
/*                          <<< Motorola 680000 >>>                          */
/*---------------------------------------------------------------------------*/
#elif defined(__m68k__)\
||    defined(__mc68000__)||defined(__MC68000__)\
||    defined(__mc68010__)||defined(__MC68010__)\
||    defined(__mc68020__)||defined(__MC68020__)\
||    defined(__mc68030__)||defined(__MC68030__)\
||    defined(__mc68040__)||defined(__MC68040__)\
||    defined(__mc68060__)||defined(__MC68060__)\
||    defined(_M_M68K)

#define CM_ARCH_M68K 1

/* Big-Endian ONLY */
#define CM_BYTE_ORDER CM_BIG_ENDIAN

/*---------------------------------------------------------------------------*/
/*                          <<< Hitachi SuperH >>>                           */
/*---------------------------------------------------------------------------*/
#elif defined(__sh__) ||defined(__SH__)\
||    defined(__sh1__)||defined(__SH1__)\
||    defined(__sh2__)||defined(__SH2__)\
||    defined(__sh3__)||defined(__SH3__)\
||    defined(__sh4__)||defined(__SH4__)\
||    defined(__sh5__)||defined(__SH5__)

#define CM_ARCH_SH 1

/* SH-1 & SH-2 are big-endian, while SH-3 through SH-5 are bi-endian.
 * For instance, the Sega Dreamcast SH-4 CPU operates in little-endian mode.
 */
#if defined(__littleendian__)\
||  defined(__LITTLE_ENDIAN__)
#  define CM_BYTE_ORDER CM_LIL_ENDIAN
#else
#  define CM_BYTE_ORDER CM_BIG_ENDIAN
#endif

/*---------------------------------------------------------------------------*/
/*                             <<< UNDEFINED >>>                             */
/*---------------------------------------------------------------------------*/
#else /* (DEFAULTS) */

/* For other architectures, the default endianness is set to little-endian,
 * provided that the macro has not been manually predefined by the user.
 */
#ifndef CM_BYTE_ORDER
#define CM_BYTE_ORDER CM_LIL_ENDIAN
#endif

#endif /* (ARCH CHAIN) */

/*===========================================================================*/
/* Target-Dependent Defines (Platform/OS)                                    */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/*                  <<< PlayStation 2 (Emotion Engine) >>>                   */
/*---------------------------------------------------------------------------*/
#if defined(__R5900__)||defined(__ee__)

#if defined(__GNUC__)
#  ifndef CM_HAVE_MODETI
#  define CM_HAVE_MODETI 1
#  endif
#  ifndef CM_SIZEOF_MODETI
#  define CM_SIZEOF_MODETI 16
#  endif

#  undef  CM_TYPE_INT64
#  define CM_TYPE_INT64 long

/* GNU C's __attribute__((mode(TF))) is unsupported.
 * GCC defines __mips64 so it must be undefined here.
 */
#  ifdef CM_HAVE_MODETF
#  undef CM_HAVE_MODETF
#  endif
#endif

#endif /* (Emotion Engine) */

/*---------------------------------------------------------------------------*/
/*                  <<< PlayStation Portable (ALLEGREX) >>>                  */
/*---------------------------------------------------------------------------*/
#if defined(__psp__)

#if defined(__GNUC__)\
||  defined(__MWERKS__) /* ref."psptypes.h" */\
||  defined(__SNC__)    /* ref."psptypes.h" */

#  ifndef CM_HAVE_MODETI
#  define CM_HAVE_MODETI 1
#  endif

#  ifdef CM_HAVE_MODETF
#  undef CM_HAVE_MODETF
#  endif
#endif

#if defined(__SCE__)

/* Check if "psptypes.h" has been included without having suppressed typedefs
 * which conflict with "cmtypes.h" and terminate the build process if so.
 */
#if defined(_SCE_PSPTYPES_H)\
&& !defined(SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE)
#error "SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE not in effect"
#endif

#ifndef SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE
#define SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE 1
#endif

#endif /* __SCE__ */
#endif /* __psp__ */

/*---------------------------------------------------------------------------*/
/*               <<< PlayStation 3 (Cell Broadband Engine) >>>               */
/*---------------------------------------------------------------------------*/
#if defined(__CELLOS_LV2__)\
||  defined(__PPU__)||defined(__SPU__)

/* SPU-Lv2-GCC does not define an architecture or endianness flag.
 * Cell/BE's PPU is also big-endian, so this check is done for both.
 */
#ifndef CM_BYTE_ORDER
#define CM_BYTE_ORDER CM_BIG_ENDIAN
#endif

#if defined(__GNUC__)\
&& !defined(__SNC__) /* Error:1103 */
#  ifndef CM_HAVE_MODETI
#  define CM_HAVE_MODETI 1
#  endif
#endif

#endif /* (CellBE/OS) */

#endif /* END OF FILE */
