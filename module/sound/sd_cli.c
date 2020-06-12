#include <sys/types.h>
#include <kernel.h>

#include "sd_incl.h"
#include "sd_ext.h"

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
			#ifdef BORMAN_DEMO
			printf("ERR:se_exp_table offset(%x)\n", temp5 & 0x7FF);
			#endif
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
			temp10 = se_data + (u_int)(se_header[temp6].addr[temp4]);
		}

		temp = 0x0100;
		temp3 = 0;

		for( temp2 = 0 ; temp2 < 12 ; temp2++ ){
			if( ((se_playing[temp2].code & 0x07FF) == (temp11 & 0x07FF)) && !se_request[temp2].code ){
				temp = 0;
				temp3 = temp2;
				break;
			} else if( ((se_request[temp2].code & 0x07FF) == (temp11 & 0x07FF)) && !temp4 ){
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
				if( (temp7 % 100) >= (temp % 100) ){
					#ifdef BORMAN_DEMO
					printf("***SE Priority:%x > (%x or %x)***\n", temp11 & 0x7FF, (u_int)se_playing[temp3].code & 0x7FF, (u_int)se_request[temp3].code & 0x7FF);
					#endif
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
		}
		/* test if this also matches retail instead of the if above! */
		else {
		#ifdef BORMAN_DEMO
			printf("SECan'tPlay:LowPriority(code=%x:pri=%x)\n", temp11 & 0x7FF, temp7);
		#endif
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
		#ifdef BORMAN_DEMO
		printf("***TooMuchBGMSoundCode(%x)***\n", a0);
		#endif
	}
}

/*---------------------------------------------------------------------------*/

void sd_set( int a0 )
{
	union {
		u_int *up;
		u_int u;
	} temp;

	if( a0 == 0xFF000000 ){
		sd_print_fg = 1;
		goto end;
	}

	if( a0 == 0xFF000001 ){
		sd_print_fg = 0;
		goto end;
	}

	if( a0 == 0xFF000002 ){
		#ifdef BORMAN_DEMO
		printf("\n\n*** FADER VOLUME STATUS ***\n");
		printf("CH00=%2x:CH01=%2x:CH02=%2x:CH03=%2x",   mix_fader[0x00].unk04, mix_fader[0x01].unk04, mix_fader[0x02].unk04, mix_fader[0x03].unk04);
		printf("CH04=%2x:CH05=%2x:CH06=%2x:CH07=%2x\n", mix_fader[0x04].unk04, mix_fader[0x05].unk04, mix_fader[0x06].unk04, mix_fader[0x07].unk04);
		printf("CH08=%2x:CH09=%2x:CH0A=%2x:CH0B=%2x",   mix_fader[0x08].unk04, mix_fader[0x09].unk04, mix_fader[0x0A].unk04, mix_fader[0x0B].unk04);
		printf("CH0C=%2x:CH0D=%2x:CH0E=%2x:CH0F=%2x\n", mix_fader[0x0C].unk04, mix_fader[0x0D].unk04, mix_fader[0x0E].unk04, mix_fader[0x0F].unk04);
		printf("CH10=%2x:CH11=%2x:CH12=%2x:CH13=%2x",   mix_fader[0x10].unk04, mix_fader[0x11].unk04, mix_fader[0x12].unk04, mix_fader[0x13].unk04);
		printf("CH14=%2x:CH15=%2x:CH16=%2x:CH17=%2x\n", mix_fader[0x14].unk04, mix_fader[0x15].unk04, mix_fader[0x16].unk04, mix_fader[0x17].unk04);
		printf("CH18=%2x:CH19=%2x:CH1A=%2x:CH1B=%2x",   mix_fader[0x18].unk04, mix_fader[0x19].unk04, mix_fader[0x1A].unk04, mix_fader[0x1B].unk04);
		printf("CH1C=%2x:CH1D=%2x:CH1E=%2x:CH1F=%2x\n", mix_fader[0x1C].unk04, mix_fader[0x1D].unk04, mix_fader[0x1E].unk04, mix_fader[0x1F].unk04);
		printf("\n*** FADER PAN STATUS ***\n");
		printf("CH00=%2x:CH01=%2x:CH02=%2x:CH03=%2x",   mix_fader[0x00].unk0C, mix_fader[0x01].unk0C, mix_fader[0x02].unk0C, mix_fader[0x03].unk0C);
		printf("CH04=%2x:CH05=%2x:CH06=%2x:CH07=%2x\n", mix_fader[0x04].unk0C, mix_fader[0x05].unk0C, mix_fader[0x06].unk0C, mix_fader[0x07].unk0C);
		printf("CH08=%2x:CH09=%2x:CH0A=%2x:CH0B=%2x",   mix_fader[0x08].unk0C, mix_fader[0x09].unk0C, mix_fader[0x0A].unk0C, mix_fader[0x0B].unk0C);
		printf("CH0C=%2x:CH0D=%2x:CH0E=%2x:CH0F=%2x\n", mix_fader[0x0C].unk0C, mix_fader[0x0D].unk0C, mix_fader[0x0E].unk0C, mix_fader[0x0F].unk0C);
		printf("CH10=%2x:CH11=%2x:CH12=%2x:CH13=%2x",   mix_fader[0x10].unk0C, mix_fader[0x11].unk0C, mix_fader[0x12].unk0C, mix_fader[0x13].unk0C);
		printf("CH14=%2x:CH15=%2x:CH16=%2x:CH17=%2x\n", mix_fader[0x14].unk0C, mix_fader[0x15].unk0C, mix_fader[0x16].unk0C, mix_fader[0x17].unk0C);
		printf("CH18=%2x:CH19=%2x:CH1A=%2x:CH1B=%2x",   mix_fader[0x18].unk0C, mix_fader[0x19].unk0C, mix_fader[0x1A].unk0C, mix_fader[0x1B].unk0C);
		printf("CH1C=%2x:CH1D=%2x:CH1E=%2x:CH1F=%2x\n", mix_fader[0x1C].unk0C, mix_fader[0x1D].unk0C, mix_fader[0x1E].unk0C, mix_fader[0x1F].unk0C);
		#endif
	}

	if( sd_print_fg ){
		#ifdef BORMAN_DEMO
		printf("SdCode=%x\n", a0);
		#endif
	}

	if( !(a0 & 0xFF000000) ) {
		if( !(a0 & 0x07FF) ) {
			goto end;
		}
		SePlay( a0 );
		goto end;
	}

	if( (a0 & 0xFF000000) == 0x1000000 ){
		set_sng_code_buf( a0 );
		goto end;
	}

	if( (a0 & 0xFF000000) == 0x2000000 ){
		se_load_code = a0;
		WakeupThread( id_SdMain );
		goto end;
	}

	if( (a0 & 0xE0000000) == 0x80000000 ){
		temp.up = sif_get_mem( path_name, a0 & 0x1FFFFFFF, 0x80 );
		while( 1 ){
			if( *temp.up & 0x80000000 ){
				break;
			}
		}
		sif_rv_release_queue( temp );
		#ifdef BORMAN_DEMO
		printf("Path name = %s\n", path_name);
		#endif
		goto end;
	}

	if( (a0 & 0xFF000000) == 0xF0000000 ){
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
				#ifdef BORMAN_DEMO
				printf("SdSet:Same Stream is Already Played.(code=%x)\n", str_load_code);
				#endif
			}
		} else {
			if( lnr8_status ){
				lnr8_stop_fg = 1;
			}
			str2_stop_fg[0] = 0;
			ee_addr[0].unk14 = (a0 & 0x00FFFFFF) << 4;
		}
		goto end;
	}

	if( (a0 & 0xFF000000) == 0xF1000000 ){
		if( !str1_use_iop ){
			ee_addr[0].unk04 = a0 & 0x00FFFFFF;
			ee_addr[0].unk0C++;
			str2_iop_load_set[0] = 1;
			WakeupThread( id_SdEELoad );
		}
		goto end;
	}

	if( (a0 & 0xFF000000) == 0xF2000000 ){
		ee_addr[1].unk14 = (a0 & 0x00FFFFFF) << 4;
		goto end;
	}

	if( (a0 & 0xFF000000) == 0xF3000000 ){
		ee_addr[1].unk04 = a0 & 0x00FFFFFF;
		ee_addr[1].unk0C++;
		str2_iop_load_set[1] = 1;
		WakeupThread( id_SdEELoad );
		goto end;
	}

	if( (a0 & 0xFF000000) == 0xF4000000 ){
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
			if( (a0 & 0xFF0000) == 0x10000 ){
				str2_mono_fg[1] = 1;
			} else {
				str2_mono_fg[1] = 0;
			}
			str2_pitch[1] = (int)((a0 & 0xFFFF) * 4096) / 48000;
			#ifdef BORMAN_DEMO
			printf("Str2 mono=%x, pitch=0x%x\n", str2_mono_fg[1], (u_short)str2_pitch[1]);
			#endif
			if( lnr8_status ){
				lnr8_stop_fg = 1;
			}
			str2_stop_fg[1] = 0;
			str2_first_load[1] = str2_load_code[1] = a0;
			str2_counter[1] = 0;
			str2_play_counter[1] = 0;
			#ifdef BORMAN_DEMO
			vox_fader[1].unk00 = 0x3F;
			vox_fader[1].unk08 = 0x20;
			#endif
			ee_addr[1].unk10 = 0;
			ee_addr[1].unk0C = 0;
			str2_status[1] = 1;
		}
		WakeupThread( id_SdEELoad );
		goto end;
	}

	if( (a0 & 0xFF000000) == 0xF5000000 ){
		if( !str1_use_iop ){
			if( (a0 & 0xFF0000) == 0x10000 ){
				str2_mono_fg[0] = 1;
			} else {
				str2_mono_fg[0] = 0;
			}
			str2_pitch[0] = (int)((a0 & 0xFFFF) * 4096) / 48000;
			#ifdef BORMAN_DEMO
			printf("Str1 mono=%x, pitch=0x%x\n", str2_mono_fg[0], (u_short)str2_pitch[0]);
			#endif
			if( lnr8_status ){
				lnr8_stop_fg = 1;
			}
			str2_first_load[0] = str2_load_code[0] = a0;
			str2_counter[0] = 0;
			str2_play_counter[0] = 0;
			#ifdef BORMAN_DEMO
			vox_fader[0].unk00 = 0x3F;
			vox_fader[0].unk08 = 0x20;
			#endif
			ee_addr[0].unk10 = 0;
			ee_addr[0].unk0C = 0;
			str2_status[0] = 1;
			WakeupThread( id_SdEELoad );
		}
		goto end;
	}

	if( (a0 & 0xFF000000) == 0xFA000000 ){
		switch( a0 & 0x0F00 ){
		case 0   : auto_env_pos  = (a0 & 0xFFFF); break;
		case 256 : auto_env_pos2 = (a0 & 0xFFFF); break;
		default  : break;
		}
		goto end;
	}

	if( (a0 & 0xFF000000) == 0xFB000000 ){
		if( a0 <= 0xFB1F3F3F ){
			temp.u = (int)(a0 & 0x1F0000) >> 16;
			mix_fader[temp.u].unk0C = (int)(a0 & 0x3F00) >> 8;
			mix_fader[temp.u].unk08 = ((a0 & 0x3F) << 10) + ((a0 & 0x3F) << 4) + ((int)(a0 & 0x3F) >> 2);
			mix_fader[temp.u].unk04 = mix_fader[temp.u].unk08;
			mix_fader[temp.u].unk00 = 0;
			#ifdef BORMAN_DEMO
			if( sd_print_fg ){
				printf("Fader:Pan=%x:Vol=%x\n", mix_fader[temp.u].unk0C, mix_fader[temp.u].unk04);
			}
			#endif
		} else {
			if( (a0 & 0xFF0000) == 0xFE0000 || (a0 & 0xFF0000) == 0xFF0000 ){
				temp.u = (int)(a0 & 0x10000) >> 16;
				vox_fader[temp.u].unk00 = a0 & 0x3F;
				vox_fader[temp.u].unk08 = (int)(a0 & 0x3F00) >> 8;
				if( sd_print_fg ){
					#ifdef BORMAN_DEMO
					printf("VoxFader:Code=%x:Ch=%x:Pan=%x:Vol=%x\n", a0, temp.u, vox_fader[temp.u].unk08, vox_fader[temp.u].unk00);
					#endif
				}
			}
		}
		goto end;
	}

	if( a0 > 0xFBFFFFFF && a0 <= 0xFC1F3FFF ){
		temp.u = (int)(a0 & 0x1F0000) >> 16;
		mix_fader[temp.u].unk0C = (int)(a0 & 0x3F00) >> 8;
		#ifdef BORMAN_DEMO
		if( sd_print_fg ) {
			printf("Fader:Pan=%x\n", mix_fader[temp.u].unk0C);
		}
		#endif
		goto end;
	}

	if( a0 > 0xFCFFFFFF && a0 <= 0xFD1F3FFF ){
		temp.u = (int)(a0 & 0x1F0000) >> 16;
		mix_fader[temp.u].unk08 = ((a0 & 0x3F00) << 2) + ((int)(a0 & 0x3F00) >> 4) + ((int)(a0 & 0x3F00) >> 10);
		if( mix_fader[temp.u].unk08 == mix_fader[temp.u].unk04 ){
			mix_fader[temp.u].unk00 = 0;
		} else if( a0 & 0xFF ){
			mix_fader[temp.u].unk00 = (mix_fader[temp.u].unk08 - mix_fader[temp.u].unk04) / ((int)(a0 & 0xFF)*10);
			if( !mix_fader[temp.u].unk00 ){
				mix_fader[temp.u].unk00 = 1;
			}
		} else {
			mix_fader[temp.u].unk04 = mix_fader[temp.u].unk08;
			mix_fader[temp.u].unk00 = 0;
		}
		goto end;
	}

	if( (a0 & 0xFF000000) == 0xFE000000 ){
		pak_cd_read_fg = 0;
		if( a0 <= 0xFE7FFFFF ){
			#ifdef BORMAN_DEMO
			if(wave_save_code != a0 && se_save_code2 != a0) {
			#endif
			wave_load_code = a0;
			wave_load_status = 1;
			#ifdef BORMAN_DEMO
			}
			#endif
		} else {
			pak_load_code = a0;
			pak_load_status = 1;
		}
		WakeupThread( id_SdMain );
		goto end;
	}

	if( (a0 & 0xFF000000) == 0xC0000000 ){
		pak_load_code = a0 & 0x0FFFFFFF;
		pak_load_status = 1;
		pak_cd_read_fg = 1;
		WakeupThread( id_SdMain );
		goto end;
	}

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
			#ifdef BORMAN_DEMO
			printf("*** STR WAIT ***\n");
			#endif
			break;

		case 0xFF00000C:
			if( str1_use_iop ){
				str_wait_fg = 0;
			} else {
				str2_wait_fg[0] = 0;
			}
			#ifdef BORMAN_DEMO
			printf("*** STR WAIT OFF (START) ***\n");
			#endif
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
			#ifdef BORMAN_DEMO
			printf("*** STR2 WAIT ***\n");
			#endif
			break;
		case 0xFF000010:
			str2_wait_fg[1] = 0;
			#ifdef BORMAN_DEMO
			printf("*** STR WAIT OFF (START) ***\n");
			#endif
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
			#ifdef BORMAN_DEMO
			printf("*** STR1:IOP DIRECT READ***\n");
			#endif
			break;
		case 0xFF000013:
			str1_use_iop = 0;
			#ifdef BORMAN_DEMO
			printf("*** STR1:EE READ***\n");
			#endif
			break;
		case 0xFF000014:
			fader_off_fg = 1;
			#ifdef BORMAN_DEMO
			printf("*** SET Volume Fader =0 for SNG ***\n");
			#endif
			break;

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

		case 0xFFFFFFEC: break;
		case 0xFFFFFFED: break;
		case 0xFFFFFFFD: break;

		default: break;
	}

end:
	return;
}
