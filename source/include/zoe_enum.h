#ifndef INCLUDED_ZOE_ENUM_H
#define INCLUDED_ZOE_ENUM_H

/*---------------------------------------------------------------------------*/

// ref.default.pdb
enum {
	GS_REGS_PRIM,
	GS_REGS_RGBA,
	GS_REGS_STQ,
	GS_REGS_UV,
	GS_REGS_XYZF2,
	GS_REGS_XYZ2,
	GS_REGS_TEX0_1,
	GS_REGS_TEX0_2,
	GS_REGS_CLAMP_1,
	GS_REGS_CLAMP_2,
	GS_REGS_FOG,
	GS_REGS_0B_UNDEFINED,
	GS_REGS_XYZF3,
	GS_REGS_XYZ3,
	GS_REGS_AD,
	GS_REGS_NOP
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
enum {
	OPTBITFLAG_VIBRATION,
	OPTBITFLAG_DEMO_CAPTION,
	OPTBITFLAG_BATTLE_CAPTION,
	OPTBITFLAG_STEREO
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
enum {
	OPTLANG_JAPANESE,
	OPTLANG_ENGLISH,
	OPTLANG_FRENCH,
	OPTLANG_GERMAN,
	OPTLANG_ITALIAN,
	OPTLANG_SPANISH,
	OPTLANG_PORTUGUESE
};

/*---------------------------------------------------------------------------*/

// ref.default.pdb
enum {
	Q_EMPTY,
	Q_WAIT,
	Q_EXEC,
	Q_SUSPEND
};

#endif /* END OF FILE */
