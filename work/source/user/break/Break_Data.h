#ifndef INC_BREAK_DATA_H
#define INC_BREAK_DATA_H

#include "global.h"
#include "libalg.h"

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class BRK_DAT
{
public: //! unconfirmed modifier
	ALG_VECTOR *pPos;
	ALG_VECTOR SP;
	uint8 F;

public:
	sint32  Check_Low(float32);
	void    SP_Add(float32, ALG_VECTOR *);
	void    SP_Add(float32);
	void    Axis_Fall(ALG_MATRIX *);
	void    Dump();
	
	BRK_DAT();
	
	BRK_DAT& operator=(const BRK_DAT&);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class BRK_FRM
{
public: //! unconfirmed modifier
	ALG_MATRIX matO;
	ALG_MATRIX matR;
	ALG_VECTOR vecP;
	ALG_VECTOR SP;
	float32 G;
	uint16  FON;
	uint8   N;
	uint8   u8EF;
	bool32  bL;

public:
	ALG_MATRIX SP_ADD();
	
	BRK_FRM();
	
	BRK_FRM& operator=(const BRK_FRM&);
};

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
