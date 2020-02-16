/*
 * Sound Driver for PS2 IOP
 * Internal Include
 *
 * ver."ZONE OF THE ENDERS"
 */
#ifndef INC_SD_INCL_H
#define INC_SD_INCL_H

#include <sys/types.h>

/*---------------------------------------------------------------------------*
 * Struct Types ref."beatmania APPEND 5thMIX"
 *---------------------------------------------------------------------------*/
struct WAVE_W {
	u_long  addr;
	char    sample_note;
	char    sample_tune;
	u_char  a_mode;
	u_char  ar;
	u_char  dr;
	u_char  s_mode;
	u_char  sr;
	u_char  sl;
	u_char  r_mode;
	u_char  rr;
	u_char  pan;
	u_char  dec_vol;
};

struct SPU_TRACK_REG {
	u_short vol_l;
	u_short vol_r;
	int     vol_fg;
	u_short pitch;
	int     pitch_fg;
	u_long  addr;
	int     addr_fg;
	long    a_mode;
	u_short ar;
	u_short dr;
	int     env1_fg;
	long    s_mode;
	u_short sr;
	u_short sl;
	int     env2_fg;
	long    r_mode;
	u_short rr;
	int     env3_fg;
};

struct SETBL {
	u_char  pri;
	u_char  tracks;
	u_char  kind;
	u_char  character;
	u_char *addr[3]; // possibly NOT fixed at 3 here
};

struct SEPLAYTBL {
	u_char  pri;
	u_char  kind;
	u_char  character;
	u_char *addr;
	u_long  code;
};

struct SOUND_W {
	u_char *mpointer;
	u_char  ngc;
	u_char  ngo;
	u_char  ngs;
	u_char  ngg;
	u_char  lp1_cnt;
	u_char  lp2_cnt;
	int     lp1_vol;
	int     lp2_vol;
	int     lp1_freq;
	int     lp2_freq;
	u_char *lp1_addr;
	u_char *lp2_addr;
	u_char *lp3_addr;
	u_char  kakfg;
	u_char *kak1ptr;
	u_char *kak2ptr;
	u_char  pvoc;
	int     pvod;
	int     pvoad;
	u_int   pvom;
	u_char  vol;
	char    panc;
	int     pand;
	int     panad;
	int     panm;
	char    panf;
	char    panoff;
	char    panmod;
	u_char  swpc;
	u_char  swphc;
	u_int   swpd;
	int     swpad;
	u_int   swpm;
	u_char  swsc;
	u_char  swshc;
	char    swsk;
	int     swss;
	u_char  vibhc;
	u_int   vib_tmp_cnt;
	u_char  vib_tbl_cnt;
	u_char  vib_tc_ofst;
	u_char  vibcc;
	u_int   vibd;
	u_int   vibdm;
	u_char  vibhs;
	u_char  vibcs;
	u_char  vibcad;
	u_int   vibad;
	u_int   rdmc;
	u_int   rdmo;
	u_char  rdms;
	u_int   rdmd;
	char    trec;
	u_char  trehc;
	char    tred;
	u_char  trecad;
	u_char  trehs;
	u_int   snos;
	int     ptps;
	u_long  dec_vol;
	int     tund;
	u_int   tmpd;
	u_char  tmp;
	u_int   tmpad;
	u_char  tmpc;
	u_int   tmpw;
	u_char  tmpm;
	u_int   rest_fg;
	char    macro;
	char    micro;
	u_short rrd;
/* ---------------------- */
/* add. for PlayStation 2 */
/* ---------------------- */
	u_int   unkD4;
	u_char  unkD8;
	u_char  unkD9; // padding?
	u_char  unkDA; // padding?
	u_char  unkDB; // padding?
	void   *unkDC;
	u_char  unkE0;
	u_char  unkE1;
	u_char  unkE2; // padding?
	u_char  unkE3; // padding?
	u_int   unkE4;
	u_char  unkE8;
	u_char  unkE9;
	u_char  unkEA;
	u_char  unkEB;
	u_char  unkEC;
	u_char  unkED;
	u_char  unkEE;
	u_char  unkEF;
	u_char  unkF0;
	u_char  unkF1;
	u_char  unkF2;
	u_char  unkF3;
	u_char  unkF4;
	u_char  unkF5;
	u_char  unkF6;
	u_char  unkF7;
	u_char  unkF8;
	u_char  unkF9; // padding?
	u_char  unkFA; // padding?
	u_char  unkFB; // padding?
};

/*---------------------------------------------------------------------------*
 * Additional Struct Types
 *---------------------------------------------------------------------------*/
// the definition of this is definitely bad,
// causes problems in mno_set
struct unkstr24 {
	u_int   unk00;
	u_int   unk04;
	u_int   unk08;
	u_int   unk0C;
	u_char *unk10;
	u_int   unk14;
};
// same here
struct unkstr16 {
	int unk00;
	int unk04;
	int unk08;
	int unk0C;
};
// used by sd_file, some kind of tiny header struct for sdx files?
struct unkstr08 {
	u_int unk00;
	u_int unk04;
};

// used by iop_main RecieveInit?
// total size 0x230?
struct unkstrbig {
	u_char pad000[512]; // 0x200
	u_int unk200;
	u_int unk204;
	u_int unk208;
	u_char pad20C[32]; // 0x20
	u_int unk22C;
};

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=euc-jp : */
