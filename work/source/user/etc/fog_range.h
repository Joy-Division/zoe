#ifndef INC_FOG_RANGE_H
#define INC_FOG_RANGE_H

#include "global.h"

// ref.default.pdb
class FOG_RANGE
{
public: //! unconfirmed modifier
	float32 N, N2;
	float32 F, F2;
	float32 S;
	float32 H;

public:
	void Init(float32, float32);
};

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
