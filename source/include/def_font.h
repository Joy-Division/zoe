#ifndef INCLUDED_DEF_FONT_H
#define INCLUDED_DEF_FONT_H

#include "global.h"
#include "zoe_defs.h"
#include "zoe_types.h"

typedef struct _DEF_HANKAKU_PROP {
	UINT16 u16width;
	UINT16 u16index;
} DEF_HANKAKU_PROP;

// ref.『ZONE OF THE ENDERS HD EDITION』(PSN ver.)
// *USRDIR/ZoE1/stage/title/ExtractSpacingInfo.rb
typedef struct _DEF_FONT_TABLE {
	UINT16	u16nTex;			// 00-01:The_number_of_Fontotekusuchadeta
	UINT16	u16SizeTex;			// 02-03:1Sentence_texture_data_size_characters
	UINT8	u8width;			// 04-04:Sumi_Tamotsu_width
	UINT8	u8height;
	UINT16	u16Kind;			// 06-07:Font_Type
	void*	pTexTop;			// 08-11:Top_Fontotekusuchadeta

	UINT16*				ptabIndex;			// 12-15:EUC -> Table_Index
	DEF_HANKAKU_PROP*	pHankakuPropTop;	// 16-19:The_top_half_of_the_property_data
	UINT32				pad1,pad2,pad3;		// 20-31:

	UINT32				u32ColClut[16];		// 32-96:CLUT Column_colors_(from_lowRGBA)
} DEF_FONT_TABLE ALIGN16;

#endif /* END OF FILE */
