#ifndef INCLUDED_LIBFS_H
#define INCLUDED_LIBFS_H

#include <sifcmd.h>

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

#include "libgv.h"
#include "libev.h"

//=============================================================================
// FS Common Data Types
//=============================================================================

typedef struct _FS_FILEINFO {
	sceSifCmdHdr hdr;
	int32	status;
	int32	size;
	void*	pBuf;
	int32	sizeRead;
	int32	pos;
	char	nmFile[60];
} FS_FILEINFO;

/*---------------------------------------------------------------------------*/

typedef struct _FS_PACKHDR {
	int32	nFile;
	UINT32	flag;
	int32	pad0,pad1;
} FS_PACKHDR;

typedef struct _FS_FILEHDR {
	char	nmFile[44];
	int32	size;
} FS_FILEHDR;

typedef struct HDRINFO {
	FS_PACKHDR packhdr;
	FS_FILEHDR filehdr;
} HDRINFO;

/*---------------------------------------------------------------------------*/

class FS_EXTEND_INFO
{
public: //! check modifier
	char nmFile[32];
	char nmPack[32];
};

class FS_LOAD_INFO
{
public: //! check modifier
	void*			pMem;
	FS_EXTEND_INFO*	pInfo;
	UINT32			u32Pos;
	UINT8			u8State;
	int32			nAllocType;
};

//=============================================================================
// FS Cache System (cache.cc)
//=============================================================================

class FS_CACHEMEMBER
{
public: //! check modifier
	UINT32	u32Id;
	void*	pBuf;
};

/*---------------------------------------------------------------------------*/

class FS_CACHE
{
public: //! check modifier
	FS_CACHEMEMBER* pMember;
	int32 size;

private:
	FS_CACHEMEMBER* Find( UINT32 );
	void Shift( FS_CACHEMEMBER* );

public:
	void	Init( FS_CACHEMEMBER*, int32 );
	void	Set( UINT32, void* );
	void	Unset( UINT32 );
	void*	Get( UINT32 );
	void	Destroy();
};

//=============================================================================
// FS Loader (loader.cc)
//=============================================================================

class FS_LOADER:
  public GV_ACTOR, //! check modifier
  public EV_JOB    //! check modifier
{
public: //! check modifier
	FS_FILEINFO	savefileinfo;
	char		nmStage[16];
	int32		indx;
	void*		pBufLoad;
	int32		nLoadPakFile;
	BOOL32		bOpen;
	BOOL32		bInterrupt;
	void*		pLastReadAddress;
	int32		nLastReadSize;
	int32		nLastReadOffset;

	enum STATE {
		IDLE,		//
		SYNC,		//
		OPEN,		//
		PACKHDR,	//
		FILEHDR,	//
		READ,		//
		CLOSE,		//
		COMP,		//
		INTR,		//
		RESTART		//
	} state;

	enum SUS_PHASE {
		S_NOTHING,	//
		S_REQUEST,	//
		S_REQUEST2,	//
		S_SUSPEND,	//
		S_REOPEN	//
	} phSuspend;

	EV_EVENT*		pEv;
	int32			nFiles;
	int32			nRestFiles;
	char*			pnmFilesTop[64];
	char**			ppnmFiles;
	char*			pnmFileLoad;
	FS_LOAD_INFO	Info[256];

public:
	void CallInitializer( void*, char*, UINT32, int32 );
	void InitStageLoad();

	FS_LOADER( const FS_LOADER& );
	FS_LOADER();

	void Act(); // override GV_ACTOR::Act()

	int32	SetStage( EV_EVENT* );
	void	Load();
	int32	CheckSuspend();
	int32	StartStage();
	void	Interrupt();
	int32	CheckBusy();
	int32	CheckReading();
	void	Restart();
	void	RequestSetStage( EV_EVENT*, char*, int32, char** );

	void SuspendJob(EV_EVENT*);	// override EV_JOB::SuspendJob()
	void WakeupJob(EV_EVENT*);	// override EV_JOB::WakeupJob()

	~FS_LOADER();

	FS_LOADER& operator = ( const FS_LOADER& );
};

//=============================================================================
// Global Functions
//=============================================================================

/* fsd.cc */
void FS_StartDaemon();

/* cache.cc */
UINT32 FS_StrCode( char* str );

/* cdvd.cc */
void FS_CdLoadDirInfo( char*, int );

#endif /* END OF FILE */
