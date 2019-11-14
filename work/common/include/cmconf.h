/*
 *【CM Library】by J.Ingram
 * Configuration Include
 */
#ifndef INC_CMCONF_H
#define INC_CMCONF_H

/*---------------------------------------------------------------------------*
 * GNU C Type Availability
 *---------------------------------------------------------------------------*/
#if defined( __GNUC__ )

/*
 * 128-bit Floating Point
 */
#if defined( __i686__ )\
 || defined( __x86_64__ )
#define HASTYPE_FLOAT128
#endif /* (ARCH) */

/*
 * 96-bit Floating Point
 */
#if defined( __i686__ )
#define HASTYPE_FLOAT96
#endif /* (ARCH) */

/*
 * 128-bit Integer
 */
#if defined( __x86_64__ )\
 || defined( __ee__ )  /* PS2 Emotion Engine */\
 || defined( __psp__ ) /* PSP Allegrex       */\
 || defined( __PPU__ ) /* PS3 Cell/B.E. PPU  */\
 || defined( __SPU__ ) /* PS3 Cell/B.E. SPU  */
#define HASTYPE_INT128
#endif /* (ARCH) */

#endif /* __GNUC__ */

/*---------------------------------------------------------------------------*
 * Conflict Check
 *---------------------------------------------------------------------------*/

/*
 * PlayStation Portable Programmer Tool
 * Runtime Library & Toolchain
 */
#if defined( __psp__ )

/* check if psptypes.h is included
   without suppressed typdefs */
#if defined( _SCE_PSPTYPES_H )\
 && !defined( SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE )
#error "psptypes.h was included before conflict suppression!!"
#endif

/* for conflicting typedefs in cmtypes.h */
#ifndef SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE
#define SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE
#endif

#endif /* __psp__ */

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=utf-8 : */
