/*
 * Sound Driver for PS2 IOP
 * Internal Include
 *
 * ver.ZONE OF THE ENDERS
 */
#ifndef INC_SD_INCL_H
#define INC_SD_INCL_H

#include <sys/types.h>

/*---------------------------------------------------------------------------*
 * Structures
 *---------------------------------------------------------------------------*/

// ref.APPEND 5thMIX
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

// ref.APPEND 5thMIX
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

// ref.APPEND 5thMIX
struct SETBL {
	u_char  pri;
	u_char  tracks;
	u_char  kind;
	u_char  character;
	u_char *addr[3]; // possibly NOT fixed at 3 here
};

// ref.APPEND 5thMIX
struct SEPLAYTBL {
	u_char  pri;
	u_char  kind;
	u_char  character;
	u_char *addr;
	u_long  code;
};

// ref.APPEND 5thMIX
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
	/*
	 * for PlayStation 2
	 */
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

// these struct definitions were not part of the PSX source as far as i can tell
// the definition of this is definitely bad though, causes problems in mno_set
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

/*---------------------------------------------------------------------------*
 * Prototypes
 *---------------------------------------------------------------------------*/

/* iop_main.c */
int createThread(void);
int HIntHandler(u_int a0);
//int start();
void RecieveInit(int a0);
void sd_set_status(void);
void sd_set_status(void);
void SdSet(void);
void setTimer(void *a0);

/* sd_cli.c */
int sd_set_cli(u_int a0);
int SePlay(u_int a0);
void sd_set(u_int a0);
void set_sng_code_buf(u_int a0);

/* sd_drv.c */
int SngFadeOutP(u_int a0);
int SngFadeOutS(u_int a0);
int SngKaihiP(void);
void init_sng_work(void);
void IntSdMain(void);
void se_adrs_set(u_int a0);
void sng_adrs_set(u_int a0);
void SngFadeInt(void);
void SngFadeIn(u_int a0);
void SngFadeWkSet(void);
void SngKaihiReset2(void);
void SngKaihiReset(void);
void SngTempoInt(void);

/* sd_file.c */
char num2char(u_int a0);
int EEOpen(int a0);
int EERead(u_int a0, u_int a1, u_int a2, u_int a3, u_int a4);
int LoadSeFile(void);
int LoadSngData(void);
int LoadWaveFile(void);
int PcmClose(int a0);
int PcmLseek(int a0, u_int a1, u_int a2);
int PcmOpen(u_int a0, u_int a1);
int PcmRead(int a0, void *a1, int a2);
void code2name(u_int a0, char *a1);
void set_voice_tbl(u_int *a0, u_int a1, u_int a2);
void str_cat(char *a0, char *a1);
void WaveCdLoad(void);
void WaveSpuTrans(void);

/* sd_ioset.c */
void drum_set(u_int a0);
void freq_set(u_int a0);
void keyoff(void);
void keyon(void);
void pan_set2(u_char a0);
void se_off_all(void);
void se_off_exp(void);
void se_off(u_int a0);
void snd_pause_off(void);
void sng_off(void);
void sng_pause(void);
void sound_off(void);
void spuwr(void);
void tone_set(u_int a0);
void vol_set(u_int a0);

/* sd_main.c */
int sd_mem_alloc(void);
void keyOff(u_int a0);
void keyOn(u_int a0);
void SdEELoad(void);
void sd_init(void);
void SdInt(void);
void SdMain(void);
void SdTerm(void);

/* sd_mstr.c */
int MemSpuTransWithNoLoop(u_int a0);
void init_mem_str_w(void);

/* sd_str2.c */
int StartEEStream(u_int a0);
int Str2SpuTrans(int a0);
void str2_int(void);
void str2_load(void);
void str2_spuwr(void);
void str2_tr_off(u_int a0);
void StrEELoad(u_int a0);

/* sd_str3.c */
int lnrSpuTrans(void);
int StartLnrEEStream(void);
void LnrEELoad(void);
void lnr_int(void);
void lnr_load(void);
void lnr_spuwr(void);
void lnr_trans_0(u_short *a0, u_int a1);
void lnr_trans_init(void);
void lnr_trans(u_short *a0, char *a1, u_int a2);
void lnr_tr_off(void);

/* sd_str.c */
int StartStream1(void);
int StartStream2(void);
int StartStream(void);
int StrSpuTrans(void);
void StrCdLoad(void);
void str_int(void);
void str_load(void);
void str_spuwr(void);
void str_tr_off(void);

/* sd_sub1.c */
int sound_sub(void);
int tx_read(void);
int vib_compute(void);
int vib_generate(char a0);
u_int random(void);
void adsr_reset(void);
void bendch(void);
void fader_automation1(void);
void fader_automation2(void);
void keych(void);
void key_cut_off(void);
void note_cntl(void);
void note_compute(void);
void note_set(void);
void pan_generate(void);
void por_compute(void);
void swpadset(int a0);
void tempo_ch(void);
void vol_compute(void);
void volxset(u_char a0);

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=euc-jp : */
