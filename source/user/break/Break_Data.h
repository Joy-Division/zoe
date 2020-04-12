#ifndef INCLUDED_BREAK_DATA_H
#define INCLUDED_BREAK_DATA_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libalg.h"

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class BRK_DAT
{
public: //! check modifier
	ALG_VECTOR *pPos;
	ALG_VECTOR SP;
	uint8 F;

public:
	sint32  Check_Low(float);
	void    SP_Add(float, ALG_VECTOR *);
	void    SP_Add(float);
	void    Axis_Fall(ALG_MATRIX *);
	void    Dump();
	
	BRK_DAT();
	
	BRK_DAT& operator=(const BRK_DAT&);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class BRK_FRM
{
public: //! check modifier
	ALG_MATRIX matO;
	ALG_MATRIX matR;
	ALG_VECTOR vecP;
	ALG_VECTOR SP;
	float   G;
	uint16  FON;
	uint8   N;
	uint8   u8EF;
	bool32  bL;

public:
	ALG_MATRIX SP_ADD();
	
	BRK_FRM();
	
	BRK_FRM& operator=(const BRK_FRM&);
};

#endif /* END OF FILE */
