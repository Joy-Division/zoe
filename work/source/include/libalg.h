/*
 * [ LibALG ]
 * Linear Algebra Library
 *
 * ver.ZONE OF THE ENDERS
 */
#ifndef INC_LIBALG_H
#define INC_LIBALG_H

#include "global.h"

/*---------------------------------------------------------------------------*
 * Vector Math (vector.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class ALG_VECTOR
{
public: //! unconfirmed modifier
	float32 fX;
	float32 fY;
	float32 fZ;
	float32 fW;

public:
	ALG_VECTOR(float32, float32, float32, float32);
	ALG_VECTOR(float32, float32, float32);
	ALG_VECTOR();
	
	void        operator()(float32, float32, float32, float32);
	void        operator()(float32, float32, float32);
	ALG_VECTOR& operator=(float32);
	ALG_VECTOR& operator=(const ALG_VECTOR&);
	ALG_VECTOR  operator+(const ALG_VECTOR&);
	ALG_VECTOR  operator-(const ALG_VECTOR&);
	ALG_VECTOR  operator-();
	ALG_VECTOR  operator*(float32);
	float32     operator*(const ALG_VECTOR&);
	ALG_VECTOR  operator/(float32);
	sint32      operator==(float32);
	sint32      operator==(const ALG_VECTOR&);
	sint32      operator!=(float32);
	sint32      operator!=(const ALG_VECTOR&);
	void        operator+=(const ALG_VECTOR&);
	void        operator-=(const ALG_VECTOR&);
	void        operator*=(float32);
	void        operator/=(float32);
	
	float32 Scalar2();
	float32 Scalar();
	float32 Dist2(ALG_VECTOR*);
	float32 Dist(ALG_VECTOR*);
	void    Cross(ALG_VECTOR*, ALG_VECTOR*);
	sint32  DistClip(ALG_VECTOR*, float32);
	void    Norm();
	void    Move(ALG_VECTOR*, float32);
	void    Interp(ALG_VECTOR*, ALG_VECTOR*, float32);
	void    Interp(ALG_VECTOR*, float32);
	void    Hermite(ALG_VECTOR*, ALG_VECTOR*, ALG_VECTOR*, float32);
	void    RelPos(ALG_MATRIX*);
	void    AbsPos(ALG_MATRIX*);
	void    RelVec(ALG_MATRIX*);
	void    AbsVec(ALG_MATRIX*);
	float32 RelZ(ALG_MATRIX*);
	void    Dump();
};

/*---------------------------------------------------------------------------*
 * Matrix Math (matrix.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class ALG_MATRIX
{
public: //! unconfirmed modifier
	ALG_VECTOR vecX;
	ALG_VECTOR vecY;
	ALG_VECTOR vecZ;
	ALG_VECTOR vecT;

public:
	ALG_MATRIX( float32 fXX, float32 fXY, float32 fXZ, float32 fXW,
	            float32 fYX, float32 fYY, float32 fYZ, float32 fYW,
	            float32 fZX, float32 fZY, float32 fZZ, float32 fZW,
	            float32 fTX, float32 fTY, float32 fTZ, float32 fTW )
	ALG_MATRIX();
	
	void        operator()( float32 fXX, float32 fXY, float32 fXZ, float32 fXW,
	                        float32 fYX, float32 fYY, float32 fYZ, float32 fYW,
	                        float32 fZX, float32 fZY, float32 fZZ, float32 fZW,
	                        float32 fTX, float32 fTY, float32 fTZ, float32 fTW )
	ALG_MATRIX& operator=( float32 fScalar );
	ALG_MATRIX& operator=( const ALG_MATRIX& rmat );
	ALG_VECTOR  operator*( const ALG_VECTOR& rvec );
	ALG_MATRIX  operator*( const ALG_MATRIX& rmat );
	ALG_MATRIX  operator/( const ALG_MATRIX& rmat );
	void        operator*=( const ALG_MATRIX& rmat );
	void        operator/=( const ALG_MATRIX& rmat );
	
	void    Invert();
	void    Invert2();
	void    Transpose();
	void    Translate(float32, float32, float32);
	void    RotateX(float32);
	void    RotateY(float32);
	void    RotateZ(float32);
	void    Rotate(float32, float32, float32);
	void    Scale(float32, float32, float32);
	void    Scale(float32);
	void    RelMat(ALG_MATRIX*);
	void    AbsMat(ALG_MATRIX*);
	void    RelRot(ALG_MATRIX*);
	void    AbsRot(ALG_MATRIX*);
	void    Convert(ALG_QUATER*);
	void    Interp(ALG_MATRIX*, float32);
	float32 AngDist(ALG_MATRIX*);
	void    SetAxisY(ALG_VECTOR*);
	void    SetAxisZ(ALG_VECTOR*);
	void    SetFreeY(ALG_VECTOR*, float32);
	void    SetFreeZ(ALG_VECTOR*, float32);
	void    Line(ALG_VECTOR*, ALG_VECTOR*, ALG_VECTOR*);
	void    Dump();
};

/*---------------------------------------------------------------------------*
 * Quaternion Math (quater.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class ALG_QUATER
{
public: //! unconfirmed modifier
	float32 fImX;
	float32 fImY;
	float32 fImZ;
	float32 fReal;

public:
	void Convert(ALG_MATRIX*);
	void Norm();
	void Slerp(ALG_QUATER*, float32);
	void Dump();
};

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
