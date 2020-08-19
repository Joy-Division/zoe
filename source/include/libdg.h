#ifndef INCLUDED_LIBDG_H
#define INCLUDED_LIBDG_H

#include <eestruct.h>
#include <libdma.h>
#include <libgraph.h>
#include <libpkt.h>

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

#include "def_mdl.h"
#include "def_tex.h"
#include "libalg.h"
#include "libgv.h"

// internal
class DBGFONT;
class DG_CAMERA;
class DG_CHANL;
class DG_DAEMON1;
class DG_DAEMON2;
class DG_DYNAMIC_TEXTURE;
class DG_FRAME;
class DG_LIGHT;
class DG_MDL;
class DG_MDL_EFIELDDATA;
class DG_MDL_ENVMAPDATA;
class DG_MDL_FLOWENVDATA;
class DG_MDL_FLOWLINEDATA;
class DG_MDL_REFRACTDATA;
class DG_MDL_SPECIALDATA;
class DG_OBJ;
class DG_OBJINFO;
class DG_OBJPTR;
class DG_OBJ_CALLBACK;
class DG_OBJ_FONT;
class DG_OBJ_POLYGON;
class DG_OBJ_QUE;
class DG_QUEUE;
class DG_TEXTURE_BUFFER;
class DG_VERTEX;

//=============================================================================
// DG Common Defines
//=============================================================================

enum {
	DG_BOUND_NOTHING,
	DG_BOUND_PART,
	DG_BOUND_ALL
};

/*---------------------------------------------------------------------------*/

enum {
	DG_OBJTYPE_OBJECT,
	DG_OBJTYPE_POLYGON,
	DG_OBJTYPE_CALLBACK,
	DG_OBJTYPE_QUE,
	DG_OBJTYPE_FONT,
	DG_OBJTYPE_MAX
};

/*---------------------------------------------------------------------------*/

typedef struct _BLOCK_UNIT {
	UINT16 u16addrBlock;
	UINT16 u16szBlock;
} BLOCK_UNIT;

/*---------------------------------------------------------------------------*/

typedef struct _DG_DRAW_ENV {
	DAT128			gtag;
	sceGsDrawEnv1	envDraw;
	sceGsDrawEnv2	envDraw2;
	sceGsClear		envClear;
	sceGsZbuf		zbufResume;
	SINT64			addrZbuf1;
	sceGsAlphaEnv	envAlpha;
	DAT128			envTex[4];
	DAT128			envMask;
} DG_DRAW_ENV;

/*---------------------------------------------------------------------------*/

typedef struct _DG_FRAMECOPY {
	DAT128			giftag;
	sceGsBitbltbuf	bitbltbuf;
	UINT64			u64AddrBitbltbuf;
	sceGsTrxpos		trxpos;
	UINT64			u64AddrTrxpos;
	sceGsTrxreg		trxreg;
	UINT64			u64AddrTrxreg;
	sceGsTrxdir		trxdir;
	UINT64			u64AddrTrxdir;
	UINT64			u64TexFlush;
	UINT64			u64AddrTexFlush;
} DG_FRAMECOPY;

/*---------------------------------------------------------------------------*/

typedef struct _DG_MATERIAL {
	FVECTOR mtrAmbient;
	FVECTOR mtrDiffuse;
	FVECTOR mtrSpecular;
} DG_MATERIAL;

/*---------------------------------------------------------------------------*/

typedef struct _DG_RESETOFFSET {
	DAT128			giftag;
	sceGsXyoffset	xyoffset1;
	UINT64			u64AddrXyoffset1;
	sceGsXyoffset	xyoffset2;
	UINT64			u64AddrXyoffset2;
} DG_RESETOFFSET;

/*---------------------------------------------------------------------------*/

typedef struct _POLYGON_PACKET
{
public: //! check modifier
	DAT128		tagDma1;
	DAT128		datParam;
	ALG_MATRIX	matL2Screen;
	ALG_VECTOR	vecPolyParam;
	DAT128		tagVif1;
	DAT128		datFog;
	DAT128		tagVif2;
	DAT128		datStrEnv[3];
	DAT128		tagTex;
	DAT128		datTex[5];
	DAT128		tagDmaRef;

public:
	_POLYGON_PACKET();

	_POLYGON_PACKET & operator = ( const _POLYGON_PACKET& );
}
POLYGON_PACKET;

/*---------------------------------------------------------------------------*/

typedef struct __SCR_WORK
{
public: //! check modifier
	ALG_MATRIX	matLightDir;
	ALG_MATRIX	matColor;
	ALG_VECTOR	vecBound[8];
	FVECTOR		vecCnst;
	ALG_VECTOR	vecFog;
	ALG_VECTOR	vecCam;
	float		fAlpha;
	UINT32		u32FogFarSortz;
	DG_CAMERA*	pcamCurrent;

public:
	__SCR_WORK();

	__SCR_WORK& operator = ( const __SCR_WORK& );
}
SCR_WORK;

/*---------------------------------------------------------------------------*/

typedef struct __SCR_SORTWORK
{
public: //! check modifier
	SCR_WORK	scr_work;
	DG_MDL*		ot3[64];
	DG_MDL*		ot2[64];
	DG_MDL*		ot1[64];
	DG_OBJINFO*	otprm3[64];
	DG_OBJINFO*	otprm2[64];
	DG_OBJINFO*	otprm1[64];

public:
	__SCR_SORTWORK();

	__SCR_SORTWORK& operator = ( const __SCR_SORTWORK& );
}
SCR_SORTWORK;

//=============================================================================
// DG Daemon (dgd.cc)
//=============================================================================

class DG_DAEMON1 : public GV_ACTOR
{
public:
	DG_DAEMON1(const DG_DAEMON1&);
	DG_DAEMON1();

	void Act(); // override GV_ACTOR::Act()

	~DG_DAEMON1();

	DG_DAEMON1& operator = ( const DG_DAEMON1& );
};

/*---------------------------------------------------------------------------*/

class DG_DAEMON2 : public GV_ACTOR
{
public:
	DG_DAEMON2( const DG_DAEMON2& );
	DG_DAEMON2();

	void Act(); // override GV_ACTOR::Act()

	~DG_DAEMON2();

	DG_DAEMON2& operator=( const DG_DAEMON2& );
};

//=============================================================================
// DG Callback (callback.cc)
//=============================================================================

class DG_OBJ_CALLBACK
{
public: //! check modifier
	DG_OBJINFO info;
	ALG_MATRIX matL2World;
	ALG_MATRIX matL2Screen;
	INT32 (*pFunc)(void*, void*);
	void* pData;

public:
	DG_OBJ_CALLBACK();

	void Draw();
	void SetOrder( UINT32 );

	DG_OBJ_CALLBACK& operator = ( const DG_OBJ_CALLBACK& );
};

//=============================================================================
// DG Camera (camera.cc)
//=============================================================================

class DG_CAMERA
{
public: //! check modifier
	const INT32 MAX_CVERT = DEFINE_ME;

	ALG_MATRIX	matC2World;
	ALG_MATRIX	matW2Camera;
	ALG_MATRIX	matC2Screen;
	ALG_MATRIX	matC2Clip;
	ALG_MATRIX	matW2Screen;
	ALG_MATRIX	matW2Clip;
	ALG_MATRIX	matReq;
	DAT128		vertClip[6];
	INT32		nVert;
	float		ax, ay;
	float		cx, cy;
	float		fScrWidth;
	float		fScrHeight;
	float		nearz;
	float		farz;
	float		fScrz;
	float		fScrzReq;
	float		fFogNear;
	float		fFogFar;
	float		fFogMin;
	float		fFogMax;
	float		fFogA;
	float		fFogB;
	UINT32		u32FogCol;
	SINT16		nChanl;
	SINT8		s8Req;
	UINT8		u8Flag;
	UINT32		u32timeCalc;

public:
	DG_CAMERA();
	~DG_CAMERA();

	void		Init();
	void		SetScreen();
	void		CalcCamera();
	DG_CAMERA*	Set( INT32 );
	void		Unset();
	void		SetClipVert( float, float );
	void		DrawClipWindow( sceVif1Packet* );
	void		EraseClipWindow( sceVif1Packet* );
	void		SetMat( ALG_MATRIX* );
	void		SetScrz( float );
	void		UpdateMat();
	void		InitMat( ALG_MATRIX* );
	INT32		ProjectScreen( ALG_VECTOR*, ALG_VECTOR* );
	void		CalcView( ALG_VECTOR*, ALG_VECTOR*, float );
	void		SetScrpadEnv();
	INT32		SendVu1Env( DAT128* );

	DG_CAMERA& operator = ( const DG_CAMERA& );
};

//=============================================================================
// DG Channel (chanl.cc)
//=============================================================================

enum {
	DG_CHANL_MAIN,
	DG_CHANL_DEMO,
	DG_CHANL_MAX
};

/*---------------------------------------------------------------------------*/

class DG_CHANL
{
public: //! check modifier
	UINT16			u16Flag;
	UINT16			u16RefChanl;
	sceGsScissor	envScissor;
	sceGsTest		envTest;
	DG_CAMERA		camDefault;
	DG_CAMERA*		pcamCurrent;
	DG_QUEUE		queNormal;
	DG_QUEUE		queEffect;
	DG_QUEUE		que2D;

public:
	DG_CHANL();
	~DG_CHANL();

	DG_CHANL& operator = ( const DG_CHANL& );
};

//=============================================================================
// DG Debug Font (dbfont2.cc)
//=============================================================================

class DBGFONT
{
public: //! check modifier
	SINT8*	pBufTop;
	UINT32	indxCur;
	UINT32	u32BufSize;
	DG_OBJ_CALLBACK call;
	DEF_TEXLIST* pTlst;
	float	fcurX;
	float	fcurY;
	float	fcurR;
	float	fcurG;
	float	fcurB;
	float	fcurA;

public:
	DBGFONT();
	~DBGFONT();

	void	Font_Queue( float, float, SINT8*, float, float, float, float );
	void	ResetBuf();
	INT32	Draw( DAT128* );
	void	Locate( float, float );
	void	SetCol( float, float, float, float );

	static DBGFONT* StartDaemon();

	DBGFONT & operator = ( const DBGFONT& );
};

//=============================================================================
// DG DMA Control (dma_ctrl.cc)
//=============================================================================

typedef struct _TRANS_MSK {
	UINT32 tagdma[4];
	UINT64 taggif[2];
	UINT64 zbuf[2];
	UINT64 zbuf2[2];
	UINT64 test[2];
} TRANS_MSK;

/*---------------------------------------------------------------------------*/

typedef struct _EFFECT_ENV {
	UINT32 tagdma[4];
	UINT64 taggif[2];
	UINT64 zbuf[2];
	UINT64 zbuf2[2];
	UINT64 test[2];
} EFFECT_ENV;

/*---------------------------------------------------------------------------*/

typedef struct _2D_TEST {
	UINT32 tagdma[4];
	UINT64 taggif[2];
	UINT64 zbuf[2];
	UINT64 zbuf2[2];
	UINT64 test2[2];
	UINT64 alpha[2];
} _2D_TEST;

/*---------------------------------------------------------------------------*/

typedef struct DG_DMATASK {
	void (**callback)(INT32);
	INT32		param;
	INT32		dma_type;
	sceDmaTag*	dma_ptr;
} DG_DMATASK;

//=============================================================================
// DG E.Field (efield.cc)
//=============================================================================

class DG_MDL_EFIELDDATA : public DG_MDL_SPECIALDATA
{
public: //! check modifier
	ALG_VECTOR	vecCol;
	float		fRefractRateS;
	float		fRefractRateT;

public:
	void	SetMdlParam( DAT128*, DG_MDL* );
	INT32	SetMdlData( DAT128*, DG_MDL* );

	DG_MDL_EFIELDDATA( const DG_MDL_EFIELDDATA& );
	DG_MDL_EFIELDDATA();
	~DG_MDL_EFIELDDATA();

	DG_MDL_EFIELDDATA& operator = ( const DG_MDL_EFIELDDATA& );
};

//=============================================================================
// DG Environ Map (envmap.cc)
//=============================================================================

class DG_MDL_ENVMAPDATA : public DG_MDL_SPECIALDATA
{
public:
	void	SetMdlParam( DAT128*, DG_MDL* );
	INT32	SetMdlData( DAT128*, DG_MDL* );

	DG_MDL_ENVMAPDATA( const DG_MDL_ENVMAPDATA & );
	DG_MDL_ENVMAPDATA();
	~DG_MDL_ENVMAPDATA();

	DG_MDL_ENVMAPDATA& operator = ( const DG_MDL_ENVMAPDATA& );
};

//=============================================================================
// DG Flow Env (flowenv.cc)
//=============================================================================

class DG_MDL_FLOWENVDATA : public DG_MDL_FLOWLINEDATA
{
public:
	void	SetMdlParam( DAT128*, DG_MDL* );
	INT32	SetMdlData( DAT128*, DG_MDL* );

	DG_MDL_FLOWENVDATA( const DG_MDL_FLOWENVDATA& );
	DG_MDL_FLOWENVDATA();
	~DG_MDL_FLOWENVDATA();

	DG_MDL_FLOWENVDATA& operator = ( const DG_MDL_FLOWENVDATA& );
};

//=============================================================================
// DG Flowline (flowline.cc)
//=============================================================================

class DG_MDL_FLOWLINEDATA : public DG_MDL_SPECIALDATA
{
public: //! check modifier
	float		fFlow;
	UINT32		u32dir;
	ALG_VECTOR	vecCol;

public:
	void	SetMdlParam( DAT128*, DG_MDL* );
	INT32	SetMdlData( DAT128*, DG_MDL* );

	DG_MDL_FLOWLINEDATA( const DG_MDL_FLOWLINEDATA& );
	DG_MDL_FLOWLINEDATA();
	~DG_MDL_FLOWLINEDATA();

	DG_MDL_FLOWLINEDATA& operator = ( const DG_MDL_FLOWLINEDATA& );
};

//=============================================================================
// DG Font (font.cc)
//=============================================================================

#if (0)
// possibly added by HVS for the HD Edition
typedef struct CODE_CONV_TREE {
	SINT16			src;
	SINT16			dstCode;
	INT32			nChild;
	CODE_CONV_TREE*	pChild;
} CODE_CONV_TREE;
#endif

/*---------------------------------------------------------------------------*/

class DG_OBJ_FONT
{
private:
	void Print2(char*);
//	void HVSDrawGlyph(INT32, INT32, DG_VERTEX*&, INT32&, INT32, float);

public: //! check modifier
	DG_OBJINFO		info;
	DG_OBJ_POLYGON	pol;
	UINT32			nTag;
	DAT128*			pDat;
	DG_VERTEX*		pVert;
	INT32			nVert;
	DAT128*			pBuf;
	INT32			sizeBuf;
	UINT32			u32Time;
	BOOL32			bPrint;
	ALG_VECTOR		vecCol;
	float			fScale;
//	INT32			m_nKernBias;	// HVS style

public:
	DG_OBJ_FONT();
	~DG_OBJ_FONT();

	void Init( SINT8* );
	void Init( DAT128*, INT32 );
	void Locate( float, float );
	void Draw();
	void Print( SINT8* );
	void SetColor( float, float, float, float );
	void Free();
//	void vGetTextBounds( float*, float*, float*, float* );	// HVS style

	static INT32 CalcBufferSize( INT32*, SINT8* );

	DG_OBJ_FONT& operator = ( DG_OBJ_FONT& );
};

//=============================================================================
// DG Frame (frame_dg.cc)
//=============================================================================

class DG_FRAME
{
public: //! check modifier

	static const UINT32 REQ_FLIP = DEFINE_ME;
	static const UINT32 REQ_SEND = DEFINE_ME;

	enum {
		IDLE,		// Idle
		MAKE,		// Making
		MAKE_COMP,	// Make Complete
		SEND,		// Sending
		SEND_COMP	// Send Complete
	};

	INT32			n_task;
	INT32			end_task;
	UINT32			u32state;
	UINT32			u32ReqFlag;
	UINT128*		pBuffer;
	DG_FRAME*		pOther;
	DG_DRAW_ENV		env;
	tGS_DISPFB1		dispfb1;
	tGS_DISPFB2		dispfb2;
	tGS_PMODE		pmode;
	tGS_DISPLAY1	display1;
	tGS_DISPLAY2	display2;
	UINT32			u32Field;
	UINT32			u32MemID;
	DG_DMATASK		task_list[1024];
	DG_RESETOFFSET	packetResetOffset;

public:
	void InitOffsetPacket();

	static void		ResetFrame();
	static void		ResetDma();
	static void		ClearDma();
	static INT32	CheckMake();
	static void		FinishDmaTask();
	static void		SendPacket();
	static void		RequestSend();
	static void		CallbackFunc();
	static INT32	DmaCheckMake();

	void SetHalfOffset();
	void SetReferenceData();

	static void FlipScreen();
	static void RequestFlip();
	static void SetFrameEnv();
};

//=============================================================================
// DG Light (light.cc)
//=============================================================================

class DG_LIGHT
{
public: //! check modifier
	ALG_VECTOR	vecPos;
	ALG_VECTOR	vecCol;
	float		fNear;
	float		fFar;
	float		fSlant;
	float		fFar2;
	DG_LIGHT*	pPrev;
	DG_LIGHT*	pNext;
	UINT8		u8Type;
	UINT8		u8Flag;
	UINT16		u8Pad0;		// should be "u16Pad0"
	UINT32		u8Pad1;		// should be "u32Pad1"

public:
	DG_LIGHT();
	~DG_LIGHT();

	void		Init();
	void		Init( UINT8, ALG_VECTOR*, ALG_VECTOR*, float, float, UINT8 );
	void		SetParam();
	void		On();
	void		Off();
	float		GetfSlant();
	float		GetfFar2();
	DG_LIGHT*	GetNext();

	static void			InitSystem();
	static void			Reset();
	static DG_LIGHT*	GetAmbient();
	static void			GetAmbient( ALG_VECTOR* );
	static void			GetStageAmbient( ALG_VECTOR* );
	static void			SearchLight( ALG_VECTOR*);
	static INT32		SearchStageLight( ALG_VECTOR* );
	static void			GetLightMatrix( ALG_MATRIX*, ALG_VECTOR* );
	static void			SetLightMatrix( ALG_MATRIX*, ALG_VECTOR* );
	static void			GetStageLightMatrix( ALG_MATRIX*, ALG_MATRIX* );
	static void			SetStageLightMatrix( ALG_MATRIX* );
	static void			GetColorMatrix( ALG_MATRIX* );
	static void			GetStageColorMatrix( ALG_MATRIX* );
	static void			PreshadeObj( DEF_OBJ*, ALG_MATRIX* );
	static void			PreshadeObj( DEF_OBJ* );
	static DG_LIGHT*	GetPointLight();
	static DG_LIGHT*	GetStaticPointLight();
	static DG_LIGHT*	GetDirLight();
	static void			PushLightEnv( DG_LIGHT** );
	static void			PopLightEnv( DG_LIGHT** );

public: //! check modifier
	const INT32 MAX_I_LIGHT = DEFINE_ME;

	static DG_LIGHT*	plitInf[4];
	static DG_LIGHT		litPoint;
	static DG_LIGHT		litPointStatic;
	static DG_LIGHT		litDir;
	static DG_LIGHT		litAmbient;
	static ALG_VECTOR	vecDirLight;

public:
	DG_LIGHT& operator = ( const DG_LIGHT& );
};

//=============================================================================
// DG Make Packet (mkpk.cc)
//=============================================================================

typedef struct _DG_MDLPACKET
{
public: //! check modifier
	DAT128		tagDma;
	DAT128		prog;
	ALG_MATRIX	matL2Screen;
	ALG_MATRIX	matLocalLight;
	DAT128		tagLast[];

public:
	_DG_MDLPACKET();

	_DG_MDLPACKET& operator = ( const _DG_MDLPACKET& );
}
DG_MDLPACKET;

/*---------------------------------------------------------------------------*/

typedef struct _DG_MDLPACKET_TRANS
{
public: //! check modifier
	DAT128		tagDma;
	DAT128		prog;
	ALG_MATRIX	matL2Screen;
	ALG_MATRIX	matLocalLight;
	ALG_MATRIX	matColor;
	ALG_VECTOR	ambColor;
	DAT128		tagExec;
	DAT128		tagDmaCl;

public:
	_DG_MDLPACKET_TRANS();

	_DG_MDLPACKET_TRANS& operator = ( const _DG_MDLPACKET_TRANS& );
}
DG_MDLPACKET_TRANS;

/*---------------------------------------------------------------------------*/

typedef struct _DG_OBJPACKET
{
public: //! check modifier
	DAT128		tagDma;
	ALG_MATRIX	matColor;
	ALG_VECTOR	ambColor;

public:
	_DG_OBJPACKET();

	_DG_OBJPACKET& operator = ( const _DG_OBJPACKET& );
}
DG_OBJPACKET;

//=============================================================================
// DG Object (obj.cc)
//=============================================================================

class DG_MDL
{
public: //! check modifier
	ALG_MATRIX		matLL2Local;
	ALG_MATRIX		matLL2World;
	ALG_VECTOR		vecCenter;
	DG_MDL*			pmdlParent;
	DG_MDL*			pmdlChild;
	DG_MDL*			pmdlSibling;
	UINT32			u32Sortz;
	UINT16			u16Flag;
	UINT16			u16mdBound;
	DEF_MDL*		pdmdl;
	DG_MDL_SPECIALDATA* pSpecial;
	DG_MDL*			pSortNext;
	INT32 (*pfuncShape)(void*, DG_MDL*, DAT128*);
	void*			pdatShape;
	ALG_MATRIX*		pmatW2Local;
	UINT8			u8bFar;
	UINT8			u8Pad;
	DEF_TEXLIST*	pTlst;

public:
	void CalcMdlWorld();
	void CalcLL2Local();
	void MoveStageLL2Local( ALG_MATRIX* );
	void CalcStageMatrix();

	DG_MDL();

	DG_MDL& operator = ( const DG_MDL& );
};

/*---------------------------------------------------------------------------*/

class DG_OBJ
{
public: //! check modifier
	DG_OBJINFO	info;
	ALG_MATRIX	matL2World;
	ALG_MATRIX	matLL2World;
	DG_MDL*		pmdlParent;
	INT32		nbMdl
	DEF_OBJ*	pdobj;
	UINT16		u16mdBound;
	UINT8		u8Alpha;
	DG_LIGHT*	plitDir;
	DG_MDL		mdl[];

public:
	void CalcMdlWorld( INT32 );
	void CalcMdlWorld( DG_MDL* );
	void SetFlag( UINT16 );
	void ResetFlag( UINT16 );
	void SetEffectFlag();
	void ResetPrecalcFlag();
	void SetParentBox();
	void CalcStageMatrix();
	void SetOrder( UINT32 );

	DG_OBJ();

	DG_OBJ& operator = ( const DG_OBJ& );
};

/*---------------------------------------------------------------------------*/

class DG_OBJPTR
{
public: //! check modifier
	DG_OBJ* pobj;

public:
	DG_OBJPTR();
	~DG_OBJPTR();

	DG_OBJ* operator DG_OBJ* ();
	DG_OBJ* operator -> ();

	void Destroy();
};

/*---------------------------------------------------------------------------*/

class DG_MDL_SPECIALDATA
{
	/* VTable */

public: //! check modifier

	enum {
		FLAG_FLOWLINE	= 0x01,
		FLAG_ENVMAP		= 0x02,
		FLAG_REFRACTION	= 0x04,
		FLAG_ENEFIELD	= 0x08
	};

	UINT8 u8Flag;

public:
	void	SetMdlParam( DAT128*, DG_MDL* );
	INT32	SetMdlData( DAT128*, DG_MDL* );
	void	PreAct( DG_MDL* );

	~DG_MDL_SPECIALDATA();
	DG_MDL_SPECIALDATA( const DG_MDL_SPECIALDATA& );
	DG_MDL_SPECIALDATA();

	DG_MDL_SPECIALDATA& operator =( const DG_MDL_SPECIALDATA& );
};

//=============================================================================
// DG Polygon (polygon.cc)
//=============================================================================

class DG_VERTEX
{
public: //! check modifier
	float	fS;				// Vertex S
	float	fT;				// Vertex T
	float	fQ;				// Vertex Q
	float	fPad;
	float	fR,fG,fB,fA;	// RGBA
	float	fX,fY,fZ;		// XYZ
	UINT32	u32Kick;

public:
	void		SetST( float, float );
	void		SetRGBA( float, float, float, float );
	void		SetXYZ( ALG_VECTOR* );
	void		SetXYZ( float, float, float );
	void		SetAspectXYZ( ALG_VECTOR*, UINT8 );
	void		SetAspectXYZ( float, float, float, UINT8 );
	void		SetKick();
	void		SetNoKick();
	void		Interpolate( DG_VERTEX*, DG_VERTEX*, float );
	ALG_VECTOR* GetpvecPos();
};

/*---------------------------------------------------------------------------*/

class DG_OBJ_POLYGON
{
// TODO: HVS added their own stuff for the HD Edition.
// Remove it after examining the PS2 code.
// Obvious additions by HVS have been commented out.

public:
	void CalcBoundBox();

public: //! check modifier
	DG_OBJINFO		info;
	ALG_MATRIX		matL2World;
	float			lx,ly,lz;
	float			ux,uy,uz;
	float			fPrio;
	DEF_TEXLIST*	pTlst;
	UINT32			prim;
	UINT32			primClip;
	UINT32			nTex;
	UINT32			nVert;
	UINT16			u16mdBound;
	SINT8			s8NoDrawBuf;
	UINT8			u8DrawCtr;
	DG_VERTEX*		pVert;
	DG_VERTEX*		pVert2;
	DAT128*			pdatPre;
	DAT128*			pdatPost;
	UINT16			u16qwszDatPre;
	UINT16			u16qwszDatPost;

//	UINT16				hvsFlags;
//	bool				m_bApplyWSOffsetsAlways;
//	bool				m_bApplyWidescreenScale;
//	HVS_WSPositionScale	m_oWidescreenPosScale;

	UINT32*			pindex[2];
	UINT32			u32NumIndices;

public:
	UINT32* GetIndexBuf( UINT32 );
	UINT32	GetNumIndices();
	void	SetIndexBuf( UINT32* );
	void	SetNumIndices( UINT32 );

public: //! check modifier
//	D3DVertexBuffer	m_oInputVB;
//	bool			m_bInputVBSet;
//	D3DIndexBuffer	m_oIndexBuffer;

public:
	DG_OBJ_POLYGON();

	void		Init( DG_VERTEX*, DG_VERTEX*, INT32, UINT16, UINT32, UINT8*, INT32, UINT16, DEF_TEXLIST* );
	void		Init( DG_VERTEX*, INT32, UINT16, UINT32, UINT8*, INT32, UINT16, DEF_TEXLIST* );
	void		SetPriority( float );
	void		SetPreData( DAT128*, UINT16 );
	void		SetPostData( DAT128*, UINT16 );
	void		SetOrder( UINT32 );
//	void		vSetPseudo3D( bool );
//	void		vSetXWidescreenScale( bool, float );
//	void		vSetWidescreenPositionScale( HVS_WSPositionScale );
//	void		vSetWidescreenPositionScale( float, float, float, float );
	DG_VERTEX*	Vertex();
	DG_VERTEX*	PrevVertex();
	void		SwapBuffer();
	void		Init2DMat();
	void		Align2DMat();
	void		Draw();

public: //! check modifier
//	float		m_fRotation;
//	void*		m_pOverrideTexture;
//	bool		m_bDoBlur;
//	int32		m_eBlurShader;
//	bool		m_bVerticalPass;
//	float		m_fBlurAmount;
//	void (*m_vDrawCallback)(DG_OBJ_POLYGON*);
//	void (*m_vSetupShaderCallback)(DG_OBJ_POLYGON*);
//	bool		m_bPseudo3D;

public:
	DG_OBJ_POLYGON& operator = ( DG_OBJ_POLYGON& );
};

//=============================================================================
// DG Queue (que.cc)
//=============================================================================

class DG_QUEUE
{
public: //! check modifier
	DG_OBJINFO lnkTop;
	DG_OBJINFO lnkEnd;

public:
	void Draw( void (**)(void) );	// TODO: ret/arg types, double ptr
	void SwapBuffers();
	void Reset();
	void Init();

	DG_QUEUE();
};

/*---------------------------------------------------------------------------*/

class DG_OBJ_QUE
{
public: //! check modifier
	DG_OBJINFO	info;
	ALG_MATRIX	matL2World;
	float		lx,ly,lz;
	float		ux,uy,uz;
	UINT16		u16mdBound;
	DG_OBJINFO	lnkTop;
	DG_OBJINFO	lnkEnd;

public:
	DG_OBJ_QUE();

	void	Reset();
	void	Queue( void* );
	void	Dequeue( void* );
	BOOL32	IsEmpty();
	void	Draw();
	void	SetOrder( UINT32 );
	void	Iterate( void (*)(void) ); // TODO: ret/arg types

	DG_OBJ_QUE& operator = ( const DG_OBJ_QUE& );
};

//=============================================================================
// DG Refraction Map (refrmap.cc)
//=============================================================================

class DG_MDL_REFRACTDATA : public DG_MDL_SPECIALDATA
{
public: //! check modifier
	ALG_VECTOR	vecCol;
	float		fRefractRateS;
	float		fRefractRateT;

public:
	void	SetMdlParam( DAT128*, DG_MDL* );
	INT32	SetMdlData( DAT128*, DG_MDL* );

	DG_MDL_REFRACTDATA( const DG_MDL_REFRACTDATA& );
	DG_MDL_REFRACTDATA();
	~DG_MDL_REFRACTDATA();

	DG_MDL_REFRACTDATA& operator = ( const DG_MDL_REFRACTDATA& );
};

//=============================================================================
// DG Sort (sort.cc)
//=============================================================================

class DG_OBJINFO
{
public: //! check modifier
	UINT8		u8Type;
	UINT8		u8Chanl;
	UINT16		u16Flag;
	UINT32		u32Sortz;
	DG_OBJINFO*	pPrev;
	DG_OBJINFO*	pNext;
	DG_OBJINFO*	pSortNext;

public:
	void Init( UINT8 );

// *** HVS additions ***
//	void	vSetNmObj(char*);
//	char*	szGetNmObj();

	DG_OBJINFO();
	DG_OBJINFO( UINT8 );

	void InstallOtag();
	void SetEffectFlag();
	void SetOrder( UINT32 );
};

//=============================================================================
// DG Texture (texture.cc)
//=============================================================================

class DG_DYNAMIC_TEXTURE
{
public: //! check modifier
	DEF_TEXLIST	texlist;
	DEF_TEXTURE	tex;
	DEF_CLUT	clut;

public:
	void Init( UINT32, INT32, INT32, UINT32, UINT8, UINT8, UINT8 );
};

/*---------------------------------------------------------------------------*/

class DG_TEXTURE_BUFFER
{
public: //! check modifier
	UINT32			u32nResi;
	UINT32			u32nNonResi;
	UINT32			u32nOnMemory;
	BOOL32			bReqFlush;
	DEF_TEXLIST*	pTlstResident[400];
	DEF_TEXLIST*	pTlstNonResident[400];
	DEF_TEXLIST*	pTlstOnMemory[800];

public:
	void Install( DEF_TEXLIST* );
	void Flush();
	void ReqFlush();
	void Reset();
	void ResetNonResident();

// *** HVS additions ***
//	void vMarkHVSNonResidentForRelease();
//	void vReleaseHVSTextures();
};

//=============================================================================
// Global Functions
//=============================================================================

/* dgd.cc */
void DG_InitClean();
void DG_StartDaemon();

/* debugprim.cc */
void DG_DebugPrimDaemon( int );

#endif /* END OF FILE */
