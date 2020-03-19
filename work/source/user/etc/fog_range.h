#ifndef INCLUDED_FOG_RANGE_H
#define INCLUDED_FOG_RANGE_H

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

#endif /* END OF FILE */
