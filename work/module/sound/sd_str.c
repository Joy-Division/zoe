/*
 * Sound Driver for PS2 IOP
 * Stream System Module 1
 *
 * ver.ZONE OF THE ENDERS
 */
#include <sys/types.h>
#include <kernel.h>
#include <libsd.h>
#include "sd_incl.h"

void str_tr_off( void )
{
	str_keyoffs = 0x30000000;
}

void str_spuwr( void )
{
	if (str_keyoffs){
		sceSdSetSwitch( 0x1601, str_keyoffs );
		str_keyoffs = 0;
	}
}

int StartStream1( void )
{
	int temp, temp2;
	
	if (str_fp){
		str_tr_off();
		PcmClose( str_fp );
		str_fp = 0;
	}
	
	str_fp = PcmOpen( str_load_code, 1 );
	
	if (str_fp < 0){
		str_load_code = 0;
		str_first_load = 0;
		str_fp = 0;
		return -1;
	}
	
	temp = PcmRead( str_fp, str_header, 0x8800 );
	
	str_wave_size = str_header[0] << 24;
	str_wave_size |= str_header[1] << 16;
	str_wave_size |= str_header[2] << 8;
	str_wave_size |= str_header[3];
	str_unplay_size = str_unload_size = str_wave_size;
	str_volume = str_header[4] << 8;
	str_volume |= str_header[5];
	str_pitch = str_header[6] << 8;
	str_pitch |= str_header[7];
	str_pitch /= 48000;
	
	if (str_header[8] == 1){
		str_mono_fg = 1;
	} else {
		str_mono_fg = 0;
	}
	
	str_trans_buf = str_header+0x800;
	temp -= 0x800;
	
	if (temp < str_unload_size){
		str_unload_size -= temp;
	} else {
		str_unload_size = 0;
	}
	
	str_trans_offset = 0;
	
	for (temp2 = 0 ; temp2 < 8 ; temp2++){
		str_read_status[temp2] = 1;
	}
	
	str_read_idx = 0;
	return 0;
}

int StartStream2( void )
{
	int temp, temp2;
	
	if (str_fp){
		str_tr_off();
		PcmClose( str_fp );
		str_fp = 0;
	}
	
	str_fp = PcmOpen( str_load_code, 1 );
	
	if (str_fp < 0){
		str_load_code = 0;
		str_first_load = 0;
		str_fp = 0;
		return -1;
	}
	
	temp = PcmRead( str_fp, str_header, 0x800 );
	
	str_wave_size =  str_header[0] << 24;
	str_wave_size |= str_header[1] << 16;
	str_wave_size |= str_header[2] << 8;
	str_wave_size |= str_header[3];
	
	if (str_start_offset*0x1000 >= str_wave_size){
		PcmClose( str_fp );
		str_load_code = 0;
		str_first_load = 0;
		str_fp = 0;
		return -1;
	} else {
		// EMPTY
	}

	str_wave_size -= str_start_offset*0x1000;
	str_unplay_size = str_unload_size = str_wave_size;
	str_volume = str_header[4] << 8;
	str_volume |= str_header[5];
	str_pitch = str_header[6] << 8;
	str_pitch |= str_header[7];
	str_pitch /= 48000;
	
	if (str_header[8] == 1){
		str_mono_fg = 1;
	} else {
		str_mono_fg = 0;
	}
	
	PcmLseek( str_fp, str_start_offset*0x1000, 1 );
	str_trans_buf = str_header+0x800;
	temp = PcmRead( str_fp, str_trans_buf, 0x8000 );
	
	if (temp < str_unload_size){
		str_unload_size -= temp;
	} else {
		str_unload_size = 0;
	}
	
	str_trans_offset = 0;
	
	for (temp2 = 0 ; temp2 < 8 ; temp2++) {
		str_read_status[temp2] = 1;
	}
	
	str_read_idx = 0;
	return 0;
}

int StartStream( void )
{
	if (str_start_offset){
		return StartStream2();
	} else {
		return StartStream1();
	}
}

void StrCdLoad( void )
{
	int temp, temp2, temp3, temp4;
	
	if (str_status < 3 || str_status > 6){
		// EMPTY
	} else {
		for (temp2 = 0 ; temp2 < 2 ; temp2++){
			if (str_unload_size){
				temp4 = 0;
				for (temp3 = 0; temp3 < 4; temp3++){
					temp4 |= str_read_status[str_read_idx+temp3];
				}
				if (!temp4){
					// wait for 7 vblanks
					WaitVblankEnd();
					WaitVblankStart(); WaitVblankEnd();
					WaitVblankStart(); WaitVblankEnd();
					WaitVblankStart(); WaitVblankEnd();
					WaitVblankStart(); WaitVblankEnd();
					WaitVblankStart(); WaitVblankEnd();
					WaitVblankStart(); WaitVblankEnd();
					WaitVblankStart(); WaitVblankEnd();
					if (str_unload_size > 0x4000){
						temp = PcmRead( str_fp, str_trans_buf+str_trans_offset, 0x4000 );
						for (temp3 = 0 ; temp3 < 4 ; temp3++){
							str_read_status[str_read_idx+temp3] = 1;
						}
						str_read_idx += 4;
						if (str_read_idx == 8){
							str_read_idx = 0;
						}
						str_unload_size -= 0x4000;
						str_trans_offset += 0x4000;
						if (str_trans_offset >= 0x8000){
							str_trans_offset = 0;
						}
					} else {
						temp = PcmRead( str_fp, str_trans_buf+str_trans_offset, 0x4000 );
						for (temp3 = 0; temp3 < 4; temp3++){
							str_read_status[str_read_idx+temp3] = 1;
						}
						str_read_idx += 4;
						if (str_read_idx == 8){
							str_read_idx = 0;
						}
						str_unload_size = 0;
						break;
					}
				}
			}
		}
	}
}

void str_load( void )
{
	switch (str_status-1){
	case 0:
		if (StartStream()){
			str_status = 0;
		}
		break;
	case 1:
	case 2:
	case 3:
	case 4:
		str_l_r_fg = 0;
		str_status = 2;
		break;
	case 5:
		StrCdLoad();
		break;
	case 6:
		PcmClose( str_fp );
		str_load_code = 0;
		str_status = 0;
		str_fp = 0;
		break;
	}
}

int StrSpuTrans( void )
{
	int temp = 0, temp2 = 0;
	u_int temp3;
	
	if (str_stop_fg && str_status > 1){
		switch (str_stop_fg){
		case 1:
			sceSdSetParam( 0x329, 0xFF );
			sceSdSetParam( 0x429, 0x07 );
			sceSdSetParam( 0x32B, 0xFF );
			sceSdSetParam( 0x42B, 0x07 );
			str_status = 7;
			break;
		
		case 2:
			sceSdSetParam( 0x329, 0xFF );
			sceSdSetParam( 0x429, 0x0D );
			sceSdSetParam( 0x32B, 0xFF );
			sceSdSetParam( 0x42B, 0x0D );
			break;
		}
		str_tr_off();
		str_stop_fg = 0;
	}
	switch (str_status-2){
	case 0:
		if (!str_l_r_fg){
			str_play_idx = 0;
			str_play_offset = 0;
			spu_str_start_ptr_l = 0x5020;
			sceSdSetAddr( 0x2169, 0x5020 );
			sceSdVoiceTrans( 1, 0, str_trans_buf, (u_char *)spu_str_start_ptr_l, 0x800 );
			if (!str_mono_fg){
				str_play_offset = 0x800;
				str_unplay_size -= 0x800;
			}
			str_l_r_fg = 1;
		} else {
			spu_str_start_ptr_l = 0x6020;
			sceSdSetAddr( 0x216B, 0x6020 );
			sceSdVoiceTrans( 1, 0, str_trans_buf+str_play_offset, (u_char *)spu_str_start_ptr_r, 0x800 );
			str_play_offset = 0x800;
			str_unplay_size -= 0x800;
			if (!str_mono_fg){
				str_read_status[str_play_idx] = 0;
				str_play_idx++;
			}
			str_l_r_fg = 0;
			str_status++;
		}
		temp = 1;
		break;
	
	case 1:
		if (!str_unplay_size || (str_unplay_size & 0x80000000)){
			str_status++;
		}
		if (!str_l_r_fg){
			str_trans_buf[str_play_offset+0x7F1] = str_trans_buf[str_play_offset+0x7F1] | 1;
			sceSdVoiceTrans( 1, 0, str_trans_buf+str_play_offset, (u_char *)spu_str_start_ptr_l, 0x800 );
			if (!str_mono_fg){
				str_play_offset += 0x800;
				str_unplay_size -= 0x800;
			}
			str_l_r_fg = 1;
		} else {
			str_trans_buf[str_play_offset+0x7F1] = str_trans_buf[str_play_offset+0x7F1] | 1;
			sceSdVoiceTrans( 1, 0, str_trans_buf+str_play_offset, (u_char *)spu_str_start_ptr_r, 0x800 );
			str_play_offset += 0x800;
			str_unplay_size -= 0x800;
			str_read_status[str_play_idx] = 0;
			str_play_idx++;
			str_l_r_fg = 0;
			str_status++;
		}
		temp = 1;
		break;
	
	case 2:
		if (str_first_load){
			str_first_load = 0;
		}
		if (str_wait_fg){
			// EMPTY
		} else {
			if (sound_mono_fg){
				temp3 = str_volume * se_pant[0x80];
				sceSdSetParam( 0x0029, ((temp3 >> 7) * str_master_vol) / 0x3FFF );
				temp3 = str_volume * se_pant[0x80];
				sceSdSetParam( 0x0129, ((temp3 >> 7) * str_master_vol) / 0x3FFF );
			} else {
				temp3 = str_volume * se_pant[0xFC];
				sceSdSetParam( 0x0029, ((temp3 >> 7) * str_master_vol) / 0x3FFF );
				sceSdSetParam( 0x0129, 0 );
			}
			temp3 = str_pitch*str_master_pitch;
			sceSdSetParam( 0x0229, temp3 >> 12 );
			sceSdSetAddr( 0x2069, 0x5020 );
			sceSdSetParam( 0x0329, 0xFF );
			sceSdSetParam( 0x0429, 0x07 );
			if (sound_mono_fg){
				temp3 = str_volume*se_pant[0x80];
				sceSdSetParam( 0x2B, ((temp3 >> 7)*str_master_vol) / 0x3FFF );
				sceSdSetParam( 0x012B, ((temp3 >> 7)*str_master_vol) / 0x3FFF );
			}
			else {
				sceSdSetParam( 0x002B, 0 );
				temp3 = str_volume*se_pant[0xFC];
				sceSdSetParam( 0x012B, ((temp3 >> 7)*str_master_vol) / 0x3FFF );
			}
			temp3 = str_pitch*str_master_pitch;
			sceSdSetParam( 0x022B, temp3 >> 12 );
			sceSdSetParam( 0x206B, 0x6020 );
			sceSdSetParam( 0x032B, 0xFF );
			sceSdSetParam( 0x042B, 0x07 );
			sceSdSetSwitch(0x1501, 0x30 );
			mute_str_l_r_fg = 0;
			spu_str_idx = 0;
			str_next_idx = 0x800;
			str_status++;
			if (str_unplay_size || (str_unplay_size & 0x80000000)){
				str_off_ctr = 0x1F;
				str_status++;
			}
		}
		break;
	
	case 3:
		if (!sceSdGetParam(0x529)){
			str_off_ctr = -1;
			str_status++;
			break;
		}
		spu_str_idx = sceSdGetAddr( 0x2269 );
		spu_str_idx -= 0x5020;
		if ((spu_str_idx < 0x1000) || (spu_str_idx & 0x80000000)){
			break;
		}
		if (str_counter_low > spu_str_idx){
			str_counter += 0x1000;
		}
		str_counter_low = spu_str_idx;
		if (((spu_str_idx & 0x800) == str_next_idx) || str_l_r_fg || mute_str_l_r_fg){
			temp = 1;
			if (str_read_status[str_play_idx] && !mute_str_l_r_fg){
				if (str_mono_fg){
					str_mono_offset = 0;
				}
				if (spu_str_idx >= 0x800){
					if (!str_l_r_fg){
						sceSdVoiceTrans( 1, 0, str_trans_buf+str_play_offset, (u_char *)spu_str_start_ptr_l, 0x800 );
						str_l_r_fg = 1;
					} else {
						sceSdVoiceTrans( 1, 0, str_trans_buf+str_play_offset, (u_char *)spu_str_start_ptr_r, 0x800 );
						str_next_idx = (str_next_idx+0x800) & 0x0FFF;
						str_l_r_fg = 0;
						if (!str_mono_fg){
							str_read_status[str_play_idx] = 0;
							str_play_idx++;
							if(str_play_idx == 8) {
								str_play_idx = 0;
							}
						}
						if (str_mono_fg){
							str_mono_offset = 1;
						}
					}
				} else {
					str_trans_buf[str_play_offset+0x7F1] = str_trans_buf[str_play_offset+0x7F1] | 1;
					if (!str_l_r_fg){
						sceSdVoiceTrans( 1, 0, str_trans_buf+str_play_offset, (u_char *)spu_str_start_ptr_l, 0x800 );
						str_l_r_fg = 1;
					} else {
						str_next_idx = (str_next_idx+0x800) & 0x0FFF;
						sceSdVoiceTrans( 1, 0, str_trans_buf+str_play_offset, (u_char *)spu_str_start_ptr_r, 0x800 );
						str_l_r_fg = 0;
						str_read_status[str_play_idx] = 0;
						str_play_idx++;
						if (str_play_idx == 8){
							str_play_idx = 0;
						}
						if (str_mono_fg){
							str_mono_offset = 1;
						}
					}
				}
				if (str_mono_fg && str_mono_offset){
					str_play_offset += 0x800;
					if (str_play_offset == 0x8000){
						str_play_offset = 0;
					}
					if (str_unplay_size > 0x800){
						str_unplay_size -= 0x800;
					} else {
						str_off_ctr = 0x1F;
						str_play_offset = 0;
						str_status++;
					}
				} else {
					str_play_offset += 0x800;
					if (str_play_offset == 0x8000){
						str_play_offset = 0;
					}
					if (str_unplay_size > 0x800){
						str_unplay_size -= 0x800;
					} else {
						str_off_ctr = 0x1F;
						str_play_offset = 0;
						str_status++;
					}
				}
			} else {
				if (spu_str_idx >= 0x800){
					dummy_data[1] = 6;
					dummy_data[0x07F1] = 2;
					if (!mute_str_l_r_fg){
						sceSdVoiceTrans( 1, 0, dummy_data, (u_char *)spu_str_start_ptr_l, 0x800 );
						mute_str_l_r_fg = 1;
					} else {
						sceSdVoiceTrans( 1, 0, dummy_data, (u_char *)spu_str_start_ptr_r, 0x800 );
						str_next_idx = (str_next_idx+0x800) & 0xFFF;
						mute_str_l_r_fg = 0;
					}
				} else {
					dummy_data[1] = 2;
					dummy_data[0x7F1] = 3;
					if (!mute_str_l_r_fg){
						mute_str_l_r_fg = 1;
						sceSdVoiceTrans( 1, 0, dummy_data, (u_char *)spu_str_start_ptr_l, 0x800 );
					} else {
						mute_str_l_r_fg = 0;
						str_next_idx = (str_next_idx+0x800) & 0xFFF;
						sceSdVoiceTrans( 1, 0, dummy_data, (u_char *)spu_str_start_ptr_r, 0x800 );
					}
				}
			}
		}
		break;
	
	case 4:
		str_counter_low += 0x80;
		if (str_counter_low >= 0x1000){
			str_counter += 0x1000;
			str_counter_low &= 0xFFF;
		}
		if (--str_off_ctr == -2){
			str_tr_off();
			str_status++;
		}
		break;
	
	case 5:
		str_counter_low += 0x80;
		if (str_counter_low >= 0x1000){
			str_counter += 0x1000;
			str_counter_low &= 0xFFF;
		}
		temp2 = 1;
		break;
	}
	return (temp | temp2);
}

void str_int( void )
{
	if (sceSdVoiceTransStatus( 1, 0 ) == 1 && StrSpuTrans()){
		WakeupThread( id_SdMain );
	}
	str_spu_wr();
}