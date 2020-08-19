#ifndef INCLUDED_ZOE_TYPES_H
#define INCLUDED_ZOE_TYPES_H

//=============================================================================
// Fixed-Width Primitive Aliases
//=============================================================================

#define zoeInt8					char
#define zoeInt16				short
#define zoeInt32				int
#define zoeInt64				long

#define zoeFloat32				float
#define zoeFloat64				double

#if !defined(__R5900__)
#  undef  zoeInt64
#  define zoeInt64				long long
#  define long					long long
#endif

//=============================================================================
// TypeDefs from "PlayStation 2" ToolChain & Runtime Library
//=============================================================================

#if defined(__R5900__)
#  include <sys/types.h>
#  include <eetypes.h>
#else
typedef unsigned zoeInt8		u_char;
typedef unsigned zoeInt16		u_short;
typedef unsigned zoeInt32		u_int;
typedef unsigned zoeInt64		u_long;

typedef unsigned zoeInt16		ushort;
typedef unsigned zoeInt32		uint;

#if defined(__GNUC__)
typedef   signed int			long128 __attribute__((mode(TI)));
typedef unsigned int			u_long128 __attribute__((mode(TI)));
#endif

#ifndef FALSE
#define FALSE					(0)
#endif
#ifndef TRUE
#define TRUE					(!FALSE)
#endif
#ifndef NULL
#define NULL					(0)
#endif

#endif // __R5900__

//=============================================================================
// BaseTypes w/ Specified Width
//=============================================================================

typedef signed zoeInt8			int8;
typedef signed zoeInt16			int16;
typedef signed zoeInt32			int32;
typedef signed zoeInt64			int64;

typedef unsigned zoeInt8		u_int8;
typedef unsigned zoeInt16		u_int16;
typedef unsigned zoeInt32		u_int32;
typedef unsigned zoeInt64		u_int64;

#if defined(__GNUC__)
typedef   signed int			int128 __attribute__((mode(TI)));
typedef unsigned int			u_int128 __attribute__((mode(TI)));
#endif

typedef zoeFloat32				float32;
typedef zoeFloat64				float64;

/*---------------------------------------------------------------------------*/

typedef   signed zoeInt8		byte;
typedef unsigned zoeInt8		u_byte;

typedef signed zoeInt8			char8;
typedef signed zoeInt16			char16;
typedef signed zoeInt16			short16;
typedef signed zoeInt32			short32;
typedef signed zoeInt32			long32;
typedef signed zoeInt64			long64;

typedef unsigned zoeInt8		u_char8;
typedef unsigned zoeInt16		u_char16;
typedef unsigned zoeInt16		u_short16;
typedef unsigned zoeInt32		u_short32;
typedef unsigned zoeInt32		u_long32;
typedef unsigned zoeInt64		u_long64;

//=============================================================================
// Fake Boolean Types
//=============================================================================

typedef zoeInt8					bool8;
typedef zoeInt16				bool16;
typedef zoeInt32				bool32;
typedef zoeInt64				bool64;

//=============================================================================
// Type Range Constants
//=============================================================================

#define ZOE_INT8_MIN			(0x80)
#define ZOE_INT8_MAX			(0x7F)
#define ZOE_UINT8_MIN			(0x00)
#define ZOE_UINT8_MAX			(0xFF)

#define ZOE_INT16_MIN			(0x8000)
#define ZOE_INT16_MAX			(0x7FFF)
#define ZOE_UINT16_MIN			(0x0000)
#define ZOE_UINT16_MAX			(0xFFFF)

#define ZOE_INT32_MIN			(0x80000000)
#define ZOE_INT32_MAX			(0x7FFFFFFF)
#define ZOE_UINT32_MIN			(0x00000000)
#define ZOE_UINT32_MAX			(0xFFFFFFFF)

#define ZOE_INT64_MIN			(0x8000000000000000)
#define ZOE_INT64_MAX			(0x7FFFFFFFFFFFFFFF)
#define ZOE_UINT64_MIN			(0x0000000000000000)
#define ZOE_UINT64_MAX			(0xFFFFFFFFFFFFFFFF)

//=============================================================================
// Additional BaseType Defines
//=============================================================================

typedef   signed zoeInt8		INT8;
typedef   signed zoeInt8		SINT8;
typedef unsigned zoeInt8		UINT8;

typedef   signed zoeInt16		INT16;
typedef   signed zoeInt16		SINT16;
typedef unsigned zoeInt16		UINT16;

typedef   signed zoeInt32		INT32;
typedef   signed zoeInt32		SINT32;
typedef unsigned zoeInt32		UINT32;

typedef   signed zoeInt64		INT64;
typedef   signed zoeInt64		SINT64;
typedef unsigned zoeInt64		UINT64;

#if defined(__GNUC__)
typedef   signed int			INT128 __attribute__((mode(TI)));
typedef   signed int			SINT128 __attribute__((mode(TI)));
typedef unsigned int			UINT128 __attribute__((mode(TI)));
#endif

typedef zoeFloat32				FLOAT32;
typedef zoeFloat64				FLOAT64;

typedef zoeInt8					BOOL8;
typedef zoeInt16				BOOL16;
typedef zoeInt32				BOOL32;
typedef zoeInt64				BOOL64;

//=============================================================================
// Unions for Type Punning
//=============================================================================

typedef union DAT16 {
	UINT16	u16;
	UINT8	u8[2];
} DAT16;

typedef union DAT32 {
	UINT32	u32;
	UINT16	u16[2];
	UINT8	u8[4];
	float	f;
} DAT32;

// ref.default.pdb
typedef union DAT64 {
	UINT64	u64;
	UINT32	u32[2];
	UINT16	u16[4];
	UINT8	u8[8];
	float	f[2];
} DAT64;

// ref.default.pdb
typedef union DAT128 {
	UINT128	u128;
	UINT64	u64[2];
	UINT32	u32[4];
	UINT16	u16[8];
	UINT8	u8[16];
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
