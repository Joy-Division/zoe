#ifndef INCLUDED_DEF_TEX_H
#define INCLUDED_DEF_TEX_H

#include <eestruct.h>

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

// ref.default.pdb
typedef struct _DEF_TEXTURE {
	sceGsTex0	regTex;		// TEX0 register
	uint16		rw;			// width
	uint16		rh;			// height
	void*		pData;		// data addr
} DEF_TEXTURE;

// ref.default.pdb
typedef struct _DEF_CLUT {
	sceGsTex0		regClut;		// TEX0 register
	DEF_TEXTURE*	pTex;			// texture addr
	void*			pData;			// data addr
	sceGsClamp		regClamp;		// CLAMP register
	uint8			u8AlphaABCD;	// CLUT alpha ABCD
	uint8			u8AlphaFIX;		// CLUT alpha FIX
	uint16			u16Flag;		// CLUT flags
	uint32			pad1;			// alignment
} DEF_CLUT;

// ref.default.pdb
typedef struct _DEF_TEXLIST {
	uint16			u16nTex;	// texture count
	uint16			u16Flag;	// texture flags
	DEF_TEXTURE*	pTex;		// texture addr
	uint32			nClut;		// CLUT count
	DEF_CLUT*		pClut;		// CLUT addr
} DEF_TEXLIST;

#endif /* END OF FILE */
