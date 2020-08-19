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

enum {
	SCN_STATE_WAKEUP,
	SCN_STATE_SLEEP,
	SCN_STATE_INTERRUPT,
	SCN_STATE_COMPLETE
};

//=============================================================================
// SCN Basic Data Type
//=============================================================================

class SCN_DATA
{
public: //! check modifier
	UINT8 u8Code[5];

public:
	UINT8		VarType();
	int32		CheckEnd();
	void		SetNumber( int32 );
	void		SetFloat( float );
	int32		GetNumber();
	float		GetFloat();
	UINT32		GetAddr();
	SCN_DATA*	GetData();
	char*		GetString();
};

//=============================================================================
// SCN Thread
//=============================================================================

typedef struct SCN_STACK {
	UINT8 u8Code[5];
} SCN_STACK;

/*---------------------------------------------------------------------------*/

class SCN_THREAD
{
public: //! check modifier
	UINT8 u8State;

private:
	void	Execute();
	void	PushCode( UINT8* );
	void	PopCode( UINT8* );
	void	PushNumber( int32 );
	int32	PopNumber();
	void	PushFloat( float );
	float	PopFloat();
	void	PushAddr( UINT32 );
	UINT32	PopAddr();

	static UINT32		Read( UINT8* );
	static void			Write( UINT8*, UINT32 );
	static void			SetNumber( UINT8*, int32 );
	static void			SetFloat( UINT8*, float );
	static int32		GetNumber( UINT8* );
	static float		GetFloat( UINT8* );
	static UINT32		GetAddr( UINT8* );
	static char*		GetString( UINT8* );
	static SCN_DATA*	GetData( UINT8* );

public: //! check modifier
	UINT8*		pu8Cursor;
	UINT16		u16StackSize;
	SCN_STACK*	pstk;
	SCN_STACK*	pstkTop;
	void*		pvData;

public:
	void		Init( SCN_STACK*, UINT16 );
	void		CallProc( UINT32 );
	void		Wakeup();
	void		Sleep();
	int32		CheckComplete();
	void		Interrupt();
	int32		GetArgNumber( UINT8 );
	float		GetArgFloat( UINT8 );
	UINT32		GetArgAddr( UINT8 );
	char*		GetArgString( UINT8 );
	SCN_DATA*	GetArgData( UINT8 );
	void		SetValNumber( int32 );
	void		SetValFloat( float );
};

//=============================================================================
// SCN System
//=============================================================================

typedef struct SCN_EXFUNC {
	UINT32 u32ID;
	void (*pfn)(void);
} SCN_EXFUNC;

typedef struct SCN_GBVAR {
	UINT32	u32ID;
	UINT8	u8Code[5];
} SCN_GBVAR;

/*---------------------------------------------------------------------------*/

class SCN_SYSTEM
{
public: //! check modifier
	static SCN_THREAD	Thread[4];
	static SCN_THREAD*	pcurThread;
	static SCN_STACK*	pstk;
	static UINT8*		pu8Code;
	static SCN_GBVAR*	pgbv;
	static SCN_EXFUNC*	pexf;
	static UINT16		u16GbVarNum;
	static UINT16		u16ExFuncNum;
	static UINT16		u16StackSize;
	static UINT16		u16GbVarSize;
	static UINT16		u16ExFuncSize;
	static SCN_THREAD*	pThreadExclusive;

private:
	static UINT8* SearchGbVar( UINT32, UINT8 );

public:
	static void			InitSystem( UINT16, UINT16, UINT16 );
	static void			EndSystem();
	static void			SetCode( UINT8* );
	static void			InitThread();
	static void			ResetExFunc();
	static void			ResetGbVar();
	static SCN_DATA*	GetGbVar( UINT32 );
	static void			SetExFunc( UINT32, void (*)(void) );
	static void			CallExFunc( UINT32 );
	static int32		GetArgNumber( UINT8 );
	static float		GetArgFloat( UINT8 );
	static UINT32		GetArgAddr( UINT8 );
	static char*		GetArgString( UINT8 );
	static SCN_DATA*	GetArgData( UINT8 );
	static void			SetValNumber( int32 );
	static void			SetValFloat( float );
	static UINT16		GetGbVarSize();
	static int32		GetGlobalDataSize();
	static void			SetGlobalData( SINT8* );
	static void			GetGlobalData( SINT8* );
	static void			CallProc( UINT32 );
	static void			SetExclusiveMode();
	static void			ResetExclusiveMode();
	static SCN_THREAD*	SearchEmptyThread();
	static SCN_THREAD*	_Sleep();				// prefixed with '_' by HVS?
	static SCN_THREAD*	_GetCurrentThread();	// prefixed with '_' by HVS?
};

#endif /* END OF FILE */
