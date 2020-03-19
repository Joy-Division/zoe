/*
 * "ZONE OF THE ENDERS"
 * DMA Tag Format Definitions
 */
#ifndef INCLUDED_TAGDEF_H
#define INCLUDED_TAGDEF_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

// ref.default.pdb
typedef struct _TAG_CNTCODE {
	uint32 tagdma[4];
} TAG_CNTCODE;

// ref.default.pdb
typedef struct _TAG_EFLDEXEC {
	uint32 tagdma[8];
} TAG_EFLDEXEC;

// ref.default.pdb
typedef struct _TAG_ENVEXEC {
	uint32 tagdma[8];
} TAG_ENVEXEC;

// ref.default.pdb
typedef struct _TAG_ENVTEX {
	uint32 tagdma[4];
	uint64 taggif[8];
} TAG_ENVTEX;

// ref.default.pdb
typedef struct _TAG_FLOWEXEC {
	uint32 tagdma[8];
} TAG_FLOWEXEC;

// ref.default.pdb
typedef struct _TAG_FLOWTEST {
	uint32 tagdma[4];
	uint64 taggif[2];
} TAG_FLOWTEST;

// ref.default.pdb
typedef struct _TAG_FLOWTEX {
	uint32 tagdma[4];
	uint64 taggif[8];
} TAG_FLOWTEX;

// ref.default.pdb
typedef struct _TAG_FLOWVEC {
	uint32  tagdma[4];
	float   vecData[16]:
} TAG_FLOWVEC;

// ref.default.pdb
typedef struct _TAG_GENVCNT {
	uint32 tagdma[8];
} TAG_GENVCNT;

// ref.default.pdb
typedef struct _TAG_MATREF {
	uint32 tagdma[4];
} TAG_MATREF;

// ref.default.pdb
typedef struct _TAG_REFREXEC {
	uint32 tagdma[8];
} TAG_REFREXEC;

// ref.default.pdb
typedef struct _TAG_REFRTEX {
	uint32 tagdma[4];
	uint64 taggif[8];
} TAG_REFRTEX;

// ref.default.pdb
typedef struct _TAG_RETCODE {
	uint32 tagdma[4];
} TAG_RETCODE;

// ref.default.pdb
typedef struct _TAG_STRIPENV {
	uint32 tagdma0[4];
	uint32 u32param[4];
	uint64 taggifclip[2];
	uint64 taggif[2];
} TAG_STRIPENV;

// ref.default.pdb
typedef struct _TAG_TEXTURE {
	uint32 tagdma[4];
	uint64 taggif[8];
} TAG_TEXTURE;

// ref.default.pdb
typedef struct _TAG_VECREF {
	uint32 tagdma[4];
} TAG_VECREF;

// ref.default.pdb
typedef struct _TAG_VECREFWEIGHT {
	uint32 tagmask[4];
	uint32 tagdma[4];
} TAG_VECREFWEIGHT;

#endif /* END OF FILE */
