/*
 * LibFS C++ Version (for PlayStation 2)
 * Copyright (C) Konami Computer Entertainment Japan
 * Codebase Restoration by Joy Division
 */
/* ver."ZONE OF THE ENDERS"
 */
#ifndef INCLUDED_LIBFS_H
#define INCLUDED_LIBFS_H

#include <sifcmd.h>

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

#include "libgv.h"
#include "libev.h"

/*---------------------------------------------------------------------------*
 * Common Structures
 *---------------------------------------------------------------------------*/

// ref.default.pdb
typedef struct _FS_FILEINFO {
	sceSifCmdHdr hdr;
	sint32  status;
	sint32  size;
	void*   pBuf;
	sint32  sizeRead;
	sint32  pos;
	char    nmFile[60];
} FS_FILEINFO;

// ref.default.pdb
typedef struct _FS_PACKHDR {
	sint32 nFile;
	uint32 flag;
	sint32 pad0;
	sint32 pad1;
} FS_PACKHDR;

// ref.default.pdb
typedef struct _FS_FILEHDR {
	char    nmFile[44];
	sint32  size;
} FS_FILEHDR;

// ref.default.pdb
typedef struct HDRINFO {
	FS_PACKHDR packhdr;
	FS_FILEHDR filehdr;
} HDRINFO;

// ref.default.pdb
class FS_EXTEND_INFO
{
public: //! check modifier
	char nmFile[32];
	char nmPack[32];
};

// ref.default.pdb
class FS_LOAD_INFO
{
public: //! check modifier
	void*           pMem;
	FS_EXTEND_INFO* pInfo;
	uint32          u32Pos;
	uint8           u8State;
	sint32          nAllocType;
};

/*---------------------------------------------------------------------------*
 * FS Cache System (cache.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class FS_CACHEMEMBER
{
public: //! check modifier
	uint32  u32Id;
	void*   pBuf;
};

// ref.default.pdb
class FS_CACHE
{
public: //! check modifier
	FS_CACHEMEMBER* pMember;
	sint32          size;

private:
	FS_CACHEMEMBER* Find(uint32);
	void            Shift(FS_CACHEMEMBER*);

public:
	void    Init(FS_CACHEMEMBER*, sint32);
	void    Set(uint32, void*);
	void    Unset(uint32);
	void*   Get(uint32);
	void    Destroy();
};


/*---------------------------------------------------------------------------*
 * FS Loader (loader.cc)
 *---------------------------------------------------------------------------*/

// ref.default.pdb
class FS_LOADER:
  public GV_ACTOR, //! check modifier
  public EV_JOB    //! check modifier
{
public: //! check modifier
	FS_FILEINFO savefileinfo;
	char        nmStage[16];
	sint32      indx;
	void*       pBufLoad;
	sint32      nLoadPakFile;
	bool32      bOpen;
	bool32      bInterrupt;
	void*       pLastReadAddress;
	sint32      nLastReadSize;
	sint32      nLastReadOffset;

	enum STATE {
		IDLE,
		SYNC,
		OPEN,
		PACKHDR,
		FILEHDR,
		READ,
		CLOSE,
		COMP,
		INTR,
		RESTART
	} state;

	enum SUS_PHASE {
		S_NOTHING,
		S_REQUEST,
		S_REQUEST2,
		S_SUSPEND,
		S_REOPEN
	} phSuspend;

	EV_EVENT*       pEv;
	sint32          nFiles;
	sint32          nRestFiles;
	char*           pnmFilesTop[64];
	char**          ppnmFiles;
	char*           pnmFileLoad;
	FS_LOAD_INFO    Info[256];

public:
	void CallInitializer(void*, char*, uint32, sint32);
	void InitStageLoad();

	FS_LOADER(const FS_LOADER&);
	FS_LOADER();

	void Act(); // override GV_ACTOR::Act()

	sint32  SetStage(EV_EVENT*);
	void    Load();
	sint32  CheckSuspend();
	sint32  StartStage();
	void    Interrupt();
	sint32  CheckBusy();
	sint32  CheckReading();
	void    Restart();
	void    RequestSetStage(EV_EVENT*, char*, sint32, char**);

	void SuspendJob(EV_EVENT*); // override EV_JOB::SuspendJob()
	void WakeupJob(EV_EVENT*);  // override EV_JOB::WakeupJob()

	~FS_LOADER();

	FS_LOADER& operator=(const FS_LOADER&);
};

/*---------------------------------------------------------------------------*
 * Prototypes
 *---------------------------------------------------------------------------*/

/* FS Daemon (fsd.cc) */
void FS_StartDaemon();

/* FS Cache System (cache.cc) */
uint32 FS_StrCode( char* str );

/* FS CDVD (cdvd.cc) */
void FS_CdLoadDirInfo( char*, int );

#endif /* END OF FILE */
