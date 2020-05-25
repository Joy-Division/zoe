#ifndef INCLUDED_LIBSCN_H
#define INCLUDED_LIBSCN_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

// internal
struct SCN_EXFUNC;
struct SCN_GBVAR;
struct SCN_STACK;

class SCN_DATA;
class SCN_THREAD;
class SCN_SYSTEM;

//=============================================================================
// SCN Common Defines
//=============================================================================

// ref.default.pdb
enum {
	SCN_STATE_WAKEUP,
	SCN_STATE_SLEEP,
	SCN_STATE_INTERRUPT,
	SCN_STATE_COMPLETE
};

//=============================================================================
// SCN Basic Data Type
//=============================================================================

// ref.default.pdb
class SCN_DATA
{
public: //! check modifier
	uint8 u8Code[5];

public:
	uint8		VarType();
	int32		CheckEnd();
	void		SetNumber( int32 );
	void		SetFloat( float );
	int32		GetNumber();
	float		GetFloat();
	uint32		GetAddr();
	SCN_DATA*	GetData();
	char*		GetString();
};

//=============================================================================
// SCN Thread
//=============================================================================

// ref.default.pdb
typedef struct SCN_STACK {
	uint8 u8Code[5];
} SCN_STACK;

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class SCN_THREAD
{
public: //! check modifier
	uint8 u8State;

private:
	void	Execute();
	void	PushCode( uint8* );
	void	PopCode( uint8* );
	void	PushNumber( int32 );
	int32	PopNumber();
	void	PushFloat( float );
	float	PopFloat();
	void	PushAddr( uint32 );
	uint32	PopAddr();

	static uint32		Read( uint8* );
	static void			Write( uint8*, uint32 );
	static void			SetNumber( uint8*, int32 );
	static void			SetFloat( uint8*, float );
	static int32		GetNumber( uint8* );
	static float		GetFloat( uint8* );
	static uint32		GetAddr( uint8* );
	static char*		GetString( uint8* );
	static SCN_DATA*	GetData( uint8* );

public: //! check modifier
	uint8*		pu8Cursor;
	uint16		u16StackSize;
	SCN_STACK*	pstk;
	SCN_STACK*	pstkTop;
	void*		pvData;

public:
	void		Init( SCN_STACK*, uint16 );
	void		CallProc( uint32 );
	void		Wakeup();
	void		Sleep();
	int32		CheckComplete();
	void		Interrupt();
	int32		GetArgNumber( uint8 );
	float		GetArgFloat( uint8 );
	uint32		GetArgAddr( uint8 );
	char*		GetArgString( uint8 );
	SCN_DATA*	GetArgData( uint8 );
	void		SetValNumber( int32 );
	void		SetValFloat( float );
};

//=============================================================================
// SCN System
//=============================================================================

// ref.default.pdb
typedef struct SCN_EXFUNC {
	uint32 u32ID;
	void (*pfn)(void); // TODO: ret/arg types
} SCN_EXFUNC;

// ref.default.pdb
typedef struct SCN_GBVAR {
	uint32	u32ID;
	uint8	u8Code[5];
} SCN_GBVAR;

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class SCN_SYSTEM
{
public: //! check modifier
	static SCN_THREAD	Thread[4];
	static SCN_THREAD*	pcurThread;
	static SCN_STACK*	pstk;
	static uint8*		pu8Code;
	static SCN_GBVAR*	pgbv;
	static SCN_EXFUNC*	pexf;
	static uint16		u16GbVarNum;
	static uint16		u16ExFuncNum;
	static uint16		u16StackSize;
	static uint16		u16GbVarSize;
	static uint16		u16ExFuncSize;
	static SCN_THREAD*	pThreadExclusive;

private:
	static uint8* SearchGbVar( uint32, uint8 );

public:
	static void			InitSystem( uint16, uint16, uint16 );
	static void			EndSystem();
	static void			SetCode( uint8* );
	static void			InitThread();
	static void			ResetExFunc();
	static void			ResetGbVar();
	static SCN_DATA*	GetGbVar( uint32 );
	static void			SetExFunc( uint32, void (*)(void) );	// TODO: func ptr ret/arg types
	static void			CallExFunc( uint32 );
	static int32		GetArgNumber( uint8 );
	static float		GetArgFloat( uint8 );
	static uint32		GetArgAddr( uint8 );
	static char*		GetArgString( uint8 );
	static SCN_DATA*	GetArgData( uint8 );
	static void			SetValNumber( int32 );
	static void			SetValFloat( float );
	static uint16		GetGbVarSize();
	static int32		GetGlobalDataSize();
	static void			SetGlobalData( sint8* );
	static void			GetGlobalData( sint8* );
	static void			CallProc( uint32 );
	static void			SetExclusiveMode();
	static void			ResetExclusiveMode();
	static SCN_THREAD*	SearchEmptyThread();
	static SCN_THREAD*	_Sleep();				// prefixed with '_' by HVS?
	static SCN_THREAD*	_GetCurrentThread();	// prefixed with '_' by HVS?
};

#endif /* END OF FILE */
