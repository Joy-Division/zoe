#ifndef REDIRECT_CDBIOS_H
#define REDIRECT_CDBIOS_H

#if defined(__R5900__)
#  include "../filesys/cdbios_ee.h"
#elif defined(__R3000__)
#  include "../filesys/cdbios.h"
#endif

#endif /* END OF FILE */
