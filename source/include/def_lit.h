#ifndef INCLUDED_DEF_LIT_H
#define INCLUDED_DEF_LIT_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libdg.h"

class DEF_LIGHT
{
public: //! check modifier
	INT32		nLight;
	UINT32		pad0;
	UINT32		pad1;
	UINT32		pad2;
	DG_LIGHT	lit[];

public:
	DEF_LIGHT(){/* TODO */}
	~DEF_LIGHT(){/* TODO */}

	DEF_LIGHT& operator = ( const DEF_LIGHT& ref )
	{/* TODO */}
};

#endif /* END OF FILE */
