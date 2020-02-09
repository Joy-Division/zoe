/*
 *【 LibCM 】by J.Ingram
 * Configuration Include
 */
#ifndef INC_CMCONF_H
#define INC_CMCONF_H

/*---------------------------------------------------------------------------*/
/* Data Type Width Specification w/ C Primitives                             */
/*---------------------------------------------------------------------------*/
#define CM_TYPE_INT8     char
#define CM_TYPE_INT16    short
#define CM_TYPE_INT32    int
#define CM_TYPE_INT64    long long
#define CM_TYPE_FLOAT32  float
#define CM_TYPE_FLOAT64  double

/*---------------------------------------------------------------------------*/
/* Data Type Availability for GNU C                                          */
/*---------------------------------------------------------------------------*/
#if defined( __GNUC__ )

/* --- 128-bit Floating Point --- */

#if defined( __i686__ )\
||  defined( __x86_64__ )
#define CM_HAVE_FLOAT128 (1)
#define CM_HAVE_MODETF   (1)
#endif

/* --- 96-bit Floating Point --- */

#if defined( __i686__ )
#define CM_HAVE_FLOAT96 (1)
#define CM_HAVE_MODEXF  (1)
#endif

/* --- 128-bit Integer --- */

#if defined( __x86_64__ )\
||  defined( __R5900__ ) /* (PS2) Emotion Engine */\
||  defined( __psp__ )   /* (PSP) Allegrex       */\
||  defined( __PPU__ )   /* (PS3) Cell/B.E. PPU  */\
||  defined( __SPU__ )   /* (PS3) Cell/B.E. SPU  */
#define CM_HAVE_INT128 (1)
#define CM_HAVE_MODETI (1)
#endif

#endif /* __GNUC__ */

/*---------------------------------------------------------------------------*/
/* Conflict Check for SCEI PSP(TM) Programmer Tool                           */
/*---------------------------------------------------------------------------*/
#if defined( __psp__ )

/* Check if psptypes.h has been included without suppressing typedefs
 * that conflict with cmtypes.h. Halt the build process if so. */
#if defined( _SCE_PSPTYPES_H )\
&& !defined( SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE )
#error "psptypes.h was included before conflict suppression!!"
#endif

#ifndef SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE
#define SCE_PSPTYPES_SUPPRESS_ADDITIONAL_DEFINE (1)
#endif

#endif /* __psp__ */

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=utf-8 : */
