#ifndef INC_FOG_RANGE_H
#define INC_FOG_RANGE_H

// ref.default.pdb
class FOG_RANGE
{
public: //! unconfirmed modifier
	float N, N2; // near
	float F, F2; // far
	float S;
	float H;

public:
	void Init(float, float);
};

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
