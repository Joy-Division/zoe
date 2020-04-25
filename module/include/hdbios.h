#ifndef REDIRECT_HDBIOS_H
#define REDIRECT_HDBIOS_H

#if defined(__R5900__)
#  include "../filesys/hdbios_ee.h"
#else /* IOP */
#  include "../filesys/hdbios.h"
#endif

#endif /* END OF FILE */
