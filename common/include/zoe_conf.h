#ifndef INCLUDED_ZOE_CONF_H
#define INCLUDED_ZOE_CONF_H

/*===========================================================================*/
/* Build Target Definition Check                                             */
/*===========================================================================*/

// One and ONLY ONE build flag must be passed to the preprocessor.
// This check expects that the supplied flag resolves to 1, precisely.
// Invoking the compiler with '-D$(VERSION)' should accomplish this.
// DO NOT MANUALLY DEFINE IT TO ANY OTHER VALUE.

#define CONF_FLAG_SUM \
/*---------------------------------------------------------------------------*/\
/* ZONE OF THE ENDERS (for PlayStation 2)                                    */\
/*---------------------------------------------------------------------------*/\
	( BORMAN_DEMO								/* Oct.09,2000 [SLPS-99999]  */\
	+ DENGEKIPS_DEMO							/* Nov.11,2000 [SLPM-61002]  */\
	+ PREPRE2_DEMO								/* Jan.17,2001 [PCPX-96611]  */\
	+ SCEA_DEMODISC								/* Jan.23,2001 [SCUS-XXXXX]  */\
	+ SCEE_DEMODISC								/* Feb.14,2001 [SCED-XXXXX]  */\
/*---------------------------------------------------------------------------*/\
	+ JAPAN_RELEASE								/* Jan.13,2001 [SLPM65018/9] */\
	+ PAL_RELEASE								/* Jan.17,2001 [SLES-50111]  */\
	+ USA_RELEASE								/* Jan.30,2001 [SLUS-20148]  */\
/*---------------------------------------------------------------------------*/\
/* for NON-MATCHING / NEW BUILDS                                             */\
/*---------------------------------------------------------------------------*/\
	+ NEW_BUILD )

/*---------------------------------------------------------------------------*/
// Basic error detection for build flag conflicts.
// There is no recovery from this state; the user MUST fix it.

#if (CONF_FLAG_SUM > 1)
#error "ERROR: Config conflict!! 2 or more flags defined."
#endif

/*---------------------------------------------------------------------------*/
// 'NEW_BUILD' is the default setting for any non-matching build of the
// codebase, and is provided with the intent to facilitate the development
// of modifications and ports to new systems.
//
// Any flags automatically set for matching configurations may need to be
// manually set by the user depending on the desired configuration.

#if (CONF_FLAG_SUM == 0)
#undef  NEW_BUILD // override if set
#define NEW_BUILD 1
#endif

// No further use.
#undef CONF_FLAG_SUM

/*---------------------------------------------------------------------------*/
// 'USE_NOMATCH' is reserved for enabling the use of non-matching C/C++ code
// over "naked" assembly functions required for the target binary to match.

#if !(NEW_BUILD)
#  ifdef USE_NOMATCH
#  undef USE_NOMATCH
#  endif
#else
#  ifndef USE_NOMATCH
#  define USE_NOMATCH 1
#  endif
#endif

/*===========================================================================*/
/* Shared Flag Definitions                                                   */
/*===========================================================================*/

// NOTE: Use of the $(VERSION) flags across the codebase should be kept to a
// minimum. Ideally, they should instead toggle additional flags that can be
// independently set for non-matching or 'NEW' builds.

//
// PLACEHOLDER
//

#endif /* END OF FILE */
