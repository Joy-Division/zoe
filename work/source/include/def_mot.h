/*
 * Motion Format Definitions
 */
#ifndef INC_DEF_MOT_H
#define INC_DEF_MOT_H

#include "global.h"

// ref.default.pdb
typedef struct _DEF_MOTION {
	float32 fFrame;
	uint32  nbNode;
	uint32  pad1;
	uint32  pad2;
} DEF_MOTION;

// ref.default.pdb
typedef struct _DEF_MOTION_LIST {
	uint32  nbMotion;
} DEF_MOTION_LIST;

// ref.default.pdb
typedef struct _DEF_MOTION_NODE {
	uint16  u16Flag;
	uint16  u16nbElm;
	uint32  nbData;
	uint16* pKeyData;
	sint16* pMotData;
} DEF_MOTION_NODE;

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
