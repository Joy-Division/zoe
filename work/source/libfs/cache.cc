/*
 * [ LibFS ]
 * FS Cache System
 */
#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libfs.h"

/*---------------------------------------------------------------------------*/
/* SLPS99999, status: MATCH, opt: -O2,-O3 */
/* SLPM65019, status: MATCH, opt: -O2,-O3 */

uint32 FS_StrCode( char *str )
{
	uint32 c;
	sint32 n  = 0;
	uint32 id = 0;
	
	while(( c = *str++ ))
	{
		id += ((id << (c & 0x0F)) | ((id >> 3) + (c << (n & 0x0F)) + c));
		n++;
	}
	return id;
}

/*---------------------------------------------------------------------------*
 * END OF FILE
 *---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
