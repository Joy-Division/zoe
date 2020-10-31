#include <sys/types.h>
#include <kernel.h>

#include "sd_incl.h"
#include "sd_ext.h"
#include "sd_debug.h"

/*---------------------------------------------------------------------------*/

u_int str1_use_iop = 0;

int se_tracks;
u_int sd_print_fg;
struct unkstr24 ee_addr[2];

/*---------------------------------------------------------------------------*/

int sd_set_cli( u_int a0 )
{
	sd_set( a0 );
	return 0;
}

/*---------------------------------------------------------------------------*/

int SePlay( u_int a0 )
{
	int temp, temp2, temp3;
	u_int temp4;
	int temp5, temp6;

	// TODO: test struct SEPLAYTBL
	u_char pri;
	u_char kind;
	u_char character;
	u_char *addr;
	u_int code;

	temp3 = song_end[1] >> 8;

	for( temp2 = 0 ; temp2 < 12 ; temp2++ ){
		if( temp3 & 1 ){
			se_playing[temp2].code = 0;
			se_playing[temp2].pri = 0;
			se_playing[temp2].character = 0;
		}
		temp3 >>= 1;
	}

	temp5 = a0 & 0x07FF;
	code = a0;

	if( temp5 < 0x0100 ){
		se_tracks = se_tbl[temp5].tracks;
		character = se_tbl[temp5].character;
	} else {
		temp6 = se_exp_table[temp5-0x0100];
		if( temp6 == 0xFF ){
			PRINTF(( "ERR:se_exp_table offset(%x)\n", temp5 & 0x07FF ));
			return -1;
		}
		se_tracks = se_header[temp6].tracks;
		character = se_header[temp6].character;
	}

	for( temp4 = 0 ; temp4 < se_tracks ; temp4++ ){
		if( temp5 < 0x0100 ){
			pri = se_tbl[temp5].pri;
			kind = se_tbl[temp5].kind;
			addr = se_tbl[temp5].addr[temp4];
		} else {
			pri = se_header[temp6].pri;
			kind = se_header[temp6].kind;
			// note to self, pointer + pointer is bad, pointer + int is ok
			addr = se_data + (u_int)(se_header[temp6].addr[temp4]);
		}

		temp = 0x0100;
		temp3 = 0;

		for( temp2 = 0 ; temp2 < 12 ; temp2++ ){
			if( ((se_playing[temp2].code & 0x07FF) == (code & 0x07FF)) && !se_request[temp2].code ){
				temp = 0;
				temp3 = temp2;
				break;
			} else if( ((se_request[temp2].code & 0x07FF) == (code & 0x07FF)) && !temp4 ){
				se_tracks = 0;
				return 0;
			}
			if( character ){
				if( se_playing[temp2].character == character ){
					temp = 0;
					temp3 = temp2;
					break;
				} else if( se_request[temp2].character == character ){
					temp = 0;
					temp3 = temp2;
					break;
				}
			}
		}
		if( temp3 != temp2 ){
			for( temp2 = 0 ; temp2 < 12 ; temp2++ ){
				if( !se_playing[temp2].code && !se_request[temp2].code ){
					temp = 0;
					temp3 = temp2;
					break;
				}
			}
			if( temp3 != temp2 ){
				for( temp2 = 0 ; temp2 < 12 ; temp2++ ){
					if( !se_request[temp2].code ){
						if( se_playing[temp2].pri <= temp ){
							temp = se_playing[temp2].pri;
							temp3 = temp2;
						}
					} else {
						if( se_request[temp2].pri <= temp ){
							temp = se_request[temp2].pri;
							temp3 = temp2;
						}
					}
				}
				if( (pri % 100) >= (temp % 100) ){
					PRINTF(( "***SE Priority:%x > (%x or %x)***\n",
						code & 0x7FF, (u_int)se_playing[temp3].code & 0x7FF,
						(u_int)se_request[temp3].code & 0x7FF ));
				}
			}
		}
		if( pri >= temp ){
			se_request[temp3].pri = pri;
			se_request[temp3].kind = kind;
			se_request[temp3].character = character;
			character = 0;
			se_request[temp3].addr = addr;
			se_request[temp3].code = code;

			if( pri == 0xFF ){
				stop_jouchuu_se = 0;
			}
		} else { /* test if this also matches retail instead of the if above! */
			PRINTF(( "SECan'tPlay:LowPriority(code=%x:pri=%x)\n", code & 0x7FF, pri ));
		}
	}
	se_tracks = 0;
	return 0;
}

/*---------------------------------------------------------------------------*/

void set_sng_code_buf( u_int a0 )
{
	if( !sd_sng_code_buf[sd_code_set] ){
		sd_sng_code_buf[sd_code_set] = a0;
		sd_code_set = (sd_code_set + 1) & 0x0F;
	} else {
		PRINTF(( "***TooMuchBGMSoundCode(%x)***\n", a0 ));
	}
}

/*---------------------------------------------------------------------------*/

void sd_set( int sound_code )
{
	union {
		u_int *up;
		u_int u;
	} temp;

	if( sound_code == 0xFF000000 ){
		sd_print_fg = 1;
		goto end;
	}

	if( sound_code == 0xFF000001 ){
		sd_print_fg = 0;
		goto end;
	}

	if( sound_code == 0xFF000002 ){
		PRINTF(( "\n\n*** FADER VOLUME STATUS ***\n" ));

		PRINTF(( "CH00=%2x:CH01=%2x:CH02=%2x:CH03=%2x",
			mix_fader[0x00].vol_current, mix_fader[0x01].vol_current,
			mix_fader[0x02].vol_current, mix_fader[0x03].vol_current ));

		PRINTF(( "CH04=%2x:CH05=%2x:CH06=%2x:CH07=%2x\n",
			mix_fader[0x04].vol_current, mix_fader[0x05].vol_current,
			mix_fader[0x06].vol_current, mix_fader[0x07].vol_current ));

		PRINTF(( "CH08=%2x:CH09=%2x:CH0A=%2x:CH0B=%2x",
			mix_fader[0x08].vol_current, mix_fader[0x09].vol_current,
			mix_fader[0x0A].vol_current, mix_fader[0x0B].vol_current ));

		PRINTF(( "CH0C=%2x:CH0D=%2x:CH0E=%2x:CH0F=%2x\n",
			mix_fader[0x0C].vol_current, mix_fader[0x0D].vol_current,
			mix_fader[0x0E].vol_current, mix_fader[0x0F].vol_current ));

		PRINTF(( "CH10=%2x:CH11=%2x:CH12=%2x:CH13=%2x",
			mix_fader[0x10].vol_current, mix_fader[0x11].vol_current,
			mix_fader[0x12].vol_current, mix_fader[0x13].vol_current ));

		PRINTF(( "CH14=%2x:CH15=%2x:CH16=%2x:CH17=%2x\n",
			mix_fader[0x14].vol_current, mix_fader[0x15].vol_current,
			mix_fader[0x16].vol_current, mix_fader[0x17].vol_current ));

		PRINTF(( "CH18=%2x:CH19=%2x:CH1A=%2x:CH1B=%2x",
			mix_fader[0x18].vol_current, mix_fader[0x19].vol_current,
			mix_fader[0x1A].vol_current, mix_fader[0x1B].vol_current ));

		PRINTF(( "CH1C=%2x:CH1D=%2x:CH1E=%2x:CH1F=%2x\n",
			mix_fader[0x1C].vol_current, mix_fader[0x1D].vol_current,
			mix_fader[0x1E].vol_current, mix_fader[0x1F].vol_current ));

		PRINTF(( "\n*** FADER PAN STATUS ***\n" ));

		PRINTF(( "CH00=%2x:CH01=%2x:CH02=%2x:CH03=%2x",
			mix_fader[0x00].pan_value, mix_fader[0x01].pan_value,
			mix_fader[0x02].pan_value, mix_fader[0x03].pan_value ));

		PRINTF(( "CH04=%2x:CH05=%2x:CH06=%2x:CH07=%2x\n",
			mix_fader[0x04].pan_value, mix_fader[0x05].pan_value,
			mix_fader[0x06].pan_value, mix_fader[0x07].pan_value ));

		PRINTF(( "CH08=%2x:CH09=%2x:CH0A=%2x:CH0B=%2x",
			mix_fader[0x08].pan_value, mix_fader[0x09].pan_value,
			mix_fader[0x0A].pan_value, mix_fader[0x0B].pan_value ));

		PRINTF(( "CH0C=%2x:CH0D=%2x:CH0E=%2x:CH0F=%2x\n",
			mix_fader[0x0C].pan_value, mix_fader[0x0D].pan_value,
			mix_fader[0x0E].pan_value, mix_fader[0x0F].pan_value ));

		PRINTF(( "CH10=%2x:CH11=%2x:CH12=%2x:CH13=%2x",
			mix_fader[0x10].pan_value, mix_fader[0x11].pan_value,
			mix_fader[0x12].pan_value, mix_fader[0x13].pan_value ));

		PRINTF(( "CH14=%2x:CH15=%2x:CH16=%2x:CH17=%2x\n",
			mix_fader[0x14].pan_value, mix_fader[0x15].pan_value,
			mix_fader[0x16].pan_value, mix_fader[0x17].pan_value ));

		PRINTF(( "CH18=%2x:CH19=%2x:CH1A=%2x:CH1B=%2x",
			mix_fader[0x18].pan_value, mix_fader[0x19].pan_value,
			mix_fader[0x1A].pan_value, mix_fader[0x1B].pan_value ));

		PRINTF(( "CH1C=%2x:CH1D=%2x:CH1E=%2x:CH1F=%2x\n",
			mix_fader[0x1C].pan_value, mix_fader[0x1D].pan_value,
			mix_fader[0x1E].pan_value, mix_fader[0x1F].pan_value ));
	}

	if( sd_print_fg ){
		PRINTF(( "SdCode=%x\n", sound_code ));
	}

	if( !(sound_code & 0xFF000000) ) {
		if( !(sound_code & 0x07FF) ) {
			goto end;
		}
		SePlay( sound_code );
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0x1000000 ){
		set_sng_code_buf( sound_code );
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0x2000000 ){
		se_load_code = sound_code;
		WakeupThread( id_SdMain );
		goto end;
	}

	if( (sound_code & 0xE0000000) == 0x80000000 ){
		temp.up = sif_get_mem( path_name, sound_code & 0x1FFFFFFF, 0x80 );
		while( 1 ){
			if( *temp.up & 0x80000000 ){
				break;
			}
		}
		sif_rv_release_queue( temp );
		PRINTF(( "Path name = %s\n", path_name ));
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0xF0000000 ){
		if( str1_use_iop ){
			if( str_load_code != sound_code ){
				if( lnr8_status ){
					lnr8_stop_fg = 1;
				}
				str_stop_fg = 0;
				str_first_load = str_load_code = sound_code;
				str_counter_low = 0;
				str_counter = 0;
				str_status = 1;
				WakeupThread( id_SdMain );
			} else {
				PRINTF(( "SdSet:Same Stream is Already Played.(code=%x)\n", str_load_code ));
			}
		} else {
			if( lnr8_status ){
				lnr8_stop_fg = 1;
			}
			str2_stop_fg[0] = 0;
			ee_addr[0].unk14 = (sound_code & 0x00FFFFFF) << 4;
		}
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0xF1000000 ){
		if( !str1_use_iop ){
			ee_addr[0].unk04 = sound_code & 0x00FFFFFF;
			ee_addr[0].unk0C++;
			str2_iop_load_set[0] = 1;
			WakeupThread( id_SdEELoad );
		}
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0xF2000000 ){
		ee_addr[1].unk14 = (sound_code & 0x00FFFFFF) << 4;
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0xF3000000 ){
		ee_addr[1].unk04 = sound_code & 0x00FFFFFF;
		ee_addr[1].unk0C++;
		str2_iop_load_set[1] = 1;
		WakeupThread( id_SdEELoad );
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0xF4000000 ){
		if( !(sound_code & 0x00FFFFFF) ){
			if( str_status ){
				str_stop_fg = 1;
			}
			if( str2_status[0] ){
				str2_stop_fg[0] = 1;
			}
			if( str2_status[1] ){
				str2_stop_fg[1] = 1;
			}
			lnr8_stop_fg = 0;
			lnr8_first_load = lnr8_load_code = sound_code;
			ee_addr[1].unk10 = 0;
			ee_addr[1].unk0C = 0;
			lnr8_status = 1;
			lnr8_counter = 0;
		} else {
			if( (sound_code & 0xFF0000) == 0x10000 ){
				str2_mono_fg[1] = 1;
			} else {
				str2_mono_fg[1] = 0;
			}
			str2_pitch[1] = (int)((sound_code & 0xFFFF) * 4096) / 48000;
			PRINTF(( "Str2 mono=%x, pitch=0x%x\n", str2_mono_fg[1], (u_short)str2_pitch[1] ));
			if( lnr8_status ){
				lnr8_stop_fg = 1;
			}
			str2_stop_fg[1] = 0;
			str2_first_load[1] = str2_load_code[1] = sound_code;
			str2_counter[1] = 0;
			str2_play_counter[1] = 0;
		#ifdef BORMAN_DEMO
			vox_fader[1].vol_target = 0x3F;
			vox_fader[1].pan_target = 0x20;
		#endif
			ee_addr[1].unk10 = 0;
			ee_addr[1].unk0C = 0;
			str2_status[1] = 1;
		}
		WakeupThread( id_SdEELoad );
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0xF5000000 ){
		if( !str1_use_iop ){
			if( (sound_code & 0xFF0000) == 0x10000 ){
				str2_mono_fg[0] = 1;
			} else {
				str2_mono_fg[0] = 0;
			}
			str2_pitch[0] = (int)((sound_code & 0xFFFF) * 4096) / 48000;
			PRINTF(( "Str1 mono=%x, pitch=0x%x\n", str2_mono_fg[0], (u_short)str2_pitch[0] ));
			if( lnr8_status ){
				lnr8_stop_fg = 1;
			}
			str2_first_load[0] = str2_load_code[0] = sound_code;
			str2_counter[0] = 0;
			str2_play_counter[0] = 0;
		#ifdef BORMAN_DEMO
			vox_fader[0].vol_target = 0x3F;
			vox_fader[0].pan_target = 0x20;
		#endif
			ee_addr[0].unk10 = 0;
			ee_addr[0].unk0C = 0;
			str2_status[0] = 1;
			WakeupThread( id_SdEELoad );
		}
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0xFA000000 ){
		switch( sound_code & 0x0F00 ){
		case 0   : auto_env_pos  = (sound_code & 0xFFFF); break;
		case 256 : auto_env_pos2 = (sound_code & 0xFFFF); break;
		default  : break;
		}
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0xFB000000 ){
		if( sound_code <= 0xFB1F3F3F ){
			temp.u = (int)(sound_code & 0x1F0000) >> 16;
			mix_fader[temp.u].pan_value = (int)(sound_code & 0x3F00) >> 8;
			mix_fader[temp.u].vol_target
				= ((sound_code & 0x3F) << 10)
				+ ((sound_code & 0x3F) << 4)
				+ ((int)(sound_code & 0x3F) >> 2);
			mix_fader[temp.u].vol_current = mix_fader[temp.u].vol_target;
			mix_fader[temp.u].vol_step = 0;
		#ifdef BORMAN_DEMO
			if( sd_print_fg ){
				PRINTF(( "Fader:Pan=%x:Vol=%x\n",
					mix_fader[temp.u].pan_value,
					mix_fader[temp.u].vol_current ));
			}
		#endif
		} else {
			if( (sound_code & 0xFF0000) == 0xFE0000 || (sound_code & 0xFF0000) == 0xFF0000 ){
				temp.u = (int)(sound_code & 0x10000) >> 16;
				vox_fader[temp.u].vol_target = sound_code & 0x3F;
				vox_fader[temp.u].pan_target = (int)(sound_code & 0x3F00) >> 8;
				if( sd_print_fg ){
					PRINTF(( "VoxFader:Code=%x:Ch=%x:Pan=%x:Vol=%x\n",
						sound_code, temp.u,
						vox_fader[temp.u].pan_target,
						vox_fader[temp.u].vol_target ));
				}
			}
		}
		goto end;
	}

	if( sound_code > 0xFBFFFFFF && sound_code <= 0xFC1F3FFF ){
		temp.u = (int)(sound_code & 0x1F0000) >> 16;
		mix_fader[temp.u].pan_value = (int)(sound_code & 0x3F00) >> 8;
	#ifdef BORMAN_DEMO
		if( sd_print_fg ){
			PRINTF(( "Fader:Pan=%x\n", mix_fader[temp.u].pan_value ));
		}
	#endif
		goto end;
	}

	if( sound_code > 0xFCFFFFFF && sound_code <= 0xFD1F3FFF ){
		temp.u = (int)(sound_code & 0x1F0000) >> 16;
		mix_fader[temp.u].vol_target
			= ((sound_code & 0x3F00) << 2)
			+ ((int)(sound_code & 0x3F00) >> 4)
			+ ((int)(sound_code & 0x3F00) >> 10);
		if( mix_fader[temp.u].vol_target == mix_fader[temp.u].vol_current ){
			mix_fader[temp.u].vol_step = 0;
		} else if( sound_code & 0xFF ){
			mix_fader[temp.u].vol_step
				= (mix_fader[temp.u].vol_target - mix_fader[temp.u].vol_current)
				/ ((int)(sound_code & 0xFF)*10);
			if( !mix_fader[temp.u].vol_step ){
				mix_fader[temp.u].vol_step = 1;
			}
		} else {
			mix_fader[temp.u].vol_current = mix_fader[temp.u].vol_target;
			mix_fader[temp.u].vol_step = 0;
		}
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0xFE000000 ){
		pak_cd_read_fg = 0;
		if( sound_code <= 0xFE7FFFFF ){
		#ifdef BORMAN_DEMO
			if(wave_save_code != sound_code && se_save_code2 != sound_code) {
		#endif
			wave_load_code = sound_code;
			wave_load_status = 1;
		#ifdef BORMAN_DEMO
			}
		#endif
		} else {
			pak_load_code = sound_code;
			pak_load_status = 1;
		}
		WakeupThread( id_SdMain );
		goto end;
	}

	if( (sound_code & 0xFF000000) == 0xC0000000 ){
		pak_load_code = sound_code & 0x0FFFFFFF;
		pak_load_status = 1;
		pak_cd_read_fg = 1;
		WakeupThread( id_SdMain );
		goto end;
	}

	switch( sound_code ){
		case 0xFF000005: sound_mono_fg = 1; break;
		case 0xFF000006: sound_mono_fg = 0; break;
		case 0xFF000007: se_rev_on = 1; vox_rev_on = 0; break;
		case 0xFF000008: se_rev_on = 0; vox_rev_on = 0; break;
		case 0xFF000009: se_rev_on = 1; vox_rev_on = 1; break;

		case 0xFF00000A:
			if( str1_use_iop ){
				if( str_status ){
					str_stop_fg = 1;
				}
			} else {
				if( str2_status[0] ){
					str2_stop_fg[0] = 1;
				}
				str2_iop_load_set[0] = 0;
			}
			break;

		case 0xFF00000B:
			if( str1_use_iop ){
				str_wait_fg = 1;
			} else {
				str2_wait_fg[0] = 1;
			}
			PRINTF(( "*** STR WAIT ***\n" ));
			break;

		case 0xFF00000C:
			if( str1_use_iop ){
				str_wait_fg = 0;
			} else {
				str2_wait_fg[0] = 0;
			}
			PRINTF(( "*** STR WAIT OFF (START) ***\n" ));
			break;

		case 0xFF00000D:
			if( str1_use_iop ){
				if( str_status ){
					str_stop_fg = 2;
				}
			} else if( str2_status[0] ){
				str2_stop_fg[0] = 2;
			}
			break;

		case 0xFF00000E:
			if( str2_status[1] ){
				str2_stop_fg[1] = 1;
			}
			if( lnr8_status ){
				lnr8_stop_fg = 1;
			}
			str2_iop_load_set[1] = 0;
			break;

		case 0xFF00000F:
			str2_wait_fg[1] = 1;
			PRINTF(( "*** STR2 WAIT ***\n" ));
			break;

		case 0xFF000010:
			str2_wait_fg[1] = 0;
			PRINTF(( "*** STR WAIT OFF (START) ***\n" ));
			break;

		case 0xFF000011:
			if( str2_status[1] ){
				str2_stop_fg[1] = 2;
			}
			if( lnr8_status ){
				lnr8_stop_fg = 1;
			}
			break;

		case 0xFF000012:
			str1_use_iop = 1;
			PRINTF(( "*** STR1:IOP DIRECT READ***\n" ));
			break;

		case 0xFF000013:
			str1_use_iop = 0;
			PRINTF(( "*** STR1:EE READ***\n" ));
			break;

		case 0xFF000014:
			fader_off_fg = 1;
			PRINTF(( "*** SET Volume Fader =0 for SNG ***\n" ));
			break;

		case 0xFF0000FE: stop_jouchuu_se = 1; break;
		case 0xFF0000FF: set_sng_code_buf( sound_code ); break;
		case 0xFF000100: fx_sound_code = 1; break;
		case 0xFF000101: set_sng_code_buf( sound_code ); break;
		case 0xFF000102: set_sng_code_buf( sound_code ); break;
		case 0xFF000103: set_sng_code_buf( sound_code ); break;
		case 0xFF000104: auto_phase_fg = 4; break;
		case 0xFF000105: set_sng_code_buf( sound_code ); break;
		case 0xFF000106: set_sng_code_buf( sound_code ); break;
		case 0xFF000107: set_sng_code_buf( sound_code ); break;
		case 0xFF000108: set_sng_code_buf( sound_code ); break;

		case 0xFFFFFFEC: break;
		case 0xFFFFFFED: break;
		case 0xFFFFFFFD: break;

		default: break;
	}

end:
	return;
}
