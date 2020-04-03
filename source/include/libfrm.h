/*
 * Oribital Frame Library
 * Global Include
 */
/* ver."ZONE OF THE ENDERS"
 */
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

/*---------------------------------------------------------------------------*
 * Common Defines
 *---------------------------------------------------------------------------*/

// ref.default.pdb
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

// ref.default.pdb
enum {
	FRM_DEMO_NORMAL,
	FRM_DEMO_PLAY,
	FRM_DEMO_EDIT
};

// ref.default.pdb
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

// ref.default.pdb
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

// ref.default.pdb
enum {
	FRM_TYPE_JEHUTY,
	FRM_TYPE_RAPTOR,
	FRM_TYPE_MUMMY,
	FRM_TYPE_CYCLOPS,
	FRM_TYPE_NEITH1,
	FRM_TYPE_NEITH2,
	FRM_TYPE_NUM
};

// ref.default.pdb
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

// ref.default.pdb
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

// ref.default.pdb
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

// ref.default.pdb
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

// ref.default.pdb
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

/*---------------------------------------------------------------------------*
 * Common Structures
 *---------------------------------------------------------------------------*/

// ref.default.pdb
struct CMD_TABLE {
	void (*pfnAct)(void); // TODO: ret/arg types
	uint16  u16ActTime[3];
	float   fParam[32];
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
struct FRM_CUSTOM {
	bool32  bPadCtrl;
	bool32  bPlayer;
	bool32  bImmortal;
	uint8   u8Type;
	uint8   u8Mode;
	uint8   u8Side;
	uint8   u8Level;
	uint8   u8Demo;
	uint32  u32EndProc;
	float   fMaxArm;
	float   fArmor;
	float   fHzdRad;
	float   fTrgRad;
	float   fArmsOffset;
	float   fGrdWidth;
	float   fGrdDepth;
	float   fGrdRad;
	float   fGrdOffset;
	float   fMoveSpd;
	float   fUpSpd;
	float   fDownSpd;
	float   fMoveVel;
	float   fTurnRate;
	float   fLockRate1;
	float   fLockRate2;
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class FRM_CAMERA
{
public: //! check modifier
	ALG_MATRIX  matOrg;
	ALG_MATRIX  matCam;
	ALG_VECTOR  vecView;
	ALG_VECTOR  vecLook;
	float       fTransRate;
	float       fRotRate;
	float       fCamRate;

public:
	FRM_CAMERA(float, float, float, float, float, float, float, float, float);
	FRM_CAMERA();

	void Init(FRM_CAMERA*, ALG_MATRIX*);
	void Set(FRM_CAMERA*);
	void Move(ALG_MATRIX*);
	void Calc(ALG_MATRIX*, ALG_MATRIX*);

	FRM_CAMERA& operator=(const FRM_CAMERA&);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class FRM_COMMAND
{
public: //! check modifier
	bool32      bInitCmd;
	bool32      bInitPhase[3];
	bool32      bLockCmd;
	bool32      bEndless;
	uint8       u8Phase;
	bool32      bChangePhase;
	uint8       u8NextPhase;
	uint16      u16Counter;
	uint16      u16ActTime[3];
	uint8       u8ID;
	uint8       u8NextID;
	FRM_OBJECT* pfrm;
	uint8       u8FrmType;

	static CMD_TABLE ctb[32][6];

	bool32      bCommon1;
	bool32      bCommon2;
	bool32      bCommon3;
	uint8       u8Common1;
	uint8       u8Common2;
	sint32      s32Common1;
	sint32      s32Common2;
	ALG_VECTOR  vecCommon1;
	ALG_VECTOR  vecCommon2;
	ALG_MATRIX  matCommon1;
	ALG_MATRIX  matCommon2;

public:
	void        Init(FRM_OBJECT*);
	void        Execute();
	sint32      InitPhase(uint8);
	void        Set(uint8);
	void        Reset(uint8);
	void        Update();
	void        Lock();
	void        Unlock();
	void        SetPhase(uint8);
	void        SetCounter(uint16);
	uint8       ID();
	uint8       NextID();
	uint8       Phase();
	uint16      Counter();
	uint16      Time();
	uint16      ActTime(uint8);
	float*      GetParam();
	sint32      GetParamNumber(uint8);
	float       GetParamFloat(uint8);
	uint32      GetParamAddr(uint8);

	FRM_COMMAND();

	FRM_COMMAND& operator=(const FRM_COMMAND&);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class FRM_PAD
{
public: //! check modifier
	float   fX1;
	float   fY1;
	float   fX2;
	float   fY2;
	float   fStateX1;
	float   fStateY1;
	float   fStateX2;
	float   fStateY2;
	uint32  u32State;
	uint32  u32Last;
	uint32  u32On;
	uint32  u32Press;
	uint32  u32Release;
	uint8   u8Press[9];

public:
	FRM_PAD();

	void    Input();
	void    SetX1(float);
	void    SetY1(float);
	void    SetX2(float);
	void    SetY2(float);
	void    _SetButton(uint32, uint8, uint8);
	void    _ResetButton(uint32, uint8);
	float   X1();
	float   Y1();
	float   X2();
	float   Y2();
	sint32  On(uint32);
	sint32  Press(uint32);
	sint32  Release(uint32);
	uint8   _Force(uint8);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class FRM_OBJECT : public GV_ACTOR //! check modifier
{
public: //! check modifier
	uint32      u32NameID;
	DG_OBJPTR   pobj;
	MT_MOTPTR   pmt;
	HZD_CAPSULE hzc;
	TRG_OBJECT  trg;
	TRG_OBJECT  trgArms;
	TRG_OBJECT  trgGuard;
	ALG_MATRIX  matOrg;
	ALG_MATRIX  matAng;
	ALG_MATRIX  matScr;
	ALG_MATRIX  matNewScr;
	DG_CAMERA   cam;
	FRM_CAMERA  fcm;
	ALG_MATRIX  matCam;
	ALG_MATRIX  matOldCam;
	float       fSwCamRate;
	float       fSwCamSpd;
	float       fFixZoom;
	ALG_MATRIX  matFixCam;
	ALG_MATRIX  matRotCam;
	float       fHzdRate;
	ALG_MATRIX  matHzdCam;
	ALG_MATRIX  matAim;
	ALG_VECTOR  vecSpeed;
	float       fSpeed;
	float       fBstRate;
	ALG_VECTOR  vecDamage;
	bool32      bDestroy;
	bool32      bSubject;
	bool32      bLastSub;
	bool32      bPosture;
	bool32      bSearch;
	FRM_COMMAND cmd;
	FRM_CUSTOM  cus;
	ENE_OBJECT  ene;
	FRM_PAD     pad;
	bool32      bNeutral;
	bool32      bLastNeutral;
	bool32      bNeutral2;
	ALG_MATRIX  matPad;
	float       fStickRate;
	ALG_MATRIX  matComp;
	float       fGravity;
	uint8       u8GravUp;
	uint8       u8GravDown;
	float       fLevRate;
	float       fAltitude;
	float       fLastAlt;
	float       fAltRate;
	float       fAltFree;
	bool32      bGround;
	float       fFootL;
	float       fFootR;
	float       fFloat;
	bool32      bGuard;
	uint16      u16LotID;
	TRG_OBJECT* ptrgLot;
	float       fLotDist;
	bool32      bInfight;
	float       fFixRate;
	float       fSpeedRate;
	uint16      u16LabID;
	TRG_OBJECT* ptrgLab;
	bool32      bLockOn;

	static uint8 u8FrameNode[41][6];

public:
	FRM_OBJECT(const FRM_OBJECT &);
	FRM_OBJECT(uint32, ALG_MATRIX*, uint8, uint8, uint8, uint8, sint32, uint32, uint8);
	~FRM_OBJECT();

	void Act(); // override GV_ACTOR::Act()

	DG_MDL&     NodeMdl(uint8);
	ALG_MATRIX& NodeMat(uint8);
	void        ResetFrame();
	void        ResetTrg();
	void        SetArms(uint8, float, float);
	void        ResetArms();
	void        SetGuard();
	void        ResetGuard();
	void        GetState();
	void        GetPosData();
	void        GetLockOnData();
	void        GetPadData();
	void        SetPad();
	void        SetPosition();
	void        SetScreen();
	void        CheckLockOn();
	void        SearchLab();
	void        CheckHazard();
	void        SetCamera();
	void        CalcFixCam();
	void        CalcRotCam();
	void        CalcHzdCam();
	void        SetTarget();
	void        SetModel();
	void        TurnFrame();
	void        MoveFrame();
	void        TurnPad(float);
	void        TurnLot(float);
	void        InterpLot(ALG_VECTOR*, float, float);
	void        TurnVec(ALG_VECTOR*, float);
	void        CalcLotVec(ALG_VECTOR*);
	void        MoveVec(ALG_VECTOR*, float, float);
	void        CheckCommand();
	void        CheckDamage();
	void        GetDamage(float);
	void        CheckHazardBack(float, float);
	float       CalcHazardAng(ALG_VECTOR*, ALG_VECTOR*, float);
	sint32      CheckTouch();
	void        CheckCross();
	void        SwitchCamera(uint8);
	void        ResetMatrix(ALG_MATRIX*);
	void        PlayVibration(uint8);
	void        DoControl();
	void        DoAction();
	void        DoDash();
	void        DoArms();
	void        DoGuard();
	void        DoHold();
	void        DoHeld();
	void        DoCross();
	void        DoDamage();
	void        DoBump();
	void        DoBlast();
	void        DoDecoy();
	void        DoJehShot();
	void        DoJehLaser();
	void        DoJehCannon();
	void        DoJavelin();
	void        DoGeyser();
	void        DoBounder();
	void        DoPhalanx();
	void        DoHalberd();
	void        DoComet();
	void        DoGauntlet();
	void        DoSniper();
	void        DoMumShell();
	void        DoFlySqrShot();
	void        DoFlySqrDShot();
	void        DoFlySqrBShot();
	void        DoRebSqrShot();
	void        DoRebSqrDShot();
	void        DoRebSqrBShot();

	static DG_LIGHT     lightPlayer;
	static DG_LIGHT     lightPlayerBack;
	static DG_LIGHT*    LockPlayerLight;
	static void         UnlockPlayerLight(DG_LIGHT*);

	FRM_OBJECT& operator=(const FRM_OBJECT&);
};

#endif /* END OF FILE */
