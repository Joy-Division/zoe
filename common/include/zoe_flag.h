#ifndef INCLUDED_ZOE_FLAG_H
#define INCLUDED_ZOE_FLAG_H

//=============================================================================
// Video Output Mode (NTSC/PAL)
//=============================================================================

#define NTSC    (60)
#define PAL     (50)

#ifndef VMODE

#if defined( SCEE_DEMODISC )\
||  defined( PAL_RELEASE )
#define VMODE	PAL
#else
#define VMODE	NTSC
#endif

#endif /* !VMODE */

//=============================================================================
// DEBUG Mode Flag
//=============================================================================

//
// PLACEHOLDER
//

#endif /* END OF FILE */
