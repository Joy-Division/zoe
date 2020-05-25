#ifndef INCLUDED_ZOE_FLAG_H
#define INCLUDED_ZOE_FLAG_H

/*---------------------------------------------------------------------------*/
/* Video Output Mode (NTSC/PAL)                                              */
/*---------------------------------------------------------------------------*/

#if !defined( BUILD_NEW )

#undef VMODE_NTSC	// override if set
#undef VMODE_PAL	// override if set

#if ( ZOE_DEMO_PAL  )\
||  ( ZOE_FINAL_PAL )
#define VMODE_PAL	TRUE
#else
#define VMODE_NTSC	TRUE
#endif

#else /* !BUILD_NEW */

#if defined( VMODE_NTSC )\
&&  defined( VMODE_PAL  )
#error "VMODE conflict!! Both NTSC & PAL have been set."
#endif

#if !defined( VMODE_NTSC )\
&&  !defined( VMODE_PAL  )
#define VMODE_NTSC	TRUE	// default to NTSC
#endif

#endif /* !BUILD_NEW */

/*---------------------------------------------------------------------------*/
/* DEBUG Mode Flag                                                           */
/*---------------------------------------------------------------------------*/

//
// PLACEHOLDER
//

#endif /* END OF FILE */
