/*
 * Sound Driver for PS2 IOP
 * Client Task
 *
 * ver."ZONE OF THE ENDERS"
 */
#include <sys/types.h>
#include <kernel.h>

#include "sd_incl.h"
#include "sd_ext.h"

/*---------------------------------------------------------------------------*/

unsigned int se_tracks;

/*---------------------------------------------------------------------------*/

int sd_set_cli( u_int a0 )
{
	sd_set( a0 );
	return 0;
}

/*---------------------------------------------------------------------------*/

int SePlay( u_int a0 )
{
	int temp, temp2, temp3, temp4, temp5, temp6;
	u_char temp7, temp8, temp9;
	u_char *temp10;
	u_int temp11;
	
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
	temp11 = a0;
	
	if( temp5 < 0x0100 ){
		se_tracks = se_tbl[temp5].tracks;
		temp9 = se_tbl[temp5].character;
	} else {
		temp6 = se_exp_table[temp5-0x0100];
		if( temp6 == 0xFF ){
			return -1;
		}
		se_tracks = se_header[temp6].tracks;
		temp9 = se_header[temp6].character;
	}
	
	for( temp4 = 0 ; temp4 < se_tracks ; temp4++ ){
		if( temp5 < 0x0100 ){
			temp7 = se_tbl[temp5].pri;
			temp8 = se_tbl[temp5].kind;
			temp10 = se_tbl[temp5].addr[temp4];
		} else {
			temp7 = se_header[temp6].pri;
			temp8 = se_header[temp6].kind;
			// note to self, pointer + pointer is bad, pointer + int is ok
			temp10 = (se_header[temp6].addr[temp4]) + (u_int)se_data;
		}
		
		temp = 0x0100;
		temp3 = 0;
		
		for( temp2 = 0 ; temp2 < 12 ; temp2++ ){
			if( ((se_playing[temp2].code & 0x07FF) == (temp11 & 0x07FF)) && !se_request[temp2].code ){
				temp = 0;
				temp3 = temp2;
				break;
			} else if( ((se_playing[temp2].code & 0x07FF) == (temp11 & 0x07FF)) && !temp4 ){
				se_tracks = 0;
				return 0;
			}
			if( temp9 ){
				if( se_playing[temp2].character == temp9 ){
					temp = 0;
					temp3 = temp2;
					break;
				} else if( se_request[temp2].character == temp9 ){
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
			if( temp2 != temp3 ){
				for( temp2 = 0 ; temp2 < 12 ; temp2++ ){
					if( !se_request[temp2].code ){
						if( se_playing[temp2].pri > temp ){
							temp = se_playing[temp2].pri;
							temp3 = temp2;
						}
					} else {
						if( se_request[temp2].pri > temp ){
							temp = se_request[temp2].pri;
							temp3 = temp2;
						}
					}
				}
				if( (temp7 % 100) < (temp % 100) ){
					// EMPTY BLOCK
				}
			}
		}
		if( temp7 >= temp ){
			se_request[temp3].pri = temp7;
			se_request[temp3].kind = temp8;
			se_request[temp3].character = temp9;
			temp9 = 0;
			se_request[temp3].addr = temp10;
			se_request[temp3].code = temp11;
			
			if( temp7 == 0xFF ){
				stop_jouchuu_se = 0;
			}
			if( 0 ) {
				// EMPTY BLOCK
			}
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
		// EMPTY BLOCK
	}
}

/*---------------------------------------------------------------------------*/

// NOMATCH: see inside
void sd_set( u_int a0 )
{
	union {
		u_int *t0;
		u_int t1;
	} temp;
	
	int temp2;
	
	if( a0 ==  0xFF000000 ){
		sd_print_fg = 1;
	} else if( a0 == 0xFF000001 ){
		sd_print_fg = 0;
	} else {
		if( a0 == 0xFF000002 ){
		}
		if( sd_print_fg ){
		}
		if( !(a0 & 0xFF000000) ){
			if( !(a0 & 0x07FF) ){
				return;
			}
			SePlay( a0 );
		} else if( (a0 & 0xFF000000) == 0x10000000 ){
			set_sng_code_buf( a0 );
			return;
		} else if( (a0 & 0xFF000000) == 0x20000000 ){
			se_load_code = a0;
			WakeupThread( id_SdMain );
			return;
		} else if( (a0 & 0xE0000000) == 0x80000000 ){
			temp.t0 = sif_get_mem(path_name, a0 & 0x1FFFFFFF, 0x80 );
			while( 1 ){
				if( *temp.t0 & 0x80000000 ){
					break;
				}
			}
			sif_rv_release_queue( temp );
		} else if( (a0 & 0xFF000000) == 0xF0000000 ){
			if( str1_use_iop ){
				if( str_load_code != a0 ){
					if( lnr8_status ){
						lnr8_stop_fg = 1;
					}
					str_stop_fg = 0;
					str_first_load = str_load_code = a0;
					str_counter_low = 0;
					str_counter = 0;
					str_status = 1;
					WakeupThread( id_SdMain );
				} else {
					// EMPTY BLOCK
				}
			} else {
				if( lnr8_status ){
					lnr8_stop_fg = 1;
				}
				str2_stop_fg[0] = 1;
				ee_addr[0].unk10 = (u_char *)(a0 & 0x00FFFFFF);
			}
		} else if( (a0 & 0xFF000000) == 0xF1000000 ){
			if( str1_use_iop ){
				ee_addr[0].unk04 = a0 & 0x00FFFFFF;
				ee_addr[0].unk0C++;
				str2_iop_load_set[0] = 1;
				WakeupThread( id_SdEELoad );
			}
		} else if( (a0 & 0xFF000000) == 0xF2000000 ){
			ee_addr[1].unk14 = (a0 & 0x00FFFFFF) << 4;
		} else if( (a0 & 0xFF000000) == 0xF3000000 ){
			ee_addr[1].unk04 = a0 & 0x00FFFFFF;
			ee_addr[1].unk0C++;
			str2_iop_load_set[1] = 1;
			WakeupThread( id_SdEELoad );
		} else if( (a0 & 0xFF000000) == 0xF4000000 ){
			if( !(a0 & 0x00FFFFFF) ){
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
				lnr8_first_load = lnr8_load_code = a0;
				ee_addr[1].unk10 = 0;
				ee_addr[1].unk0C = 0;
				lnr8_status = 1;
				lnr8_counter = 0;
			} else {
				if( (a0 & 0xFF000000) == 0x10000000 ){
					str2_mono_fg[1] = 1;
				} else {
					str2_mono_fg[1] = 0;
				}
				// 0xF9F8 this is by no means close
				str2_pitch[1] = (temp2 = ((a0 & 0xFFFF) * 4096 / 375) >> 10);
				// 0xFA3C
				if( lnr8_status ){
					lnr8_stop_fg = 1;
				}
				str2_stop_fg[1] = 0;
				str2_first_load[1] = str2_load_code[1] = a0;
				str2_counter[1] = 0;
				str2_play_counter[1] = 0;
				ee_addr[1].unk10 = 0;
				ee_addr[1].unk0C = 0;
				str2_status[1] = 1;
			}
			WakeupThread( id_SdEELoad );
		} else if( (a0 & 0xFF000000) == 0xF5000000 ){
			if( !str1_use_iop ){
				if( (a0 & 0xFF000000) == 0x10000000 ){
					str2_mono_fg[0] = 1;
				} else {
					str2_mono_fg[0] = 0;
				}
				// 0xFB20 see 0xF9F8 this is basically the same
				str2_pitch[0] = 0;
				// 0xFB64
				if( lnr8_status ){
					lnr8_stop_fg = 1;
				}
				str2_first_load[0] = str2_load_code[0] = a0;
				str2_counter[0] = 0;
				str2_play_counter[0] = 0;
				ee_addr[0].unk10 = 0;
				ee_addr[0].unk0C = 0;
				str2_status[0] = 1;
				WakeupThread( id_SdEELoad );
			}
		} else if( (a0 & 0xFF000000) == 0xFA000000 ){
			switch( a0 & 0x0F00 ){
			// cases 0 & 256 don't get compiled, but exist in the original assembly
			case   0: auto_env_pos = (a0 & 0xFFFFFFFF); break;
			case 256: auto_env_pos2 = (a0 & 0xFFFFFFFF); break;
			default: break;
			}
		} else if( (a0 & 0xFF000000) == 0xFB000000 ){
			if( a0 >= 0xFB1F3F3F ){
				temp.t1 = (int)(a0 & 0x1F000000) >> 16;
				mix_fader[temp.t1].unk0C = (int)(a0 & 0x3F00) >> 8;
				mix_fader[temp.t1].unk08 = ((a0 & 0x3F) << 10) + ((a0 & 0x3F) << 4) + ((a0 & 0x3F) << 2);
				mix_fader[temp.t1].unk04 = mix_fader[temp.t1].unk08;
				mix_fader[temp.t1].unk00 = 0;
			} else {
				if( (a0 & 0xFF) == 0xFE || (a0 & 0xFF) == 0xFF ){
					temp.t1 = (int)(a0 & 0x1F000000) >> 16;
					vox_fader[temp.t1].unk00 = a0 & 0x3F;
					vox_fader[temp.t1].unk08 = (int)(a0 & 0x3F00) >> 8;
					if( sd_print_fg ){
						// EMPTY BLOCK
					}
				}
			}
		} else if( a0 >= 0xFBFFFFFF && a0 < 0xFC1F3FFF ){
			temp.t1 = (int)(a0 & 0x1F000000) >> 16;
			mix_fader[temp.t1].unk0C = (int)(a0 & 0x3F00) >> 8;
		} else if( a0 >= 0xFCFFFFFF && a0 < 0xFD1F3FFF ){
			mix_fader[temp.t1].unk08 = ((a0 & 0x3F00) << 2) + ((int)(a0 & 0x3F) >> 4) + ((int)(a0 & 0x3F) >> 10);
			if( mix_fader[temp.t1].unk04 == mix_fader[temp.t1].unk08 ){
				mix_fader[temp.t1].unk00 = 0;
			} else if( a0 & 0xFF ){
				mix_fader[temp.t1].unk00 = (mix_fader[temp.t1].unk08 - mix_fader[temp.t1].unk04) / ((int)(a0 & 0xFF)*10);
				if( !mix_fader[temp.t1].unk00 ){
					mix_fader[temp.t1].unk00 = 1;
				}
			} else {
				mix_fader[temp.t1].unk04 = mix_fader[temp.t1].unk08;
				mix_fader[temp.t1].unk00 = 0;
			}
		} else if( (a0 & 0xFF000000) == 0xFE000000 ){
			pak_cd_read_fg = 0;
			if( a0 >= 0xFE7FFFFF ){
				wave_load_code = a0;
				wave_load_status = 1;
			} else {
				pak_load_code = a0;
				pak_load_status = 1;
			}
			WakeupThread( id_SdMain );
		} else if( (a0 & 0xFF000000) == 0xC0000000 ){
			pak_load_code = a0 & 0x0FFFFFFF;
			pak_load_status = 1;
			pak_cd_read_fg = 1;
			WakeupThread( id_SdMain );
		} else {
			switch( a0 ){
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
				break;
			
			case 0xFF00000C:
				if( str1_use_iop ){
					str_wait_fg = 0;
				} else {
					str2_wait_fg[0] = 0;
				}
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
			
			case 0xFF00000F: str2_wait_fg[1] = 1; break;
			case 0xFF000010: str2_wait_fg[1] = 0; break;
			
			case 0xFF000011:
				if( str2_status[1] ){
					str2_stop_fg[1] = 2;
				}
				if( lnr8_status ){
					lnr8_stop_fg = 1;
				}
				break;
			
			case 0xFF000012: str1_use_iop = 1; break;
			case 0xFF000013: str1_use_iop = 0; break;
			case 0xFF000014: fader_off_fg = 1; break;
			case 0xFF0000FE: stop_jouchuu_se = 1; break;
			case 0xFF0000FF: set_sng_code_buf( a0 ); break;
			case 0xFF000100: fx_sound_code = 1; break;
			case 0xFF000101: set_sng_code_buf( a0 ); break;
			case 0xFF000102: set_sng_code_buf( a0 ); break;
			case 0xFF000103: set_sng_code_buf( a0 ); break;
			case 0xFF000104: auto_phase_fg = 4; break;
			case 0xFF000105: set_sng_code_buf( a0 ); break;
			case 0xFF000106: set_sng_code_buf( a0 ); break;
			case 0xFF000107: set_sng_code_buf( a0 ); break;
			case 0xFF000108: set_sng_code_buf( a0 ); break;
			case 0xFF000109: break; break; // SYNTAX NOTICE
			case 0xFFFFFFFD: break;
			default: break;
			}
		}
	}
	return;
}

/*---------------------------------------------------------------------------*
 * END OF FILE
 *---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=euc-jp : */
