#ifndef INCLUDED_DEF_TEX_H
#define INCLUDED_DEF_TEX_H

#include <eestruct.h>

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

typedef struct _DEF_TEXTURE {
	sceGsTex0	regTex;		// TEX0 register
	UINT16		rw;			// width
	UINT16		rh;			// height
	void*		pData;		// data addr
} DEF_TEXTURE;

typedef struct _DEF_CLUT {
	sceGsTex0		regClut;		// TEX0 register
	DEF_TEXTURE*	pTex;			// texture addr
	void*			pData;			// data addr
	sceGsClamp		regClamp;		// CLAMP register
	UINT8			u8AlphaABCD;	// CLUT alpha ABCD
	UINT8			u8AlphaFIX;		// CLUT alpha FIX
	UINT16			u16Flag;		// CLUT flags
	UINT32			pad1;			// alignment
} DEF_CLUT;

typedef struct _DEF_TEXLIST {
	UINT16			u16nTex;	// texture count
	UINT16			u16Flag;	// texture flags
	DEF_TEXTURE*	pTex;		// texture addr
	UINT32			nClut;		// CLUT count
	DEF_CLUT*		pClut;		// CLUT addr
} DEF_TEXLIST;

#endif /* END OF FILE */
