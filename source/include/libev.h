#ifndef INCLUDED_LIBEV_H
#define INCLUDED_LIBEV_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

#include "libgv.h"
//#include "libscn.h"

// external
class SCN_THREAD;

// internal
class EV_EVENT;
class EV_JOB;
class EV_EVENTLIST;
class EV_DAEMON;

//=============================================================================
// Basic Event
//=============================================================================

class EV_EVENT
{
public: //! check modifier
	UINT32	u32AddrProc;
	void (*pFunc)(EV_EVENT*);
	UINT8	u8Prio;
	UINT8	u8Flag;
	UINT16	u16Resource;
	UINT16	u16Timer;
	UINT16	u16ID;
	UINT8	u8User[4];
	DAT128	datUser;

public:
	void GetScnEvent( int32 );
	void Set( void (*)(EV_EVENT*), UINT8, UINT16, UINT8, UINT16, UINT16 );
	void UnlockResource( UINT16 );
};

//=============================================================================
// Event Job
//=============================================================================

class EV_JOB
{
public:
	virtual void SuspendJob( EV_EVENT* pEv );
	virtual void WakeupJob( EV_EVENT* pEv );
	virtual void StopJob( EV_EVENT* pEv );

	EV_JOB( const EV_JOB& );
	EV_JOB();

	EV_JOB& operator = ( const EV_JOB& );
};

//=============================================================================
// Event Linked List
//=============================================================================

class EV_EVENTLIST : public EV_EVENT
{
public: //! check modifier
	EV_EVENTLIST*	pPrev;
	EV_EVENTLIST*	pNext;
	UINT16			u16State;
	BOOL16			bReset;		// BOOL16 for alignment
	SCN_THREAD*		pThread;
	EV_JOB*			pJob;

	static EV_EVENTLIST* pTop;

public:
	void Insert( EV_EVENTLIST* );
	void Delete();
	void Reset();
};

//=============================================================================
// Event Daemon
//=============================================================================

class EV_DAEMON : public GV_ACTOR
{
public: //! check modifier

	static const int32 QUE_LENGTH = DEFINE_ME;

	EV_EVENTLIST que[32];

private:
	EV_EVENTLIST* SearchEmptyQue();

public: //! check modifier
	EV_JOB	jbDefault;
	BOOL32	bReset;

private:
	void ExecReset();

public: //! check modifier
	UINT16			u16UseRes;
	UINT16			u16SusRes;
	EV_EVENTLIST*	pEvCurrent;

public:
	EV_DAEMON( const EV_DAEMON& );
	EV_DAEMON();

	void Act(); // override GV_ACTOR::Act()

	int Queue( EV_EVENT* );
	void Reset();

	~EV_DAEMON();

	EV_DAEMON& operator = ( const EV_DAEMON& );
};

//=============================================================================
// Global Functions
//=============================================================================

/* evd.cc */
void EV_StartDaemon();

#endif /* END OF FILE */
