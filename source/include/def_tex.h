/*
 * "ZONE OF THE ENDERS"
 * Texture Format Definitions
 */
#ifndef INCLUDED_DEF_TEX_H
#define INCLUDED_DEF_TEX_H

#include <eestruct.h>

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

// ref.default.pdb
typedef struct _DEF_TEXTURE {
	sceGsTex0   regTex;
	uint16      rw;
	uint16      rh;
	void*       pData;
} DEF_TEXTURE;

// ref.default.pdb
typedef struct _DEF_CLUT {
	sceGsTex0       regClut;
	DEF_TEXTURE*    pTex;
	void*           pData;
	sceGsClamp      regClamp;
	uint8           u8AlphaABCD;
	uint8           u8AlphaFIX;
	uint16          u16Flag;
	uint32          pad1;
} DEF_CLUT;

// ref.default.pdb
typedef struct _DEF_TEXLIST {
	uint16          u16nTex;
	uint16          u16Flag;
	DEF_TEXTURE*    pTex;
	uint32          nClut;
	DEF_CLUT*       pClut;
} DEF_TEXLIST;

#endif /* END OF FILE */
