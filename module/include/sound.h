#ifndef REDIRECT_SOUND_H
#define REDIRECT_SOUND_H

#if defined(__R5900__)
#  include "../filesys/sd_ee.h"
#else /* IOP */
#  include "../filesys/sd_ext.h"
#  include "../filesys/sd_incl.h"
#endif

#endif /* END OF FILE */
