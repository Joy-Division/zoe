#ifndef INCLUDED_LIBEFF_H
#define INCLUDED_LIBEFF_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libalg.h"

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class EFF_FIELD
{
	/* VTable */

public: //! check modifier
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

#endif /* END OF FILE */
