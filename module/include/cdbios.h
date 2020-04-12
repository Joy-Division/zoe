#ifndef REDIRECT_CDBIOS_H
#define REDIRECT_CDBIOS_H

#if defined(__R5900__)
#  include "../filesys/cdbios_ee.h"
#else /* IOP */
#  include "../filesys/cdbios.h"
#endif

#endif /* END OF FILE */
