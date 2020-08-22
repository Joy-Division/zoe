#include <sys/types.h>
#include <kernel.h>

#include "sd_incl.h"
#include "sd_ext.h"
#include "sd_debug.h"

/*---------------------------------------------------------------------------*/

void IntSdMain( void )
{
	int temp, i;

	if( sd_sng_code_buf[sd_code_read] ){
		temp = sd_sng_code_buf[sd_code_read];
		sd_sng_code_buf[sd_code_read] = 0;
		sd_code_read = (sd_code_read+1) & 0x0F;
	} else {
		temp = 0;
	}

	if( temp ){
		switch( temp ){

		/* Pause Song */
		case 0x01FFFF01:
			sng_pause_fg = 1;
			sng_pause();
			PRINTF(( "SongPauseOn\n" ));
			break;

		/* Unpause Song */
		case 0x01FFFF02:
			sng_pause_off();
			sng_pause_fg = 0;
			PRINTF(( "SongPauseOff\n" ));
			break;

		case 0x01FFFF03: /* fallthrough */
		case 0x01FFFF04: /* fallthrough */
		case 0x01FFFF05:
			if( sng_play_code != 0xFFFFFFFF ){
				sng_fout_fg = 0;
				if( sng_status < 3 ){
					sng_fadein_fg = temp;
				} else {
					SngFadeIn( temp );
				}
				sng_kaihi_fg = 0;
			}
			PRINTF(( "SongFadein\n" ));
			break;

		/* Fade Out */
		case 0x01FFFF06: /* fallthrough */
		case 0x01FFFF07: /* fallthrough */
		case 0x01FFFF08: /* fallthrough */
		case 0x01FFFF09:
			SngFadeOutP( temp );
			PRINTF(( "SongFadeout&Pause\n" ));
			break;

		case 0x01FFFF0A: /* fallthrough */
		case 0x01FFFF0B: /* fallthrough */
		case 0x01FFFF0C: /* fallthrough */
		case 0x01FFFF0D:
			SngFadeOutS( temp );
			PRINTF(( "SongFadeout&Stop\n" ));
			break;

		/* 回避モード *//* Evasion Mode */
		case 0x01FFFF10:
			SngKaihiP();
			PRINTF(( "SongKaihiMode\n" ));
			break;

		case 0x01FFFF11:
			SngKaihiReset();
			PRINTF(( "SongKaihiReset\n" ));
			break;

		case 0x01FFFF12:
			SngKaihiReset2();
			PRINTF(( "SongKaihiReset\n" ));
			break;

		/* 主観モード *//* First Person Mode */
		case 0x01FFFF20:
			sng_syukan_fg = 1;
			PRINTF(( "SongSyukanMode On\n" ));
			break;

		case 0x01FFFF21:
			sng_syukan_fg = 0;
			PRINTF(( "SongSyukanMode Off\n" ));
			break;

		/* Sound Effect Off */
		case 0x01FFFFFD: se_off_exp(); break;
		case 0x01FFFFFE: se_off_all(); break;

		/* Song Off */
		case 0x01FFFFFF:
		#ifdef BORMAN_DEMO
			sng_play_code = 0;
		#else
			sng_play_code = 0xFFFFFFFF;
		#endif
			sng_off();
			PRINTF(( "SongStop\n" ));
		#ifndef BORMAN_DEMO
			sng_status = 0;
		#endif
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

		case 0x1000001: /* fallthrough */
		case 0x1000002: /* fallthrough */
		case 0x1000003: /* fallthrough */
		case 0x1000004: /* fallthrough */
		case 0x1000005: /* fallthrough */
		case 0x1000006: /* fallthrough */
		case 0x1000007: /* fallthrough */
		case 0x1000008:
			if( sng_play_code != temp ){
				/* more ifdef here */
				#ifdef BORMAN_DEMO
				if( sng_status >= 2 ) {
				#endif
				if( sng_data[0] < (temp & 0x0F) ){
					PRINTF(( "ERROR:SNG PLAY CODE(%x/%x)\n", temp, sng_data[0] ));
					temp = 0;
				} else {
					sng_status = 2;
					if( sng_play_code == 0xFFFFFFFF ){
						for( i = 0 ; i < 32 ; i++ ){
							sng_fade_time[i] = 0;
							sng_fade_value[i] = 0;
							sng_master_vol[i] = 0;
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
				#ifdef BORMAN_DEMO
				} else {
					PRINTF(( "sng_status=%x\n", sng_status ));
				}
				#endif
			} else {
				PRINTF(( "SameSongHasAlreadyPlayed\n" ));
			}
			break;

		default:
			if( sng_load_code != temp ){
				sng_load_code = temp;
			#ifdef BORMAN_DEMO
				sng_play_code = 0;
				sng_status = 1;
				sng_off();
			#endif
				WakeupThread( id_SdMain );
			}
			break;
		}
	}

#ifndef BORMAN_DEMO
	if( mem_str_fg ){				// guessed varname
		sng_load_code = mem_str_fg;	// guessed varname
		mem_str_fg = 0;				// guessed varname
	}
#endif

	switch( sng_status ){
#ifndef BORMAN_DEMO
	case 1:
		break;
#endif
	case 2:
	#ifndef BORMAN_DEMO
		if( sng_load_code || pak_load_status ){
			break;
		}
	#endif
		if( sng_play_code && sng_play_code != 0xFFFFFFFF ){
			sng_adrs_set( sng_play_code );
			SngFadeWkSet();
			if( fader_off_fg ){
				for( i = 0 ; i < 32 ; i++ ){
					mix_fader[i].vol_current = mix_fader[i].vol_target = 0;
					mix_fader[i].vol_step = 0;
				}
				fader_off_fg = 0;
			} else {
				for( i = 0 ; i < 32 ; i++ ){
					mix_fader[i].vol_current = mix_fader[i].vol_target = 0xFFFF;
					mix_fader[i].vol_step = 0;
				}
			}
			sng_status = 3;
		}
		break;

	case 3:
		SngFadeInt();
		SngTempoInt();
		for( mtrack = 0 ; mtrack < 32 ; mtrack++ ){
			if( mtrack < 24 ){
				keyd[0] = (1 << mtrack);
				keyd[1] = 0;
				if( song_end[0] & keyd[0] ){
					continue;
				}
			} else {
				keyd[0] = 0;
				keyd[1] = (1 << (mtrack-24));
				if( song_end[1] & keyd[1] ){
					continue;
				}
			}
			sptr = &sound_w[mtrack];
			if( !sptr->mpointer ){
				song_end[0] |= keyd[0];
				song_end[1] |= keyd[1];
			} else {
				mptr = sptr->mpointer;
				if( sound_sub() ){
					song_end[0] |= keyd[0];
					song_end[1] |= keyd[1];
					sptr->mpointer = 0;
				} else {
					sptr->mpointer = mptr;
				}
			}
		}
		if( song_end[0] == 0x00FFFFFF && song_end[1] == 0xFF ){
			sng_status = 4;
		}
		if( fx_sound_code > 1 ){
			fx_sound_code = 0;
		}
		if( skip_intro_loop > 1 ){
			skip_intro_loop = 0;
		}
		break;

	case 4:
		sng_off();
		sng_play_code = 0;
		sng_status = 2;
		break;
	}


	for( mtrack = 32 ; mtrack < 44 ; mtrack++ ){
		if( se_tracks <= 1 && se_request[mtrack-32].code ){
			se_off( mtrack-32 );
			se_adrs_set( mtrack-32 );
		} else {
			keyd[0] = 0;
			keyd[1] = (1 << (mtrack-0x18));
			if( song_end[1] & keyd[1] ){
				continue;
			}
			sptr = &sound_w[mtrack];
			if( !sptr->mpointer ){
				song_end[1] |= keyd[1];
			} else {
				mptr = sptr->mpointer;
				if( sound_sub() ){
					song_end[1] |= keyd[1];
					sptr->mpointer = 0;
				} else {
					sptr->mpointer = mptr;
				}
			}
		}
	}

	if( stop_jouchuu_se > 1 ){
		stop_jouchuu_se = 0;
	}

	if( sceSdVoiceTransStatus( 0, SD_TRANS_STATUS_CHECK ) == 1 ){
		if( wave_load_status == 2 || wave_load_status == 4 ){
			WaveSpuTrans();
			WakeupThread( id_SdMain );
		} else {
			for( mtrack = 32 ; mtrack < 44 ; mtrack++ ){
				keyd[0] = 0;
				keyd[1] = (1 << (mtrack-0x18));
				if( MemSpuTransWithNoLoop(mtrack) ){
					break;
				}
			}
		}
	} else {
		PRINTF(( ">" ));
	}
	spuwr();
}

/*---------------------------------------------------------------------------*/

void SngFadeIn( u_int a0 )
{
	int i;

	switch( a0 ){
	case 0x01FFFF03: sng_fadein_time = 0x0147; break;
	case 0x01FFFF04: sng_fadein_time = 0x006D; break;
	case 0x01FFFF05: sng_fadein_time = 0x0041; break;
	}

	if( !sng_fadein_time ){
		sng_fadein_time = 1;
	}

	for( i = 0 ; i < 32 ; i++ ){
		sng_fade_time[i] = 0;
	}

	sng_fout_term[1] = 0;
	sng_fout_term[0] = 0;
}

/*---------------------------------------------------------------------------*/

int SngFadeOutP( u_int a0 )
{
	int temp, i;

	if( sng_status && sng_fout_term[0] != 0x00FFFFFF && sng_fout_term[1] != 0xFF ){
		switch( a0 ){
		case 0x01FFFF06: temp = 0x028F; break;
		case 0x01FFFF07: temp = 0x0147; break;
		case 0x01FFFF08: temp = 0x006D; break;
		case 0x01FFFF09: temp = 0x0041; break;
		}
		if( !temp ){
			temp = 1;
		}
		for( i = 0 ; i < 32 ; i++ ){
			if( i < 24 ){
				if( !((sng_fout_term[0] >> i) & 1) ){
					sng_fade_time[i] = temp;
				}
			} else {
				if( !((sng_fout_term[1] >> (i-24)) & 1) ){
					sng_fade_time[i] = temp;
				}
			}
		}
		sng_fadein_time = 0;
		return 0;
	} else {
		return -1;
	}
}

/*---------------------------------------------------------------------------*/

int SngFadeOutS( u_int a0 )
{
	int temp, i;

	if( (sng_status && sng_fout_term[0] != 0x00FFFFFF && sng_fout_term[1] != 0xFF) || (sng_status && sng_fadein_time) ){
		switch( a0 ){
		case 0x01FFFF0A: temp = 0x028F; break;
		case 0x01FFFF0B: temp = 0x0147; break;
		case 0x01FFFF0C: temp = 0x006D; break;
		case 0x01FFFF0D: temp = 0x0041; break;
		}
		if( !temp ){
			temp = 1;
		}
		for( i = 0 ; i < 32 ; i++ ){
			if( i < 0x18 ){
				if( !((sng_fout_term[0] >> i) & 1) ){
					sng_fade_time[i] = temp;
				}
			} else {
				if( !((sng_fout_term[1] >> (i - 0x18)) & 1) ){
					sng_fade_time[i] = temp;
				}
			}
		}
		sng_fadein_time = 0;
		sng_play_code = -1;
		PRINTF(( "SNG FADEOUT START(status=%x)\n", sng_status ));
		return 0;
	} else {
	#ifdef BORMAN_DEMO
		PRINTF(( "SNG FADEOUT CANCELED(status=%x)\n", sng_status ));
	#else
		sng_fadein_time = 0;
		sng_play_code = -1;
		sng_off();
		sng_status = 0;
	#endif
		return -1;
	}
}

/*---------------------------------------------------------------------------*/

int SngKaihiP( void )
{
	int i;

	if( !sng_kaihi_fg ){
		for( i = 0 ; i < 16 ; i++ ){
			mix_fader[i].vol_target = 0;
			mix_fader[i].vol_step = (mix_fader[i].vol_target - mix_fader[i].vol_current) / 1200;
		}
		for( i = 16 ; i < 32 ; i++ ){
			mix_fader[i].vol_target = 0xFFFF;
			mix_fader[i].vol_step = (mix_fader[i].vol_target - mix_fader[i].vol_current) / 1000;
		}
		sng_kaihi_fg = 1;
	} else {
		for( i = 0 ; i < 16 ; i++ ){
			mix_fader[i].vol_target = 0xFFFF;
			mix_fader[i].vol_step = (mix_fader[i].vol_target - mix_fader[i].vol_current) / 100;
		}
		for( i = 16 ; i < 32 ; i++ ){
			mix_fader[i].vol_target = 0;
			mix_fader[i].vol_step = (mix_fader[i].vol_target - mix_fader[i].vol_current) / 400;
		}
		sng_kaihi_fg = 0;
	}
	return 0;
}

/*---------------------------------------------------------------------------*/

void SngKaihiReset( void )
{
	int i;

	for( i = 0 ; i < 16 ; i++ ){
		mix_fader[i].vol_current = 0xFFFF;
		mix_fader[i].vol_target = 0xFFFF;
		mix_fader[i].vol_step = 0;
	}
	for( i = 16 ; i < 32 ; i++ ){
		mix_fader[i].vol_current = 0;
		mix_fader[i].vol_target = 0;
		mix_fader[i].vol_step = 0;
	}
	sng_kaihi_fg = 0;
}

/*---------------------------------------------------------------------------*/

void SngKaihiReset2( void )
{
	int i;

	for( i = 0 ; i < 16 ; i++ ){
		mix_fader[i].vol_current = 0;
		mix_fader[i].vol_target = 0;
		mix_fader[i].vol_step = 0;
	}
	for( i = 16 ; i < 32 ; i++ ){
		mix_fader[i].vol_current = 0xFFFF;
		mix_fader[i].vol_target = 0xFFFF;
		mix_fader[i].vol_step = 0;
	}
	sng_kaihi_fg = 0;
}

/*---------------------------------------------------------------------------*/

void SngFadeWkSet( void )
{
	int i;

	if( !sng_fadein_fg ){
		sng_fadein_time = 0;
		for( i = 0 ; i < 32 ; i++ ){
			sng_fade_time[i] = 0;
		}
		for( i = 0 ; i < 32 ; i++ ){
			sng_fade_value[i] = 0;
		}
	} else {
		switch( sng_fadein_fg ){
		case 0x01FFFF03:
		case 0x01FFFF04:
		case 0x01FFFF05:
			SngFadeIn( sng_fadein_fg );
			for( i = 0 ; i < 32 ; i++ ){
				sng_fade_value[i] = 0x10000;
			}
			sng_fadein_fg = 0;
		}
	}
	sng_fout_term[1] = 0;
	sng_fout_term[0] = 0;
	sng_fout_fg = 0;
}

/*---------------------------------------------------------------------------*/

void SngFadeInt( void )
{
	u_int temp;
	u_int temp2, temp3;
	int i, temp5 = 0, temp6 = 0;

	if( sng_status >= 3 ){
		for( i = 0 ; i < 32 ; i++ ){
			temp5 |= sng_fade_time[i];
		}
		if( temp5 ){
			for( i = 0 ; i < 32 ; i++ ){
				if( sng_fade_time[i] ){
					sng_fade_value[i] += sng_fade_time[i];
					if( sng_fade_value[i] >= 0x10000 ){
						if( i < 0x18 ){
							sng_fout_term[0] |= (1 << i);
						} else {
							sng_fout_term[1] |= (1 << (i-0x18));
						}
						sng_fade_value[i] = 0x10000;
						sng_fade_time[i] = 0;
					}
					if( sng_fout_term[0] == 0x00FFFFFF && sng_fout_term[1] == 0xFF ){
						if( sng_play_code == 0xFFFFFFFF ){
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
			if( (str_load_code && str_status) || (str2_load_code[0] && str2_status[0]) || (str2_load_code[1] && str2_status[1]) ){
				if( vox_on_vol < 0x6000 ){
					vox_on_vol += 0xF5;
					if( vox_on_vol > 0x6000 ){
						vox_on_vol = 0x6000;
					}
				}
			} else {
				if( vox_on_vol ){
					vox_on_vol -= 0x7A;
					if( vox_on_vol < 0 ){
						vox_on_vol = 0;
					}
				}
			}
			if( sng_fadein_time ){
				for( i = 0 ; i < 32 ; i++ ){
					if( sng_fade_value[i] <= sng_fadein_time ){
						sng_fade_value[i] = 0;
					} else {
						sng_fade_value[i] -= sng_fadein_time;
					}
					temp6 |= sng_fade_value[i];
				}
				if( !temp6 ){
					sng_fadein_time = 0;
				}
			}
		}
		if( sng_syukan_fg ){
			if( sng_syukan_vol < 0x5000 ){
				sng_syukan_vol += 0xCC;
				if( sng_syukan_vol > 0x5000 ){
					sng_syukan_vol = 0x5000;
				}
			}
		} else {
			if( sng_syukan_vol ){
				sng_syukan_vol -= 0x66;
				if( sng_syukan_vol < 0 ){
					sng_syukan_vol = 0;
				}
			}
		}
		for( i = 0 ; i < 32 ; i++ ){
			temp = 0x10000;
			if( (sng_syukan_vol >= vox_on_vol) && !fg_syukan_off[i] ){
				temp3 = sng_syukan_vol;
			} else {
				temp3 = vox_on_vol;
			}
			if( sng_fade_value[i] > temp3 ){
				temp2 = sng_fade_value[i];
			} else {
				temp2 = temp3;
			}
			if( temp < temp2 ){
				temp = 0;
			} else {
				temp -= temp2;
			}
			if( mix_fader[i].vol_current != mix_fader[i].vol_target ){
				mix_fader[i].vol_current += mix_fader[i].vol_step;
				if( mix_fader[i].vol_step >= 0 ){
					if( (u_int)mix_fader[i].vol_current > mix_fader[i].vol_target ){
						mix_fader[i].vol_current = mix_fader[i].vol_target;
						mix_fader[i].vol_step = 0;
					}
				} else {
					if( mix_fader[i].vol_current < mix_fader[i].vol_target ){
						mix_fader[i].vol_current = mix_fader[i].vol_target;
						mix_fader[i].vol_step = 0;
					}
				}
			}
			temp = (temp * mix_fader[i].vol_current) / 65535;
			sng_master_vol[i] = temp;
		}
	}
}

/*---------------------------------------------------------------------------*/

void SngTempoInt( void )
{
	//
	// EMPTY FUNCTION
	//
}

/*---------------------------------------------------------------------------*/

void init_sng_work( void )
{
	for( mtrack = 0 ; mtrack < 44 ; mtrack++ ){
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

/*---------------------------------------------------------------------------*/

void sng_adrs_set( u_int a0 )
{
	int i;
	u_int temp2, temp3, temp4;

	a0 &= 0x0F;

#ifdef BORMAN_DEMO
	temp3 = sng_data[a0*4+1] << 8;
#else
	temp3 = sng_data[a0*4+3] << 24;
	temp3 += sng_data[a0*4+2] << 16;
	temp3 += sng_data[a0*4+1] << 8;
#endif
	temp3 += sng_data[a0*4];

	song_end[0] = 0;
	song_end[1] &= 0x00FFFF00;

	for( i = 0 ; i < 32 ; i++ ){
		temp2 = i << 2;
		temp4 = sng_data[(temp3 + temp2 + 2)] << 16;
		temp4 += sng_data[(temp3 + temp2 + 1)] << 8;
		temp4 += sng_data[(temp3 + temp2)];
		if( temp4 ){
			sound_w[i].mpointer = sng_data + temp4;
			sng_track_init( &sound_w[i] );
		} else {
			if( i < 24 ){
				song_end[0] |= (1 << i);
			} else {
				song_end[1] |= (1 << (i-24));
			}
		}
	}
	keyons[0] = 0;
	keyons[1] &= 0x00FFFF00;
	fx_sound_code = 0;
}

/*---------------------------------------------------------------------------*/

void se_adrs_set( u_int a0 )
{
	se_playing[a0].code			= se_request[a0].code;
	se_playing[a0].pri			= se_request[a0].pri;
	se_playing[a0].kind			= se_request[a0].kind;
	se_playing[a0].character	= se_request[a0].character;
	se_playing[a0].addr			= se_request[a0].addr;
	se_request[a0].code			= 0;
	se_request[a0].pri			= 0;
	se_request[a0].character	= 0;

	sng_track_init( &sound_w[a0+32] );

	se_vol[a0] = (se_playing[a0].code & 0x3F000) >> 12;
	se_pan[a0] = (se_playing[a0].code >> 18) & 0x3F;
	sound_w[a0+32].mpointer = se_playing[a0].addr;
	song_end[1] &= ~(1 << (a0+8));
	keyons[1] &= ~(1 << (a0+8));
	keyoffs[1] &= ~(1 << (a0+8));

	if( se_playing[a0].kind ){
		if( se_rev_on ){
			rev_on_bit[1] |= (1 << (a0+8));
			rev_bit_data[1] |= (1 << (a0+8));
		} else {
			rev_off_bit[1] |= (1 << (a0+8));
			rev_bit_data[1] &= ~(1 << (a0+8));
		}
	}
}

/*---------------------------------------------------------------------------*/

void sng_track_init( struct SOUND_W *work )
{
	work->rdmd		= 0;
	work->ngc		= 1;
	work->ngo		= 0;
	work->ngs		= 0;
	work->ngg		= 0;
	work->lp1_cnt	= 0;
	work->lp2_cnt	= 0;
	work->lp1_vol	= 0;
	work->lp2_vol	= 0;
	work->lp1_freq	= 0;
	work->lp2_freq	= 0;
	work->pvoc		= 0;
	work->pvod		= 0x7F;
	work->vol		= 0x7F;
	work->pand		= 0x1400;
	work->panf		= 0x14;
	work->panoff	= 0;
	work->panmod	= 0;
	work->swsk		= 0;
	work->swsc		= 0;
	work->vibd		= 0;
	work->vibdm		= 0;
	work->tred		= 0;
	work->snos		= 0;
	work->ptps		= 0;
	work->dec_vol	= 0;
	work->tund		= 0;
	work->tmpd		= 1;
	work->tmp		= 0xFF;
	work->tmpc		= 0;
/* ************************* */
/* Addition for PS2 IOP ver. */
/* ************************* */
	work->unkD4		= 0;
	work->unkD9		= 1;
	work->unkE0		= 0;
	work->unkE1		= 0;
	work->unkE4		= 0xFFFFFFFF;
	work->unkE8		= 0;
	work->unkE9		= 0;
	work->unkEA		= 0;
	work->unkEB		= 0;
	work->unkEC		= 0;
	work->unkED		= 0;
	work->unkEE		= 0;
	work->unkEF		= 0;
	work->unkF0		= 0;
	work->unkF1		= 0;
	work->unkF2		= 0;
	work->unkF3		= 0;
	work->unkF4		= 0;
	work->unkF5		= 0;
	work->unkF6		= 0;
	work->unkF7		= 0;
	work->unkF8		= 0;
}
