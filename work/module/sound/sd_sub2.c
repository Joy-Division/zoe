/*
 * Sound Driver for PS2 IOP
 * Sub-Module 2
 *
 * ver.ZONE OF THE ENDERS
 */
#include <sys/types.h>
#include "sd_incl.h"

extern struct SOUND_W *sptr;
extern void *mptr;
extern u_char mdata2;
extern u_char mdata3;
extern u_char mdata4;
extern u_int mtrack;
extern u_int skip_intro_loop;
extern u_int stop_jouchuu_se;

extern u_int keyd[2];
extern u_int keyoffs[2];

extern struct SEPLAYTBL se_playing[12];
extern u_int fg_rev_set[44];
extern struct SOUND_W sound_w[44];
extern struct SPU_TRACK_REG spu_tr_wk[44];
extern u_int rev_off_bit[2];
extern u_int rev_bit_data[2];
extern u_int rev_on_bit[2];
extern u_char auto_env_pos;
extern u_int auto_phase_fg;

extern struct unkstr24 *mem_str_w;
extern struct unkstr16 *mix_fader;

// forward declaration
void block_end( void );

/*---------------------------------------------------------------------------*
 * Functions
 *---------------------------------------------------------------------------*/

// NOTE FOR ALL: Epilogues may be wrong; recheck later.

void rest_set( void )
{
	sptr->rest_fg = 1;
	keyoff();
	sptr->ngs = mdata2;
	sptr->ngg = 0;
	sptr->vol = 0;
	sptr->ngc = sptr->ngs;
	sptr->ngo = 0;
}

void tie_set( void )
{
	int temp1;
	
	sptr->rest_fg = 1;
	sptr->ngs = mdata2;
	sptr->ngg = mdata3;
	sptr->ngc = sptr->ngs;
	temp1 = ((sptr->ngg * sptr->ngc) / 100);
	
	if (!temp1) temp1 = 1;
	sptr->ngo = temp1;
}

// NOMATCH: keyoff() doesnt get interleaved properly
void sno_set( void )
{
	sptr->snos = mdata2;
	keyoff();
	tone_set( mdata2 );
}

// NOMATCH: keyoff() doesnt get interleaved properly
void svl_set( void )
{
	sptr->snos = mdata2;
	keyoff();
	tone_set( mdata2 );
}

// NOMATCH: keyoff() doesnt get interleaved properly
void svp_set( void )
{
	sptr->snos = mdata2;
	keyoff();
	tone_set( mdata2 );
}

void ofs_set( void )
{
	spu_tr_wk[mtrack].addr += mdata2 * 4096 + mdata3 * 16;
	spu_tr_wk[mtrack].addr_fg = 1;
}

void use_set( void )
{
}

// NOMATCH: epilogue
void pan_set( void )
{
	sptr->panmod = mdata2;
	sptr->panf = mdata3 + 0x14;
	sptr->pand = sptr->panf << 8;
	sptr->panc = 0;
}

// TODO:
// - Check break instructions. (codes differ between assemblers)
// - Do another pass of the code.
void pan_move( void )
{
	int temp2;
	u_char temp1;
	
	sptr->panc = mdata2;
	temp1 = mdata3 + 0x14;
	sptr->panm = temp1 << 8;
	temp2 = temp1 - sptr->panf;
	
	if (temp2 < 0){
		sptr->panad = -(((-temp2) << 8) / mdata2);
		if (sptr->panad < -0x7F0)
			sptr->panad = -0x7F0;
	} else {
		sptr->panad = (temp2 << 8) / mdata2;
		if (sptr->panad > 0x7F0)
			sptr->panad = 0x7F0;
	}
}

// NOMATCH:
// - At least one delay slot doesnt get used as it should.
void vib_set( void )
{
	sptr->vibhs = mdata2;
	sptr->vibcad = mdata2;
	
	if (sptr->vibcad < 0x40){
		if (sptr->vibcad < 0x20){
			sptr->vib_tc_ofst = 1;
			sptr->vibcad = sptr->vibcad << 3;
		} else {
			sptr->vib_tc_ofst = 2;
			sptr->vibcad = sptr->vibcad << 2;
		}
	} else {
		if (sptr->vibcad >= 0){
			sptr->vib_tc_ofst = 4;
			sptr->vibcad = sptr->vibcad << 1;
		} else if (((u_char)sptr->vibcad) != 0xFF){
			sptr->vib_tc_ofst = 8;
		} else {
			sptr->vib_tc_ofst = 0x10;
		}
	}
	sptr->vibd = mdata4 << 8;
	sptr->vibdm = mdata4 << 8;
}

// NOMATCH: epilogue
void vib_change( void )
{
	sptr->vibhs = mdata2;
	sptr->vibad = sptr->vibdm / mdata2;
}

// NOMATCH: epilogue
void rdm_set( void )
{
	sptr->rdms = mdata2;
	sptr->rdmd = (mdata3 << 8) + mdata4;
	sptr->rdmc = 0;
	sptr->rdmo = 0;
}

// NOMATCH: epilogue
void lp1_start( void )
{
	sptr->lp1_addr = mptr;
	sptr->lp1_cnt = 0;
	sptr->lp1_freq = sptr->lp1_vol = 0;
}

void lp1_end( void )
{
	if (mtrack < 0x20){
		if (skip_intro_loop && !mdata2){
			sptr->lp1_vol = 0;
			sptr->lp1_freq = 0;
			skip_intro_loop++;
			return;
		}
	} else {
		if (stop_jouchuu_se && !mdata2){
			sptr->lp1_vol = 0;
			sptr->lp1_freq = 0;
			stop_jouchuu_se++;
			return;
		}
	}
	
	if (((++sptr->lp1_cnt) & 0xFF) != mdata2 || !mdata2){
		sptr->lp1_vol += (char)mdata3;
		sptr->lp1_freq += (char)mdata4 << 3;
		mptr = sptr->lp1_addr;
	} else {
		sptr->lp1_vol = 0;
		sptr->lp1_freq = 0;
	}
}

void lp2_start( void )
{
	sptr->lp2_addr = mptr;
	sptr->lp2_cnt = 0;
	sptr->lp2_vol = sptr->lp2_freq = 0;
}

void lp2_end( void )
{
	if (((++sptr->lp2_cnt) & 0xFF) != mdata2 || !mdata2){
		sptr->lp2_vol += (char)mdata3;
		sptr->lp2_freq += (char)mdata4 << 3;
		mptr = sptr->lp2_addr;
	}
}

void l3s_set( void )
{
	sptr->lp3_addr = mptr;
}

void l3e_set( void )
{
	if (sptr->lp3_addr)
		mptr = sptr->lp3_addr;
	else
		block_end();
}

void tempo_set( void )
{
	sptr->tmp = mdata2;
}

void tempo_move( void )
{
	// this is required to avoid recomputing
	// the assignment below for inside the ifs
	register int temp;
	
	sptr->tmpc = mdata2;
	sptr->tmpm = mdata3;
	sptr->tmpw = sptr->tmp << 8;
	temp = (sptr->tmpm - sptr->tmp);
	
	if (temp < 0){
		if (temp < -127)
			temp = -127;
		
		sptr->tmpad = (-temp << 8) / sptr->tmpc;
		
		if (sptr->tmpad < -0x7F0)
			sptr->tmpad = -0x7F0;
	} else {
		if (temp > 127)
			temp = 127;
		
		sptr->tmpad = (temp << 8) / sptr->tmpc;
		
		if (sptr->tmpad > 0x7F0)
			sptr->tmpad = 0x7F0;
	}
}

void trans_set( void )
{
	sptr->ptps = mdata2;
}

void tre_set( void )
{
	sptr->trehs = mdata2;
	sptr->trecad = mdata3;
	sptr->tred = mdata4;
}

void vol_chg( void )
{
	sptr->pvod = mdata2 << 8;
	sptr->pvoc = 0;
}

void vol_move( void )
{
	int temp;
	
	sptr->pvoc = mdata2;
	sptr->pvom = mdata3;
	temp = mdata3 << 8;
	temp -= sptr->pvod;
	
	if (temp < 0){
		sptr->pvoad = -temp / sptr->pvoc;
		if (sptr->pvoad < -0x7F0)
			sptr->pvoad = -0x7F0;
	} else {
		sptr->pvoad = temp / sptr->pvoc;
		if (sptr->pvoad > 0x7F0)
			sptr->pvoad = 0x7F0;
	}
}

void por_set( void )
{
	sptr->swshc = 0;
	sptr->swsc = mdata2;
	
	if (!mdata2) sptr->swsk = 0;
	else sptr->swsk = 1;
}

void sws_set( void )
{
	sptr->swsk = 0;
	sptr->swshc = mdata2;
	sptr->swsc = mdata3;
	sptr->swss = mdata4 << 8;
}

void detune_set( void )
{
	sptr->tund = mdata2 << 2;
}

void swp_set( void )
{
	// EMPTY
}

void echo_set1( void )
{
	// EMPTY
}

void echo_set2( void )
{
	// EMPTY
}

void eon_set( void )
{
	if (mtrack >= 0x20 && mtrack < 0x2C){
		if (se_playing[mtrack-0x20].kind == 0 || fg_rev_set[mtrack]){
			rev_on_bit[1] |= keyd[1];
			rev_bit_data[1] |= keyd[1];
		}
	} else {
		rev_on_bit[0] |= keyd[0];
		rev_on_bit[1] |= keyd[1];
		rev_bit_data[0] |= keyd[0];
		rev_bit_data[1] |= keyd[1];
	}
}

void eof_set( void )
{
	if (mtrack >= 0x20 && mtrack < 0x2C){
		if (se_playing[mtrack-0x20].kind == 0 || fg_rev_set[mtrack]){
			rev_off_bit[1] |= keyd[1];
			rev_bit_data[1] &= ~keyd[1];
		}
	} else {
		rev_off_bit[0] |= keyd[0];
		rev_off_bit[1] |= keyd[1];
		rev_bit_data[0] &= ~keyd[0];
		rev_bit_data[1] &= ~keyd[1];
	}	
}

void kakko_start( void )
{
	sptr->kak1ptr = mptr;
	sptr->kakfg = 0;
}

void kakko_end( void )
{
	switch (sptr->kakfg){
	case 0:
		sptr->kakfg++;
		break;
	case 1:
		sptr->kakfg++;
		sptr->kak2ptr = mptr;
		mptr = sptr->kak1ptr;
		break;
	case 2:
		sptr->kakfg--;
		mptr = sptr->kak2ptr;
		break;
	}
}

void env_set( void )
{
	if (mdata2){
		spu_tr_wk[mtrack].a_mode = 0x8000;
	} else {
		spu_tr_wk[mtrack].a_mode = 0;
	}
	
	spu_tr_wk[mtrack].env1_fg = 1;
	
	switch (mdata3){
	case 0:  spu_tr_wk[mtrack].s_mode = 0x4000; break;
	case 1:  spu_tr_wk[mtrack].s_mode = 0xC000; break;
	case 2:  spu_tr_wk[mtrack].s_mode = 0x0000; break;
	default: spu_tr_wk[mtrack].s_mode = 0x8000; break;
	}
	
	spu_tr_wk[mtrack].env2_fg = 1;
	
	if (mdata4){
		spu_tr_wk[mtrack].r_mode = 0x20;
	} else {
		spu_tr_wk[mtrack].r_mode = 0;
	}
	
	spu_tr_wk[mtrack].env3_fg = 1;
}

void ads_set( void )
{
	spu_tr_wk[mtrack].a_mode = 0;
	spu_tr_wk[mtrack].ar = 0x7F - (mdata2 & 0x7F);
	spu_tr_wk[mtrack].dr = 0xF - (mdata3 & 0xF);
	spu_tr_wk[mtrack].sl = mdata4 & 0xF;
	spu_tr_wk[mtrack].env1_fg = 1;
}

void srs_set( void )
{
	spu_tr_wk[mtrack].s_mode = 0x4000;
	spu_tr_wk[mtrack].sr = 0x7F-(mdata2 & 0x7F);
	spu_tr_wk[mtrack].env2_fg = 1;
}

void rrs_set( void )
{
	spu_tr_wk[mtrack].r_mode = 0;
	sptr->rrd = spu_tr_wk[mtrack].rr = 0x1F - (mdata2 & 0x1F);
	spu_tr_wk[mtrack].env3_fg = 1;
}

void pm_set( void )
{
	// EMPTY
}

void jump_set( void )
{
	// EMPTY
}

void block_end( void )
{
	keyoffs[0] |= keyd[0];
	keyoffs[1] |= keyd[1];
}

void fxs_set( void )
{
	sptr->unkD8 = mdata2;
	sptr->unkD4 = mdata3;
	sptr->unkDC = mptr;
}

void fxe_set( void )
{
	mptr = sptr->unkDC;
	sptr->unkE0 = 0;
}

void xon_set( void )
{
	sptr->unkE1 = 1;
}

void vol_i_move( void )
{
	int temp2;
	struct SOUND_W *work;
	
	work = &sound_w[mdata2];
	work->pvoc = mdata3;
	work->pvom = mdata4;
	temp2 = mdata4 << 8;
	temp2 -= work->pvod;
	if (temp2 < 0){
		work->pvoad = -(-temp2 / work->pvoc);
		if (work->pvoad < -0x7F0)
			work->pvoad = -0x7F0;
	} else {
		work->pvoad = temp2 / work->pvoc;
		if (work->pvoad > 0x7F0)
			work->pvoad = 0x7F0;
	}
}

void at1_set( void )
{
	if (sptr->unkE4 == auto_env_pos || sptr->unkE4 == auto_phase_fg){
		// not sure about this, will have to wait until struct is identified
		mix_fader[mtrack].unk08 = mdata2 + (mdata2 << 8);
		mix_fader[mtrack].unk04 = mix_fader[mtrack].unk08;
		mix_fader[mtrack].unk00 = 0;
	}
	
	sptr->unkE9 = mdata2;
	sptr->unkF1 = mdata3;
	sptr->unkE8 = mdata4;
	
	if (sptr->unkE8 == 1){
		sptr->unkEA = mdata2;
		sptr->unkF2 = 0;
		sptr->unkEB = mdata2;
		sptr->unkF3 = 0;
		sptr->unkEC = mdata2;
		sptr->unkF4 = 0;
		sptr->unkED = mdata2;
		sptr->unkF5 = 0;
		sptr->unkEE = mdata2;
		sptr->unkF6 = 0;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0;
	} else {
		sptr->unkEA = mdata2;
		sptr->unkF2 = 0xFF;
		sptr->unkEB = mdata2;
		sptr->unkF3 = 0xFF;
		sptr->unkEC = mdata2;
		sptr->unkF4 = 0xFF;
		sptr->unkED = mdata2;
		sptr->unkF5 = 0xFF;
		sptr->unkEE = mdata2;
		sptr->unkF6 = 0xFF;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0xFF;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0xFF;
	}
}

void at2_set( void )
{
	if (sptr->unkE8 == 1){
		sptr->unkEA = mdata2;
		sptr->unkF2 = mdata3;
		sptr->unkEB = mdata2;
		sptr->unkF3 = 0;
		sptr->unkEC = mdata2;
		sptr->unkF4 = 0;
		sptr->unkED = mdata2;
		sptr->unkF5 = 0;
		sptr->unkEE = mdata2;
		sptr->unkF6 = 0;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0;
	} else {
		sptr->unkEA = mdata2;
		sptr->unkF2 = mdata3;
		sptr->unkEB = mdata2;
		sptr->unkF3 = 0xFF;
		sptr->unkEC = mdata2;
		sptr->unkF4 = 0xFF;
		sptr->unkED = mdata2;
		sptr->unkF5 = 0xFF;
		sptr->unkEE = mdata2;
		sptr->unkF6 = 0xFF;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0xFF;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0xFF;
	}
}

void at3_set( void )
{
	if (sptr->unkE8){
		sptr->unkEB = mdata2;
		sptr->unkF3 = mdata3;
		sptr->unkEC = mdata2;
		sptr->unkF4 = 0;
		sptr->unkED = mdata2;
		sptr->unkF5 = 0;
		sptr->unkEE = mdata2;
		sptr->unkF6 = 0;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0;
	} else {
		sptr->unkEB = mdata2;
		sptr->unkF3 = mdata3;
		sptr->unkEC = mdata2;
		sptr->unkF4 = 0xFF;
		sptr->unkED = mdata2;
		sptr->unkF5 = 0xFF;
		sptr->unkEE = mdata2;
		sptr->unkF6 = 0xFF;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0xFF;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0xFF;
	}
}

void at4_set( void )
{
	if (sptr->unkE8){
		sptr->unkEC = mdata2;
		sptr->unkF4 = mdata3;
		sptr->unkED = mdata2;
		sptr->unkF5 = 0;
		sptr->unkEE = mdata2;
		sptr->unkF6 = 0;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0;
	} else {
		sptr->unkEC = mdata2;
		sptr->unkF4 = mdata3;
		sptr->unkED = mdata2;
		sptr->unkF5 = 0xFF;
		sptr->unkEE = mdata2;
		sptr->unkF6 = 0xFF;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0xFF;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0xFF;
	}
}

void at5_set( void )
{
	if (sptr->unkE8 == 1){
		sptr->unkED = mdata2;
		sptr->unkF5 = mdata3;
		sptr->unkEE = mdata2;
		sptr->unkF6 = 0;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0;
	} else {
		sptr->unkED = mdata2;
		sptr->unkF5 = mdata3;
		sptr->unkEE = mdata2;
		sptr->unkF6 = 0xFF;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0xFF;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0xFF;
	}
}

void at6_set( void )
{
	if (sptr->unkE8 == 1){
		sptr->unkEE = mdata2;
		sptr->unkF6 = mdata3;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0;
	} else {
		sptr->unkEE = mdata2;
		sptr->unkF6 = mdata3;
		sptr->unkEF = mdata2;
		sptr->unkF7 = 0xFF;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0xFF;
	}
}

void at7_set( void )
{
	if (sptr->unkE8 == 1){
		sptr->unkEF = mdata2;
		sptr->unkF7 = mdata3;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0;
	} else {
		sptr->unkEF = mdata2;
		sptr->unkF7 = mdata3;
		sptr->unkF0 = mdata2;
		sptr->unkF8 = 0xFF;
	}
}

void at8_set( void )
{
	sptr->unkF0 = mdata2;
	sptr->unkF8 = mdata3;
}

// NOMATCH: see inside
void mno_set( void )
{
	if (mtrack >= 0x20){
	// this array access is only a placeholder, mem_str_w appears to be a struct (same addition problem as in eon_set as well)
		mem_str_w[mtrack-0x20].unk0C = sptr->snos = mdata2+0x100;
		keyoff();
		tone_set( sptr->snos );
	}
}

void flg_set( void )
{
	switch (mdata2){
	case 0: fg_syukan_off[mtrack] = mdata3; break;
	case 1: fg_rev_set[mtrack] = mdata3; break;
	}
}

void no_cmd( void )
{
	// EMPTY
}

/*---------------------------------------------------------------------------*
 * END OF FILE
 *---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=euc-jp : */