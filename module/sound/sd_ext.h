#ifndef INCLUDED_SD_EXT_H
#define INCLUDED_SD_EXT_H

#include <sys/types.h>
#include <kernel.h> // TODO: make explicit in C files
#include <libsd.h>  // TODO: make explicit in C files
#include <stdio.h>  // TODO: make explicit in C files

// TODO: from jsifman, replace once decompiled
extern u_int sif_send_mem( u_int *, volatile u_int *, u_int );
extern void sif_set_callback_func(u_int, void (*)(void*, int*), int*);
extern void sif_rv_release_queue();
extern u_int *sif_get_mem(void *, u_int, u_int);

//=============================================================================
// iop_main.c
//=============================================================================

extern int id_SdInt;
extern int id_SdEELoad;
extern int id_SdMain;
extern int id_SdSet;
extern int id_HSyncTim;
extern int common;

void sd_set_status(void);
void sd_send_status(void);
void SdSet(void);
int HIntHandler(u_int a0);
void setTimer(void *a0);
int createThread(void);

//=============================================================================
// sd_cli.c
//=============================================================================

extern u_int str1_use_iop;
extern int se_tracks;
extern u_int sd_print_fg;
extern struct unkstr24 ee_addr[2];

int sd_set_cli(u_int a0);
int SePlay(u_int a0);
void set_sng_code_buf(u_int a0);
void sd_set(int sound_code);

//=============================================================================
// sd_drv.c
//=============================================================================

void IntSdMain(void);
void SngFadeIn(u_int a0);
int SngFadeOutP(u_int a0);
int SngFadeOutS(u_int a0);
int SngKaihiP(void);
void SngKaihiReset(void);
void SngKaihiReset2(void);
void SngFadeWkSet(void);
void SngFadeInt(void);
void SngTempoInt(void);
void init_sng_work(void);
void sng_adrs_set(u_int a0);
void se_adrs_set(u_int a0);
void sng_track_init(struct SOUND_W *work);

//=============================================================================
// sd_file.c
//=============================================================================

extern u_int gsize;	// UNUSED
extern u_int pak_cd_read_fg;
extern u_int save_wvx1, save_wvx2;
extern u_int save_efx;
extern u_int save_mdx;
extern u_int pak_header[512];
extern char *sd_path_cd1[6];

void LoadPakFile(void);
int LoadSeFile(void);
int LoadSngData();	// Should be LoadSngData(void),
					// but SdMain() passes an argument
void set_voice_tbl(u_int *a0, u_int a1, u_int a2);
int LoadWaveFile(void);
void WaveCdLoad(void);
void WaveSpuTrans(void);
void code2name(u_int code, char *name);
char num2char(u_int a0);
void str_cat(char *a0, char *a1);
int PcmOpen( u_int code, u_int path_idx );
int PcmRead(int a0, void *a1, int a2);
int PcmLseek(int a0, u_int a1, u_int a2);
int PcmClose(int a0);
int EEOpen(int a0);
int EERead(u_int a0, u_int* a1, u_int a2, u_int a3);

//=============================================================================
// sd_ioset.c
//=============================================================================

extern int pant[41];
extern u_int se_pant[65];
extern int freq_tbl[108];
extern u_char send_timer[16];	// UNUSED

void spuwr(void);
void sound_off(void);
void sng_off(void);
void se_off(u_int a0);
void se_off_exp(void);
void se_off_all(void);
void sng_pause(void);
void sng_pause_off(void);
void keyon(void);
void keyoff(void);
void tone_set(u_int a0);
void pan_set2(u_char a0);
void vol_set(u_int a0);
void freq_set(u_int a0);
void drum_set(u_int a0);

//=============================================================================
// sd_main.c
//=============================================================================

extern u_char *se_exp_table;
extern struct SETBL *se_header;
extern u_char *se_data;

void SdMain(void);
void SdEELoad(void);
void SdInt(void);
void sd_init(void);
void SdTerm(void);
void keyOff(u_int a0);
void keyOn(u_int a0);
int sd_mem_alloc(void);

//=============================================================================
// sd_mstr.c
//=============================================================================

extern unsigned char wave_header[0x2000]; // struct WAVE_W ?
extern u_char sng_data[0x20000];
extern u_char se_data_area[0x4800];
extern u_char cdload_buf[0x18000];

void init_mem_str_w(void);
int MemSpuTransWithNoLoop(u_int a0);

//=============================================================================
// sd_str.c
//=============================================================================

extern u_short str_master_vol;
extern u_short str_master_pitch;

extern u_char dummy_data[2048];

extern u_int ee_str_load_addr;	// UNUSED
extern u_int str_mute_fg;		// UNUSED

extern unsigned int str_mono_offset;
extern unsigned int str_counter;
extern unsigned int str_wait_fg;
extern unsigned int str_wave_size;
extern unsigned short str_volume;
extern unsigned int str_counter_low;
extern unsigned int str_mono_fg;
extern unsigned int str_next_idx;
extern unsigned int spu_str_idx;
extern int str_off_ctr;
extern unsigned int str_status;
extern unsigned int spu_str_start_ptr_r;
extern unsigned int str_trans_offset;
extern unsigned int str_unplay_size;
extern unsigned int mute_str_l_r_fg;
extern int str_fp;
extern unsigned int str_unload_size;
extern unsigned int str_keyoffs;
extern unsigned int str_first_load;
extern unsigned int spu_str_start_ptr_l;
extern unsigned int str_play_offset;
extern unsigned int str_load_code;
extern unsigned short str_pitch;
extern unsigned int str_l_r_fg;
extern unsigned int str_play_idx;
extern unsigned int str_stop_fg;
extern unsigned int str_start_offset;
extern unsigned char *str_trans_buf;
extern unsigned int str_read_idx;

extern u_char str_header[0x8800];
extern u_int str_read_status[8];

void str_tr_off(void);
void str_spuwr(void);
int StartStream1(void);
int StartStream2(void);
int StartStream(void);
void StrCdLoad(void);
void str_load(void);
int StrSpuTrans(void);
void str_int(void);

//=============================================================================
// sd_str2.c
//=============================================================================

extern u_short str2_master_vol;
extern u_short str2_master_pitch;

extern unsigned int spu_str2_start_ptr_r[2];
extern unsigned int str2_iop_load_set[2];
extern unsigned int str2_wait_fg[2];
extern unsigned int str2_first_load[2];
extern unsigned int spu_str2_start_ptr_l[2];
extern unsigned int str2_off_ctr[2];
extern int str2_fp[2];
extern unsigned int str2_mono_fg[2];
extern unsigned short str2_volume[2];
extern unsigned int str2_l_r_fg[2];
extern unsigned int spu_str2_idx[2];
extern unsigned int str2_load_code[2];
extern unsigned int ee2_buf_idx[2];
extern unsigned int str2_play_offset[2];
extern unsigned int str2_stop_fg[2];
extern short str2_pitch[2];
extern unsigned int str2_unload_size[2];
extern unsigned int str2_mono_offset[2];
extern unsigned int str2_unplay_size[2];
extern unsigned int str2_next_idx[2];
extern int mute2_l_r_fg[2];
extern unsigned int str2_play_counter[2];
extern unsigned int str2_keyoffs;
extern unsigned int str2_mute_fg[2];
extern unsigned int str2_counter[2];
extern unsigned int str2_status[2];
extern unsigned char *str2_trans_buf[2];
extern unsigned int str2_play_idx[2];
extern unsigned int str2_read_disable[2];

extern u_char eeload2_buf[0x10000];
extern u_int str2_read_status[2][8];

void str2_tr_off(u_int a0);
void str2_spuwr(void);
int StartEEStream(u_int a0);
void StrEELoad(u_int a0);
void str2_load(void);
int Str2SpuTrans(int core);
void str2_int(void);

//=============================================================================
// sd_str3.c
//=============================================================================

extern unsigned int lnr8_read_idx;
extern unsigned short lnr_volume;
extern unsigned int lnr8_play_ofst;
extern unsigned int lnr8_load_code;
extern unsigned int lnr_keyoffs;
extern unsigned int lnr8_first_load;
extern unsigned short lnr_val[2];
extern unsigned char *lnr8_trans_buf;
extern unsigned int lnr8_play_idx;
extern unsigned int lnr16_next_ofst;
extern unsigned int lnr8_unload_size;
extern int lnr8_off_ctr;
extern unsigned int lnr8_fade_vol;
extern int lnr8_fp;
extern unsigned int lnr8_wave_size;
extern unsigned int lnr8_unplay_size;
extern unsigned int lnr8_stop_fg;
extern unsigned int spu_lnr16_idx;
extern unsigned int lnr8_read_disable;
extern unsigned int lnr8_counter;
extern unsigned int lnr8_status;

extern u_short lnr16_buf[0x0800];
extern u_int lnr8_read_status[32];
extern u_char lnr8_buf[0x8000];

void lnr_tr_off(void);
void lnr_spuwr(void);
int StartLnrEEStream(void);
void LnrEELoad(void);
void lnr_load(void);
void lnr_trans_init(void);
void lnr_trans_0(u_short *a0, u_int a1);
void lnr_trans(u_short *a0, char *a1, u_int a2);
int lnrSpuTrans(void);
void lnr_int(void);

//=============================================================================
// sd_sub1.c
//=============================================================================

extern void (*cntl_tbl[128])(void);
extern char rdm_tbl[129];
extern u_char VIBX_TBL[44];

int sound_sub(void);
int tx_read(void);
void note_set(void);
void adsr_reset(void);
void note_compute(void);
void swpadset(int a0);
void vol_compute(void);
void pan_generate(void);
void key_cut_off(void);
void keych(void);
void por_compute(void);
int vib_compute(void);
int vib_generate(char a0);
void bendch(void);
void note_cntl(void);
u_int random(void);
void tempo_ch(void);
void volxset(u_char a0);
void fader_automation1(void);
void fader_automation2(void);

//=============================================================================
// sd_sub2.c
//=============================================================================

void rest_set(void);
void tie_set(void);
void sno_set(void);
void svl_set(void);
void svp_set(void);
void ofs_set(void);
void use_set(void);
void pan_set(void);
void pan_move(void);
void vib_set(void);
void vib_change(void);
void rdm_set(void);
void lp1_start(void);
void lp1_end(void);
void lp2_start(void);
void lp2_end(void);
void l3s_set(void);
void l3e_set(void);
void tempo_set(void);
void tempo_move(void);
void trans_set(void);
void tre_set(void);
void vol_chg(void);
void vol_move(void);
void por_set(void);
void sws_set(void);
void detune_set(void);
void swp_set(void);
void echo_set1(void);
void echo_set2(void);
void eon_set(void);
void eof_set(void);
void kakko_start(void);
void kakko_end(void);
void env_set(void);
void ads_set(void);
void srs_set(void);
void rrs_set(void);
void pm_set(void);
void jump_set(void);
void block_end(void);
void fxs_set(void);
void fxe_set(void);
void xon_set(void);
void vol_i_move(void);
void at1_set(void);
void at2_set(void);
void at3_set(void);
void at4_set(void);
void at5_set(void);
void at6_set(void);
void at7_set(void);
void at8_set(void);
void mno_set(void);
void flg_set(void);
void no_cmd(void);

//=============================================================================
// sd_wk.c
//=============================================================================

extern u_int se_vol[12];
extern struct SEPLAYTBL se_request[12];

extern struct unkstr24 mem_str_w[12];

#if defined(BORMAN_DEMO)
extern u_char mem_str_buf[0x00080000]; /* 512KB */
#else
extern u_char mem_str_buf[0x000A0000]; /* 640KB */
#endif

extern int sng_status;
extern int skip_intro_loop;

extern u_int rev_on_bit[2];
extern u_int rev_off_bit[2];
extern u_int sound_mono_fg;
extern u_int sng_load_code;

extern u_int mdata1;
extern u_int mdata2;
extern u_int mdata3;
extern u_int mdata4;
extern u_long spu_load_offset;
extern u_int song_end[2];
extern int stop_jouchuu_se;
extern u_char *wave_load_ptr;
extern u_int key_fg;
extern u_int mtrack;
extern u_int keyons[2];
extern u_long spu_wave_start_ptr;
extern u_int wave_load_code;
extern u_int keyd[2];
extern u_long wave_unload_size;
extern u_long wave_load_status;
extern struct WAVE_W *voice_tbl;
extern u_int wave_save_code;
extern u_int se_rev_on;
extern u_char *mptr;
extern struct SOUND_W *sptr;
extern u_long wave_load_size;
extern u_int se_load_code;
extern int wave_fp;
extern u_int keyoffs[2];
extern int se_fp;

extern u_int rev_bit_data[2];
extern u_char auto_env_pos;
extern u_char auto_env_pos2;
extern u_int auto_phase_fg;

extern u_int pak_load_status;
extern u_int pak_read_fg;
extern int pak_fp;
extern u_int pak_load_code;

extern int sng_fp;
extern int fx_sound_code;
extern int sng_fadein_time;
extern int sng_fout_term[2];
extern int sng_play_code;
extern u_int sng_kaihi_fg;
extern int sng_fadein_fg;
extern u_int sng_fout_fg;
extern int vox_on_vol;
extern u_int sng_syukan_fg;
extern int sng_syukan_vol;

extern u_int sd_code_set;
extern u_int vox_rev_on;
extern u_int fader_off_fg;
extern u_int sd_code_read;
extern u_int sng_pause_fg;

extern u_int lnr8_fg;
extern u_int irq_addr;

#if !(defined(BORMAN_DEMO)||defined(DENGEKI_DEMO))
extern u_int ue_;	// 029c034e (0ecc:30), UNUSED
#endif
#if !defined(BORMAN_DEMO)
extern u_int um_;	// 025e432f (0f12:1f)
#endif

extern u_int mem_str_fg;

extern u_int wave_loaded;		// UNUSED
extern u_int se_save_code2;
extern u_int spu_irq_counter;	// UNUSED
extern u_int blank_data_addr;	// UNUSED

extern struct SEPLAYTBL se_playing[12];
extern u_int fg_rev_set[44];
extern int sd_sng_code_buf[16];
extern u_int drum_tbl[0x100];
extern u_int fg_syukan_off[44];
extern struct SOUND_W sound_w[44];
extern struct VOX_FADER vox_fader[2];
extern struct SPU_TRACK_REG spu_tr_wk[44];
extern int sng_fade_value[32];
extern u_int sng_fade_time[32];
extern u_int sng_master_vol[32];
extern struct FADER mix_fader[32];

extern char path_name[0x80];
extern u_int se_pan[12];

//=============================================================================
// se_tbl.c
//=============================================================================

extern struct SETBL se_tbl[128];


#endif /* END OF FILE */
