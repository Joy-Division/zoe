#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libfs.h"

/*---------------------------------------------------------------------------*/
// SLPS99999, status: MATCH, opt: -O2,-O3
// SLPM65019, status: MATCH, opt: -O2,-O3

UINT32 FS_StrCode( char *str )
{
	UINT32 c;
	SINT32 n = 0;
	UINT32 id = 0;

	while(( c = *str++ ))
	{
		id += ((id << (c & 0x0F)) | ((id >> 3) + (c << (n & 0x0F)) + c));
		n++;
	}
	return id;
}
