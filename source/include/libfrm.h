#ifndef INCLUDED_LIBFRM_H
#define INCLUDED_LIBFRM_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

#include "libalg.h"
#include "libdg.h"
#include "libene.h"
#include "libgv.h"
#include "libhzd.h"
#include "libmt.h"
#include "libtrg.h"

// internal
class FRM_CAMERA;
class FRM_COMMAND;
class FRM_OBJECT;
class FRM_PAD;

//=============================================================================
// Orbital Frame Common Defines
//=============================================================================

enum {
	FRM_DEMO_NORMAL,
	FRM_DEMO_PLAY,
	FRM_DEMO_EDIT
};

/*---------------------------------------------------------------------------*/

enum {
	FRM_NODE_HEAD,
	FRM_NODE_UBODY,
	FRM_NODE_LBODY,
	FRM_NODE_UARM_L,
	FRM_NODE_UARM_R,
	FRM_NODE_LARM_L,
	FRM_NODE_LARM_R,
	FRM_NODE_FIST_L,
	FRM_NODE_FIST_R,
	FRM_NODE_ULEG_L,
	FRM_NODE_ULEG_R,
	FRM_NODE_LLEG_L,
	FRM_NODE_LLEG_R,
	FRM_NODE_FOOT_L,
	FRM_NODE_FOOT_R,
	FRM_NODE_BST_L,
	FRM_NODE_BST_R,
	FRM_NODE_COMMON,
	FRM_NODE_NECK,
	FRM_NODE_WAIST,
	FRM_NODE_CHEST,
	FRM_NODE_BLADE,
	FRM_NODE_SHIELD,
	FRM_NODE_SLD_L,
	FRM_NODE_SLD_R,
	FRM_NODE_BST2_L,
	FRM_NODE_BST2_R,
	FRM_NODE_BST3_L,
	FRM_NODE_BST3_R,
	FRM_NODE_BST4_L,
	FRM_NODE_BST4_R,
	FRM_NODE_BST5_L,
	FRM_NODE_BST5_R,
	FRM_NODE_BST6_L,
	FRM_NODE_BST6_R,
	FRM_NODE_BST7_L,
	FRM_NODE_BST7_R,
	FRM_NODE_BST8_L,
	FRM_NODE_BST8_R,
	FRM_NODE_LBST_L,
	FRM_NODE_LBST_R,
	FRM_NODE_COCK,
	FRM_NODE_NUM,
	FRM_NODE_CAN_L,
	FRM_NODE_CAN_R,
	FRM_NODE_BST_C,
	FRM_NODE_CAV_L,
	FRM_NODE_CAV_R,
	FRM_NODE_FS1_L,
	FRM_NODE_FS1_R,
	FRM_NODE_FS2_L,
	FRM_NODE_FS2_R,
	FRM_NODE_FS3_L,
	FRM_NODE_FS3_R,
	FRM_NODE_FS4_L,
	FRM_NODE_FS4_R,
	FRM_NODE_FS5_L,
	FRM_NODE_FS5_R,
	FRM_NODE_FS6_L,
	FRM_NODE_FS6_R,
	FRM_NODE_FS7_L,
	FRM_NODE_FS7_R,
	FRM_NODE_ANTENNA
};

/*---------------------------------------------------------------------------*/

enum {
	FRM_SEQ_IDLE_A,
	FRM_SEQ_IDLE_G,
	FRM_SEQ_MOVE_F_A,
	FRM_SEQ_MOVE_F_G,
	FRM_SEQ_MOVE_B_A,
	FRM_SEQ_MOVE_B_G,
	FRM_SEQ_MOVE_L_A,
	FRM_SEQ_MOVE_L_G,
	FRM_SEQ_MOVE_R_A,
	FRM_SEQ_MOVE_R_G,
	FRM_SEQ_MROLL_L_A,
	FRM_SEQ_MROLL_L_G,
	FRM_SEQ_MROLL_R_A,
	FRM_SEQ_MROLL_R_G,
	FRM_SEQ_MOVE_U,
	FRM_SEQ_MOVE_D_A,
	FRM_SEQ_MOVE_D_G,
	FRM_SEQ_DASH_N_A_1,
	FRM_SEQ_DASH_N_G_1,
	FRM_SEQ_DASH_N_A_2,
	FRM_SEQ_DASH_N_G_2,
	FRM_SEQ_DASH_F_1,
	FRM_SEQ_DASH_F_2,
	FRM_SEQ_DASH_B_1,
	FRM_SEQ_DASH_B_2,
	FRM_SEQ_DASH_L_1,
	FRM_SEQ_DASH_L_2,
	FRM_SEQ_DASH_R_1,
	FRM_SEQ_DASH_R_2,
	FRM_SEQ_DASH_U_1,
	FRM_SEQ_DASH_U_2,
	FRM_SEQ_DASH_D_1,
	FRM_SEQ_DASH_D_2,
	FRM_SEQ_DASH_S_1,
	FRM_SEQ_DASH_S_2,
	FRM_SEQ_DROLL_L_A,
	FRM_SEQ_DROLL_L_G,
	FRM_SEQ_DROLL_R_A,
	FRM_SEQ_DROLL_R_G,
	FRM_SEQ_ARMS_1,
	FRM_SEQ_ARMS_2,
	FRM_SEQ_ARMS_3,
	FRM_SEQ_ARMS_4,
	FRM_SEQ_DARMS_F,
	FRM_SEQ_DARMS_B,
	FRM_SEQ_DARMS_L,
	FRM_SEQ_DARMS_R,
	FRM_SEQ_DARMS_U,
	FRM_SEQ_DARMS_D,
	FRM_SEQ_BARMS,
	FRM_SEQ_SHOT,
	FRM_SEQ_DSHOT_F,
	FRM_SEQ_DSHOT_B,
	FRM_SEQ_DSHOT_L,
	FRM_SEQ_DSHOT_R,
	FRM_SEQ_DSHOT_U,
	FRM_SEQ_DSHOT_D,
	FRM_SEQ_BSHOT,
	FRM_SEQ_HOLD_1,
	FRM_SEQ_HOLD_2_O,
	FRM_SEQ_HOLD_2_X,
	FRM_SEQ_HELD_F,
	FRM_SEQ_HELD_B,
	FRM_SEQ_GUARD,
	FRM_SEQ_GUARD_ATTACK,
	FRM_SEQ_GUARD_CATCH,
	FRM_SEQ_GUARD_CROSS,
	FRM_SEQ_SDAMAGE_F,
	FRM_SEQ_SDAMAGE_B,
	FRM_SEQ_BDAMAGE_F,
	FRM_SEQ_BDAMAGE_B,
	FRM_SEQ_BUMP_F,
	FRM_SEQ_BUMP_B,
	FRM_SEQ_BLAST,
	FRM_SEQ_COMMON,
	FRM_SEQ_GETPROG,
	FRM_SEQ_GETITEM,
	FRM_SEQ_CANNON_2A,
	FRM_SEQ_CANNON_2B,
	FRM_SEQ_BIRD,
	FRM_SEQ_BIRD_L,
	FRM_SEQ_BIRD_R,
	FRM_SEQ_JAVELIN,
	FRM_SEQ_GEYSER,
	FRM_SEQ_BOUNDER,
	FRM_SEQ_MUMARM,
	FRM_SEQ_GAUNTLET,
	FRM_SEQ_SNIPER,
	FRM_SEQ_DECOY
};

/*---------------------------------------------------------------------------*/

enum {
	FRM_TYPE_JEHUTY,	// Jehuty (default)
	FRM_TYPE_RAPTOR,	// Raptor
	FRM_TYPE_MUMMY,		// MummyHead
	FRM_TYPE_CYCLOPS,	// Cyclops
	FRM_TYPE_NEITH1,	// Neith (1st battle)
	FRM_TYPE_NEITH2,	// Neith (2nd battle)
	FRM_TYPE_NUM
};

/*---------------------------------------------------------------------------*/

enum {
	PASS_JAVELIN,
	PASS_GEYSER,
	PASS_BOUNDER,
	PASS_PHALANX,
	PASS_HALBERD,
	PASS_COMET,
	PASS_GAUNTLET,
	PASS_DECOY_1,
	PASS_DECOY_2,
	PASS_MUMMY,
	PASS_GLOBAL,
	PASS_CONTROL_1,
	PASS_CONTROL_2,
	PASS_VACCINE,
	PASS_INFO,
	PASS_NUM
};

/*---------------------------------------------------------------------------*/

enum {
	PROG_JAVELIN,
	PROG_GEYSER,
	PROG_BOUNDER,
	PROG_PHALANX,
	PROG_HALBERD,
	PROG_COMET,
	PROG_GAUNTLET,
	PROG_SNIPER,
	PROG_DECOY,
	PROG_MUMMY,
	PROG_MONITOR,
	PROG_GLOBAL,
	PROG_CONTROL,
	PROG_GOGGLE,
	PROG_VIRUS,
	PROG_VACCINE,
	PROG_INFO_A,
	PROG_INFO_B,
	PROG_INFO_C,
	PROG_INFO_D,
	PROG_NUM
};

/*---------------------------------------------------------------------------*/

enum {
	WEP_NONE,
	WEP_JAVELIN,
	WEP_GEYSER,
	WEP_BOUNDER,
	WEP_PHALANX,
	WEP_HALBERD,
	WEP_COMET,
	WEP_GAUNTLET,
	WEP_SNIPER,
	WEP_DECOY,
	WEP_MUMMY,
	WEP_NUM
};

//=============================================================================
// Orbital Frame Commands
//=============================================================================

enum {
	CMD_ID_CONTROL,
	CMD_ID_ACTION,
	CMD_ID_DASH,
	CMD_ID_ARMS1,
	CMD_ID_ARMS2,
	CMD_ID_ARMS3,
	CMD_ID_ARMS4,
	CMD_ID_D_ARMS,
	CMD_ID_B_ARMS,
	CMD_ID_CATCH,
	CMD_ID_GUARD,
	CMD_ID_HOLD,
	CMD_ID_HELD,
	CMD_ID_CROSS,
	CMD_ID_BACK,
	CMD_ID_S_DMG,
	CMD_ID_B_DMG,
	CMD_ID_BUMP,
	CMD_ID_BLAST,
	CMD_ID_SHOT,
	CMD_ID_D_SHOT,
	CMD_ID_B_SHOT,
	CMD_ID_JAVELIN,
	CMD_ID_GEYSER,
	CMD_ID_SQUASH,
	CMD_ID_PHALANX,
	CMD_ID_HALBERD,
	CMD_ID_COMET,
	CMD_ID_GAUNTLET,
	CMD_ID_SNIPER,
	CMD_ID_DECOY,
	CMD_ID_MUMMY,
	CMD_ID_NUM
};

/*---------------------------------------------------------------------------*/

struct CMD_TABLE {
	void (*pfnAct)(void);
	UINT16	u16ActTime[3];
	float	fParam[ CMD_ID_NUM ];
};

/*---------------------------------------------------------------------------*/

class FRM_COMMAND
{
public: //! check modifier
	BOOL32		bInitCmd;
	BOOL32		bInitPhase[3];
	BOOL32		bLockCmd;
	BOOL32		bEndless;
	UINT8		u8Phase;
	BOOL32		bChangePhase;
	UINT8		u8NextPhase;
	UINT16		u16Counter;
	UINT16		u16ActTime[3];
	UINT8		u8ID;
	UINT8		u8NextID;
	FRM_OBJECT*	pfrm;
	UINT8		u8FrmType;

//	static CMD_TABLE ctb[ CMD_ID_NUM ][ FRM_TYPE_NUM ];
	static CMD_TABLE ctb[ FRM_TYPE_NUM ][ CMD_ID_NUM ];

	BOOL32		bCommon1;
	BOOL32		bCommon2;
	BOOL32		bCommon3;
	UINT8		u8Common1;
	UINT8		u8Common2;
	SINT32		s32Common1;
	SINT32		s32Common2;
	ALG_VECTOR	vecCommon1;
	ALG_VECTOR	vecCommon2;
	ALG_MATRIX	matCommon1;
	ALG_MATRIX	matCommon2;

public:
	void	Init( FRM_OBJECT* );
	void	Execute();
	SINT32	InitPhase( UINT8 );
	void	Set( UINT8 );
	void	Reset( UINT8 );
	void	Update();
	void	Lock();
	void	Unlock();
	void	SetPhase( UINT8 );
	void	SetCounter( UINT16 );
	UINT8	ID();
	UINT8	NextID();
	UINT8	Phase();
	UINT16	Counter();
	UINT16	Time();
	UINT16	ActTime( UINT8 );
	float*	GetParam();
	SINT32	GetParamNumber( UINT8 );
	float	GetParamFloat( UINT8 );
	UINT32	GetParamAddr( UINT8 );

	FRM_COMMAND();

	FRM_COMMAND& operator = ( const FRM_COMMAND& );
};

//=============================================================================
// Orbital Frame Camera
//=============================================================================

class FRM_CAMERA
{
public: //! check modifier
	ALG_MATRIX	matOrg;
	ALG_MATRIX	matCam;
	ALG_VECTOR	vecView;
	ALG_VECTOR	vecLook;
	float		fTransRate;
	float		fRotRate;
	float		fCamRate;

public:
	FRM_CAMERA( float, float, float, float, float, float, float, float, float );
	FRM_CAMERA();

	void Init( FRM_CAMERA*, ALG_MATRIX* );
	void Set( FRM_CAMERA* );
	void Move( ALG_MATRIX* );
	void Calc( ALG_MATRIX*, ALG_MATRIX* );

	FRM_CAMERA& operator = ( const FRM_CAMERA& );
};

//=============================================================================
// Orbital Frame GamePad Input
//=============================================================================

enum {
	PAD_UP     = 0x01,
	PAD_DOWN   = 0x02,
	PAD_DASH   = 0x04,
	PAD_ATTACK = 0x08,
	PAD_WEAPON = 0x10,
	PAD_GUARD  = 0x20,
	PAD_CAMERA = 0x40,
	PAD_LOCKON = 0x80
};

/*---------------------------------------------------------------------------*/

enum {
	PAD_UP_P,
	PAD_DOWN_P,
	PAD_DASH_P,
	PAD_ATTACK_P,
	PAD_WEAPON_P,
	PAD_GUARD_P,
	PAD_CAMERA_P,
	PAD_LOCKON_P,
	PAD_SELECT_P,
	FRM_PAD_NUM
};

/*---------------------------------------------------------------------------*/

class FRM_PAD
{
public: //! check modifier
	float	fX1, fY1;
	float	fX2, fY2;
	float	fStateX1, fStateY1;
	float	fStateX2, fStateY2;
	UINT32	u32State;
	UINT32	u32Last;
	UINT32	u32On;
	UINT32	u32Press;
	UINT32	u32Release;
	UINT8	u8Press[ FRM_PAD_NUM ];

public:
	FRM_PAD();

	void	Input();
	void	SetX1( float );
	void	SetY1( float );
	void	SetX2( float );
	void	SetY2( float );
	void	_SetButton( UINT32, UINT8, UINT8 );	// prefixed with '_' by HVS?
	void	_ResetButton( UINT32, UINT8 );		// prefixed with '_' by HVS?
	float	X1();
	float	Y1();
	float	X2();
	float	Y2();
	SINT32	On( UINT32 );
	SINT32	Press( UINT32 );
	SINT32	Release( UINT32 );
	UINT8	_Force( UINT8 );	// prefixed with '_' by HVS?
};

//=============================================================================
// Orbital Frame Custom Data
//=============================================================================

struct FRM_CUSTOM {
	BOOL32	bPadCtrl;
	BOOL32	bPlayer;
	BOOL32	bImmortal;
	UINT8	u8Type;
	UINT8	u8Mode;
	UINT8	u8Side;
	UINT8	u8Level;
	UINT8	u8Demo;
	UINT32	u32EndProc;
	float	fMaxArm;
	float	fArmor;
	float	fHzdRad;
	float	fTrgRad;
	float	fArmsOffset;
	float	fGrdWidth;
	float	fGrdDepth;
	float	fGrdRad;
	float	fGrdOffset;
	float	fMoveSpd;
	float	fUpSpd;
	float	fDownSpd;
	float	fMoveVel;
	float	fTurnRate;
	float	fLockRate1;
	float	fLockRate2;
};

//=============================================================================
// Orbital Frame Object
//=============================================================================

class FRM_OBJECT : public GV_ACTOR
{
public: //! check modifier
	UINT32			u32NameID;
	DG_OBJPTR		pobj;
	MT_MOTPTR		pmt;
	HZD_CAPSULE		hzc;
	TRG_OBJECT		trg;
	TRG_OBJECT		trgArms;
	TRG_OBJECT		trgGuard;
	ALG_MATRIX		matOrg;
	ALG_MATRIX		matAng;
	ALG_MATRIX		matScr;
	ALG_MATRIX		matNewScr;
	DG_CAMERA		cam;
	FRM_CAMERA		fcm;
	ALG_MATRIX		matCam;
	ALG_MATRIX		matOldCam;
	float			fSwCamRate;
	float			fSwCamSpd;
	float			fFixZoom;
	ALG_MATRIX		matFixCam;
	ALG_MATRIX		matRotCam;
	float			fHzdRate;
	ALG_MATRIX		matHzdCam;
	ALG_MATRIX		matAim;
	ALG_VECTOR		vecSpeed;
	float			fSpeed;
	float			fBstRate;
	ALG_VECTOR		vecDamage;
	BOOL32			bDestroy;
	BOOL32			bSubject;
	BOOL32			bLastSub;
	BOOL32			bPosture;
	BOOL32			bSearch;
	FRM_COMMAND		cmd;
	FRM_CUSTOM		cus;
	ENE_OBJECT		ene;
	FRM_PAD			pad;
	BOOL32			bNeutral;
	BOOL32			bLastNeutral;
	BOOL32			bNeutral2;
	ALG_MATRIX		matPad;
	float			fStickRate;
	ALG_MATRIX		matComp;
	float			fGravity;
	UINT8			u8GravUp;
	UINT8			u8GravDown;
	float			fLevRate;
	float			fAltitude;
	float			fLastAlt;
	float			fAltRate;
	float			fAltFree;
	BOOL32			bGround;
	float			fFootL;
	float			fFootR;
	float			fFloat;
	BOOL32			bGuard;
	UINT16			u16LotID;
	TRG_OBJECT*		ptrgLot;
	float			fLotDist;
	BOOL32			bInfight;
	float			fFixRate;
	float			fSpeedRate;
	UINT16			u16LabID;
	TRG_OBJECT*		ptrgLab;
	BOOL32			bLockOn;

//	static UINT8 u8FrameNode[ 41 ][ FRM_TYPE_NUM ];
	static UINT8 u8FrameNode[ FRM_TYPE_NUM ][ 41 ];

public:

	FRM_OBJECT( const FRM_OBJECT & );
	FRM_OBJECT( UINT32, ALG_MATRIX*, UINT8, UINT8, UINT8, UINT8, SINT32, UINT32, UINT8 );
	~FRM_OBJECT();

	void Act(); // override GV_ACTOR::Act()

	DG_MDL&		NodeMdl( UINT8 );
	ALG_MATRIX&	NodeMat( UINT8 );

	void ResetFrame();	// Reset Orbital Frame
	void ResetTrg();	// Reset Target

	void SetArms( UINT8, float, float );
	void ResetArms();

	void SetGuard();
	void ResetGuard();

	void GetState();
	void GetPosData();
	void GetLockOnData();
	void GetPadData();
	void SetPad();
	void SetPosition();
	void SetScreen();
	void CheckLockOn();
	void SearchLab();
	void CheckHazard();

	void SetCamera();
	void CalcFixCam();
	void CalcRotCam();
	void CalcHzdCam();

	void SetTarget();
	void SetModel();
	void TurnFrame();
	void MoveFrame();
	void TurnPad( float );
	void TurnLot( float );
	void InterpLot( ALG_VECTOR*, float, float );
	void TurnVec( ALG_VECTOR*, float );
	void CalcLotVec( ALG_VECTOR* );
	void MoveVec( ALG_VECTOR*, float, float );
	void CheckCommand();
	void CheckDamage();
	void GetDamage( float );
	void CheckHazardBack( float, float );
	float CalcHazardAng( ALG_VECTOR*, ALG_VECTOR*, float );
	int32 CheckTouch();
	void CheckCross();
	void SwitchCamera( UINT8 );
	void ResetMatrix( ALG_MATRIX* );
	void PlayVibration( UINT8 );

	// Do Actions
	void DoControl();
	void DoAction();		// defined here (libfrm.h)
	void DoDash();
	void DoArms();
	void DoGuard();
	void DoHold();
	void DoHeld();			// defined here (libfrm.h)
	void DoCross();
	void DoDamage();
	void DoBump();
	void DoBlast();
	void DoDecoy();
	void DoJehShot();		// Jehuty Shot
	void DoJehLaser();		// Jehuty Laser
	void DoJehCannon();		// Jehuty Cannon
	void DoJavelin();
	void DoGeyser();
	void DoBounder();
	void DoPhalanx();
	void DoHalberd();
	void DoComet();
	void DoGauntlet();
	void DoSniper();
	void DoMumShell();
	void DoFlySqrShot();
	void DoFlySqrDShot();
	void DoFlySqrBShot();
	void DoRebSqrShot();
	void DoRebSqrDShot();
	void DoRebSqrBShot();

	static DG_LIGHT		lightPlayer;
	static DG_LIGHT		lightPlayerBack;

	static DG_LIGHT*	LockPlayerLight();
	static void			UnlockPlayerLight( DG_LIGHT* );

	FRM_OBJECT& operator = ( const FRM_OBJECT& );
};

#endif /* END OF FILE */
