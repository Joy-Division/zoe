#ifndef INCLUDED_SD_DEBUG_H
#define INCLUDED_SD_DEBUG_H

#include <stdio.h>

#ifdef BORMAN_DEMO
#define PRINTF(x) printf x
#else
#define PRINTF(x)
#endif

#endif /* END OF FILE */
