#ifndef INCLUDED_ZOE_DEFS_H
#define INCLUDED_ZOE_DEFS_H

//=============================================================================
// Data Alignment Macros
//=============================================================================

#if defined(__GNUC__)
#define ALIGN(x)	__attribute__((aligned(x)))
#define ALIGN8		__attribute__((aligned(1)))
#define ALIGN16		__attribute__((aligned(2)))
#define ALIGN32		__attribute__((aligned(4)))
#define ALIGN64		__attribute__((aligned(8)))
#define ALIGN128	__attribute__((aligned(16)))
#define ALIGN256	__attribute__((aligned(32)))
#define ALIGN512	__attribute__((aligned(64)))
#else
#define ALIGN(x)	//__attribute__((aligned(x)))
#define ALIGN8		//__attribute__((aligned(1)))
#define ALIGN16		//__attribute__((aligned(2)))
#define ALIGN32		//__attribute__((aligned(4)))
#define ALIGN64		//__attribute__((aligned(8)))
#define ALIGN128	//__attribute__((aligned(16)))
#define ALIGN256	//__attribute__((aligned(32)))
#define ALIGN512	//__attribute__((aligned(64)))
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

#if (ZOE_FINAL_JAPAN)
// dummy_printf() is possibly defined in include/orgtype.h
// according to .mdebug
void dummy_printf( const char *fmt, ... );

// dummy printf for non-debug builds
//#define printf(fmt, ...)	dummy_printf(fmt, ##__VA_ARGS__)
#define printf				dummy_printf

#endif // ZOE_FINAL_JAPAN

#endif /* END OF FILE */
