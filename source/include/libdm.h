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

// internal
class DM_MANAGER;
class DM_RECFRAME;
class DM_BUFFER;
class DM_STRPACK;
class DM_DATA;
class DM_FRAME;
struct DM_PRCAMERA_DATA;
struct DM_PRDEMO_CAMERA_RECDATA;
class DM_PRDEMO_CAMERA;

//=============================================================================
// Demo Common Defines
//=============================================================================

enum {
	DM_PDCFLAG_INTFIX_X			= 0x0001,
	DM_PDCFLAG_INTFIX_Y			= 0x0002,
	DM_PDCFLAG_INTFIX_Z			= 0x0004,
	DM_PDCFLAG_VIEWFIX_X		= 0x0008,
	DM_PDCFLAG_VIEWFIX_Y		= 0x0010,
	DM_PDCFLAG_VIEWFIX_Z		= 0x0020,
	DM_PDCFLAG_INTERP_LINEAR	= 0x0040,
	DM_PDCFLAG_INTERP_SPHERE	= 0x0080,
	DM_PDCMASK_INTERP_TYPE		= 0x00C0,
	DM_PDCFLAG_OFF				= 0x0100,
	DM_PDCFLAG_DATA				= 0x0200
};

//=============================================================================
// Classes (IN-PROGRESS)
//=============================================================================

//! INCOMPLETE
class DM_MANAGER
{
public:
	static void InitSystem();
};

/*---------------------------------------------------------------------------*/

//! INCOMPLETE
class DM_RECFRAME
{
	enum {
		REC,
		APPREC,
		PLAY
	};
};

//=============================================================================
// Demo Buffer
//=============================================================================

class DM_BUFFER
{
public: //! check modifier

	enum {
		STATE_EMPTY,
		STATE_FULL
	};

	UINT16	u16Key;
	UINT8	u8State;
	UINT8	pad0;		// alignment
	UINT32	pad1;		// alignment
	UINT32	pad2;		// alignment
	UINT32	pad3;		// alignment
};

//=============================================================================
// Demo StreamPack
//=============================================================================

class DM_STRPACK
{
public: //! check modifier
	UINT16 u16Id;
	UINT16 u16Frame;
	UINT32 u32Func;
	UINT32 u32szPack;
	UINT64 u64Dat;
};

//=============================================================================
// Demo Data
//=============================================================================

class DM_DATA
{
public: //! check modifier
	UINT16		u16szBuf;
	UINT16		u16szRead;
	UINT8		u8Flag;
	UINT8		u8State;
	UINT8		u8Current;
	UINT8		u8End;
	int32		prevPosX;
	int32		prevPosY;
	int32		prevPosZ;
	DM_BUFFER*	pQue;
	float		fRate;

public:
	DM_STRPACK*	Que( DM_STRPACK* );
	DM_BUFFER*	GetpQue( UINT8 );
	DM_BUFFER*	SetValidQue( UINT16 );
};

//=============================================================================
// Demo Orbital Frame
//=============================================================================

class DM_FRAME : public FRM_OBJECT
{
public: //! check modifier
	ALG_MATRIX	matCamera;
	UINT16		u16Time;
	void (*pModulateFunc)(DM_FRAME*, UINT16, void*);
	void*		pArg;

private:
	void Act();
	void SetPad();
	void SetScreen();

public: //! check modifier
	static FRM_OBJECT* pfrmPlayer;

	DM_DATA*	pDatPad;
	int32		id;

public:
	void Update( UINT16 );
	void Reset();
	void SetModulateFunc( void (*pModulateFunc)(DM_FRAME*, UINT16, void*), void* );

	DM_FRAME( const DM_FRAME& );
	DM_FRAME( UINT32, ALG_MATRIX*, UINT8, UINT8, UINT8, UINT8, int32, UINT32, UINT8 );
	DM_FRAME( char*, UINT8, ALG_MATRIX*, ALG_MATRIX* );
	~DM_FRAME();

public: //! check modifier
	static SINT8 s8NameCounter;

public:
	static FRM_OBJECT& Player();

	DM_FRAME& operator = ( const DM_FRAME& );
};

//=============================================================================
// Demo PR Camera
//=============================================================================

struct DM_PRCAMERA_DATA
{
public: //! check modifier
	ALG_VECTOR	vecView;
	ALG_VECTOR	vecInterrest;
	UINT16		u16Flag;
	UINT16		u16Time;
	int32		idRefActor;
	float		fRoll;
	float		fAng;

public:
	DM_PRCAMERA_DATA();

	DM_PRCAMERA_DATA& operator = ( const DM_PRCAMERA_DATA& );
};

/*---------------------------------------------------------------------------*/

struct DM_PRDEMO_CAMERA_RECDATA
{
public: //! check modifier
	ALG_VECTOR	vecView;
	ALG_VECTOR	vecInterrest;

public:
	DM_PRDEMO_CAMERA_RECDATA();

	DM_PRDEMO_CAMERA_RECDATA& operator = ( const DM_PRDEMO_CAMERA_RECDATA& );
};

/*---------------------------------------------------------------------------*/

class DM_PRDEMO_CAMERA
{
public: //! check modifier
	ALG_VECTOR	vecViewRel;
	ALG_VECTOR	vecInterrestRel;
	ALG_VECTOR	vecViewAbs;
	ALG_VECTOR	vecInterrestAbs;
	UINT16		u16Flag;
	UINT16		u16Time;
	float		fRoll;
	float		fAng;
	float		fSlantPrev;
	float		fSlantPost;
	ALG_MATRIX*	pmatRefCamera;
	INT32		idRefActor;
	DM_PRDEMO_CAMERA_RECDATA* pRecData;
	INT32		nData;

public:
	void Calc( int32 );
	void GetMatrix( ALG_MATRIX* );
	void GetInterpMatrix( DM_PRDEMO_CAMERA_RECDATA*, DM_PRDEMO_CAMERA*, DM_PRDEMO_CAMERA*, DM_PRDEMO_CAMERA*, float );
	void UpdateCamera( int32 );
	void GetData( DM_PRCAMERA_DATA* );
	void PutData( DM_PRCAMERA_DATA* );
	void SetPlayData( int32 );
	void Reset();

public: //! check modifier
	static DG_CAMERA* pdgcam;

public:
	DM_PRDEMO_CAMERA();

	DM_PRDEMO_CAMERA& operator = ( const DM_PRDEMO_CAMERA& );
};

#endif /* END OF FILE */
