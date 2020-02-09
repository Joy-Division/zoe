#ifndef INC_ZOE_CONF_H
#define INC_ZOE_CONF_H

/*---------------------------------------------------------------------------*
 * Definition Check
 *---------------------------------------------------------------------------*/
#if (( BUILD_SLPM65019 \
     + BUILD_SLES50111 \
     + BUILD_SLUS20148 \
     + BUILD_SLPS99999 \
     + BUILD_SLPM61002 \
     + BUILD_PCPX96611 \
     + BUILD_USA_DEMO \
     + BUILD_PAL_DEMO \
     + BUILD_NEW ) != 1 )
#error "ERROR: 0 or >1 config flags defined."
#endif

/*---------------------------------------------------------------------------*
 * Alias Definition
 *---------------------------------------------------------------------------*/
#define ZOE_JPN             BUILD_SLPM65019 // Jan.13,2001
#define ZOE_PAL             BUILD_SLES50111 // Jan.17,2001
#define ZOE_USA             BUILD_SLUS20148 // Jan.30,2001

#define ZOE_DEMO_OCT2000    BUILD_SLPS99999 // Oct.09,2000
#define ZOE_DEMO_DENGEKI    BUILD_SLPM61002 // Nov.11,2000 :: 電撃PlayStation D40
#define ZOE_DEMO_PURE2      BUILD_PCPX96611 // Jan.17,2001 :: プレプレ2 Vol.1 2001.04
#define ZOE_DEMO_USA        BUILD_USA_DEMO  // Jan.23,2001 :: PlayStation Underground
#define ZOE_DEMO_PAL        BUILD_PAL_DEMO  // Feb.14,2001 :: Official PS2 Magazine

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=utf-8 : */
