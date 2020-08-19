#ifndef INCLUDED_DEF_MOT_H
#define INCLUDED_DEF_MOT_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

typedef struct _DEF_MOTION {
	float	fFrame;
	UINT32	nbNode;
	UINT32	pad1;
	UINT32	pad2;
} DEF_MOTION;

typedef struct _DEF_MOTION_LIST {
	UINT32	nbMotion;
} DEF_MOTION_LIST;

typedef struct _DEF_MOTION_NODE {
	UINT16	u16Flag;
	UINT16	u16nbElm;
	UINT32	nbData;
	UINT16*	pKeyData;
	SINT16*	pMotData;
} DEF_MOTION_NODE;

#endif /* END OF FILE */
