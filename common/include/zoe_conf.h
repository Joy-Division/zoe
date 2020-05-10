#ifndef INCLUDED_ZOE_CONF_H
#define INCLUDED_ZOE_CONF_H

/*===========================================================================*/
/* Build Type Definition Check                                               */
/*===========================================================================*/

// One and ONLY ONE build flag must be passed to the preprocessor.
// This check expects that the supplied flag resolves to 1, precisely.
// Invoking the compiler with '-DBUILD_$(VERSION)' should accomplish this.
// DO NOT MANUALLY DEFINE IT TO ANY OTHER VALUE.

// SLPM65018 == SLPM65019
#ifdef BUILD_SLPM65018
#undef BUILD_SLPM65018
#define BUILD_SLPM65019 1
#endif

#define CONF_FLAG_SUM \
/*------------------------------------------------------*/\
/* -- BUILD_$(VERSION) --       -- PROJECT STATUS --    */\
/*------------------------------------------------------*/\
    ( BUILD_SLPS99999           /* NOT YET SUPPORTED    */\
    + BUILD_SLPM61002           /* NOT YET SUPPORTED    */\
    + BUILD_PCPX96611           /* NOT YET SUPPORTED    */\
    + BUILD_USA_DEMO            /* NOT YET SUPPORTED    */\
    + BUILD_PAL_DEMO            /* NOT YET SUPPORTED    */\
/*------------------------------------------------------*/\
    + BUILD_SLPM65018           /* (SEE SLPM-65019)     */\
    + BUILD_SLPM65019           /* IN PROGRESS          */\
    + BUILD_SLES50111           /* NOT YET SUPPORTED    */\
    + BUILD_SLUS20148           /* NOT YET SUPPORTED    */\
/*------------------------------------------------------*/\
    + BUILD_NEW )

/*---------------------------------------------------------------------------*/
// Basic error detection for build flag conflicts.
// There is no recovery from this state; the user MUST fix it.

#if (CONF_FLAG_SUM >= 2)
#error "ERROR: Config conflict!! 2 or more flags defined."
#endif

/*---------------------------------------------------------------------------*/
// 'BUILD_NEW' is the default setting for any non-matching build of the
// codebase, and is provided with the intent to facilitate the development
// of modifications and ports to new systems.
//
// Any flags automatically set for matching configurations may need to be
// manually set by the user depending on the desired configuration.

#if (CONF_FLAG_SUM == 0)
#undef  BUILD_NEW
#define BUILD_NEW 1
#endif

// No further use.
#undef CONF_FLAG_SUM

/*===========================================================================*/
/* Build Type Alias Definitions                                              */
/*===========================================================================*/

// These provide descriptive names to use in place of 'BUILD_$(VERSION)'.
// They will resolve to 1 (TRUE) if the corresponding flag is set.
//
// NOTE: In the current implementation, they are unconditionally #defined.
// Preprocessor conditionals MUST avoid using the #ifdef/#ifndef directives.
//
// NOTE: Direct use of the BUILD_$(VERSION) flags and their respective aliases
// across the codebase should be reduced as much as possible. Ideally, they
// should instead toggle additional flags that can be independently set for
// non-matching 'NEW' builds.

/*---------------------------------------------------------------------------*/
/* ZONE OF THE ENDERS (for PlayStation 2)                                    */
/*---------------------------------------------------------------------------*/

#define ZOE_DEMO_BORMAN		BUILD_SLPS99999		// Oct.09,2000
#define ZOE_DEMO_DENGEKI	BUILD_SLPM61002		// Nov.11,2000, 電撃PlayStation D40
#define ZOE_DEMO_PURE2		BUILD_PCPX96611		// Jan.17,2001, プレプレ2 Vol.1 2001.04
#define ZOE_DEMO_USA		BUILD_USA_DEMO		// Jan.23,2001, PlayStation Underground
#define ZOE_DEMO_PAL		BUILD_PAL_DEMO		// Feb.14,2001, Official PS2 Magazine

#define ZOE_JAPAN			BUILD_SLPM65019		// Jan.13,2001
#define ZOE_PAL				BUILD_SLES50111		// Jan.17,2001
#define ZOE_USA				BUILD_SLUS20148		// Jan.30,2001

/*===========================================================================*/
/* Additional Checks & Defines                                               */
/*===========================================================================*/

//
// PLACEHOLDER
//

#endif /* END OF FILE */
