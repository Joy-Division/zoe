#ifndef INCLUDED_LIBGV_H
#define INCLUDED_LIBGV_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

// internal
struct GV_LIST;
struct GV_MSG_DATA;
struct GV_PAD_ONE;

class GV_ACTOR;
class GV_DAEMON;
class GV_MEMORY;
class GV_MESSAGE;
class GV_PAD;

//=============================================================================
// GV Common Defines
//=============================================================================

enum {
	GV_KILL_SYSTEM = 0x01,
	GV_KILL_LOAD   = 0x02,
	GV_KILL_STAGE  = 0x03,
	GV_KILL_DEMO   = 0x04,
	GV_KILL_MEMORY = 0x80,
	GV_KILL_STAGE2 = 0x83,
	GV_KILL_DEMO2  = 0x84
};

enum {
	GV_KILLSTATE_NOTHING,
	GV_KILLSTATE_READY,
	GV_KILLSTATE_REQUEST
};

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

enum {
	GV_PAUSE_NOSTOP,
	GV_PAUSE_STOP,
	GV_PAUSE_RDERR
};

enum {
	GV_TYPE_DYNAMIC,
	GV_TYPE_STATIC
};

//=============================================================================
// GV Actor (actor.cc)
//=============================================================================

struct GV_LIST {
	UINT8		u8Pause;
	GV_ACTOR*	pactStart;
	GV_ACTOR*	pactEnd;
};

/*---------------------------------------------------------------------------*/

class GV_ACTOR
{
	/* VTable */

public: //! check modifier
	UINT8		u8Level;
	UINT8		u8Type;
	UINT8		u8Kill;
	UINT8		u8KillState;
	GV_ACTOR*	pactPrev;
	GV_ACTOR*	pactNext;

	static UINT8	u8Pause;
	static UINT8	u8NextPause;
	static UINT8	u8NextCancelPause;
	static SINT8	s8ReqKill;
	static UINT32	u32Time;
	static GV_LIST	list[9];

private:
	void AddActor();
	void InsertActor();
	void DeleteActor();

	static void KillExec();

public: //! check modifier
	UINT32 s32SoundEmitter;

	static float fEffect_Accum;

public:
	GV_ACTOR( const GV_ACTOR& );
	GV_ACTOR( UINT8, UINT8, UINT8 );
	~GV_ACTOR();

	virtual void Act(); //! check VTable

	void	SetActor();
	void	DestroyQuick();
	void	Destroy();
	void	ResetDestroy();
	int32	CheckDestroy();
	void	SetKillLevel(UINT8);

	static void		StartDaemon();
	static void		Execute();
	static void		Pause(UINT32);
	static void		CancelPause(UINT32);
	static void		Kill(UINT8);
	static void		Kill2();
//	static void		HVS_KillAll();
	static void		Update();
	static UINT8	PauseAtt();
	static UINT8	NextPauseAtt();
	static UINT8	NextCancelPauseAtt();
	static UINT32	Time();
	static float	GetEffectScale();

	GV_ACTOR& operator = ( const GV_ACTOR& );
};

//=============================================================================
// GV Daemon (gvd.cc)
//=============================================================================

class GV_DAEMON : public GV_ACTOR
{
public:
	GV_DAEMON( const GV_DAEMON& );
	GV_DAEMON();

	void Act(); // override GV_ACTOR::Act()

	~GV_DAEMON();

	GV_DAEMON& operator = ( const GV_DAEMON& );
};

//=============================================================================
// GV Memory (memory.cc)
//=============================================================================

enum {
	MEM_FREE_INSTANT,
	MEM_FREE_FRAME_1,
	MEM_FREE_FRAME_2,
	MEM_FREE_NUM
};

enum {
	MEM_MODE_NORMAL,
	MEM_MODE_INVERSE
};

enum {
	MEM_TYPE_NORMAL,
	MEM_TYPE_RESIDENT,
	MEM_TYPE_NONRESID,
	MEM_TYPE_RESIDENT2
};

/*---------------------------------------------------------------------------*/

class GV_MEMORY
{
public: //! check modifier
	UINT8		u8Type;
	UINT8		u8State;
	UINT8		u8Mode;
	UINT32		u32Size;
	GV_MEMORY*	pmemPrev;
	GV_MEMORY*	pmemNext;
	GV_MEMORY*	pmemFreePrev;
	GV_MEMORY*	pmemFreeNext;

	static UINT8		u8FreeType;
	static UINT32		u32MaxFreeSize;
	static GV_MEMORY*	pmemList;
	static GV_MEMORY*	pmemFreeList;
	static GV_MEMORY*	pmemVoidList[3];
	static GV_MEMORY*	pmemListResident;
	static GV_MEMORY*	pmemListNonResident;
	static UINT8		u8ModeNonResident;

public:
	static void		InitSystem();
	static void		DestroySystem();
	static void*	Alloc( UINT32, UINT8 );	// "_Alloc" in default.pdb
	static void*	Alloc( UINT32 );		// "_Alloc" in default.pdb
	static void		Free( void* );
	static void		Update( UINT8 );
//	static void		SetFreeType( UINT8 );
//	static UINT8	nGetFreeType();
	static void		SwitchNonResidentMode();
	static void		FreePrevMemory();
	static void		FreeCurrentMemory();
	static void		CheckMaxFreeSize();
	static int32	CheckMemoryLack();
	static int32	CheckSync();
	static UINT8	GetType( void* );
	static UINT32	GetSize( void* );

// *** HVS addition ***
//	static UINT32	nGetHVSAllocType( UINT8 );
//	static UINT32	nGetHVSNonResidentModeCurrent();
//	static UINT32	nGetHVSNonResidentModePrevious();
};

//=============================================================================
// GV Message (message.cc)
//=============================================================================

struct GV_MSG_DATA {
	UINT8	u8Type;
	UINT32	u32Data;
};

enum {
	MSG_TYPE_NUMBER,
	MSG_TYPE_FLOAT,
	MSG_TYPE_ADDR,
	MSG_TYPE_STRING
};

/*---------------------------------------------------------------------------*/

class GV_MESSAGE
{
public: //! check modifier
	UINT32		u32ID;
	UINT8		u8ArgNum;
	BOOL32		bReceive;
	GV_MESSAGE*	pmsgPrev;
	GV_MESSAGE*	pmsgNext;
	GV_MSG_DATA	msd[16];

	static GV_MESSAGE* pmsgList;
	static GV_MESSAGE* pmsgCursor;

public:
	GV_MESSAGE( UINT32 );
	~GV_MESSAGE();

	void	SetNumber( int32 );
	void	SetFloat( float );
	void	SetAddr( void* );
	void	SetString( char* );
	int32	GetNumber( UINT8 );
	float	GetFloat( UINT8 );
	void*	GetAddr( UINT8 );
	char*	GetString( UINT8 );

	static void			Update();
	static GV_MESSAGE*	Send( UINT32 );
	static void			Reset();
	static GV_MESSAGE*	Receive( UINT32 );
};

//=============================================================================
// GV Pad (pad.cc)
//=============================================================================

enum {
	PAD_UDLR	= 0x000000F0,
	PAD_ABXY	= 0xFFFFF000,	// Xbox
	PAD_LR		= 0x00000F00,
	PAD_U		= 0x00000010,
	PAD_D		= 0x00000040,
	PAD_L		= 0x00000080,
	PAD_R		= 0x00000020,
	PAD_A		= 0x00002000,	// Xbox
	PAD_B		= 0x00004000,	// Xbox
	PAD_X		= 0x00001000,	// Xbox
	PAD_Y		= 0xFFFF8000,	// Xbox
	PAD_L1		= 0x00000400,
	PAD_R1		= 0x00000800,
	PAD_L2		= 0x00000100,
	PAD_R2		= 0x00000200,
	PAD_STA		= 0x00000008,
	PAD_SEL		= 0x00000001,
	PAD_AL		= 0x00000002,	// PlayStation L3
	PAD_AR		= 0x00000004	// PlayStation R3
};

enum {
	PAD_R_P,
	PAD_L_P,
	PAD_U_P,
	PAD_D_P,
	PAD_X_P,	// Xbox
	PAD_A_P,	// Xbox
	PAD_B_P,	// Xbox
	PAD_Y_P,	// Xbox
	PAD_L1_P,
	PAD_R1_P,
	PAD_L2_P,
	PAD_R2_P,
	NUM_PRESS
};

enum {
	PAD_VIB_HIGH,
	PAD_VIB_LOW
};

/*---------------------------------------------------------------------------*/

struct GV_PAD_ONE
{
// This class has been modified by HVS to reference the Xbox 360 pad.
// Examine this class during decompilation and change member names to
// reference the DualShock 2.

	UINT8	u8State;
	UINT8	u8IDLen;
	UINT16	u16Button;
	UINT8	u8RightX;
	UINT8	u8RightY;
	UINT8	u8LeftX;
	UINT8	u8LeftY;
	UINT8	u8PressR;
	UINT8	u8PressL;
	UINT8	u8PressU;
	UINT8	u8PressD;
	UINT8	u8PressX;	// Xbox-specific
	UINT8	u8PressA;	// Xbox-specific
	UINT8	u8PressB;	// Xbox-specific
	UINT8	u8PressY;	// Xbox-specific
	UINT8	u8PressL1;
	UINT8	u8PressR1;
	UINT8	u8PressL2;
	UINT8	u8PressR2;
	UINT32	pad0;
	UINT64	pad1;
};

/*---------------------------------------------------------------------------*/

class GV_PAD
{
// Examine this class during decompilation.
// It appares that HVS has modified it somewhat.

public: //! check modifier
	UINT128	u128buf[4];
	SINT8	s8X1;
	SINT8	s8Y1;
	SINT8	s8X2;
	SINT8	s8Y2;
	UINT8	u8Press[12];
	UINT8	u8PressCount[12];
	UINT16	u16State;
	UINT16	u16Last;
	UINT16	u16On;
	UINT16	u16Press;
	UINT16	u16Release;
	UINT16	u16State2;
	UINT16	u16Last2;
	UINT16	u16On2;
	UINT16	u16Press2;
	UINT16	u16Release2;
	UINT8	u8Phase;
	UINT8	u8Kind;
	UINT8	u8ActDirect[6];
	BOOL8	bActChange;

	static UINT32 nCurrentSecondaryPort;

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
	void Read( int );

	static void Update();

	SINT8	X1();
	SINT8	Y1();
	SINT8	X2();
	SINT8	Y2();
	UINT16	On();
	int32	On( UINT16 );
	UINT16	Press();
	int32	Press( UINT16 );
	UINT16	Release();
	int32	Release( UINT16 );
	UINT16	On2();
	int32	On2( UINT16 );
	UINT16	Press2();
	int32	Press2( UINT16 );
	UINT16	Release2();
	int32	Release2( UINT16 );
	UINT8	_Force( UINT16 );		// "_" added by HVS?
	void	SetAct( int32, UINT8 );

	static void	ResetCurrentSecondaryPort();
	static int	nGetCurrentSecondaryPort(); // HVS?

public: //! check modifier

// *** HVS addition ***
//	bool	mbPressureSensitive;
//	bool	mbSensorSupported;
//	bool	mbSupportsVibration;
//	int		mbActive;
//	bool	mbYAxisInvert;
//	bool	mbVibration;

// *** HVS addition ***
//	UINT32			m_nLastFrame;
//	bool			m_bReassigned;
//	bool			m_bSemiReassigned;
//	bool			m_bConnected;
//	_XINPUT_STATE	m_oPadState;
	GV_PAD_ONE		padone;
};

//=============================================================================
// Global Functions
//=============================================================================

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
