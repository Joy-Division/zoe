/*
 * "ZONE OF THE ENDERS"
 * Light Format Definitions
 */
#ifndef INCLUDED_DEF_LIT_H
#define INCLUDED_DEF_LIT_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libdg.h"

// ref.default.pdb
class DEF_LIGHT
{
public: //! check modifier
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

#endif /* END OF FILE */
