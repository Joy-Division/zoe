#ifndef INCLUDED_DEF_MOT_H
#define INCLUDED_DEF_MOT_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

// ref.default.pdb
typedef struct _DEF_MOTION {
	float   fFrame;
	uint32  nbNode;
	uint32  pad1;
	uint32  pad2;
} DEF_MOTION;

// ref.default.pdb
typedef struct _DEF_MOTION_LIST {
	uint32 nbMotion;
} DEF_MOTION_LIST;

// ref.default.pdb
typedef struct _DEF_MOTION_NODE {
	uint16  u16Flag;
	uint16  u16nbElm;
	uint32  nbData;
	uint16* pKeyData;
	sint16* pMotData;
} DEF_MOTION_NODE;

#endif /* END OF FILE */
