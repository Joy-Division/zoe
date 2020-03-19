/*
 * LibGV for PS2
 * Global Include
 */
/* ver."ZONE OF THE ENDERS"
 */
#ifndef INCLUDED_LIBGV_H
#define INCLUDED_LIBGV_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

/*---------------------------------------------------------------------------*
 * Common Defines
 *---------------------------------------------------------------------------*/

// ref.default.pdb
enum {
	GV_KILL_SYSTEM = 0x01,
	GV_KILL_LOAD   = 0x02,
	GV_KILL_STAGE  = 0x03,
	GV_KILL_DEMO   = 0x04,
	GV_KILL_MEMORY = 0x80,
	GV_KILL_STAGE2 = 0x83,
	GV_KILL_DEMO2  = 0x84
};

// ref.default.pdb
enum {
	GV_KILLSTATE_NOTHING,
	GV_KILLSTATE_READY,
	GV_KILLSTATE_REQUEST
};

// ref.default.pdb
enum {
	GV_LEVEL_DAEMON1,
	GV_LEVEL_MANAGER,
	GV_LEVEL_ASSIST,
	GV_LEVEL_PREPARE,
	GV_LEVEL_ACTOR,
	GV_LEVEL_MODIFY,
	GV_LEVEL_REFER,
	GV_LEVEL_PAUSE,
	GV_LEVEL_DAEMON2,
	GV_LEVEL_NUM
};

// ref.default.pdb
enum {
	GV_PAUSE_NOSTOP,
	GV_PAUSE_STOP,
	GV_PAUSE_RDERR
};

// ref.default.pdb
enum {
	GV_TYPE_DYNAMIC,
	GV_TYPE_STATIC
};

/*---------------------------------------------------------------------------*
 * Common Structures
 *---------------------------------------------------------------------------*/

// ref.default.pdb
typedef struct GV_LIST {
	uint8       u8Pause;
	GV_ACTOR*   pactStart;
	GV_ACTOR*   pactEnd;
} GV_LIST;

/*---------------------------------------------------------------------------*
 * GV Actor (actor.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class GV_ACTOR
{
	/* VTable */
	
public: //! unconfirmed modifier
	uint8       u8Level;
	uint8       u8Type;
	uint8       u8Kill;
	uint8       u8KillState;
	GV_ACTOR*   pactPrev;
	GV_ACTOR*   pactNext;
	
	static uint8    u8Pause;
	static uint8    u8NextPause;
	static uint8    u8NextCancelPause;
	static sint8    s8ReqKill;
	static uint32   u32Time;
	static GV_LIST  list[9];
	
private:
	void AddActor();
	void InsertActor();
	void DeleteActor();
	
	static void KillExec();
	
public: //! unconfirmed modifier
	uint32 s32SoundEmitter;
	
	static float fEffect_Accum;
	
public:
	GV_ACTOR(const GV_ACTOR&);
	GV_ACTOR(uint8, uint8, uint8);
	~GV_ACTOR();
	
	void    Act();
	void    SetActor();
	void    DestroyQuick();
	void    Destroy();
	void    ResetDestroy();
	sint32  CheckDestroy();
	void    SetKillLevel(uint8);
	
	static void     StartDaemon();
	static void     Execute();
	static void     Pause(uint32);
	static void     CancelPause(uint32);
	static void     Kill(uint8);
	static void     Kill2();
//	static void     HVS_KillAll();
	static void     Update();
	static uint8    PauseAtt();
	static uint8    NextPauseAtt();
	static uint8    NextCancelPauseAtt();
	static uint32   Time();
	static float    GetEffectScale();
	
	GV_ACTOR& operator=(const GV_ACTOR&);
};

/*---------------------------------------------------------------------------*
 * GV Daemon (gvd.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class GV_DAEMON:
  public GV_ACTOR //! unconfirmed modifier
{
public:
	GV_DAEMON(const GV_DAEMON&);
	GV_DAEMON();
	
	void Act();
	
	~GV_DAEMON();
	
	GV_DAEMON& operator=(const GV_DAEMON&);
};

/*---------------------------------------------------------------------------*
 * GV Memory (memory.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
enum {
	MEM_FREE_INSTANT,
	MEM_FREE_FRAME_1,
	MEM_FREE_FRAME_2,
	MEM_FREE_NUM
};

// ref.default.pdb
enum {
	MEM_MODE_NORMAL,
	MEM_MODE_INVERSE
};

// ref.default.pdb
enum {
	MEM_TYPE_NORMAL,
	MEM_TYPE_RESIDENT,
	MEM_TYPE_NONRESID,
	MEM_TYPE_RESIDENT2
};

// ref.default.pdb
class GV_MEMORY
{
public: //! unconfirmed modifier
	uint8       u8Type;
	uint8       u8State;
	uint8       u8Mode;
	uint32      u32Size;
	GV_MEMORY*  pmemPrev;
	GV_MEMORY*  pmemNext;
	GV_MEMORY*  pmemFreePrev;
	GV_MEMORY*  pmemFreeNext;
	
	static uint8        u8FreeType;
	static uint32       u32MaxFreeSize;
	static GV_MEMORY*   pmemList;
	static GV_MEMORY*   pmemFreeList;
	static GV_MEMORY*   pmemVoidList[3];
	static GV_MEMORY*   pmemListResident;
	static GV_MEMORY*   pmemListNonResident;
	static uint8        u8ModeNonResident;

public:
	static void     InitSystem();
	static void     DestroySystem();
	static void*    Alloc(uint32, uint8); // "_Alloc" in default.pdb
	static void*    Alloc(uint32);        // "_Alloc" in default.pdb
	static void     Free(void*);
	static void     Update(uint8);
//	static void     SetFreeType(uint8);
//	static uint8    nGetFreeType();
	static void     SwitchNonResidentMode();
	static void     FreePrevMemory();
	static void     FreeCurrentMemory();
	static void     CheckMaxFreeSize();
	static sint32   CheckMemoryLack();
	static sint32   CheckSync();
	static uint8    GetType(void*);
	static uint32   GetSize(void*);

// *** HVS addition ***
//	static uint32   nGetHVSAllocType(uint8);
//	static uint32   nGetHVSNonResidentModeCurrent();
//	static uint32   nGetHVSNonResidentModePrevious();
};

/*---------------------------------------------------------------------------*
 * GV Message (message.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
typedef struct GV_MSG_DATA {
	uint8   u8Type;
	uint32  u32Data;
} GV_MSG_DATA;

// ref.default.pdb
enum {
	MSG_TYPE_NUMBER,
	MSG_TYPE_FLOAT,
	MSG_TYPE_ADDR,
	MSG_TYPE_STRING
};

// ref.default.pdb
class GV_MESSAGE
{
public: //! unconfirmed modifier
	uint32      u32ID;
	uint8       u8ArgNum;
	bool32      bReceive;
	GV_MESSAGE* pmsgPrev;
	GV_MESSAGE* pmsgNext;
	GV_MSG_DATA msd[16];
	
	static GV_MESSAGE* pmsgList;
	static GV_MESSAGE* pmsgCursor;

public:
	GV_MESSAGE(uint32);
	~GV_MESSAGE();
	
	void    SetNumber(sint32);
	void    SetFloat(float);
	void    SetAddr(void*);
	void    SetString(char*);
	sint32  GetNumber(uint8);
	float   GetFloat(uint8);
	void*   GetAddr(uint8);
	char*   GetString(uint8);
	
	static void         Update();
	static GV_MESSAGE*  Send(uint32);
	static void         Reset();
	static GV_MESSAGE*  Receive(uint32);
};

/*---------------------------------------------------------------------------*
/* GV Pad (pad.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
enum {
	PAD_UDLR = 0x000000F0,
	PAD_ABXY = 0xFFFFF000, // Xbox-specific
	PAD_LR   = 0x00000F00,
	PAD_U    = 0x00000010,
	PAD_D    = 0x00000040,
	PAD_L    = 0x00000080,
	PAD_R    = 0x00000020,
	PAD_A    = 0x00002000, // Xbox-specific
	PAD_B    = 0x00004000, // Xbox-specific
	PAD_X    = 0x00001000, // Xbox-specific
	PAD_Y    = 0xFFFF8000, // Xbox-specific
	PAD_L1   = 0x00000400,
	PAD_R1   = 0x00000800,
	PAD_L2   = 0x00000100,
	PAD_R2   = 0x00000200,
	PAD_STA  = 0x00000008,
	PAD_SEL  = 0x00000001,
	PAD_AL   = 0x00000002, // PlayStation L3
	PAD_AR   = 0x00000004  // PlayStation R3
};

// ref.default.pdb
enum {
	PAD_R_P,
	PAD_L_P,
	PAD_U_P,
	PAD_D_P,
	PAD_X_P, // Xbox-specific
	PAD_A_P, // Xbox-specific
	PAD_B_P, // Xbox-specific
	PAD_Y_P, // Xbox-specific
	PAD_L1_P,
	PAD_R1_P,
	PAD_L2_P,
	PAD_R2_P,
	NUM_PRESS
};

// ref.default.pdb
enum {
	PAD_VIB_HIGH,
	PAD_VIB_LOW
};

// ref.default.pdb
typedef struct GV_PAD_ONE {

// This class has been modified by HVS to reference the Xbox 360 pad.
// Examine this class during decompilation and change member names to
// reference the DualShock 2.
	
	uint8   u8State;
	uint8   u8IDLen;
	uint16  u16Button;
	uint8   u8RightX;
	uint8   u8RightY;
	uint8   u8LeftX;
	uint8   u8LeftY;
	uint8   u8PressR;
	uint8   u8PressL;
	uint8   u8PressU;
	uint8   u8PressD;
	uint8   u8PressX; // Xbox-specific
	uint8   u8PressA; // Xbox-specific
	uint8   u8PressB; // Xbox-specific
	uint8   u8PressY; // Xbox-specific
	uint8   u8PressL1;
	uint8   u8PressR1;
	uint8   u8PressL2;
	uint8   u8PressR2;
	uint32  pad0;
	uint64  pad1;
} GV_PAD_ONE;

// ref.default.pdb
class GV_PAD
{
// Examine this class during decompilation.
// It appares that HVS has modified it somewhat.
	
public: //! unconfirmed modifier
	uint128 u128buf[4];
	sint8   s8X1;
	sint8   s8Y1;
	sint8   s8X2;
	sint8   s8Y2;
	uint8   u8Press[12];
	uint8   u8PressCount[12];
	uint16  u16State;
	uint16  u16Last;
	uint16  u16On;
	uint16  u16Press;
	uint16  u16Release;
	uint16  u16State2;
	uint16  u16Last2;
	uint16  u16On2;
	uint16  u16Press2;
	uint16  u16Release2;
	uint8   u8Phase;
	uint8   u8Kind;
	uint8   u8ActDirect[6];
	bool8   bActChange;
	
	static uint32 nCurrentSecondaryPort;
	
	enum {
		PH_INIT,
		PH_SETDIGIT,
		PH_SETMAIN,
		PH_SETMAIN2,
		PH_ALIGN,
		PH_ALIGN2,
		PH_ENTERPRESS,
		PH_NORMAL,
		PH_ACTRESET
	};

public:
	static void InitPad();
	
	void Reset();
	void Read(int);
	
	static void Update();
	
	sint8   X1();
	sint8   Y1();
	sint8   X2();
	sint8   Y2();
	uint16  On();
	sint32  On(uint16);
	uint16  Press();
	sint32  Press(uint16);
	uint16  Release();
	sint32  Release(uint16);
	uint16  On2();
	sint32  On2(uint16);
	uint16  Press2();
	sint32  Press2(uint16);
	uint16  Release2();
	sint32  Release2(uint16);
	uint8   _Force(uint16);
	void    SetAct(sint32, uint8);
	
	static void     ResetCurrentSecondaryPort();
	static sint32   nGetCurrentSecondaryPort(); // HVS?

public: //! unconfirmed modifier
	bool            mbPressureSensitive;
	bool            mbSensorSupported;
	bool            mbSupportsVibration;
	int             mbActive;
	bool            mbYAxisInvert;
	bool            mbVibration;

// *** HVS addition ***
//	uint32          m_nLastFrame;
//	bool            m_bReassigned;
//	bool            m_bSemiReassigned;
//	bool            m_bConnected;
//	_XINPUT_STATE   m_oPadState;
	GV_PAD_ONE      padone;
};

/*---------------------------------------------------------------------------*
 * Prototypes
 *---------------------------------------------------------------------------*/

// GV_InitSystem() is defined here according to the .mdebug section.
// It was not inlined by the compiler, and is marked as an exported
// function (i.e. not static/private).
#ifdef IN_MAIN_CC
void GV_InitSystem()
{
	GV_MEMORY::InitSystem();
	GV_ACTOR::StartDaemon();
}
#endif

#endif /* END OF FILE */
