#ifndef INCLUDED_FOG_RANGE_H
#define INCLUDED_FOG_RANGE_H

class FOG_RANGE
{
public: //! check modifier
	float N, N2;	// Near
	float F, F2;	// Far
	float S;		//
	float H;		//

public:
	void Init( float, float );
};

#endif /* END OF FILE */
