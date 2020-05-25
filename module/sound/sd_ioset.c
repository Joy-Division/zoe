#include <sys/types.h>
#include <libsd.h>

#include "sd_incl.h"
#include "sd_ext.h"

/*---------------------------------------------------------------------------*/

int pant[41] = {
	0x0000,0x0141,0x0352,0x06F5,0x0A7A,0x0DE3,0x0F5D,0x12F7,
	0x1617,0x1919,0x1A66,0x1D40,0x1FFC,0x229C,0x2404,0x2677,
	0x28CE,0x2B07,0x2D24,0x2E44,0x2FFF,0x31A3,0x329D,0x344B,
	0x35DB,0x374F,0x3811,0x3958,0x3A82,0x3B90,0x3C81,0x3CE3,
	0x3DAA,0x3E55,0x3EF1,0x3F25,0x3F87,0x3FCB,0x3FF3,0x3FFF,
	0x3FFF
};

u_int se_pant[65] = {
	0x0000,0x00C5,0x024D,0x04CF,0x0688,0x08F3,0x0A61,0x0CB7,
	0x0E51,0x0FAC,0x11E3,0x1369,0x1589,0x16FF,0x18D5,0x1A3C,
	0x1B9C,0x1D87,0x1EA8,0x207E,0x21BF,0x22CD,0x2485,0x25B0,
	0x2751,0x2845,0x29D1,0x2ADD,0x2BE4,0x2D2C,0x2E23,0x2F7A,
	0x2FFF,0x3082,0x31C0,0x3297,0x33A2,0x346A,0x352B,0x3634,
	0x36CD,0x37C1,0x3863,0x3940,0x39BF,0x3A4C,0x3B0A,0x3B76,
	0x3C1F,0x3C8E,0x3CF6,0x3D72,0x3DCB,0x3E3F,0x3E88,0x3EE5,
	0x3F17,0x3F4A,0x3F89,0x3FA8,0x3FD2,0x3FE6,0x3FF9,0x3FFF,
	0x3FFF
};

// beat_mania_pan_table

int freq_tbl[111] = {
	0x010B,0x011B,0x012C,0x013E,0x0151,0x0165,0x017A,0x0191,
	0x01A9,0x01C2,0x01DD,0x01F9,0x0217,0x0237,0x0259,0x027D,
	0x02A3,0x02CB,0x02F5,0x0322,0x0352,0x0385,0x03BA,0x03F3,
	0x042F,0x046F,0x04B2,0x04FA,0x0546,0x0596,0x05EB,0x0645,
	0x06A5,0x070A,0x0775,0x07E6,0x085F,0x08DE,0x0965,0x09F4,
	0x0A8C,0x0B2C,0x0BD6,0x0C8B,0x0D4A,0x0E14,0x0EEA,0x0FCD,
	0x10BE,0x11BD,0x12CB,0x13E9,0x1518,0x1659,0x17AD,0x1916,
	0x1A94,0x1C28,0x1DD5,0x1F9B,0x217C,0x237A,0x2596,0x27D2,
	0x2A30,0x2CB2,0x2F5A,0x322C,0x3528,0x3850,0x3BAC,0x3F36,
	0x0021,0x0023,0x0026,0x0028,0x002A,0x002D,0x002F,0x0032,
	0x0035,0x0038,0x003C,0x003F,0x0042,0x0046,0x004B,0x004F,
	0x0054,0x0059,0x005E,0x0064,0x006A,0x0070,0x0077,0x007E,
	0x0085,0x008D,0x0096,0x009F,0x00A8,0x00B2,0x00BD,0x00C8,
	0x00D4,0x00E1,0x00EE,0x00FC,0x0000,0x0000,0x0000
};


/* unreferenced TGS2000 variables */
// char send_timer[16] = {0};



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
				sceSdSetAddr( SD_CORE_0|(i<<1)|SD_VA_SSA, spu_tr_wk[i].addr+(u_int)spu_wave_start_ptr );
			} else {
				sceSdSetAddr( SD_CORE_1|((i-24)<<1)|SD_VA_SSA, spu_tr_wk[i].addr+(u_int)spu_wave_start_ptr );
			}
			spu_tr_wk[i].addr_fg = 0;
		}
		if( spu_tr_wk[i].env1_fg || spu_tr_wk[i].env2_fg || spu_tr_wk[i].env3_fg ){
			if( i < 24 ){
				sceSdSetParam( SD_CORE_0|(i<<1)|SD_VP_ADSR1,
					SD_ADSR1(spu_tr_wk[i].a_mode, spu_tr_wk[i].ar, spu_tr_wk[i].dr, spu_tr_wk[i].sl)
				);
				sceSdSetParam( SD_CORE_0|(i<<1)|SD_VP_ADSR2,
					SD_ADSR2(spu_tr_wk[i].s_mode, spu_tr_wk[i].sr, spu_tr_wk[i].r_mode, spu_tr_wk[i].rr)
				);
			} else {
				sceSdSetParam( SD_CORE_1|((i-24)<<1)|SD_VP_ADSR1,
					SD_ADSR1(spu_tr_wk[i].a_mode, spu_tr_wk[i].ar, spu_tr_wk[i].dr, spu_tr_wk[i].sl)
				);
				sceSdSetParam( SD_CORE_1|((i-24)<<1)|SD_VP_ADSR2,
					SD_ADSR2(spu_tr_wk[i].s_mode, spu_tr_wk[i].sr, spu_tr_wk[i].r_mode, spu_tr_wk[i].rr)
				);
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

	for( i = 0 ; i < 32 ; i++ ){
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
		spu_tr_wk[mtrack].vol_r = (((a0 * se_pant[temp]) / 127) * sng_master_vol[mtrack]) >> 16;
		spu_tr_wk[mtrack].vol_l = (((a0 * se_pant[64-temp]) / 127) * sng_master_vol[mtrack]) >> 16;
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
				spu_tr_wk[mtrack].vol_r = (((a0 * pant[temp]) / 127) * sng_master_vol[mtrack]) >> 16;
				spu_tr_wk[mtrack].vol_l = (((a0 * pant[40-temp]) / 127) * sng_master_vol[mtrack]) >> 16;
			} else {
				spu_tr_wk[mtrack].vol_r = (a0 * pant[temp]) / 127;
				spu_tr_wk[mtrack].vol_l = (a0 * pant[40-temp]) / 127;
			}
			spu_tr_wk[mtrack].vol_fg = 1;
		} else {
			a0 = ((a0+1) * se_vol[mtrack-32]) >> 6;
			temp = se_pan[mtrack-32];
			if( sound_mono_fg ){
				temp = 32;
			}
			a0++;
			spu_tr_wk[mtrack].vol_r = (a0 * se_pant[temp]) >> 7;
			spu_tr_wk[mtrack].vol_l = (a0 * se_pant[64-temp]) >> 7;
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
