/*
 * Sound Driver for PS2 IOP
 * External Include
 *
 * ver.ZONE OF THE ENDERS
 */
#ifndef INC_SD_EXT_H
#define INC_SD_EXT_H

#include <sys/types.h>
#include <libsd.h>  // TODO: make explicit in C files
#include <kernel.h> // TODO: make explicit in C files
#include <stdio.h>  // TODO: make explicit in C files

// TODO: from jsifman, replace once decompiled
extern u_int sif_send_mem( u_int *, u_int *, u_int );
extern void sif_set_callback_func(u_int, void (*)(void*, int*), int*);
extern void sif_rv_release_queue();
extern u_int *sif_get_mem(void *, u_int, u_int);

// TODO: from usbfs
extern int pcOpen(char *, int);
extern int pcClose(int);
extern int pcRead(int, void *, int);
extern int pcLseek(int, u_int, u_int);

// TODO: from cdbios
extern void cdRead(int, void *, int);
extern void cdOpen();
extern void cdClose();

/*---------------------------------------------------------------------------*
 * Global Data
 *---------------------------------------------------------------------------*/

/* iop_main.c */
extern int id_SdInt;
extern int id_SdEELoad;
extern int id_SdMain;
extern int id_SdSet;
extern int id_HSyncTim;

/* sd_cli.c */
extern u_int se_tracks;

/* sd_drv.c */
extern int sng_status;
extern u_int skip_intro_loop;

/* sd_file.c */
//~ extern u_int pak_read_fg;
//~ extern int pak_fp;
//~ extern u_int pak_load_code;
//~ extern u_int save_wvx1, save_wvx2;
//~ extern u_int d1E0E4[2];
//~ extern u_int wave_load_status;
//~ extern u_int save_efx;
//~ extern u_int *se_exp_table;
//~ extern u_int save_mdx;
//~ extern u_int pak_header[512];
//~ extern u_char sng_data[0x20000];
//~ extern u_int drum_tbl[0x100];
//~ extern u_char cdload_buf[0x18000];
//~ extern u_char mem_str_buf[0xA0000];
//~ extern char path_name[0x80];

/* sd_ioset.c */

/* sd_main.c */

/* sd_mstr.c */

/* sd_str2.c */
extern u_int str2_iop_load_set[2];
extern u_int str2_load_code[2];
extern u_int str2_first_load[2];
extern u_int str2_counter[2];
extern u_int str2_status[2];
extern u_int str2_play_counter[2];
extern u_int str2_stop_fg[2];
extern u_int str2_mono_fg[2];
extern u_int str2_wait_fg[2];
extern short str2_pitch[2];
extern u_int str2_keyoffs;
extern u_int str2_read_disable[2];
extern int str2_fp[2];
extern u_int str2_unload_size[2];
extern u_int str2_unplay_size[2];
extern u_short str2_volume[2];
extern u_int ee2_buf_idx[2];
extern u_char *str2_trans_buf[2];
extern u_int str2_l_r_fg[2];
extern u_int str2_play_idx[2];
extern u_int str2_play_offset[2];
extern u_int spu_str2_start_ptr_l[2];
extern u_int spu_str2_start_ptr_r[2];
extern u_int spu_str2_idx[2];
extern u_int mute2_l_r_fg[2];
extern u_int str2_off_ctr[2];
extern u_int str2_next_idx[2];
extern u_int str2_mute_fg[2];
extern u_int str2_mono_offset[2];

/* sd_str3.c */
extern u_int lnr8_load_code;
extern u_int lnr8_first_load;
extern u_int lnr8_counter;
extern u_int lnr8_status;
extern u_int lnr8_stop_fg;
extern u_int lnr_keyoffs;
extern u_int lnr8_read_disable;
extern int lnr8_fp;
extern u_int lnr8_wave_size;
extern u_int lnr8_unplay_size;
extern u_int lnr8_unload_size;
extern u_short lnr_volume;
extern u_int lnr8_read_idx;
extern u_char *lnr8_trans_buf;
extern u_short lnr_val[2];
extern u_int lnr8_play_idx;
extern u_int lnr8_play_ofst;
extern u_int lnr8_fade_vol;
extern u_int lnr16_next_ofst;
extern int lnr8_off_ctr;
extern u_int spu_lnr16_idx;

/* sd_str.c */
extern u_int str_load_code;
extern u_int str_first_load;
extern u_int str_status;
extern u_int str_counter;
extern u_int str_counter_low;
extern u_int str_stop_fg;
extern u_int str_wait_fg;
extern u_int str_keyoffs;
extern int str_fp;
extern u_int str_wave_size;
extern u_int str_unplay_size;
extern u_int str_unload_size;
extern u_short str_volume;
extern u_short str_pitch;
extern u_int str_mono_fg;
extern u_char *str_trans_buf;
extern u_int str_trans_offset;
extern u_int str_read_idx;
extern u_int str_start_offset;
extern u_int str_l_r_fg;
extern u_int str_play_idx;
extern u_int str_play_offset;
extern u_int spu_str_start_ptr_l;
extern u_int spu_str_start_ptr_r;
extern u_int mute_str_l_r_fg;
extern u_int spu_str_idx;
extern u_int str_next_idx;
extern int str_off_ctr;
extern u_int str_mono_offset;

/* sd_sub1.c */

/* sd_sub2.c */
//~ extern struct SOUND_W *sptr;
//~ extern void *mptr;
//~ extern u_char mdata2;
//~ extern u_char mdata3;
//~ extern u_char mdata4;
//~ extern u_int mtrack;
//~ extern u_int skip_intro_loop;
//~ extern u_int stop_jouchuu_se;
//~ extern u_int keyd[2];
//~ extern u_int keyoffs[2];
//~ extern struct SEPLAYTBL se_playing[12];
//~ extern u_int fg_rev_set[44];
//~ extern struct SOUND_W sound_w[32];
//~ extern struct SPU_TRACK_REG spu_tr_wk[44];
//~ extern u_int rev_off_bit[2];
//~ extern u_int rev_bit_data[2];
//~ extern u_int rev_on_bit[2];
//~ extern u_char auto_env_pos;
//~ extern u_int auto_phase_fg;

/* sd_wk.c */

extern u_int pak_cd_read_fg;
extern u_int save_wvx1, save_wvx2;
extern u_int save_efx;
extern u_int save_mdx;

char *sd_path_sd1[6];
extern void (*cntl_tbl[128])(void);
extern char rdm_tbl[129];
extern u_char VIBX_TBL[44];
extern int pant[41];
extern u_int se_pant[65];
extern int freq_tbl[108];
extern u_int str1_use_iop;
extern u_short str_master_vol;
extern u_short str_master_pitch;
extern u_char dummy_data[0x800];
extern u_short str2_master_vol;
extern u_short str2_master_pitch;

extern u_int se_vol[12];
extern struct SEPLAYTBL se_request[12];
extern struct unkstr24 mem_str_w[12];
extern u_char mem_str_buf[0xA0000];
extern struct SEPLAYTBL se_playing[12];
extern u_int fg_rev_set[44];
extern int sd_sng_code_buf[16];
extern u_int drum_tbl[0x100];
extern u_int fg_syukan_off[44];
extern struct SOUND_W sound_w[44];
extern struct unkstr16 vox_fader[2];
extern struct SPU_TRACK_REG spu_tr_wk[44];
extern int sng_fade_value[32];
extern u_int sng_fade_time[32];
extern u_int sng_master_vol[32];
extern struct unkstr16 mix_fader[32];
extern char path_name[0x80];
extern u_int se_pan[12];
extern u_int pak_header[512];
extern struct unkstr24 ee_addr[2];
extern u_char wave_header[0x2000]; // this is most likely struct WAVE_W
extern u_char sng_data[0x20000];
extern u_char se_data_area[0x4800];
extern u_char cdload_buf[0x18000];
extern u_char str_header[0x8800];
extern u_int str_read_status[8];
extern u_char eeload2_buf[0x10000];
extern u_int str2_read_status[2][8];
extern u_short lnr16_buf[0x800];
extern u_int lnr8_read_status[32];
extern u_char lnr8_buf[0x8000];



extern u_int rev_on_bit[2];
extern void *common;
extern u_int mdata1;
extern u_int mdata2;
extern u_int mdata3;
extern u_int mdata4;
extern u_int spu_load_offset;
extern u_int song_end[2];
extern u_int stop_jouchuu_se;
extern u_char *wave_load_ptr;
extern u_int sound_mono_fg;
extern u_int key_fg;
extern u_int mtrack;
extern u_int rev_off_bit[2];
extern u_int keyons[2];
extern struct SETBL *se_header;
extern u_char *spu_wave_start_ptr;
extern u_int wave_load_code;
extern u_int keyd[2];
extern u_int wave_unload_size;
extern u_int wave_load_status;
extern struct WAVE_W *voice_tbl;
extern u_int wave_save_code;
extern u_int se_rev_on;
extern u_char *mptr;
extern struct SOUND_W *sptr;
extern u_int wave_load_size;
extern u_int se_load_code;
extern u_char *se_data;
extern int wave_fp;
extern u_int keyoffs[2];
extern int se_fp;
//~ extern struct WAVE_W *wave_w;
extern u_int rev_bit_data[2];
extern u_char auto_env_pos;
extern u_char auto_env_pos2;
extern u_int auto_phase_fg;
extern u_int pak_load_status;
extern u_int sng_load_code;
extern u_int pak_read_fg;
extern int pak_fp;
extern u_int pak_load_code;
extern u_int d1E0E4[2];
extern u_char *se_exp_table;
extern int sng_fp;
extern u_int fx_sound_code;
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
extern u_int sd_print_fg;
extern u_int vox_rev_on;
extern u_int fader_off_fg;
extern u_int sd_code_read;
extern u_int sng_pause_fg;

/* se_tbl.c */
extern struct SETBL se_tbl[128];

/*---------------------------------------------------------------------------*
 * Prototypes
 *---------------------------------------------------------------------------*/

/* iop_main.c */
int createThread(void);
int HIntHandler(u_int a0);
//int start();
void RecieveInit(int a0);
void sd_set_status(void);
void sd_send_status(void);
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
void sng_track_init(struct SOUND_W *work);
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
int EERead(u_int a0, u_int* a1, u_int a2, u_int a3);
void LoadPakFile(void);
int LoadSeFile(void);
int LoadSngData(); // this cannot be void(void): function doesnt take argument but is called with one
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

/* sd_sub2.c */
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

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=euc-jp : */
