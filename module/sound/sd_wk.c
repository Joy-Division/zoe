#include <sys/types.h>
#include "sd_incl.h"

// from drv
u_int se_vol[12];
struct SEPLAYTBL se_request[12];

// from mstr
struct unkstr24 mem_str_w[12];

#if defined(BORMAN_DEMO)
u_char mem_str_buf[0x00080000]; /* 512KB */
#else
u_char mem_str_buf[0x000A0000]; /* 640KB */
#endif

int sng_status;
int skip_intro_loop;

u_int rev_on_bit[2];
u_int rev_off_bit[2];
u_int sound_mono_fg;
u_int sng_load_code;

u_int mdata1;
u_int mdata2;
u_int mdata3;
u_int mdata4;
u_long spu_load_offset;
u_int song_end[2];
int stop_jouchuu_se;
u_char *wave_load_ptr;
u_int key_fg;
u_int mtrack;
u_int keyons[2];
u_long spu_wave_start_ptr;
u_int wave_load_code;
u_int keyd[2];
u_long wave_unload_size;
u_long wave_load_status;
struct WAVE_W *voice_tbl;
u_int wave_save_code;
u_int se_rev_on;
u_char *mptr;
struct SOUND_W *sptr;
u_long wave_load_size;
u_int se_load_code;
int wave_fp;
u_int keyoffs[2];
int se_fp;

u_int rev_bit_data[2];
u_char auto_env_pos;
u_char auto_env_pos2;
u_int auto_phase_fg;

u_int pak_load_status;
u_int pak_read_fg;
int pak_fp;
u_int pak_load_code;
int sng_fp;
int fx_sound_code;
int sng_fadein_time;
int sng_fout_term[2];
int sng_play_code;
u_int sng_kaihi_fg;
int sng_fadein_fg;
u_int sng_fout_fg;
int vox_on_vol;
u_int sng_syukan_fg;
int sng_syukan_vol;

u_int sd_code_set;
u_int vox_rev_on;
u_int fader_off_fg;
u_int sd_code_read;
u_int sng_pause_fg;

/* --- Unreferenced Data --- */

u_int lnr8_fg;
u_int irq_addr; // also in bm5thMIX

#if !(defined BORMAN_DEMO || defined DENGEKI_DEMO)
u_int ue_;	// 029c034e (0ecc:30), unused
#endif
#if !defined BORMAN_DEMO
u_int um_;	// 025e432f (0f12:1f), used in retail
#endif

u_int mem_str_fg;	// used in retail

u_int wave_loaded;	// also in bm5thMIX
u_int se_save_code2;	// also in bm5thMIX
u_int spu_irq_counter;	// also in bm5thMIX
u_int blank_data_addr;	// also in bm5thMIX


/* --- End of Unreferenced Data --- */

struct SEPLAYTBL se_playing[12];
u_int fg_rev_set[44];
int sd_sng_code_buf[16];
u_int drum_tbl[0x100];
u_int fg_syukan_off[44];
struct SOUND_W sound_w[44];
struct VOX_FADER vox_fader[2];
struct SPU_TRACK_REG spu_tr_wk[44];
int sng_fade_value[32];
u_int sng_fade_time[32];
u_int sng_master_vol[32];
struct FADER mix_fader[32];

char path_name[0x80];
u_int se_pan[12];
