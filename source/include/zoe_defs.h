#ifndef INCLUDED_ZOE_DEFS_H
#define INCLUDED_ZOE_DEFS_H

//=============================================================================
// Data Alignment Macros
//=============================================================================

#if defined(__GNUC__)

// Align to Boundary (in Bytes)
#define ALIGN(x)	__attribute__((aligned(x)))
#define ALIGN8		__attribute__((aligned(8)))
#define ALIGN16		__attribute__((aligned(16)))
#define ALIGN32		__attribute__((aligned(32)))
#define ALIGN64		__attribute__((aligned(64)))
#define ALIGN128	__attribute__((aligned(128)))
#define ALIGN256	__attribute__((aligned(256)))
#define ALIGN512	__attribute__((aligned(512)))

// Align to Boundary (in Bits)
//	#define ALIGN8		__attribute__((aligned(1)))
//	#define ALIGN16		__attribute__((aligned(2)))
//	#define ALIGN32		__attribute__((aligned(4)))
//	#define ALIGN64		__attribute__((aligned(8)))
//	#define ALIGN128	__attribute__((aligned(16)))
//	#define ALIGN256	__attribute__((aligned(32)))
//	#define ALIGN512	__attribute__((aligned(64)))

#else
#define ALIGN(x)	// NO USE if !defined(__GNUC__)
#define ALIGN8		// NO USE if !defined(__GNUC__)
#define ALIGN16		// NO USE if !defined(__GNUC__)
#define ALIGN32		// NO USE if !defined(__GNUC__)
#define ALIGN64		// NO USE if !defined(__GNUC__)
#define ALIGN128	// NO USE if !defined(__GNUC__)
#define ALIGN256	// NO USE if !defined(__GNUC__)
#define ALIGN512	// NO USE if !defined(__GNUC__)
#endif

//=============================================================================
// Hack for Unknown Constants
//=============================================================================

// TODO:
// * Replace anything initialized to these macros with the real values.
// * Delete these definitions once all instances have been replaced.
#define TEMP_ZERO	(0)
#define DEFINE_ME	(0)

//=============================================================================
// Configuration Definitions
//=============================================================================

#if defined(JAPAN_RELEASE)

// dummy_printf() is possibly defined in include/orgtype.h
// according to .mdebug
void dummy_printf( const char *fmt, ... );

// Redirect printf() for non-DEBUG builds
//#	define printf(fmt, ...)		dummy_printf(fmt, ##__VA_ARGS__)
//#	define printf(fmt, ...)		dummy_printf(fmt __VA_OPT__(,) __VA_ARGS__)
#	define printf				dummy_printf

#endif // JAPAN_RELEASE

#endif /* END OF FILE */
