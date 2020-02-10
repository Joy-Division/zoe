/*
 * Model Format Definitions
 */
#ifndef INC_DEF_MDL_H
#define INC_DEF_MDL_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"
#include "def_tex.h"
#include "libalg.h"
#include "libdg.h"

// external
typedef struct _DG_MATERIAL DG_MATERIAL;

// ref.default.pdb
typedef struct _DEF_OBJ {
	uint32          u32Flag;
	uint16          u16nMdl;
	uint16          u16szMdl;
	float           lx, ly, lz;
	float           ux, uy, uz;
	void*           pBuf;
	uint32          u32size;
	DEF_TEXLIST*    pTlst;
	float           fScale;
} DEF_OBJ;

// ref.default.pdb
typedef struct _DEF_STRIP {
	DG_MATERIAL*    pmtr;
	uint16          u16Flag;
	uint16          u16nVert;
	sint16*         ps16Vert;
	sint16          s16Clut;
	uint16          u16TBP0;
	void*           pTag;
	uint32          u32pad0;
	uint8           u8EnvFlag;
	uint8           u8pad1;
	sint16          s16Clut2;
	sint16          s16Clut3;
	uint16          u16pad2;
} DEF_STRIP;

// ref.default.pdb
typedef struct _DEF_MDL {
	FMATRIX     matLocal;
	float       lx, ly, lz;
	float       ux, uy, uz;
	uint16      u16Flag;
	sint16      s16Parent;
	sint16      s16Child;
	sint16      s16Sibling;
	uint16      u16nStrip;
	uint16      u16szStrip;
	DEF_STRIP*  pStrip;
	uint8       u8Env1;
	uint8       u8Env2;
	uint8       u8spType;
	uint8       u8Env3;
} DEF_MDL;

// ref.default.pdb
typedef struct _DEF_MDL_ENVMAP {
	char* pName;
	uint32 pad0, pad1, pad2;
} DEF_MDL_ENVMAP;

// ref.default.pdb
typedef struct _DEF_MDL_FLOWLINE
{
public: //! unconfirmed modifier
	ALG_VECTOR vecStart;
	ALG_VECTOR vecEnd;
	ALG_VECTOR vecSide;

public:
	_DEF_MDL_FLOWLINE()
	{/* TODO */}

	_DEF_MDL_FLOWLINE& operator=( const _DEF_MDL_FLOWLINE& ref )
	{/* TODO */}
}
DEF_MDL_FLOWLINE;

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
