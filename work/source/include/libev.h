/*
 * Event Task Library
 * Global Include
 */
/* ver."ZONE OF THE ENDERS"
 */
#ifndef INCLUDED_LIBEV_H
#define INCLUDED_LIBEV_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "libgv.h"
#include "libscn.h"

/*---------------------------------------------------------------------------*
 * Classes
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class EV_EVENT
{
public: //! unconfirmed modifier
	uint32  u32AddrProc;
	void (*pFunc)(void); // TODO: ret/arg types
	uint8   u8Prio;
	uint8   u8Flag;
	uint16  u16Resource;
	uint16  u16Timer;
	uint16  u16ID;
	uint8   u8User[4];
	DAT128  datUser;

public:
	void GetScnEvent(sint32);
	void Set(void (*)(void), uint8, uint16, uint8, uint16, uint16); // TODO: func ptr ret/arg types
	void UnlockResource(uint16);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class EV_JOB
{
	/* VTable */

public:
	void SuspendJob(EV_EVENT*);
	void WakeupJob(EV_EVENT*);
	void StopJob(EV_EVENT*);
	
	EV_JOB(const EV_JOB&);
	EV_JOB();
	
	EV_JOB& operator=(const EV_JOB&);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class EV_EVENTLIST:
  public EV_EVENT //! unconfirmed modifier
{
public: //! unconfirmed modifier
	EV_EVENTLIST*   pPrev;
	EV_EVENTLIST*   pNext;
	uint16          u16State;
	bool16          bReset;
	SCN_THREAD*     pThread;
	EV_JOB*         pJob;
	
	static EV_EVENTLIST* pTop;

public:
	void Insert(EV_EVENTLIST*);
	void Delete();
	void Reset();
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class EV_DAEMON:
  public GV_ACTOR //! unconfirmed modifier
{
public: //! unconfirmed modifier

	static const sint32 QUE_LENGTH = TEMP_ZERO;

	EV_EVENTLIST que[32];

private:
	EV_EVENTLIST* SearchEmptyQue();

public: //! unconfirmed modifier
	EV_JOB jbDefault;
	bool32 bReset;

private:
	void ExecReset();

public: //! unconfirmed modifier
	uint16          u16UseRes;
	uint16          u16SusRes;
	EV_EVENTLIST*   pEvCurrent;

public:
	EV_DAEMON(const EV_DAEMON&);
	EV_DAEMON();
	
	void Act();
	int Queue(EV_EVENT*);
	void Reset();
	
	~EV_DAEMON();
	
	EV_DAEMON& operator=(const EV_DAEMON&);
};

/*---------------------------------------------------------------------------*
 * Prototypes
 *---------------------------------------------------------------------------*/

/* EV Daemon (evd.cc) */
void EV_StartDaemon();

#endif /* END OF FILE */
