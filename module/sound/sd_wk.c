/*
 * Sound Driver for PS2 IOP
 * Global Work Data
 */
/* ver."ZONE OF THE ENDERS"
 */
#include <sys/types.h>
#include "sd_incl.h"
#include "sd_ext.h"

/*---------------------------------------------------------------------------*
 * Initialized Data
 *---------------------------------------------------------------------------*/

// spu_ch_tbl
// blank_data (appears to be the same as "dummy_data" except first and last sampleset)





/*---------------------------------------------------------------------------*
 * Uninitialized Data
 *---------------------------------------------------------------------------*/



/* GUESSED NAMES */
u_int d1E0E4; // used to be d1E0E4[0] or d1E0E4
u_int d1E0E8; // used to be d1E0E4[1] or d1E0E8

u_int sd_print_fg;
u_char *se_exp_table;
struct SETBL *se_header;
u_char *se_data;
int se_tracks;


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
u_int spu_load_offset;
u_int song_end[2];
int stop_jouchuu_se;
u_char *wave_load_ptr;
u_int key_fg;
u_int mtrack;
u_int keyons[2];
u_char *spu_wave_start_ptr;
u_int wave_load_code;
u_int keyd[2];
u_int wave_unload_size;
u_int wave_load_status;
struct WAVE_W *voice_tbl;
u_int wave_save_code;
u_int se_rev_on;
u_char *mptr;
struct SOUND_W *sptr;
u_int wave_load_size;
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


/* referenced TGS2000 variables */
// u_int se_save_code2;

/* unreferenced TGS2000 variables */
// u_int spu_irq_counter;
// u_int blank_data_addr;
// u_int lnr8_fg;
// u_int irq_addr;
// u_int mem_str_fg;


struct SEPLAYTBL se_playing[12];
u_int fg_rev_set[44];
int sd_sng_code_buf[16];
u_int drum_tbl[0x100];
u_int fg_syukan_off[44];
struct SOUND_W sound_w[44];
struct unkstr16 vox_fader[2];
struct SPU_TRACK_REG spu_tr_wk[44];
int sng_fade_value[32];
u_int sng_fade_time[32];
u_int sng_master_vol[32];
struct unkstr16 mix_fader[32];
char path_name[0x80];
u_int se_pan[12];
u_int pak_header[512];
struct unkstr24 ee_addr[2];
struct WAVE_W wave_header[0x200];
u_char sng_data[0x00020000];
u_char se_data_area[0x4800];
u_char cdload_buf[0x18000];

