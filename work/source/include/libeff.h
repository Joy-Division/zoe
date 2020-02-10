/*
 * [ LibEFF ]
 * Effects Library
 *
 * ver.ZONE OF THE ENDERS
 */
#ifndef INC_LIBEFF_H
#define INC_LIBEFF_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libalg.h"

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class EFF_FIELD
{
	/* VTable */

public: //! unconfirmed modifier
	int     nProcess;
	bool32  bLock;

public:
	EFF_FIELD(const EFF_FIELD&);
	EFF_FIELD();
	
	void AddProcess();
	void DeleteProcess();
	void Lock();
	void Unlock();
	void FieldFunc(ALG_VECTOR*, ALG_VECTOR*);
	
	EFF_FIELD& operator=(const EFF_FIELD&);
};

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
