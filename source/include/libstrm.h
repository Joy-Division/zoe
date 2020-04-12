/*
 * LibSTRM (for PlayStation 2)
 * Copyright (C) Konami Computer Entertainment Japan
 * Codebase Restoration by Joy Division
 */
/* ver."ZONE OF THE ENDERS"
 */
#ifndef INCLUDED_LIBSTRM_H
#define INCLUDED_LIBSTRM_H

#include <libmpeg.h>

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

/*---------------------------------------------------------------------------*
 * Common Defines
 *---------------------------------------------------------------------------*/

// ref.default.pdb
enum {
/* 0x0 */ STRM_DATANUM_JIMAKU,
/* 0x1 */ STRM_DATANUM_PCM,
/* 0x2 */ STRM_DATANUM_PROGDEMO,
/* 0x3 */ STRM_DATANUM_POLYDEMO,
/* 0x4 */ STRM_DATANUM_SCN,
/* 0x5 */ STRM_DATANUM_DMX,
/* 0x6 */ STRM_DATANUM_MPG,
/* 0x7 */ STRM_DATANUM_EU_JIMAKU,
/* 0x7 */ STRM_DATANUM_JIMAKU_ENGLISH = STRM_DATANUM_EU_JIMAKU,
/* 0x8 */ STRM_DATANUM_JIMAKU_FRENCH,
/* 0x9 */ STRM_DATANUM_JIMAKU_GERMAN,
/* 0xA */ STRM_DATANUM_JIMAKU_ITALIAN,
/* 0xB */ STRM_DATANUM_JIMAKU_SPANISH,
/* 0xC */ STRM_DATANUM_JIMAKU_PORTUGUESE,
/* 0xD */ STRM_DATANUM_MAX
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class STRM_RING_AREA
{
public: //! check modifier
	sint32  indxTop;
	sint32  size;
	uint8*  pBufTop;
	sint32  sizeBuf;

public:
	sint32  Write(STRM_RING_AREA*);
	sint32  Write(void*, sint32);
	void*   GetTop();
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class STRM_RING_BUFFER
{
public: //! check modifier
	void*   pBufTop;
	sint32  sizeBuf;
	sint32  indxDataTop;
	sint32  sizeData;
	sint32  indxFreeTop;
	sint32  sizeFree;

public:
	void    Init(void*, sint32);
	sint32  GetFree(STRM_RING_AREA*, sint32);
	sint32  GetFree(STRM_RING_AREA*);
	void    UngetFree(sint32);
	void    PutData(sint32);
	sint32  GetData(STRM_RING_AREA*, sint32);
	sint32  GetData(STRM_RING_AREA*);
	void    UngetData(sint32);
	void    PutFree(sint32);
	void*   GetTop();
	sint32  GetBufferSize();
	void    SetArea(STRM_RING_AREA*, uint8*, sint32);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class STRM_DATACONSUMER : public STRM_RING_BUFFER //! check modifier
{
	/* VTable */

public: //! check modifier

/* typedef (function *) */
/* TODO: create replacement, ret/arg types */

	enum PHASE {
		INIT1,
		INIT2,
		INIT3,
		INIT4,
		INIT5,
		PRIMED,
		ACT,
		ACT2,
		ACT3,
		ACT4,
		END
	};

	static const sint32 TIMEOUT_INIT = TEMP_ZERO;

	void*               pBuf;
	STRM_RING_BUFFER*   pRingRead;
	sint32              sizeExtend;
	PHASE               ph;
	bool32              bPackMem;
	sint32              ctrInitTimeout;

public:
	sint32 Update(sint32);

	STRM_DATACONSUMER(const STRM_DATACONSUMER&);
	STRM_DATACONSUMER(sint32, sint32, sint32);
	~STRM_DATACONSUMER();

	void    Cancel();
	void    SetExtendArea();
	void    CheckInitTimeout();
	sint32  CbData(sceMpeg*, sceMpegCbDataStr*);

public: //! check modifier
	static void (*pNewfunc[13])(void); // TODO: ret/arg types
	static char* pnmFile;
	static bool32 bStrEnd;

public:
	static void SetFunc(sint32, void(*)(void)); // TODO: func ptr ret/arg types

	STRM_DATACONSUMER& operator=(const STRM_DATACONSUMER&);
};

/*---------------------------------------------------------------------------*
 * Prototypes
 *---------------------------------------------------------------------------*/

/* CDVD Stream System (streamcd.cc) */
void STRM_LoadPcmDir();

#endif /* END OF FILE */
