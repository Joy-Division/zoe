#ifndef INCLUDED_DEF_MDL_H
#define INCLUDED_DEF_MDL_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

#include "def_tex.h"
#include "libalg.h"
//#include "libdg.h"

// external
typedef struct _DG_MATERIAL DG_MATERIAL;

/*---------------------------------------------------------------------------*/

typedef struct _DEF_OBJ {
	UINT32			u32Flag;
	UINT16			u16nMdl;
	UINT16			u16szMdl;
	float			lx,ly,lz;
	float			ux,uy,uz;
	void*			pBuf;
	UINT32			u32size;
	DEF_TEXLIST*	pTlst;
	float			fScale;
} DEF_OBJ;

/*---------------------------------------------------------------------------*/

typedef struct _DEF_STRIP {
	DG_MATERIAL*	pmtr;
	UINT16			u16Flag;
	UINT16			u16nVert;
	SINT16*			ps16Vert;
	SINT16			s16Clut;
	UINT16			u16TBP0;
	void*			pTag;
	UINT32			u32pad0;
	UINT8			u8EnvFlag;
	UINT8			u8pad1;
	SINT16			s16Clut2;
	SINT16			s16Clut3;
	UINT16			u16pad2;
} DEF_STRIP;

/*---------------------------------------------------------------------------*/

typedef struct _DEF_MDL {
	FMATRIX		matLocal;
	float		lx,ly,lz;
	float		ux,uy,uz;
	UINT16		u16Flag;
	SINT16		s16Parent;
	SINT16		s16Child;
	SINT16		s16Sibling;
	UINT16		u16nStrip;
	UINT16		u16szStrip;
	DEF_STRIP*	pStrip;
	UINT8		u8Env1;
	UINT8		u8Env2;
	UINT8		u8spType;
	UINT8		u8Env3;
} DEF_MDL;

/*---------------------------------------------------------------------------*/

typedef struct _DEF_MDL_ENVMAP {
	char*	pName;
	UINT32	pad0;
	UINT32	pad1;
	UINT32	pad2;
} DEF_MDL_ENVMAP;

/*---------------------------------------------------------------------------*/

typedef struct _DEF_MDL_FLOWLINE
{
public: //! check modifier
	ALG_VECTOR	vecStart;
	ALG_VECTOR	vecEnd;
	ALG_VECTOR	vecSide;

public:
	_DEF_MDL_FLOWLINE()
	{/* TODO */}

	_DEF_MDL_FLOWLINE& operator = ( const _DEF_MDL_FLOWLINE& ref )
	{/* TODO */}
}
DEF_MDL_FLOWLINE;

#endif /* END OF FILE */
