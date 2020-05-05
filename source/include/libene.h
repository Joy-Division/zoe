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

// ref.default.pdb
struct ENE_ENTRY
{
public: //! check modifier
	ENE_PARTY*	ppar;
	uint8		u8Index;
	uint8		u8State;
	ALG_MATRIX	matInit;
	TRG_OBJECT*	ptrg;

public:
	ENE_ENTRY();

	ENE_ENTRY& operator = ( const ENE_ENTRY& );
};

//=============================================================================
// Enemy Member
//=============================================================================

// ref.default.pdb
struct ENE_MEMBER
{
public: //! check modifier
	uint32		u32NameID;
	uint8		u8Type;
	uint8		u8Mode;
	uint8		u8Level;
	bool32		bLive;
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

// ref.default.pdb
class ENE_STATE
{
public: //! check modifier
	uint8	u8ID;
	uint8	u8NextID;
	bool32	bInit;
	bool32	bChange;

public:
	ENE_STATE();

	void	Set( uint8 );
	void	Update();
	int32	Init();
	uint8	ID();
};

//=============================================================================
// Enemy Manager
//=============================================================================

// ref.default.pdb
class ENE_MANAGER : public GV_ACTOR //! check modifier
{
public: //! check modifier
	static uint8		u8PartyNum;
	static uint8		u8EntryNum;
	static uint8		u8FightNum;
	static uint16		u16EndCntr;
	static bool32		bForce;
	static bool32		bEncount;
	static bool32		bNoEnemy;
	static bool32		bEscape;
	static bool32		bInitEsc;
	static uint16		u16EscCntr;
	static uint16		u16LotID;
	static ENE_PARTY*	pparEntry[16];
	static ENE_ENTRY	entry[64];

public:
	ENE_MANAGER( const ENE_MANAGER& );
	ENE_MANAGER();
	~ENE_MANAGER();

	void Act(); // override GV_ACTOR::Act()

	static int32	Encount();
	static int32	Escape();
	static uint16	EscapeCounter();
	static uint8	PartyNumber();
	static uint8	EnemyNumber();
	static uint8	EnemyType( uint8 );
	static uint32	EnemyID( uint8 );
	static void		LockOn( uint16 );
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

// ref.default.pdb
class ENE_OBJECT
{
public: //! check modifier
	FRM_OBJECT*	pfrm;
	ENE_STATE	state;
	ALG_VECTOR	vecLotPos;
	bool32		bLocked;
	FRM_OBJECT*	pfrmLot;
	TRG_OBJECT	trgCheck;
	void (*pfnThink)(void); // TODO: ret/arg types
	uint8		u8Common1;
	uint8		u8Common2;
	uint8		u8Common3;
	uint8		u8Common4;
	uint8		u8Common5;
	uint8		u8Common6;
	uint8		u8Common7;
	uint8		u8Common8;
	sint8		s8Common1;
	sint8		s8Common2;
	sint8		s8Common3;
	sint8		s8Common4;
	sint8		s8Common5;
	sint8		s8Common6;
	sint8		s8Common7;
	sint8		s8Common8;
	uint16		u16Common1;
	uint16		u16Common2;
	uint16		u16Common3;
	uint16		u16Common4;
	uint16		u16Common5;
	uint16		u16Common6;
	uint16		u16Common7;
	uint16		u16Common8;
	float		fCommon1;
	float		fCommon2;
	float		fCommon3;
	float		fCommon4;
	float		fCommon5;
	float		fCommon6;
	float		fCommon7;
	float		fCommon8;
	bool32		bCommon1;
	bool32		bCommon2;
	bool32		bCommon3;
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

// ref.default.pdb
class ENE_PARTY : public GV_ACTOR //! check modifier
{
public: //! check modifier
	uint32		  u32NameID;
	uint8		  u8MoveType;
	float		  fMoveSpeed;
	uint8		  u8Item;
	uint32		  u32DestProc;
	uint8		  u8Level;
	uint8		  u8State;
	uint8		  u8MemNum;
	uint8		  u8LiveNum;
	uint8		  u8RouteNum;
	uint8		  u8CurRoute;
	ALG_MATRIX	  matMove;
	bool32		  bReverse;
	uint16		  u16BreakCntr;
	ALG_VECTOR	  vecRoute[16];
	ENE_MEMBER	  mem[8];
	TRG_OBJECT	  trgParty;
	ALG_MATRIX	  matParty;
	ALG_VECTOR	  vecBound[2];

public:
	ENE_PARTY( const ENE_PARTY& );
	ENE_PARTY( uint32, uint8, uint32, uint8, uint32*, ALG_VECTOR*, uint8*, uint8*, uint8*, uint8, float, uint8, ALG_VECTOR* );
	~ENE_PARTY();

	void Act(); // override GV_ACTOR::Act()

	void CalcPartyData();
	void SetBullet();

	ENE_PARTY& operator = ( const ENE_PARTY& );
};

#endif /* END OF FILE */
