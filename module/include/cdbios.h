#ifndef REDIRECT_CDBIOS_H
#define REDIRECT_CDBIOS_H

#if defined(__R5900__)
#  include "../cdbios/cdbios_ee.h"
#elif defined(__R3000__)
#  include "../cdbios/cdbios.h"
#endif

#endif /* END OF FILE */
