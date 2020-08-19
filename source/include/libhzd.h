#ifndef INCLUDED_LIBHZD_H
#define INCLUDED_LIBHZD_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libalg.h"
//#include "libdg.h"

// external
class DG_MDL;

// internal
class HZD_AXIS_LIMIT;
class HZD_BREAK;
class HZD_BREAK_STATUS;
class HZD_CIRCLE_LIMIT;
class HZD_GRAVITY;
class HZD_G_DIR;
class HZD_G_LINE;
class HZD_G_ROT;
class HZD_LIMIT;
class HZD_OFFSET_TREE;
class HZD_PLANE;
class HZD_TREE_NODE;

//=============================================================================
// Hazard Break (break.cc, status.cc)
//=============================================================================

typedef struct _HZD_BREAK_LIST {
	BOOL8	blBrkFlag;
	BOOL8	blRescue;
	UINT8	u8Depth;
	UINT8	u8Shaft;
	UINT32	u32BrkOffset;
} HZD_BREAK_LIST;

/*---------------------------------------------------------------------------*/

class HZD_BREAK_STATUS
{
public: //! check modifier
	static const int32 HZD_N_BREAK = DEFINE_ME;

	UINT32			u32HZTCode;
	HZD_TREE_NODE*	pRoot;
	HZD_BREAK_LIST	pData[256];
	UINT32			u32nBreak;
	UINT32			u32TotalPoint;
	UINT32			u32NowPoint;
	UINT32			u32NowBreak;

public:
	int32			CheckStatus( UINT32 );
	void			SetStatus( UINT32, HZD_TREE_NODE* );
	void			CreateStatus( UINT32, HZD_TREE_NODE* );
	HZD_BREAK_LIST*	CreateData( HZD_TREE_NODE*, int32 );
	void			ChangeBreak();
	void			Link();
	void			ChangeData( HZD_TREE_NODE* );
	void			AddPoint( UINT8 );
	UINT32			GetTotalPoint();
	UINT32			GetNowPoint();
	UINT32			GetNumber();
	int32			GetStatus( UINT32 );
	HZD_TREE_NODE*	GetPtr( UINT32 );
	void			Dump();
};

/*---------------------------------------------------------------------------*/

class HZD_BREAK
{
public: //! check modifier
	static const UINT8 HZD_N_STAGE = DEFINE_ME;

	UINT32				u32StageNo;
	UINT32				u32NowStage;
	UINT32				u32Flag;
	BOOL32				bInit;
	HZD_BREAK_STATUS	pHZDBreak[24];

public:
	HZD_BREAK();

	void				Reset();
	int32				HZD_SetBreakStatus( char*, HZD_TREE_NODE* );
	int32				HZD_CheckBreakStatus();
	HZD_BREAK_LIST*		HZD_CreateData( HZD_TREE_NODE*, int32 );
	void				HZD_ChangeData( HZD_TREE_NODE* );
	void				HZD_ChangeBreak();
	void				HZD_AddData(UINT8);
	UINT32				HZD_GetTotalPoint();
	UINT32				HZD_GetNowPoint();
	UINT32				HZD_GetNumber();
	int32				HZD_GetStatus( UINT32 );
	HZD_TREE_NODE*		HZD_GetPtr( UINT32 );
	void				HZD_Dump();
	HZD_BREAK_STATUS*	GetCurrentStatus();
	float				GetBreakStatus( UINT32 );
	HZD_BREAK_STATUS*	GetBreakList( UINT32 );

	static HZD_BREAK* Init();
};

//=============================================================================
// Hazard Capsule (capsule.cc)
//=============================================================================

typedef struct _HZD_CAPSULE
{
public: //! check modifier
	float		fRadius;
	UINT32		pad0,pad1,pad2;
	ALG_VECTOR	vecFrontCenter;
	ALG_VECTOR	vecRearCenter;

public:
	_HZD_CAPSULE();

	_HZD_CAPSULE& operator = ( const _HZD_CAPSULE& );
}
HZD_CAPSULE;

//=============================================================================
// Hazard Gravity Field (gfield.cc)
//=============================================================================

class HZD_G_DIR
{
public: //! check modifier
	ALG_MATRIX matDir;

public:
	void GetComp( ALG_MATRIX*, ALG_VECTOR* );
	void Init();

	HZD_G_DIR();

	HZD_G_DIR& operator = ( const HZD_G_DIR& );
};

/*---------------------------------------------------------------------------*/

class HZD_G_LINE
{
public: //! check modifier
	ALG_MATRIX	matCenter;
	float		fHeight;

public:
	void GetComp( ALG_MATRIX*, ALG_VECTOR* );
	void Inverse( ALG_VECTOR*, ALG_VECTOR* );
	void Init();

	HZD_G_LINE();

	HZD_G_LINE& operator = ( const HZD_G_LINE& );
};

/*---------------------------------------------------------------------------*/

class HZD_G_ROT
{
public: //! check modifier
	ALG_MATRIX	matCenter;
	float		fHeight;

public:
	void GetComp( ALG_MATRIX*, ALG_VECTOR* );
	void Init();

	HZD_G_ROT();

	HZD_G_ROT& operator = ( const HZD_G_ROT& );
};

/*---------------------------------------------------------------------------*/

class HZD_GRAVITY
{
public: //! check modifier
	UINT8		u8Type;
	HZD_G_DIR	g_dir;
	HZD_G_LINE	g_line;
	HZD_G_ROT	g_rot;

private:
	void iGetComp( ALG_MATRIX*, ALG_VECTOR* );	// internal GetComp()
	void iSetComp( UINT8, ALG_MATRIX* );		// internal SetComp()
	void iInverse( ALG_VECTOR*, ALG_VECTOR* );	// internal Inverse()

public: //! check modifier
	static HZD_GRAVITY* pGrav;

public:
	static void GetComp( ALG_MATRIX*, ALG_VECTOR* );
	static void SetComp( UINT8, ALG_MATRIX* );
	static void Inverse( ALG_VECTOR*, ALG_VECTOR* );
	static void Reset();
	static void Init();

	HZD_GRAVITY();

	HZD_GRAVITY& operator = ( const HZD_GRAVITY& );
};

//=============================================================================
// Hazard Limit (limit.cc)
//=============================================================================

class HZD_AXIS_LIMIT
{
public: //! check modifier
	float fOuter;
	float fInner;

private:
	float LimitRate(float);
	float GetDist(float);
};

/*---------------------------------------------------------------------------*/

class HZD_CIRCLE_LIMIT
{
public: //! check modifier
	float fOuter;
	float fInner;
	float fX, fY;

private:
	float LimitRate( float, float );
};

/*---------------------------------------------------------------------------*/

class HZD_LIMIT
{
public: //! check modifier
	HZD_AXIS_LIMIT		axlNorth;
	HZD_AXIS_LIMIT		axlSouth;
	HZD_AXIS_LIMIT		axlWest;
	HZD_AXIS_LIMIT		axlEast;
	HZD_AXIS_LIMIT		axlTop;
	HZD_AXIS_LIMIT		axlBottom;
	HZD_CIRCLE_LIMIT	crlLevel;
	BOOL32				bGravity;
	float				fSpdGravity;
	int32				ctrLimit[2];
	UINT8				u8Flag;

private:
	int32	Limit( ALG_VECTOR*, ALG_MATRIX*, int32, int32 );
	void	NearestLimit( ALG_VECTOR*, ALG_MATRIX* );

public:
	void SetAxisLimitNS( float, float, float );
	void SetAxisLimitWE( float, float, float );
	void SetLimitRangeWE( float, float );
	void SetAxisLimitTop( float, float );
	void SetAxisLimitBottom( float, float );
	void SetCircleLimit( float, float, float, float );
	void SetGravitySpeed( float );

	static int32	LimitVelocity( ALG_VECTOR*, ALG_MATRIX*, int32, int32 );
	static void		GetNearestLimit( ALG_VECTOR*, ALG_MATRIX* );

	void Reset();

	static int Time( int );
};

//=============================================================================
// Hazard Plane
//=============================================================================

class HZD_PLANE
{
public: //! check modifier
	UINT32			u32Flag;
	HZD_TREE_NODE*	pNode;
	UINT32			pad0,pad1;
	ALG_VECTOR		vecp[4];
	ALG_VECTOR		vecn;

public:
	int32			BReverse();
	UINT8			AddDamage(int32);
	void			ChangeModel();
	HZD_TREE_NODE*	CheckChain();

	HZD_PLANE();

	HZD_PLANE& operator = ( const HZD_PLANE& );
};

//=============================================================================
// Hazard Tree
//=============================================================================

class HZD_TREE_NODE
{
public: //! check modifier
	float			lx, ly, lz;
	HZD_TREE_NODE*	pChildOrg;
	float			ux, uy, uz;
	HZD_TREE_NODE*	pSiblingOrg;
	HZD_BREAK_LIST*	pBreakList;
	DG_MDL*			pmdl;
	HZD_TREE_NODE*	pChild;
	HZD_TREE_NODE*	pSibling;
	HZD_TREE_NODE*	pRef;
	SINT16			s16Mdl;
	UINT16			u16Flag;
	HZD_PLANE*		pPlLeaf;
	int				nbPlane;
	HZD_TREE_NODE*	pBreak;
	UINT8			u8Damage;
	UINT8			u8MAXDamage;
	UINT8			u8BreakFlag;
	UINT8			u8BreakPoint;
	HZD_TREE_NODE*	pBreakChain;
	UINT16			u16Brk;
	UINT16			u16Total;

public:
	void			ChangeBreakModel();
	HZD_TREE_NODE*	CheckChainNode();
};

/*---------------------------------------------------------------------------*/

class HZD_OFFSET_TREE
{
public: //! check modifier
	static HZD_OFFSET_TREE*	pOffsetTop;
	static int				nTree;
	ALG_MATRIX				matL2World;
	ALG_MATRIX				matInv;
	HZD_TREE_NODE*			pTreeRoot;

public:
	void Set(int32);
	void CalcInv();

	static void Reset();

	~HZD_OFFSET_TREE();

	static HZD_OFFSET_TREE* GetCurrent();

	HZD_OFFSET_TREE();

	HZD_OFFSET_TREE& operator = ( const HZD_OFFSET_TREE& );
};

//=============================================================================
// Global Functions
//=============================================================================

/* hzdd.cc */
void HZD_Init();

#endif /* END OF FILE */
