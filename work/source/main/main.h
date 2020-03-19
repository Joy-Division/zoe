/*
 * "ZONE OF THE ENDERS"
 * Startup / Main Module
 */
#ifndef INCLUDED_MAIN_H
#define INCLUDED_MAIN_H

//
// The following COP0 Cache definitions were removed from eekernel.h in
// version 2.3.0 (Jan.22,2003), however the functions are still present
// within the libkernl.a static library.
//
#if defined(_eekernel_h_)
#if !defined( INST_CACHE )\
||  !defined( DATA_CACHE )\
||  !defined( CacheOn    )\
||  !defined( CacheOff   )

#define INST_CACHE  2
#define DATA_CACHE  1
#define CacheOn()   EnableCache(INST_CACHE | DATA_CACHE)
#define CacheOff()  DisableCache(INST_CACHE | DATA_CACHE)

extern "C" int EnableCache(int);
extern "C" int DisableCache(int);

#endif // (CACHE DEFS)
#endif // _eekernel_h_

#endif /* END OF FILE */
