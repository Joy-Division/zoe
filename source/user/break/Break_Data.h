#ifndef INCLUDED_BREAK_DATA_H
#define INCLUDED_BREAK_DATA_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libalg.h"

/*---------------------------------------------------------------------------*/

class BRK_DAT
{
public: //! check modifier
	ALG_VECTOR*	pPos;	//
	ALG_VECTOR	SP;		//
	UINT8		F;		//

public:
	BOOL32	Check_Low( float );
	void	SP_Add( float, ALG_VECTOR* );
	void	SP_Add( float );
	void	Axis_Fall( ALG_MATRIX* );
	void	Dump();

	BRK_DAT();

	BRK_DAT& operator = ( const BRK_DAT& );
};

/*---------------------------------------------------------------------------*/

class BRK_FRM
{
public: //! check modifier
	ALG_MATRIX	matO;	//
	ALG_MATRIX	matR;	//
	ALG_VECTOR	vecP;	//
	ALG_VECTOR	SP;		//
	float		G;		//
	UINT16		FON;	//
	UINT8		N;		//
	UINT8		u8EF;	//
	BOOL32		bL;		//

public:
	ALG_MATRIX SP_ADD();

	BRK_FRM();

	BRK_FRM& operator = ( const BRK_FRM& );
};

#endif /* END OF FILE */
