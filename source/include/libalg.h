/*
 * Linear Algebra Library
 * Global Include
 */
/* ver."ZONE OF THE ENDERS"
 */
#ifndef INCLUDED_LIBALG_H
#define INCLUDED_LIBALG_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

class ALG_VECTOR;
class ALG_MATRIX;
class ALG_QUATER;

/*---------------------------------------------------------------------------*
 * Vector Math (vector.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class ALG_VECTOR
{
public: //! check modifier
	float fX;
	float fY;
	float fZ;
	float fW;

public:
	ALG_VECTOR(float, float, float, float);
	ALG_VECTOR(float, float, float);
	ALG_VECTOR();
	
	void        operator () (float, float, float, float);
	void        operator () (float, float, float);
	ALG_VECTOR& operator =  (float);
	ALG_VECTOR& operator =  (const ALG_VECTOR&);
	ALG_VECTOR  operator +  (const ALG_VECTOR&);
	ALG_VECTOR  operator -  (const ALG_VECTOR&);
	ALG_VECTOR  operator -  ();
	ALG_VECTOR  operator *  (float);
	float       operator *  (const ALG_VECTOR&);
	ALG_VECTOR  operator /  (float);
	int         operator == (float);
	int         operator == (const ALG_VECTOR&);
	int         operator != (float);
	int         operator != (const ALG_VECTOR&);
	void        operator += (const ALG_VECTOR&);
	void        operator -= (const ALG_VECTOR&);
	void        operator *= (float);
	void        operator /= (float);
	
	float   Scalar2();
	float   Scalar();
	float   Dist2(ALG_VECTOR*);
	float   Dist(ALG_VECTOR*);
	void    Cross(ALG_VECTOR*, ALG_VECTOR*);
	int     DistClip(ALG_VECTOR*, float);
	void    Norm();
	void    Move(ALG_VECTOR*, float);
	void    Interp(ALG_VECTOR*, ALG_VECTOR*, float);
	void    Interp(ALG_VECTOR*, float);
	void    Hermite(ALG_VECTOR*, ALG_VECTOR*, ALG_VECTOR*, float);
	void    RelPos(ALG_MATRIX*);
	void    AbsPos(ALG_MATRIX*);
	void    RelVec(ALG_MATRIX*);
	void    AbsVec(ALG_MATRIX*);
	float   RelZ(ALG_MATRIX*);
	void    Dump();
};

/*---------------------------------------------------------------------------*
 * Matrix Math (matrix.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class ALG_MATRIX
{
public: //! check modifier
	ALG_VECTOR vecX;
	ALG_VECTOR vecY;
	ALG_VECTOR vecZ;
	ALG_VECTOR vecT;

public:
	ALG_MATRIX( float fXX, float fXY, float fXZ, float fXW,
	            float fYX, float fYY, float fYZ, float fYW,
	            float fZX, float fZY, float fZZ, float fZW,
	            float fTX, float fTY, float fTZ, float fTW );
	ALG_MATRIX();
	
	void        operator () ( float fXX, float fXY, float fXZ, float fXW,
	                          float fYX, float fYY, float fYZ, float fYW,
	                          float fZX, float fZY, float fZZ, float fZW,
	                          float fTX, float fTY, float fTZ, float fTW );
	ALG_MATRIX& operator =  ( float fScalar );
	ALG_MATRIX& operator =  ( const ALG_MATRIX& rmat );
	ALG_VECTOR  operator *  ( const ALG_VECTOR& rvec );
	ALG_MATRIX  operator *  ( const ALG_MATRIX& rmat );
	ALG_MATRIX  operator /  ( const ALG_MATRIX& rmat );
	void        operator *= ( const ALG_MATRIX& rmat );
	void        operator /= ( const ALG_MATRIX& rmat );
	
	void    Invert();
	void    Invert2();
	void    Transpose();
	void    Translate(float, float, float);
	void    RotateX(float);
	void    RotateY(float);
	void    RotateZ(float);
	void    Rotate(float, float, float);
	void    Scale(float, float, float);
	void    Scale(float);
	void    RelMat(ALG_MATRIX*);
	void    AbsMat(ALG_MATRIX*);
	void    RelRot(ALG_MATRIX*);
	void    AbsRot(ALG_MATRIX*);
	void    Convert(ALG_QUATER*);
	void    Interp(ALG_MATRIX*, float);
	float   AngDist(ALG_MATRIX*);
	void    SetAxisY(ALG_VECTOR*);
	void    SetAxisZ(ALG_VECTOR*);
	void    SetFreeY(ALG_VECTOR*, float);
	void    SetFreeZ(ALG_VECTOR*, float);
	void    Line(ALG_VECTOR*, ALG_VECTOR*, ALG_VECTOR*);
	void    Dump();
};

/*---------------------------------------------------------------------------*
 * Quaternion Math (quater.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class ALG_QUATER
{
public: //! check modifier
	float fImX;
	float fImY;
	float fImZ;
	float fReal;

public:
	void Convert(ALG_MATRIX*);
	void Norm();
	void Slerp(ALG_QUATER*, float);
	void Dump();
};

#endif /* END OF FILE */
