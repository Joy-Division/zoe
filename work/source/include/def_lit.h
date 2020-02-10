/*
 * Light Format Definitions
 */
#ifndef INC_DEF_LIT_H
#define INC_DEF_LIT_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libdg.h"

// ref.default.pdb
class DEF_LIGHT
{
public: //! unconfirmed modifier
	int nLight;
	uint32 pad0;
	uint32 pad1;
	uint32 pad2;
	DG_LIGHT lit[];

public:
	DEF_LIGHT(){/* TODO */}
	~DEF_LIGHT(){/* TODO */}

	DEF_LIGHT& operator=( const DEF_LIGHT& ref )
	{/* TODO */}
};

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
