/*
 * LibDM (for PlayStation 2)
 * Copyright (C) Konami Computer Entertainment Japan
 * Codebase Restoration by Joy Division
 */
/* ver."ZONE OF THE ENDERS"
 */
#ifndef INCLUDED_LIBDM_H
#define INCLUDED_LIBDM_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

#include "libalg.h"
//#include "libdg.h"
#include "libfrm.h"

// external
class DG_CAMERA;

/*---------------------------------------------------------------------------*
 * Common Defines
 *---------------------------------------------------------------------------*/

// ref.default.pdb
enum {
	DM_PDCFLAG_INTFIX_X      = 0x0001,
	DM_PDCFLAG_INTFIX_Y      = 0x0002,
	DM_PDCFLAG_INTFIX_Z      = 0x0004,
	DM_PDCFLAG_VIEWFIX_X     = 0x0008,
	DM_PDCFLAG_VIEWFIX_Y     = 0x0010,
	DM_PDCFLAG_VIEWFIX_Z     = 0x0020,
	DM_PDCFLAG_INTERP_LINEAR = 0x0040,
	DM_PDCFLAG_INTERP_SPHERE = 0x0080,
	DM_PDCMASK_INTERP_TYPE   = 0x00C0,
	DM_PDCFLAG_OFF           = 0x0100,
	DM_PDCFLAG_DATA          = 0x0200
};

/*---------------------------------------------------------------------------*
 * Classes
 *---------------------------------------------------------------------------*/

//! INCOMPLETE
class DM_MANAGER
{
public:
	static void InitSystem();
};

//! INCOMPLETE
class DM_RECFRAME
{
	enum {
		REC,
		APPREC,
		PLAY
	};
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class DM_BUFFER
{
public: //! check modifier

	enum {
		STATE_EMPTY,
		STATE_FULL
	};

	uint16 u16Key;
	uint8  u8State;
	uint8  pad0;
	uint32 pad1;
	uint32 pad2;
	uint32 pad3;
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class DM_STRPACK
{
public: //! check modifier
	uint16 u16Id;
	uint16 u16Frame;
	uint32 u32Func;
	uint32 u32szPack;
	uint64 u64Dat;
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class DM_DATA
{
public: //! check modifier
	uint16      u16szBuf;
	uint16      u16szRead;
	uint8       u8Flag;
	uint8       u8State;
	uint8       u8Current;
	uint8       u8End;
	sint32      prevPosX;
	sint32      prevPosY;
	sint32      prevPosZ;
	DM_BUFFER*  pQue;
	float       fRate;

public:
	DM_STRPACK* Que(DM_STRPACK*);
	DM_BUFFER*  GetpQue(uint8);
	DM_BUFFER*  SetValidQue(uint16);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
class DM_FRAME : public FRM_OBJECT //! check modifier
{
public: //! check modifier
	ALG_MATRIX  matCamera;
	uint16      u16Time;
	void (*pModulateFunc)(void); // TODO: ret/arg types
	void*       pArg;

private:
	void Act();
	void SetPad();
	void SetScreen();

public: //! check modifier
	static FRM_OBJECT* pfrmPlayer;

	DM_DATA*    pDatPad;
	sint32      id;

public:
	void Update(uint16);
	void Reset();
	void SetModulateFunc( void (*)(void), void*); // TODO: func ptr ret/arg types

	DM_FRAME(const DM_FRAME&);
	DM_FRAME(uint32, ALG_MATRIX*, uint8, uint8, uint8, uint8, sint32, uint32, uint8);
	DM_FRAME(char*, uint8, ALG_MATRIX*, ALG_MATRIX*);
	~DM_FRAME();

public: //! check modifier
	static sint8 s8NameCounter;

public:
	static FRM_OBJECT& Player();

	DM_FRAME& operator=(const DM_FRAME&);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
struct DM_PRCAMERA_DATA
{
public: //! check modifier
	ALG_VECTOR  vecView;
	ALG_VECTOR  vecInterrest;
	uint16      u16Flag;
	uint16      u16Time;
	sint32      idRefActor;
	float       fRoll;
	float       fAng;

public:
	DM_PRCAMERA_DATA();

	DM_PRCAMERA_DATA& operator=(const DM_PRCAMERA_DATA&);
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
struct DM_PRDEMO_CAMERA_RECDATA
{
public: //! check modifier
	ALG_VECTOR vecView;
	ALG_VECTOR vecInterrest;

public:
	DM_PRDEMO_CAMERA_RECDATA();

	DM_PRDEMO_CAMERA_RECDATA& operator=(const DM_PRDEMO_CAMERA_RECDATA&);
};

// ref.default.pdb
class DM_PRDEMO_CAMERA
{
public: //! check modifier
	ALG_VECTOR  vecViewRel;
	ALG_VECTOR  vecInterrestRel;
	ALG_VECTOR  vecViewAbs;
	ALG_VECTOR  vecInterrestAbs;
	uint16      u16Flag;
	uint16      u16Time;
	float       fRoll;
	float       fAng;
	float       fSlantPrev;
	float       fSlantPost;
	ALG_MATRIX* pmatRefCamera;
	sint32      idRefActor;
	DM_PRDEMO_CAMERA_RECDATA* pRecData;
	int         nData;

public:
	void Calc(sint32);
	void GetMatrix(ALG_MATRIX*);
	void GetInterpMatrix(DM_PRDEMO_CAMERA_RECDATA*, DM_PRDEMO_CAMERA*, DM_PRDEMO_CAMERA*, DM_PRDEMO_CAMERA*, float);
	void UpdateCamera(sint32);
	void GetData(DM_PRCAMERA_DATA*);
	void PutData(DM_PRCAMERA_DATA*);
	void SetPlayData(sint32);
	void Reset();

public: //! check modifier
	static DG_CAMERA* pdgcam;

public:
	DM_PRDEMO_CAMERA();

	DM_PRDEMO_CAMERA& operator=(const DM_PRDEMO_CAMERA&);
};

#endif /* END OF FILE */
