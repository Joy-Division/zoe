/*
 * Sound Driver for PS2 IOP
 * I/O Set Module
 */
/* ver."ZONE OF THE ENDERS"
 */
#include <sys/types.h>
#include <libsd.h>

#include "sd_incl.h"
#include "sd_ext.h"

/*---------------------------------------------------------------------------*/

void spuwr( void )
{
	int i;
	
	if( keyoffs[0] ){
		sceSdSetSwitch( SD_CORE_0|SD_S_KOFF, keyoffs[0] );
		keyoffs[0] = 0;
	}
	if( keyoffs[1] ){
		sceSdSetSwitch( SD_CORE_1|SD_S_KOFF, keyoffs[1] );
		keyoffs[1] = 0;
	}
	if( rev_off_bit[0] ){
		sceSdSetSwitch( SD_CORE_0|SD_S_VMIXEL, rev_bit_data[0] );
		sceSdSetSwitch( SD_CORE_0|SD_S_VMIXER, rev_bit_data[0] );
		rev_off_bit[0] = 0;
	}
	if( rev_off_bit[1] ){
		sceSdSetSwitch( SD_CORE_1|SD_S_VMIXEL, rev_bit_data[1] );
		sceSdSetSwitch( SD_CORE_1|SD_S_VMIXER, rev_bit_data[1] );
		rev_off_bit[1] = 0;
	}
	for( i = 0 ; i < 44 ; i++ ){
		if( spu_tr_wk[i].vol_fg ){
			if( i < 24 ){
				sceSdSetParam( SD_CORE_0|(i<<1)|SD_VP_VOLL, spu_tr_wk[i].vol_l );
				sceSdSetParam( SD_CORE_0|(i<<1)|SD_VP_VOLR, spu_tr_wk[i].vol_r );
			} else {
				sceSdSetParam( SD_CORE_1|((i-24)<<1)|SD_VP_VOLL, spu_tr_wk[i].vol_l );
				sceSdSetParam( SD_CORE_1|((i-24)<<1)|SD_VP_VOLR, spu_tr_wk[i].vol_r );
			}
			spu_tr_wk[i].vol_fg = 0;
		}
		if( spu_tr_wk[i].pitch_fg ){
			if( i < 24 ){
				sceSdSetParam( SD_CORE_0|(i<<1)|SD_VP_PITCH, spu_tr_wk[i].pitch );
			} else {
				sceSdSetParam( SD_CORE_1|((i-24)<<1)|SD_VP_PITCH, spu_tr_wk[i].pitch );
			}
			spu_tr_wk[i].pitch_fg = 0;
		}
		if( spu_tr_wk[i].addr_fg ){
			if( i < 24 ){
				sceSdSetAddr( SD_CORE_0|(i<<1)|SD_VA_SSA, (u_int)(spu_wave_start_ptr+spu_tr_wk[i].addr) );
			} else {
				sceSdSetAddr( SD_CORE_1|((i-24)<<1)|SD_VA_SSA, (u_int)(spu_wave_start_ptr+spu_tr_wk[i].addr) );
			}
			spu_tr_wk[i].addr_fg = 0;
		}
		if( spu_tr_wk[i].env1_fg || spu_tr_wk[i].env2_fg || spu_tr_wk[i].env3_fg ){
			if( i < 24 ){
				sceSdSetParam( SD_CORE_0|(i<<1)|SD_VP_ADSR1, spu_tr_wk[i].a_mode | ((spu_tr_wk[i].ar & 0x7F) << 8) | ((spu_tr_wk[i].dr & 0x0F) << 4) | (spu_tr_wk[i].sl & 0x0F) );
				sceSdSetParam( SD_CORE_0|(i<<1)|SD_VP_ADSR2, spu_tr_wk[i].s_mode | ((spu_tr_wk[i].sr & 0x7F) << 6) | spu_tr_wk[i].r_mode | (spu_tr_wk[i].rr & 0x1F) );
			} else {
				sceSdSetParam( SD_CORE_1|((i-24)<<1)|SD_VP_ADSR1, spu_tr_wk[i].a_mode | ((spu_tr_wk[i].ar & 0x7F) << 8) | ((spu_tr_wk[i].dr & 0x0F) << 4) | (spu_tr_wk[i].sl & 0x0F) );
				sceSdSetParam( SD_CORE_1|((i-24)<<1)|SD_VP_ADSR2, spu_tr_wk[i].s_mode | ((spu_tr_wk[i].sr & 0x7F) << 6) | spu_tr_wk[i].r_mode | (spu_tr_wk[i].rr & 0x1F) );
			}
			spu_tr_wk[i].env1_fg = spu_tr_wk[i].env2_fg = spu_tr_wk[i].env3_fg = 0;
		}
	}
	if( rev_on_bit[0] ){
		sceSdSetSwitch( SD_CORE_0|SD_S_VMIXEL, rev_bit_data[0] );
		sceSdSetSwitch( SD_CORE_0|SD_S_VMIXER, rev_bit_data[0] );
		rev_on_bit[0] = 0;
	}
	if( rev_on_bit[1] ){
		sceSdSetSwitch( SD_CORE_1|SD_S_VMIXEL, rev_bit_data[1] );
		sceSdSetSwitch( SD_CORE_1|SD_S_VMIXER, rev_bit_data[1] );
		rev_on_bit[1] = 0;
	}
	if( keyons[0] ){
		sceSdSetSwitch( SD_CORE_0|SD_S_KON, keyons[0] );
		keyons[0] = 0;
	}
	if( keyons[1] ){
		sceSdSetSwitch( SD_CORE_1|SD_S_KON, keyons[1] );
		keyons[1] = 0;
	}
}

/*---------------------------------------------------------------------------*/

void sound_off( void )
{
	int i;
	
	for( i = 0 ; i < 44 ; i++ ){
		spu_tr_wk[i].rr = 7;
		spu_tr_wk[i].env3_fg = 1;
	}
	
	keyoffs[0] = 0x00FFFFFF;
	keyoffs[1] = 0x003FFFFF;
	spuwr();
}

/*---------------------------------------------------------------------------*/

void sng_off( void )
{
	int i;
	
	for( i = 0 ; i < 44 ; i++ ){
		spu_tr_wk[i].rr = 7;
		spu_tr_wk[i].env3_fg = 1;
	}
	
	song_end[0] |= 0x00FFFFFF;
	song_end[1] |= 0xFF;
	keyoffs[0] |= 0x00FFFFFF;
	keyoffs[1] |= 0xFF;
}

/*---------------------------------------------------------------------------*/

void se_off( u_int a0 )
{
	spu_tr_wk[a0+32].rr = 0;
	spu_tr_wk[a0+32].env3_fg = 1;
	song_end[1] |= 1 << (a0+8);
	keyoffs[1] |= 1 << (a0+8);
	sound_w[a0+32].mpointer = 0;
}

/*---------------------------------------------------------------------------*/

void se_off_exp( void )
{
	int i;
	
	for( i = 32 ; i < 44 ; i++ ){
		if( sound_w[i].mpointer >= se_data && sound_w[i].mpointer < se_data+0x3000 ){
			se_off(i-32);
		}
	}
}

/*---------------------------------------------------------------------------*/

void se_off_all( void )
{
	int i;
	
	for( i = 32 ; i < 44 ; i++ ){
		if( sound_w[i].mpointer ){
			se_off(i-32);
		}
	}
}

/*---------------------------------------------------------------------------*/

void sng_pause( void )
{
	sceSdSetParam( SD_CORE_0|SD_P_MVOLL, 0 );
	sceSdSetParam( SD_CORE_0|SD_P_MVOLR, 0 );
	sceSdSetParam( SD_CORE_1|SD_P_MVOLL, 0 );
	sceSdSetParam( SD_CORE_1|SD_P_MVOLR, 0 );
}

/*---------------------------------------------------------------------------*/

void snd_pause_off( void )
{
	sceSdSetParam( SD_CORE_0|SD_P_MVOLL, 0x3FFF );
	sceSdSetParam( SD_CORE_0|SD_P_MVOLR, 0x3FFF );
	sceSdSetParam( SD_CORE_1|SD_P_MVOLL, 0x3FFF );
	sceSdSetParam( SD_CORE_1|SD_P_MVOLR, 0x3FFF );
}

/*---------------------------------------------------------------------------*/

void keyon( void )
{
	keyons[0] |= keyd[0];
	keyons[1] |= keyd[1];
}

/*---------------------------------------------------------------------------*/

void keyoff( void )
{
	keyoffs[0] |= keyd[0];
	keyoffs[1] |= keyd[1];
}

/*---------------------------------------------------------------------------*/

void tone_set( u_int a0 )
{
	u_int temp;
	struct WAVE_W *wave;
	
	if( a0 < 0x200 ){
		wave = &(voice_tbl[a0]);
	} else {
		wave = &(((struct WAVE_W *)(mem_str_buf+0x9E180))[a0]);
	}
	
	temp = (mtrack << 4)+4; // UNUSED
	spu_tr_wk[mtrack].addr = wave->addr;
	spu_tr_wk[mtrack].addr_fg = 1;
	sptr->macro = wave->sample_note;
	sptr->micro = wave->sample_tune;
	
	if( wave->a_mode ){
		spu_tr_wk[mtrack].a_mode = 0x8000;
	} else {
		spu_tr_wk[mtrack].a_mode = 0;
	}
	
	spu_tr_wk[mtrack].ar = 0x7F - ((wave->ar & 0x7F) & 0xFF);
	spu_tr_wk[mtrack].dr = 0x0F - ((wave->dr & 0x0F) & 0xFF);
	spu_tr_wk[mtrack].env1_fg = 1;
	
	switch( wave->s_mode ){
	case 0:  spu_tr_wk[mtrack].s_mode = 0x4000; break;
	case 1:  spu_tr_wk[mtrack].s_mode = 0xC000; break;
	case 2:  spu_tr_wk[mtrack].s_mode = 0x0000; break;
	default: spu_tr_wk[mtrack].s_mode = 0x8000; break;
	}
	
	spu_tr_wk[mtrack].sr = 0x7F - ((wave->sr & 0x7F) & 0xFF);
	spu_tr_wk[mtrack].sl = ((wave->sl & 0x0F) & 0xFF);
	spu_tr_wk[mtrack].env2_fg = 1;
	
	if( wave->r_mode ){
		spu_tr_wk[mtrack].r_mode = 32;
	} else {
		spu_tr_wk[mtrack].r_mode = 0;
	}
	
	spu_tr_wk[mtrack].rr = sptr->rrd = 0x1F - ((wave->rr & 0x1F) & 0xFF);
	spu_tr_wk[mtrack].env3_fg = 1;
	
	if( !sptr->panmod ){
		pan_set2( wave->pan );
	}
	
	sptr->dec_vol = wave->dec_vol;
}

/*---------------------------------------------------------------------------*/

void pan_set2( u_char a0 )
{
	if( !sptr->panoff ){
		sptr->panf = a0*2;
		sptr->pand = a0*2 << 8;
	}
}

/*---------------------------------------------------------------------------*/

// NOMATCH: accessing se_playing and se_vol produces wrong addition
void vol_set( u_int a0 )
{
	u_int temp, temp2;
	
	if( !(a0 < sptr->dec_vol) ){
		a0 -= sptr->dec_vol;
	} else {
		a0 = 0;
	}
	
	if( sptr->panmod == 2 && mtrack < 32 ){
		temp = mix_fader[mtrack].unk0C;
		if( sound_mono_fg ){
			temp = 32;
		}
		a0++;
		spu_tr_wk[mtrack].vol_r = (((se_pant[temp] * a0) / 127) * sng_master_vol[mtrack]) >> 16;
		spu_tr_wk[mtrack].vol_l = (((se_pant[64-temp] * a0) / 127) * sng_master_vol[mtrack]) >> 16;
		spu_tr_wk[mtrack].vol_fg = 1;
	} else {
		if( mtrack < 32 || !(se_playing[mtrack-32].kind) ){
			temp = sptr->pand >> 8;
			if( temp >= 41 ){
				temp = 40;
			}
			if( sound_mono_fg ){
				temp = 20;
			}
			a0++;
			if( mtrack < 32 ){
				spu_tr_wk[mtrack].vol_r = (((pant[temp] * a0) / 127) * sng_master_vol[mtrack]) >> 16;
				spu_tr_wk[mtrack].vol_l = (((pant[40-temp] * a0) / 127) * sng_master_vol[mtrack]) >> 16;
			} else {
				spu_tr_wk[mtrack].vol_r = (pant[temp] * a0) / 127;
				spu_tr_wk[mtrack].vol_l = (pant[40-temp] * a0) / 127;
			}
			spu_tr_wk[mtrack].vol_fg = 1;
		} else {
			a0 = ((a0+1) * se_vol[mtrack-32]) >> 6;
			temp = se_pan[mtrack-32];
			if( sound_mono_fg ){
				temp = 32;
			}
			a0++;
			spu_tr_wk[mtrack].vol_r = (se_pant[temp] * a0) >> 7;
			spu_tr_wk[mtrack].vol_l = (se_pant[64-temp] * a0) >> 7;
			spu_tr_wk[mtrack].vol_fg = 1;
		}
	}
}

/*---------------------------------------------------------------------------*/

void freq_set( u_int a0 )
{
	u_char temp, temp2, temp3, temp4;
	u_int temp5, *temp6;
	
	a0 += (u_char)sptr->micro;
	temp4 = a0;
	temp3 = (a0 >> 8) + ((u_char)sptr->macro);
	temp3 &= 0x7F;
	temp6 = freq_tbl;
	temp5 = temp6[temp3+1] - temp6[temp3];
	
	if( temp5 & 0x8000 ){
		temp5 = 0xC9;
	}
	
	temp = temp5;
	temp2 = temp5 >> 8;
	temp5 = ((temp * temp4) >> 8) + (temp2 * temp4);
	temp5 += temp6[temp3];
	spu_tr_wk[mtrack].pitch = temp5;
	spu_tr_wk[mtrack].pitch_fg = 1;
}

/*---------------------------------------------------------------------------*/

void drum_set( u_int a0 )
{
	a0 += 0x01B8;
	tone_set( a0 );
}
