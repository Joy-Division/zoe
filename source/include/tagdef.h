#ifndef INCLUDED_TAGDEF_H
#define INCLUDED_TAGDEF_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

typedef struct _TAG_CNTCODE {
	UINT32 tagdma[4];
} TAG_CNTCODE;

typedef struct _TAG_EFLDEXEC {
	UINT32 tagdma[8];
} TAG_EFLDEXEC;

typedef struct _TAG_ENVEXEC {
	UINT32 tagdma[8];
} TAG_ENVEXEC;

typedef struct _TAG_ENVTEX {
	UINT32 tagdma[4];
	UINT64 taggif[8];
} TAG_ENVTEX;

typedef struct _TAG_FLOWEXEC {
	UINT32 tagdma[8];
} TAG_FLOWEXEC;

typedef struct _TAG_FLOWTEST {
	UINT32 tagdma[4];
	UINT64 taggif[2];
} TAG_FLOWTEST;

typedef struct _TAG_FLOWTEX {
	UINT32 tagdma[4];
	UINT64 taggif[8];
} TAG_FLOWTEX;

typedef struct _TAG_FLOWVEC {
	UINT32 tagdma[4];
	float vecData[16]:
} TAG_FLOWVEC;

typedef struct _TAG_GENVCNT {
	UINT32 tagdma[8];
} TAG_GENVCNT;

typedef struct _TAG_MATREF {
	UINT32 tagdma[4];
} TAG_MATREF;

typedef struct _TAG_REFREXEC {
	UINT32 tagdma[8];
} TAG_REFREXEC;

typedef struct _TAG_REFRTEX {
	UINT32 tagdma[4];
	UINT64 taggif[8];
} TAG_REFRTEX;

typedef struct _TAG_RETCODE {
	UINT32 tagdma[4];
} TAG_RETCODE;

typedef struct _TAG_STRIPENV {
	UINT32 tagdma0[4];
	UINT32 u32param[4];
	UINT64 taggifclip[2];
	UINT64 taggif[2];
} TAG_STRIPENV;

typedef struct _TAG_TEXTURE {
	UINT32 tagdma[4];
	UINT64 taggif[8];
} TAG_TEXTURE;

typedef struct _TAG_VECREF {
	UINT32 tagdma[4];
} TAG_VECREF;

typedef struct _TAG_VECREFWEIGHT {
	UINT32 tagmask[4];
	UINT32 tagdma[4];
} TAG_VECREFWEIGHT;

#endif /* END OF FILE */
