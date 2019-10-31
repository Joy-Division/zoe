/*
 * [ LibFS ]
 * FS Cache System
 */
#include "global.h"
#include "libfs.h"

/*---------------------------------------------------------------------------*/
/* Version   | Status     | Oflag | I./R. | etc.                             */
/*-----------+------------+-------+-------+----------------------------------*/
/* SLPS99999 | MATCH      | O2,O3 | OK/OK |                                  */
/* SLPM65019 | MATCH      | O2,O3 | OK/OK |                                  */
/*---------------------------------------------------------------------------*/
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
