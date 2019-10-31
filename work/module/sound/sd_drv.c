/*
 * Sound Driver for PS2 IOP
 * Driver Module
 *
 * ver.ZONE OF THE ENDERS
 */
#include <sys/types.h>
#include <kernel.h>
#include "sd_incl.h"

void IntSdMain( void )
{
	int temp, temp2;
	
	if (sd_sng_code_buf[sd_code_read]){
		temp = sd_sng_code_buf[sd_code_read];
		sd_sng_code_buf[sd_code_read] = 0;
		sd_code_read = (sd_code_read+1) & 0xF;
	}
	else {
		temp = 0;
	}
	
	if (temp){
		switch (temp){
		case 0x01FFFF01:
			sng_pause_fg = 1;
			sng_pause();
			break;
		case 0x01FFFF02:
			snd_pause_off();
			sng_pause_fg = 0;
			break;
		case 0x01FFFF03: {
			if(sng_play_code != 0xFFFFFFFF) {
				sng_fout_fg = 0;
				if(sng_status < 3) {
					sng_fadein_fg = temp;
				}
				else {
					SngFadeIn(temp);
				}
				sng_kaihi_fg = 0;
			}
			break;
		
		// Fade Out
		case 0x01FFFF04: SngFadeOutP( temp ); break;
		case 0x01FFFF05: SngFadeOutS( temp ); break;
		
		// 回避モード (Evasion Mode)
		case 0x01FFFF10: SngKaihiP(); break;
		case 0x01FFFF11: SngKaihiReset(); break;
		case 0x01FFFF12: SngKaihiReset2(); break;
		
		// 主観モード (First Person Mode)
		case 0x01FFFF20: sng_syukan_fg = 1; break;
		case 0x01FFFF21: sng_syukan_fg = 0; break;
		
		// Sound Effect
		case 0x01FFFFFD: se_off_exp(); break;
		case 0x01FFFFFE: se_off_all(); break;
		
		// Song Off
		case 0x01FFFFFF:
			sng_play_code = 0xFFFFFFFF;
			sng_off();
			sng_status = 0;
			break;
		
		case 0xFF0000FF: skip_intro_loop = 1; break;
		case 0xFF000101: auto_phase_fg = 1; break;
		case 0xFF000102: auto_phase_fg = 2; break;
		case 0xFF000103: auto_phase_fg = 3; break;
		case 0xFF000104: auto_phase_fg = 4; break;
		case 0xFF000105: auto_phase_fg = 5; break;
		case 0xFF000106: auto_phase_fg = 6; break;
		case 0xFF000107: auto_phase_fg = 7; break;
		case 0xFF000108: auto_phase_fg = 8; break;
		
		case 0xFF000109:
			if (sng_play_code != temp){
				if (sng_data[0] < (temp & 0xF)){
					temp = 0;
				} else {
					sng_status = 2;
					if (sng_play_code == 0xFFFFFFFF){
						for (temp2 = 0; temp2 < 0x20; temp2++){
							sng_fade_time[temp2] = 0;
							sng_fade_value[temp2] = 0;
							sng_master_vol[temp2] = 0;
						}
						sng_fout_term[1] = 0;
						sng_fout_term[0] = 0;
					}
					sng_play_code = temp;
					sng_off();
					sng_pause_fg = 0;
					sng_kaihi_fg = 0;
					auto_phase_fg = 0;
					auto_env_pos2 = 0;
					auto_env_pos = 0;
					skip_intro_loop = 0;
				}
			} else {
				// EMPTY
			}
			break;
		
		default:
			if (sng_load_code != temp){
				sng_load_code = temp;
				WakeupThread( id_SdMain );
			}
			break;
		}
	}
	
	if (d1E0E4[1]){
		sng_load_code = d1E0E4[1];
		d1E0E4[1] = 0;
	}
	
	switch (sng_status){
	case 1: break;
	case 2:
		if (sng_load_code || pak_load_status){
			break;
		}
		if (sng_play_code && sng_play_code != 0xFFFFFFFF){
			sng_adrs_set( sng_play_code );
			SngFadeWkSet();
			if (fader_off_fg){
				for (temp2 = 0 ; temp2 < 0x20 ; temp2++){
					mix_fader[temp2].unk04 = mix_fader[temp2].unk08 = 0;
					mix_fader[temp2].unk00 = 0;
				}
				fader_off_fg = 0;
			} else {
				for (temp2 = 0 ; temp2 < 0x20 ; temp2++){
					mix_fader[temp2].unk04 = mix_fader[temp2].unk08 = 0xFFFF;
					mix_fader[temp2].unk00 = 0;
				}
			}
			sng_status = 3;
		}
		break;
	
	case 3:
		SngFadeInt();
		SngTempoInt();
		for (mtrack = 0 ; mtrack < 0x20 ; mtrack++){
			if (mtrack < 0x18){
				keyd[0] = (1 << mtrack);
				keyd[1] = 0;
				if (song_end[0] & keyd[0]){
					continue;
				}
			} else {
				keyd[0] = 0;
				keyd[1] = (1 << (mtrack-0x18));
				if (song_end[1] & keyd[1]){
					continue;
				}
			}
			sptr = &sound_w[mtrack];
			if (!sptr->mpointer){
				song_end[0] |= keyd[0];
				song_end[1] |= keyd[1];
			} else {
				mptr = sptr->mpointer;
				if (sound_sub()){
					song_end[0] |= keyd[0];
					song_end[1] |= keyd[1];
					sptr->mpointer = 0;
				} else {
					sptr->mpointer = mptr;
				}
			}
		}
		if (song_end[0] == 0xFFFFFF && song_end[1] == 0xFF){
			sng_status = 4;
		}
		if (fx_sound_code >= 2){
			fx_sound_code = 0;
		}
		if (skip_intro_loop >= 2){
			skip_intro_loop = 0;
		}
		break;
	
	case 4:
		sng_off();
		sng_play_code = 0;
		sng_status = 2;
		break;
	}
	
	for (mtrack = 0x20 ; mtrack < 0x2C ; mtrack++){
		if (se_tracks < 2 && se_request[mtrack-0x20].code){
			se_off(mtrack-0x20);
			se_adrs_set(mtrack-0x20);
		} else {
			keyd[0] = 0;
			keyd[1] = (1 << (mtrack-0x18));
			if (song_end[1] & keyd[1]){
				continue;
			}
			sptr = &sound_w[mtrack];
			if (!sptr->mpointer){
				song_end[1] |= keyd[1];
			} else {
				mptr = sptr->mpointer;
				if (sound_sub()){
					song_end[1] |= keyd[1];
					sptr->mpointer = 0;
				} else {
					sptr->mpointer = mptr;
				}
			}
		}
	}
	
	if (stop_jouchuu_se >= 2){
		stop_jouchuu_se = 0;
	}
	
	if (sceSdVoiceTransStatus( 0, 0 ) == 1){
		if (wave_load_status == 2 || wave_load_status == 4){
			WaveSpuTrans();
			WakeupThread( id_SdMain );
		} else {
			for (mtrack = 0x20 ; mtrack < 0x2C ; mtrack++){
				keyd[0] = 0;
				keyd[1] = (1 << (mtrack-0x18));
				if (MemSpuTransWithNoLoop(mtrack)){
					break;
				}
			}
		}
	}
	
	spuwr();
}

void SngFadeIn( u_int a0 )
{
	int temp;
	
	switch (a0){
	case 0x1FFFF03: sng_fadein_time = 0x0147; break;
	case 0x1FFFF04: sng_fadein_time = 0x006D; break;
	case 0x1FFFF05: sng_fadein_time = 0x0041; break;
	}
	
	if (!sng_fadein_time){
		sng_fadein_time = 1;
	}
	
	for (temp = 0 ; temp < 0x20 ; temp++){
		sng_fade_time[temp] = 0;
	}
	
	sng_fout_term[1] = 0;
	sng_fout_term[0] = 0;
}

int SngFadeOutP( u_int a0 )
{
	int temp, temp2;
	
	if (sng_status && sng_fout_term[0] != 0xFFFFFF && sng_fout_term[1] != 0xFF){
		switch (a0){
		case 0x1FFFF06: temp = 0x028F; break;
		case 0x1FFFF07: temp = 0x0147; break;
		case 0x1FFFF08: temp = 0x006D; break;
		case 0x1FFFF09: temp = 0x0041; break;
		}
		if (!temp){
			sng_fadein_time = 1;
		}
		for (temp2 = 0 ; temp2 < 0x20 ; temp2++){
			if (temp2 < 0x18){
				if (!((sng_fout_term[0] >> temp2) & 1)){
					sng_fade_time[temp2] = temp;
				}
			} else {
				if (!((sng_fout_term[1] >> (temp2 - 0x18)) & 1)){
					sng_fade_time[temp2] = temp;
				}
			}
		}
		sng_fadein_time = 0;
		return 0;
	} else {
		return -1;
	}
}

int SngFadeOutS( u_int a0 )
{
	int temp, temp2;
	
	if ((sng_status && sng_fout_term[0] != 0xFFFFFF && sng_fout_term[1] != 0xFF) || (sng_status && sng_fadein_time)){
		switch (a0){
		case 0x1FFFF0A: temp = 0x028F; break;
		case 0x1FFFF0B: temp = 0x0147; break;
		case 0x1FFFF0C: temp = 0x006D; break;
		case 0x1FFFF0D: temp = 0x0041; break;
		}
		if (!temp){
			sng_fadein_time = 1;
		}
		for (temp2 = 0 ; temp2 < 0x20 ; temp2++){
			if(temp2 < 0x18) {
				if (!((sng_fout_term[0] >> temp2) & 1)){
					sng_fade_time[temp2] = temp;
				}
			} else {
				if (!((sng_fout_term[1] >> (temp2 - 0x18)) & 1)){
					sng_fade_time[temp2] = temp;
				}
			}
		}
		sng_fadein_time = 0;
		sng_play_code = -1;
		return 0;
	} else {
		sng_fadein_time = 0;
		sng_play_code = -1;
		sng_off();
		sng_status = 0;
		return -1;
	}
}

int SngKaihiP( void )
{
	int temp;
	
	if (!sng_kaihi_fg){
		for (temp = 0 ; temp < 0x10 ; temp++){
			mix_fader[temp].unk08 = 0;
			mix_fader[temp].unk00 = (mix_fader[temp].unk08 - mix_fader[temp].unk04) / 1200;
		}
		for (temp = 0x10 ; temp < 0x20 ; temp++){
			mix_fader[temp].unk08 = 0xFFFF;
			mix_fader[temp].unk00 = (mix_fader[temp].unk08 - mix_fader[temp].unk04) / 1000;
		}
		sng_kaihi_fg = 1;
	} else {
		for (temp = 0 ; temp < 0x10 ; temp++){
			mix_fader[temp].unk08 = 0xFFFF;
			mix_fader[temp].unk00 = (mix_fader[temp].unk08 - mix_fader[temp].unk04) / 100;
		}
		for (temp = 0x10; temp < 0x20; temp++){
			mix_fader[temp].unk08 = 0xFFFF;
			mix_fader[temp].unk00 = (mix_fader[temp].unk08 - mix_fader[temp].unk04) / 400;
		}
		sng_kaihi_fg = 0;
	}
	return 0;
}

void SngKaihiReset( void )
{
	int i;
	
	for (i = 0 ; i < 0x10 ; i++){
		mix_fader[i].unk04 = 0xFFFF;
		mix_fader[i].unk08 = 0xFFFF;
		mix_fader[i].unk00 = 0;
	}
	for (i = 0x10 ; i < 0x20 ; i++){
		mix_fader[i].unk04 = 0;
		mix_fader[i].unk08 = 0;
		mix_fader[i].unk00 = 0;
	}
	sng_kaihi_fg = 0;
}

void SngKaihiReset2( void )
{
	int i;
	
	for (i = 0 ; i < 0x10 ; i++){
		mix_fader[i].unk04 = 0;
		mix_fader[i].unk08 = 0;
		mix_fader[i].unk00 = 0;
	}
	for (i = 0x10 ; i < 0x20 ; i++){
		mix_fader[i].unk04 = 0xFFFF;
		mix_fader[i].unk08 = 0xFFFF;
		mix_fader[i].unk00 = 0;
	}
	sng_kaihi_fg = 0;
}

void SngFadeWkSet( void )
{
	int i;
	
	if (!sng_fadein_fg){
		sng_fadein_time = 0;
		for (i = 0 ; i < 0x20 ; i++){
			sng_fade_time[i] = 0;
		}
		for (i = 0 ; i < 0x20 ; i++){
			sng_fade_value[i] = 0;
		}
	} else {
		switch(sng_fadein_fg) {
		case 0x1FFFF03:
		case 0x1FFFF04:
		case 0x1FFFF05:
			SngFadeIn(sng_fadein_fg);
			for (i = 0 ; i < 0x20 ; i++){
				sng_fade_value[i] = 1;
			}
			sng_fadein_fg = 0;
		}
	}
	sng_fout_term[1] = 0;
	sng_fout_term[0] = 0;
	sng_fout_fg = 0;
}

// NOMATCH: see inside
void SngFadeInt( void )
{
	int temp;
	u_int temp2, temp3;
	int i, temp5 = 0, temp6 = 0;
	u_int temp7, temp8;
	
	if (sng_status < 3){
		for (i = 0; i < 0x20; i++){
			temp5 |= sng_fade_time[i];
		}
		if (temp5){
			for (i = 0 ; i < 0x20 ; i++){
				if (sng_fade_time[i]){
					sng_fade_value[i] += sng_fade_time[i];
					if (sng_fade_value[i] >= 0x10000){
						if (i < 0x18){
							sng_fout_term[0] |= (1 << i);
						} else {
							sng_fout_term[1] |= (1 << (i-0x18));
						}
						sng_fade_value[i] = 1;
						sng_fade_time[i] = 0;
					}
					if (sng_fout_term[0] == 0xFFFFFF && sng_fout_term[1] == 0xFF){
						if (sng_play_code == 0xFFFFFFFF){
							sng_status = 4;
						} else {
							sng_fout_fg = 1;
						}
					} else {
						sng_fout_fg = 0;
					}
				}
			}
		} else {
			if ((str_load_code && str_status) || (str2_load_code[0] && str2_status[0]) || (str2_load_code[1] && str2_status[1])){
				if (vox_on_vol < 0x6000){
					vox_on_vol += 0xF5;
					if (vox_on_vol > 0x6000){
						vox_on_vol = 0x6000;
					}
				}
			} else {
				if (vox_on_vol){
					vox_on_vol -= 0x7A;
					if (vox_on_vol < 0){
						vox_on_vol = 0;
					}
				}
			}
			if (sng_fadein_time){
				for (i = 0 ; i < 0x20 ; i++){
					if (sng_fade_value[i] <= sng_fadein_time){
						sng_fade_value[i] = 0;
					} else {
						sng_fade_value[i] -= sng_fadein_time;
					}
					temp6 |= sng_fade_value[i];
				}
				if (!temp6){
					sng_fadein_time = 0;
				}
			}
		}
		if (sng_syukan_fg){
			if (sng_syukan_vol < 0x5000){
				sng_syukan_vol += 0xCC;
				if (sng_syukan_vol > 0x5000){
					sng_syukan_vol = 0x5000;
				}
			}
		} else {
			if (sng_syukan_vol){
				sng_syukan_vol -= 0x66;
				if (sng_syukan_vol < 0){
					sng_syukan_vol = 0;
				}
			}
		}
		for (i = 0 ; i < 0x20 ; i++){
			temp = 1;
			if ((vox_on_vol >= sng_syukan_vol) && !fg_syukan_off[i]){
				temp3 = sng_syukan_vol;
			} else {
				temp3 = vox_on_vol;
			}
			if (sng_fade_value[i] > temp3){
				temp2 = sng_fade_value[i];
			} else {
				temp2 = temp3;
			}
			if (temp2 < temp3){
				temp = 0;
			} else {
				temp -= temp2;
			}
			if (mix_fader[i].unk04 != mix_fader[i].unk08){
				mix_fader[i].unk04 += mix_fader[i].unk00;
				if (mix_fader[i].unk00 >= 0){
					if ((u_int)mix_fader[i].unk04 > mix_fader[i].unk08){
						mix_fader[i].unk04 = mix_fader[i].unk08;
						mix_fader[i].unk00 = 0;
					}
				} else {
					if (mix_fader[i].unk04 < mix_fader[i].unk08){
						mix_fader[i].unk04 = mix_fader[i].unk08;
						mix_fader[i].unk00 = 0;
					}
				}
			}
			temp8 = temp * mix_fader[i].unk04;
			// 0xD5B4 this is rather close but it has an additional
			// shift after the multiplication
			temp7 = (temp8 / (65535));
			temp = temp7 >> 15;
			sng_master_vol[i] = temp;
		}
	}
}

void SngTempoInt( void )
{
	// EMPTY
}

void init_sng_work( void )
{
	for (mtrack = 0 ; mtrack < 0x2C ; mtrack++){
		sptr = &sound_w[mtrack];
		sptr->mpointer = 0;
		sptr->lp1_addr = sptr->lp2_addr = sptr->lp3_addr = 0;
		sng_track_init( sptr );
	}
	keyons[1] = 0;
	keyons[0] = 0;
	keyoffs[1] = 0;
	keyoffs[0] = 0;
	sng_play_code = 0;
}

void sng_adrs_set( u_int a0 )
{
	u_int i, temp2, temp3, temp4, temp5;
	
	a0 &= 0xF;
	temp3 = sng_data[a0*4+3] << 24;
	temp3 += sng_data[a0*4+2] << 16;
	temp3 += sng_data[a0*4+1] << 8;
	temp3 += sng_data[a0*4];
	song_end[0] = 0;
	song_end[1] &= 0xFFFF00;
	
	for (i = 0; i < 0x20; i++){
		temp2 = i << 2;
		temp4 = sng_data[(temp3 + temp2 + 2)] << 16;
		temp4 += sng_data[(temp3 + temp2 + 1)] << 8;
		temp4 += sng_data[(temp3 + temp2)];
		if (temp4){
			sound_w[i].mpointer = sng_data + temp4;
			sng_track_init( &sound_w[i] );
		} else {
			if (i < 0x18){
				song_end[0] |= (1 << i);
			} else {
				song_end[1] |= (1 << (i-0x18));
			}
		}
	}
	keyons[0] = 0;
	keyons[1] &= 0xFFFF00;
	fx_sound_code = 0;
}

void se_adrs_set( u_int a0 )
{
	se_playing[a0].code = se_request[a0].code;
	se_playing[a0].pri = se_request[a0].pri;
	se_playing[a0].kind = se_request[a0].kind;
	se_playing[a0].character = se_request[a0].character;
	se_playing[a0].addr = se_request[a0].addr;
	se_request[a0].code = 0;
	se_request[a0].pri = 0;
	se_request[a0].character = 0;
	
	sng_track_init( &sound_w[a0+0x20] );
	
	se_vol[a0] = (se_playing[a0].code & (u_int)(mem_str_buf+0x20920)) >> 12;
	se_pan[a0] = (se_playing[a0].code >> 18) & 0x3F;
	sound_w[a0+0x20].mpointer = se_playing[a0].addr;
	song_end[1] &= ~(1 << (a0+8));
	keyons[1] &= ~(1 << (a0+8));
	keyoffs[1] &= ~(1 << (a0+8));
	
	if (se_playing[a0].kind){
		if (se_rev_on){
			rev_on_bit[1] |= (1 << (a0+8));
			rev_bit_data[1] |= (1 << (a0+8));
		} else {
			rev_off_bit[1] |= (1 << (a0+8));
			rev_bit_data[1] &= ~(1 << (a0+8));
		}
	}
}

void sng_track_init( struct SOUND_W *work )
{
	work->rdmd = 0;
	work->ngc = 1;
	work->ngo = 0;
	work->ngs = 0;
	work->ngg = 0;
	work->lp1_cnt = 0;
	work->lp2_cnt = 0;
	work->lp1_vol = 0;
	work->lp2_vol = 0;
	work->lp1_freq = 0;
	work->lp2_freq = 0;
	work->pvoc = 0;
	work->pvod = 0x7F;
	work->vol = 0x7F;
	work->pand = 0x1400;
	work->panf = 0x14;
	work->panoff = 0;
	work->panmod = 0;
	work->swsk = 0;
	work->swsc = 0;
	work->vibd = 0;
	work->vibdm = 0;
	work->tred = 0;
	work->snos = 0;
	work->ptps = 0;
	work->dec_vol = 0;
	work->tund = 0;
	work->tmpd = 1;
	work->tmp = 0xFF;
	work->tmpc = 0;
	/*
	 * for PlayStation 2
	 */
	work->unkD4 = 0;
	work->unkD9 = 1;
	work->unkE0 = 0;
	work->unkE1 = 0;
	work->unkE4 = 0xFFFFFFFF;
	work->unkE8 = 0;
	work->unkE9 = 0;
	work->unkEA = 0;
	work->unkEB = 0;
	work->unkEC = 0;
	work->unkED = 0;
	work->unkEE = 0;
	work->unkEF = 0;
	work->unkF0 = 0;
	work->unkF1 = 0;
	work->unkF2 = 0;
	work->unkF3 = 0;
	work->unkF4 = 0;
	work->unkF5 = 0;
	work->unkF6 = 0;
	work->unkF7 = 0;
	work->unkF8 = 0;
}