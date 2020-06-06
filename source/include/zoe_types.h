#ifndef INCLUDED_ZOE_TYPES_H
#define INCLUDED_ZOE_TYPES_H

/*===========================================================================*/
/* Target-Dependent Defines                                                  */
/*===========================================================================*/

#if !defined(__R5900__)
#define long long long	// force sizeof(long)==8
#endif

/*===========================================================================*/
/* Integer Types w/ Unspecified Width                                        */
/*===========================================================================*/

#if defined(__R5900__)
#include <sys/types.h>
#include <eetypes.h>
#else
/*---------------------------------------------------------------------------*/
// #include <sys/types.h>

typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

//	typedef unsigned short	ushort;
//	typedef unsigned int	uint;
//	typedef unsigned long	ulong;

/*---------------------------------------------------------------------------*/
// #include <eetypes.h>

#if defined(__GNUC__)
typedef int long128 __attribute__((mode(TI)));
typedef unsigned int u_long128 __attribute__((mode(TI)));
#endif

#ifndef FALSE
#define FALSE	(0)
#endif
#ifndef TRUE
#define TRUE	(!FALSE)
#endif
#ifndef NULL
#define NULL	(0)
#endif

#endif // __R5900__

/*===========================================================================*/
/* Integer Types w/ Specified Width                                          */
/*===========================================================================*/

#define byte char
typedef unsigned byte u_byte;

#define int8		char
#define int16		short
#define int32		int
#define int64		long

typedef unsigned int8		u_int8;
typedef unsigned int16		u_int16;
typedef unsigned int32		u_int32;
typedef unsigned int64		u_int64;

#if defined(__GNUC__)
typedef long128 int128;
typedef u_long128 u_int128;
#endif

#define char8		char
#define char16		short
#define short16		short
#define short32		int
#define long32		int
#define long64		long

typedef unsigned char8		u_char8;
typedef unsigned char16		u_char16;
typedef unsigned short16	u_short16;
typedef unsigned short32	u_short32;
typedef unsigned long32		u_long32;
typedef unsigned long64		u_long64;

/*===========================================================================*/
/* Floating Point Types w/ Specified Width                                   */
/*===========================================================================*/

typedef float float32;
typedef double float64;

/*===========================================================================*/
/* Fake Boolean Types                                                        */
/*===========================================================================*/

#define bool8	char
#define bool16	short
#define bool32	int
#define bool64	long

//=============================================================================
// KCEJ Z.O.E-Style Basetypes
//=============================================================================

#define INT8	int8
#define INT16	int16
#define INT32	int32
#define INT64	int64

typedef unsigned int8	UINT8;
typedef unsigned int16	UINT16;
typedef unsigned int32	UINT32;
typedef unsigned int64	UINT64;

typedef   signed int8	sint8;
typedef unsigned int8	uint8;
typedef   signed int16	sint16;
typedef unsigned int16	uint16;
typedef   signed int32	sint32;
typedef unsigned int32	uint32;
typedef   signed int64	sint64;
typedef unsigned int64	uint64;

#if defined(__GNUC__)
typedef int INT128 __attribute__((mode(TI)));
typedef unsigned int UINT128 __attribute__((mode(TI)));
typedef unsigned int uint128 __attribute__((mode(TI)));
#endif

typedef float32 FLOAT32;
typedef float64 FLOAT64;

#define BOOL8	bool8
#define BOOL16	bool16
#define BOOL32	bool32
#define BOOL64	bool64

//=============================================================================
// Unions for Type Punning
//=============================================================================

typedef union DAT16 {
	uint16	u16;
	uint8	u8[2];
} DAT16;

typedef union DAT32 {
	uint32	u32;
	uint16	u16[2];
	uint8	u8[4];
	float	f;
} DAT32;

// ref.default.pdb
typedef union DAT64 {
	uint64	u64;
	uint32	u32[2];
	uint16	u16[4];
	uint8	u8[8];
	float	f[2];
} DAT64;

// ref.default.pdb
typedef union DAT128 {
	uint128	u128;
	uint64	u64[2];
	uint32	u32[4];
	uint16	u16[8];
	uint8	u8[16];
	float	f[4];
} DAT128;

//=============================================================================
// 3D Math Data Types
//=============================================================================

// ref.default.pdb
typedef struct FVECTOR {
	float vx, vy, vz, vw;
} FVECTOR;

// ref.default.pdb
typedef struct FMATRIX {
	float m[4][4];
} FMATRIX;

#endif /* END OF FILE */
