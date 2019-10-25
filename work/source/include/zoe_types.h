/*
 * ZONE OF THE ENDERS
 * Common Type Includes
 */
#ifndef INC_ZOE_TYPES_H
#define INC_ZOE_TYPES_H

#include "global.h"

/*---------------------------------------------------------------------------*
 * BASETYPES
 *---------------------------------------------------------------------------*/
#ifndef INT8
#define INT8  int8
#endif
#ifndef INT16
#define INT16 int16
#endif
#ifndef INT32
#define INT32 int32
#endif
#ifndef INT64
#define INT64 int64
#endif

typedef   signed int8  SINT8;
typedef unsigned int8  UINT8;
typedef   signed int16 SINT16;
typedef unsigned int16 UINT16;
typedef   signed int32 SINT32;
typedef unsigned int32 UINT32;
typedef   signed int64 SINT64;
typedef unsigned int64 UINT64;

typedef float32 FLOAT32;
typedef float64 FLOAT64;

#if defined( __GNUC__ )
#if defined( __R5900__ )
typedef          int  INT128 __attribute__((mode(TI)));
typedef   signed int SINT128 __attribute__((mode(TI)));
typedef unsigned int UINT128 __attribute__((mode(TI)));
#endif // __R5900__
#endif // __GNUC__

#ifndef BOOL8
#define BOOL8  bool8
#endif
#ifndef BOOL16
#define BOOL16 bool16
#endif
#ifndef BOOL32
#define BOOL32 bool32
#endif
#ifndef BOOL64
#define BOOL64 bool64
#endif

/*---------------------------------------------------------------------------*
 * ZOE Common Types
 *---------------------------------------------------------------------------*/
typedef union DAT16 {
	uint16  u16;
	uint8   u8[2];
} DAT16;

typedef union DAT32 {
	uint32  u32;
	uint16  u16[2];
	uint8   u8[4];
	float32 f;
} DAT32;

// ref.default.pdb
typedef union DAT64 {
	uint64  u64;
	uint32  u32[2];
	uint16  u16[4];
	uint8   u8[8];
	float32 f[2];
} DAT64;

// ref.default.pdb
typedef union DAT128 {
	uint128 u128;
	uint64  u64[2];
	uint32  u32[4];
	uint16  u16[8];
	uint8   u8[16];
	float32 f[4];
} DAT128;

// ref.default.pdb
typedef struct FMATRIX {
	float32 m[4][4];
} FMATRIX;

// ref.default.pdb
typedef struct FVECTOR {
	float32 vx, vy, vz, vw;
} FVECTOR;

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
