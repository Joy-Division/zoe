/*
 * [ LibHZD ]
 * Collision Library
 *
 * ver.ZONE OF THE ENDERS
 */
#ifndef INC_LIBHZD_H
#define INC_LIBHZD_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libalg.h"
#include "libdg.h"

// declaration
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

/*---------------------------------------------------------------------------*
 * Hazard Break (break.cc, status.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
typedef struct _HZD_BREAK_LIST {
	bool8   blBrkFlag;
	bool8   blRescue;
	uint8   u8Depth;
	sint8   u8Shaft;
	uint32  u32BrkOffset;
} HZD_BREAK_LIST;

// ref.default.pdb
class HZD_BREAK_STATUS
{
public: //! unconfirmed modifier
	static const sint32 HZD_N_BREAK = TEMP_ZERO;
	
	uint32          u32HZTCode;
	HZD_TREE_NODE*  pRoot;
	HZD_BREAK_LIST  pData[256];
	uint32          u32nBreak;
	uint32          u32TotalPoint;
	uint32          u32NowPoint;
	uint32          u32NowBreak;

public:
	sint32          CheckStatus(uint32);
	void            SetStatus(uint32, HZD_TREE_NODE*);
	void            CreateStatus(uint32, HZD_TREE_NODE*);
	HZD_BREAK_LIST* CreateData(HZD_TREE_NODE*, sint32);
	void            ChangeBreak();
	void            Link();
	void            ChangeData(HZD_TREE_NODE*);
	void            AddPoint(uint8);
	uint32          GetTotalPoint();
	uint32          GetNowPoint();
	uint32          GetNumber();
	sint32          GetStatus(uint32);
	HZD_TREE_NODE*  GetPtr(uint32);
	void            Dump();
};

// ref.default.pdb
class HZD_BREAK
{
public: //! unconfirmed modifier
	static const uint8 HZD_N_STAGE = TEMP_ZERO;
	
	uint32              u32StageNo;
	uint32              u32NowStage;
	uint32              u32Flag;
	bool32              bInit;
	HZD_BREAK_STATUS    pHZDBreak[24];

public:
	HZD_BREAK();
	
	void                Reset();
	sint32              HZD_SetBreakStatus(char*, HZD_TREE_NODE*);
	sint32              HZD_CheckBreakStatus();
	HZD_BREAK_LIST*     HZD_CreateData(HZD_TREE_NODE*, sint32);
	void                HZD_ChangeData(HZD_TREE_NODE*);
	void                HZD_ChangeBreak();
	void                HZD_AddData(uint8);
	uint32              HZD_GetTotalPoint();
	uint32              HZD_GetNowPoint();
	uint32              HZD_GetNumber();
	sint32              HZD_GetStatus(uint32);
	HZD_TREE_NODE*      HZD_GetPtr(uint32);
	void                HZD_Dump();
	HZD_BREAK_STATUS*   GetCurrentStatus();
	float               GetBreakStatus(uint32);
	HZD_BREAK_STATUS*   GetBreakList(uint32);
	
	static HZD_BREAK*   Init();
};

/*---------------------------------------------------------------------------*
 * Hazard Capsule (capsule.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
typedef struct _HZD_CAPSULE
{
public: //! unconfirmed modifier
	float       fRadius;
	uint32      pad0;
	uint32      pad1;
	uint32      pad2;
	ALG_VECTOR  vecFrontCenter;
	ALG_VECTOR  vecRearCenter;

public:
	_HZD_CAPSULE();
	
	_HZD_CAPSULE& operator=(const _HZD_CAPSULE&);
}
HZD_CAPSULE;

/*---------------------------------------------------------------------------*
 * Hazard Gravity Field (gfield.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class HZD_G_DIR
{
public: //! unconfirmed modifier
	ALG_MATRIX matDir;

public:
	void GetComp(ALG_MATRIX*, ALG_VECTOR*);
	void Init();
	
	HZD_G_DIR();
	
	HZD_G_DIR& operator=(const HZD_G_DIR&);
};

// ref.default.pdb
class HZD_G_LINE
{
public: //! unconfirmed modifier
	ALG_MATRIX  matCenter;
	float       fHeight;

public:
	void GetComp(ALG_MATRIX*, ALG_VECTOR*);
	void Inverse(ALG_VECTOR*, ALG_VECTOR*);
	void Init();
	
	void HZD_G_LINE();
	
	HZD_G_LINE& operator=(const HZD_G_LINE&);
};

// ref.default.pdb
class HZD_G_ROT
{
public: //! unconfirmed modifier
	ALG_MATRIX  matCenter;
	float       fHeight;

public:
	void GetComp(ALG_MATRIX*, ALG_VECTOR*);
	void Init();
	
	void HZD_G_ROT();
	
	HZD_G_ROT& operator=(const HZD_G_ROT&);
};

// ref.default.pdb
class HZD_GRAVITY
{
public: //! unconfirmed modifier
	uint8       u8Type;
	HZD_G_DIR   g_dir;
	HZD_G_LINE  g_line;
	HZD_G_ROT   g_rot;

private:
	void iGetComp(ALG_MATRIX*, ALG_VECTOR*);
	void iSetComp(uint8, ALG_MATRIX*);
	void iInverse(ALG_VECTOR*, ALG_VECTOR*);

public: //! unconfirmed modifier
	static HZD_GRAVITY* pGrav;

public:
	static void GetComp(ALG_MATRIX*, ALG_VECTOR*);
	static void SetComp(uint8, ALG_MATRIX*);
	static void Inverse(ALG_VECTOR*, ALG_VECTOR*);
	static void Reset();
	static void Init();
	
	HZD_GRAVITY();
	
	HZD_GRAVITY& operator=(const HZD_GRAVITY&);
};

/*---------------------------------------------------------------------------*
 * Hazard Limit (limit.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class HZD_AXIS_LIMIT
{
public: //! unconfirmed modifier
	float fOuter;
	float fInner;

private:
	float LimitRate(float);
	float GetDist(float);
};

// ref.default.pdb
class HZD_CIRCLE_LIMIT
{
public: //! unconfirmed modifier
	float fOuter;
	float fInner;
	float fX, fY;

private:
	float LimitRate(float, float);
};

// ref.default.pdb
class HZD_LIMIT
{
public: //! unconfirmed modifier
	HZD_AXIS_LIMIT      axlNorth;
	HZD_AXIS_LIMIT      axlSouth;
	HZD_AXIS_LIMIT      axlWest;
	HZD_AXIS_LIMIT      axlEast;
	HZD_AXIS_LIMIT      axlTop;
	HZD_AXIS_LIMIT      axlBottom;
	HZD_CIRCLE_LIMIT    crlLevel;
	bool32              bGravity;
	float               fSpdGravity;
	sint32              ctrLimit[2];
	uint8               u8Flag;

private:
	sint32 Limit(ALG_VECTOR*, ALG_MATRIX*, sint32, sint32);
	void   NearestLimit(ALG_VECTOR*, ALG_MATRIX*);

public:
	void SetAxisLimitNS(float, float, float);
	void SetAxisLimitWE(float, float, float);
	void SetLimitRangeWE(float, float);
	void SetAxisLimitTop(float, float);
	void SetAxisLimitBottom(float, float);
	void SetCircleLimit(float, float, float, float);
	void SetGravitySpeed(float);
	
	static sint32 LimitVelocity(ALG_VECTOR*, ALG_MATRIX*, sint32, sint32);
	static void   GetNearestLimit(ALG_VECTOR*, ALG_MATRIX*);
	
	void Reset();
	
	static int Time(int);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class HZD_PLANE
{
public: //! unconfirmed modifier
	uint32          u32Flag;
	HZD_TREE_NODE*  pNode;
	uint32          pad0;
	uint32          pad1;
	ALG_VECTOR      vecp[4];
	ALG_VECTOR      vecn;

public:
	sint32          BReverse();
	uint8           AddDamage(sint32);
	void            ChangeModel();
	HZD_TREE_NODE*  CheckChain();
	
	HZD_PLANE();
	
	HZD_PLANE& operator=(const HZD_PLANE&);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class HZD_TREE_NODE
{
public: //! unconfirmed modifier
	float           lx, ly, lz;
	HZD_TREE_NODE*  pChildOrg;
	float           ux, uy, uz;
	HZD_TREE_NODE*  pSiblingOrg;
	HZD_BREAK_LIST* pBreakList;
	DG_MDL*         pmdl;
	HZD_TREE_NODE*  pChild;
	HZD_TREE_NODE*  pSibling;
	HZD_TREE_NODE*  pRef;
	sint16          s16Mdl;
	uint16          u16Flag;
	HZD_PLANE*      pPlLeaf;
	sint32          nbPlane;
	HZD_TREE_NODE*  pBreak;
	uint8           u8Damage;
	uint8           u8MAXDamage;
	uint8           u8BreakFlag;
	uint8           u8BreakPoint;
	HZD_TREE_NODE*  pBreakChain;
	uint16          u16Brk;
	uint16          u16Total;

public:
	void            ChangeBreakModel();
	HZD_TREE_NODE*  CheckChainNode();
};

// ref.default.pdb
class HZD_OFFSET_TREE
{
public: //! unconfirmed modifier
	static HZD_OFFSET_TREE* pOffsetTop;
	static sint32           nTree;

	ALG_MATRIX      matL2World;
	ALG_MATRIX      matInv;
	HZD_TREE_NODE*  pTreeRoot;

public:
	void Set(sint32);
	void CalcInv();
	
	static void Reset();
	
	~HZD_OFFSET_TREE();
	
	static HZD_OFFSET_TREE* GetCurrent();
	
	HZD_OFFSET_TREE();
	
	HZD_OFFSET_TREE& operator=(const HZD_OFFSET_TREE&);
};

/*---------------------------------------------------------------------------*
 * Prototypes
 *---------------------------------------------------------------------------*/

/* Hazard Daemon (hzdd.cc) */
void HZD_Init();

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
