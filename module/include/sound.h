#ifndef REDIRECT_SOUND_H
#define REDIRECT_SOUND_H

#if defined(__R5900__)
#  include "../sound/sd_ee.h"
#elif defined(__R3000__)
#  include "../sound/sd_ext.h"
#  include "../sound/sd_incl.h"
#endif

#endif /* END OF FILE */
