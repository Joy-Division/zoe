/*
 *【 LibCM 】ver.20200504
 * Copyright (C) 2019 2020 J.Ingram
 * All Rights Reserved.
 */
#ifndef INCLUDED_CMTYPES_H
#define INCLUDED_CMTYPES_H

#include "cmconf.h"

/*===========================================================================*/
/* Integer Types w/ Unspecified Sign                                         */
/*===========================================================================*/
/* These types are declared as preprocessor macros to sidestep a limitation  */
/* of typedef aliasing in which the user becomes unable to specify the       */
/* alias's signedness.                                                       */
/*---------------------------------------------------------------------------*/

#ifndef byte
#define byte    CM_TYPE_INT8
#endif
#ifndef llong
#define llong   long long
#endif

/*---------------------------------------------------------------------------*/

#ifndef int8
#define int8    CM_TYPE_INT8
#endif
#ifndef int16
#define int16   CM_TYPE_INT16
#endif
#ifndef int32
#define int32   CM_TYPE_INT32
#endif
#ifndef int64
#define int64   CM_TYPE_INT64
#endif

/*---------------------------------------------------------------------------*/

#ifndef char8
#define char8   CM_TYPE_INT8
#endif
#ifndef char16
#define char16  CM_TYPE_INT16
#endif
#ifndef short16
#define short16 CM_TYPE_INT16
#endif
#ifndef short32
#define short32 CM_TYPE_INT32
#endif
#ifndef long32
#define long32  CM_TYPE_INT32
#endif
#ifndef long64
#define long64  CM_TYPE_INT64
#endif

/*===========================================================================*/
/* Integer Types w/ Unspecified Width                                        */
/*===========================================================================*/

typedef   signed char       schar,  s_char;
typedef unsigned char       uchar,  u_char;
typedef   signed short      sshort, s_short;
typedef unsigned short      ushort, u_short;
typedef   signed int        sint,   s_int;
typedef unsigned int        uint,   u_int;
typedef   signed long       slong,  s_long;
typedef unsigned long       ulong,  u_long;
typedef   signed long long  sllong, s_llong;
typedef unsigned long long  ullong, u_llong;

/*===========================================================================*/
/* Integer Types w/ Specified Width                                          */
/*===========================================================================*/

typedef   signed CM_TYPE_INT8   sbyte, s_byte;
typedef unsigned CM_TYPE_INT8   ubyte, u_byte;

typedef   signed CM_TYPE_INT8   sint8,  s_int8,  s8;
typedef unsigned CM_TYPE_INT8   uint8,  u_int8,  u8;
typedef   signed CM_TYPE_INT16  sint16, s_int16, s16;
typedef unsigned CM_TYPE_INT16  uint16, u_int16, u16;
typedef   signed CM_TYPE_INT32  sint32, s_int32, s32;
typedef unsigned CM_TYPE_INT32  uint32, u_int32, u32;
typedef   signed CM_TYPE_INT64  sint64, s_int64, s64;
typedef unsigned CM_TYPE_INT64  uint64, u_int64, u64;

typedef   signed CM_TYPE_INT8   schar8,   s_char8;
typedef unsigned CM_TYPE_INT8   uchar8,   u_char8;
typedef   signed CM_TYPE_INT16  schar16,  s_char16;
typedef unsigned CM_TYPE_INT16  uchar16,  u_char16;
typedef   signed CM_TYPE_INT16  sshort16, s_short16;
typedef unsigned CM_TYPE_INT16  ushort16, u_short16;
typedef   signed CM_TYPE_INT32  sshort32, s_short32;
typedef unsigned CM_TYPE_INT32  ushort32, u_short32;
typedef   signed CM_TYPE_INT32  slong32,  s_long32;
typedef unsigned CM_TYPE_INT32  ulong32,  u_long32;
typedef   signed CM_TYPE_INT64  slong64,  s_long64;
typedef unsigned CM_TYPE_INT64  ulong64,  u_long64;

/*===========================================================================*/
/* Floating Point Types w/ Specified Width                                   */
/*===========================================================================*/

typedef CM_TYPE_FLOAT32  float32, f32;
typedef CM_TYPE_FLOAT64  float64, f64;

#if defined(CM_HAVE_MODETF)
typedef float floatTF  __attribute__((mode(TF)));
#if (CM_SIZEOF_MODETF == 16)
typedef float float128 __attribute__((mode(TF)));
typedef float f128     __attribute__((mode(TF)));
#define CM_HAVE_FLOAT128 1
#endif
#endif /* CM_HAVE_MODETF */

#if defined(CM_HAVE_MODEXF)
typedef float floatXF  __attribute__((mode(XF)));
#if (CM_SIZEOF_MODEXF == 12)
typedef float float96  __attribute__((mode(XF)));
typedef float f96      __attribute__((mode(XF)));
#define CM_HAVE_FLOAT96 1
#endif
#endif /* CM_HAVE_MODEXF */

/*===========================================================================*/
/* 128bit Integer Types (Tetra-Integer Mode)                                 */
/*===========================================================================*/

#if defined(CM_HAVE_MODETI)
typedef /******/ int int128    __attribute__((mode(TI)));
typedef /******/ int long128   __attribute__((mode(TI)));
typedef   signed int sint128   __attribute__((mode(TI)));
typedef unsigned int uint128   __attribute__((mode(TI)));
typedef   signed int slong128  __attribute__((mode(TI)));
typedef unsigned int ulong128  __attribute__((mode(TI)));
typedef   signed int s_int128  __attribute__((mode(TI)));
typedef unsigned int u_int128  __attribute__((mode(TI)));
typedef   signed int s_long128 __attribute__((mode(TI)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef   signed int s128      __attribute__((mode(TI)));
typedef unsigned int u128      __attribute__((mode(TI)));
#define CM_HAVE_INT128 1
#endif /* CM_HAVE_MODETI */

/*===========================================================================*/
/* Fake Boolean Types                                                        */
/*===========================================================================*/

#ifndef bool8
#define bool8   CM_TYPE_INT8
#endif
#ifndef bool16
#define bool16  CM_TYPE_INT16
#endif
#ifndef bool32
#define bool32  CM_TYPE_INT32
#endif
#ifndef bool64
#define bool64  CM_TYPE_INT64
#endif

/* These macros were copied to "cmdefs.h" to avoid
 * creating a dependency on this header or vice versa.
 */
#ifndef TRUE       /* Duplicately defined in "cmdefs.h" */
#define TRUE  (1)  /* Any changes must be synchronized. */
#endif
#ifndef FALSE      /* Duplicately defined in "cmdefs.h" */
#define FALSE (0)  /* Any changes must be synchronized. */
#endif

/*===========================================================================*/
/* Generic Union Types                                                       */
/*===========================================================================*/

/*
 * 8-bit (1 Byte)
 */
typedef union cmUnion8 {
	struct {
		u_byte
			bit0:1, /*   1 (0x01) */
			bit1:1, /*   2 (0x02) */
			bit2:1, /*   4 (0x04) */
			bit3:1, /*   8 (0x08) */
			bit4:1, /*  16 (0x10) */
			bit5:1, /*  32 (0x20) */
			bit6:1, /*  64 (0x40) */
			bit7:1; /* 128 (0x80) */
	} f; /* bitField */
	s_int8 s8;
	u_int8 u8;
} cmUnion8;

/*
 * 16-bit (2 Bytes)
 */
typedef union cmUnion16 {
	s_int16     s16;
	u_int16     u16;
	s_int8      s8[2];
	u_int8      u8[2];
	cmUnion8    r8[2];
} cmUnion16;

/*
 * 32-bit (4 Bytes)
 */
typedef union cmUnion32 {
	s_int32     s32;
	u_int32     u32;
	float32     f32;
	s_int16     s16[2];
	u_int16     u16[2];
	cmUnion16   r16[2];
	s_int8      s8[4];
	u_int8      u8[4];
	cmUnion8    r8[4];
} cmUnion32;

/*
 * 64-bit (8 Bytes)
 */
typedef union cmUnion64 {
	s_int64     s64;
	u_int64     u64;
	float64     f64;
	s_int32     s32[2];
	u_int32     u32[2];
	float32     f32[2];
	cmUnion32   r32[2];
	s_int16     s16[4];
	u_int16     u16[4];
	cmUnion16   r16[4];
	s_int8      s8[8];
	u_int8      u8[8];
	cmUnion8    r8[8];
} cmUnion64;

/*
 * 128-bit (16 Bytes)
 */
typedef union cmUnion128 {
#ifdef CM_HAVE_INT128
	s_int128    s128;
	u_int128    u128;
#endif
#ifdef CM_HAVE_FLOAT128
	float128    f128;
#endif
	s_int64     s64[2];
	u_int64     u64[2];
	float64     f64[2];
	cmUnion64   r64[2];
	s_int32     s32[4];
	u_int32     u32[4];
	float32     f32[4];
	cmUnion32   r32[4];
	s_int16     s16[8];
	u_int16     u16[8];
	cmUnion16   r16[8];
	s_int8      s8[16];
	u_int8      u8[16];
	cmUnion8    r8[16];
} cmUnion128;

#endif /* END OF FILE */
