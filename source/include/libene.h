#ifndef INCLUDED_LIBENE_H
#define INCLUDED_LIBENE_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

#include "libalg.h"
//#include "libdg.h"
//#include "libfrm.h"
#include "libgv.h"
#include "libtrg.h"

// external
class DG_OBJ;
class FRM_OBJECT;

// internal
struct ENE_ENTRY;
struct ENE_MEMBER;
class ENE_MANAGER;
class ENE_OBJECT;
class ENE_PARTY;
class ENE_STATE;

//=============================================================================
// Enemy Entry
//=============================================================================

struct ENE_ENTRY
{
public: //! check modifier
	ENE_PARTY*	ppar;
	UINT8		u8Index;
	UINT8		u8State;
	ALG_MATRIX	matInit;
	TRG_OBJECT*	ptrg;

public:
	ENE_ENTRY();

	ENE_ENTRY& operator = ( const ENE_ENTRY& );
};

//=============================================================================
// Enemy Member
//=============================================================================

struct ENE_MEMBER
{
public: //! check modifier
	UINT32		u32NameID;
	UINT8		u8Type;
	UINT8		u8Mode;
	UINT8		u8Level;
	BOOL32		bLive;
	ALG_VECTOR	vecPos;
	DG_OBJ*		pobj;
	TRG_OBJECT	trg;
	ALG_MATRIX	matOrg;

public:
	ENE_MEMBER();
	~ENE_MEMBER();

	ENE_MEMBER& operator = ( const ENE_MEMBER& );
};

//=============================================================================
// Enemy State
//=============================================================================

class ENE_STATE
{
public: //! check modifier
	UINT8	u8ID;
	UINT8	u8NextID;
	BOOL32	bInit;
	BOOL32	bChange;

public:
	ENE_STATE();

	void	Set( UINT8 );
	void	Update();
	int32	Init();
	UINT8	ID();
};

//=============================================================================
// Enemy Manager
//=============================================================================

class ENE_MANAGER : public GV_ACTOR
{
public: //! check modifier
	static UINT8		u8PartyNum;
	static UINT8		u8EntryNum;
	static UINT8		u8FightNum;
	static UINT16		u16EndCntr;
	static BOOL32		bForce;
	static BOOL32		bEncount;
	static BOOL32		bNoEnemy;
	static BOOL32		bEscape;
	static BOOL32		bInitEsc;
	static UINT16		u16EscCntr;
	static UINT16		u16LotID;
	static ENE_PARTY*	pparEntry[16];
	static ENE_ENTRY	entry[64];

public:
	ENE_MANAGER( const ENE_MANAGER& );
	ENE_MANAGER();
	~ENE_MANAGER();

	void Act(); // override GV_ACTOR::Act()

	static int32	Encount();
	static int32	Escape();
	static UINT16	EscapeCounter();
	static UINT8	PartyNumber();
	static UINT8	EnemyNumber();
	static UINT8	EnemyType( UINT8 );
	static UINT32	EnemyID( UINT8 );
	static void		LockOn( UINT16 );
	static void		KeepEnd();
	static void		SetNoEnemy();
	static void		SetFight();
	static void		ResetFight();
	static void		ForceEscape();

	ENE_MANAGER& operator = ( const ENE_MANAGER& );
};

//=============================================================================
// Enemy Object
//=============================================================================

class ENE_OBJECT
{
public: //! check modifier
	FRM_OBJECT*	pfrm;
	ENE_STATE	state;
	ALG_VECTOR	vecLotPos;
	BOOL32		bLocked;
	FRM_OBJECT*	pfrmLot;
	TRG_OBJECT	trgCheck;
	void (*pfnThink)(void);
	UINT8		u8Common1;
	UINT8		u8Common2;
	UINT8		u8Common3;
	UINT8		u8Common4;
	UINT8		u8Common5;
	UINT8		u8Common6;
	UINT8		u8Common7;
	UINT8		u8Common8;
	SINT8		s8Common1;
	SINT8		s8Common2;
	SINT8		s8Common3;
	SINT8		s8Common4;
	SINT8		s8Common5;
	SINT8		s8Common6;
	SINT8		s8Common7;
	SINT8		s8Common8;
	UINT16		u16Common1;
	UINT16		u16Common2;
	UINT16		u16Common3;
	UINT16		u16Common4;
	UINT16		u16Common5;
	UINT16		u16Common6;
	UINT16		u16Common7;
	UINT16		u16Common8;
	float		fCommon1;
	float		fCommon2;
	float		fCommon3;
	float		fCommon4;
	float		fCommon5;
	float		fCommon6;
	float		fCommon7;
	float		fCommon8;
	BOOL32		bCommon1;
	BOOL32		bCommon2;
	BOOL32		bCommon3;
	ALG_VECTOR	vecCommon1;
	ALG_VECTOR	vecCommon2;
	ALG_VECTOR	vecCommon3;
	ALG_MATRIX	matCommon1;
	ALG_MATRIX	matCommon2;
	ALG_MATRIX	matCommon3;

public:
	void InitJehuty();
	void ThinkJehuty();
	void InitRaptor();
	void ThinkRaptor();
	void InitMummy();
	void ThinkMummy();
	void InitCyclops();
	void ThinkCyclops();
	void InitNeith1();
	void ThinkNeith1();
	void InitNeith2();
	void ThinkNeith2();
	void Init( FRM_OBJECT* );
	void SetPad();

	ENE_OBJECT();
	~ENE_OBJECT();

	ENE_OBJECT& operator = ( const ENE_OBJECT& );
};

//=============================================================================
// Enemy Party
//=============================================================================

class ENE_PARTY : public GV_ACTOR
{
public: //! check modifier
	UINT32		u32NameID;
	UINT8		u8MoveType;
	float		fMoveSpeed;
	UINT8		u8Item;
	UINT32		u32DestProc;
	UINT8		u8Level;
	UINT8		u8State;
	UINT8		u8MemNum;
	UINT8		u8LiveNum;
	UINT8		u8RouteNum;
	UINT8		u8CurRoute;
	ALG_MATRIX	matMove;
	BOOL32		bReverse;
	UINT16		u16BreakCntr;
	ALG_VECTOR	vecRoute[16];
	ENE_MEMBER	mem[8];
	TRG_OBJECT	trgParty;
	ALG_MATRIX	matParty;
	ALG_VECTOR	vecBound[2];

public:
	ENE_PARTY( const ENE_PARTY& );
	ENE_PARTY( UINT32, UINT8, UINT32, UINT8, UINT32*, ALG_VECTOR*, UINT8*, UINT8*, UINT8*, UINT8, float, UINT8, ALG_VECTOR* );
	~ENE_PARTY();

	void Act(); // override GV_ACTOR::Act()

	void CalcPartyData();
	void SetBullet();

	ENE_PARTY& operator = ( const ENE_PARTY& );
};

#endif /* END OF FILE */
