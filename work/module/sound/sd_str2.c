/*
 * Sound Driver for PS2 IOP
 * Stream System Module 2
 *
 * ver.ZONE OF THE ENDERS
 */
#include <sys/types.h>
#include <kernel.h>
#include <libsd.h>
#include "sd_incl.h"

void str2_tr_off( u_int a0 )
{
	if (!a0){
		str2_keyoffs |= 0x30000000;
	} else {
		str2_keyoffs |= 0xC0000000;
	}
}

void str2_spuwr( void )
{
	if (str2_keyoffs){
		sceSdSetSwitch( 0x1601, str2_keyoffs );
		str2_keyoffs = 0;
	}
}

int StartEEStream( u_int a0 )
{
	int temp, temp2;
	
	str2_read_disable[a0] = 0;
	str2_tr_off( a0 );
	
	if ((str2_fp[a0] = EEOpen(str2_load_code[a0])) < 0){
		str2_fp[a0] = str2_first_load[a0] = str2_load_code[a0] = 0;
		str2_iop_load_set[a0] = 0;
		return -1;
	}
	
	str2_unplay_size[a0] = str2_unload_size[a0] = ee_addr[a0].unk14;
	str2_volume[a0] = 0x7F;
	ee2_buf_idx[a0] = 0;
	temp = EERead( str2_fp[a0], a0*0x8000+eeload2_buf+ee2_buf_idx[a0]*0x4000, ee2_buf_idx[a0], 0x4000 );
	
	for (temp2 = 0 ; temp2 < 4 ; temp2++){
		str2_read_status[a0][ee2_buf_idx[a0]+temp2] = 1;
	}
	
	ee2_buf_idx[a0]++;
	
	if (temp < str2_unload_size[a0]){
		str2_unload_size[a0] -= temp;
	} else {
		str2_unload_size[a0] = 0;
	}
	
	for (temp2 = 0 ; temp2 < 4 ; temp2++){
		str2_read_status[a0][ee2_buf_idx[a0]+temp2] = 0;
	}
	
	str2_trans_buf[a0] = eeload2_buf+a0*0x8000;
	return 0;
}

void StrEELoad( u_int a0 )
{
	int temp, temp2, temp3, temp4;
	
	for (temp2 = 0 ; temp2 < 2 ; temp2++){
		if (str2_unload_size[a0]){
			temp4 = 0;
			for (temp3 = 0 ; temp3 < 4 ; temp3++){
				temp4 |= str2_read_status[a0][ee2_buf_idx[a0]+temp3];
			}
			if (!temp4){
				
				// wait for 1 vblank
				WaitVblankStart();
				WaitVblankEnd();
				
				if (str2_unload_size[a0] > 0x4000){
					temp = EERead(str2_fp[a0], a0*0x8000+eeload2_buf+ee2_buf_idx[a0]*0x4000, ee2_buf_idx[a0], 0x4000);
					if (temp){
						for (temp3 = 0; temp3 < 4; temp3++){
							str2_read_status[a0][ee2_buf_idx[a0]+temp3] = 1;
						}
						ee2_buf_idx[a0] = ee2_buf_idx[a0]+1 & 1;
						str2_unload_size[a0] -= 0x4000;
					}
				} else {
					temp = EERead(str2_fp[a0], a0*0x8000+eeload2_buf+ee2_buf_idx[a0]*0x4000, ee2_buf_idx[a0], 0x4000);
					if (temp){
						for (temp3 = 0 ; temp3 < 4 ; temp3++){
							str2_read_status[a0][ee2_buf_idx[a0]+temp3] = 1;
						}
						ee2_buf_idx[a0] = ee2_buf_idx[a0]+1 & 1;
						str2_unload_size[a0] = 0;
					}
					break;
				}
			}
		}
	}
}

void str2_load( void )
{
	int temp;
	
	for (temp = 0 ; temp < 2 ; temp++){
		switch (str2_status[temp]-1){
		case 0:
			if (ee_addr[temp].unk0C){
				if(StartEEStream( temp )){
					str2_status[temp] = 0;
				} else {
					str2_l_r_fg[temp] = 0;
					str2_status[temp] = 0;
				}
			}
			break;
		
		case 1:
			if (!ee_addr[temp].unk0C){
				StrEELoad( temp );
				str2_status[temp]++;
			} else {
				// EMPTY
			}
		
		case 2:
		case 3:
		case 4:
		case 5:
			StrEELoad( temp );
			break;
		
		case 6:
			break;
		
		case 7:
			ee_addr[temp].unk10 = (u_char *)ee_addr[temp].unk0C = str2_fp[temp] = str2_status[temp] = str2_load_code[temp] = 0;
			break;
		}
	}
}


int Str2SpuTrans( int a0 )
{
	int temp, temp2, temp3, temp4;
	
	if (a0 >= 2){
		return 0;
	}
	
	if (str2_stop_fg[a0] && str2_status[a0] >= 3){
		switch (str2_stop_fg[a0]){
		case 1: // 0x13D94
			// these are functionally fine but dont emit the same assembly
			// lacks some register shuffling
			sceSdSetParam( ((a0*2)+0x14)*2 | 0x0301, 0xFF );
			sceSdSetParam( ((a0*2)+0x14)*2 | 0x0401, 0x07 );
			sceSdSetParam( ((a0*2)+0x15)*2 | 0x0301, 0xFF );
			sceSdSetParam( ((a0*2)+0x15)*2 | 0x0401, 0x07 );
			str2_first_load[a0] = 0;
			str2_status[a0] = 8;
			break;
		
		case 2: // 0x13EB8
			// these are functionally fine but dont emit the same assembly
			// lacks some register shuffling
			sceSdSetParam( ((a0*2)+0x14)*2 | 0x0301, 0xFF );
			sceSdSetParam( ((a0*2)+0x14)*2 | 0x0401, 0x0D );
			sceSdSetParam( ((a0*2)+0x15)*2 | 0x0301, 0xFF );
			sceSdSetParam( ((a0*2)+0x15)*2 | 0x0401, 0x0D );
			break;
		}
		str2_tr_off(a0);
		str2_stop_fg[a0] = 0;

	} else if (str2_stop_fg[a0] && str2_status[a0]){
		str2_first_load[a0] = 0;
		str2_status[a0] = 8;
		str2_stop_fg[a0] = 0;
	}
	
	switch(str2_status[a0]-3) {
	case 0: // 0x140C8
		if (!str2_l_r_fg[a0]){
			str2_play_idx[a0] = 0;
			str2_play_offset[a0] = 0;
			spu_str2_start_ptr_l[a0] = a0 * 0x2000 + 0x5020;
			// this is functionally fine but doesnt emit the same assembly
			// lacks some register shuffling
			sceSdSetAddr( ((a0*2)+0x14)*2 | 0x2141, a0*0x2000+0x5020 );
			sceSdVoiceTrans( 1, 0, str2_trans_buf[a0], (u_char *)(spu_str2_start_ptr_l[a0]), 0x800 );
			if (!str2_mono_fg[a0]){
				str2_play_offset[a0] = 0x800;
				str2_unplay_size[a0] -= 0x800;
			}
			str2_l_r_fg[a0] = 1;
		} else { // 0x142A0
			spu_str2_start_ptr_r[a0] = a0*0x2000+0x6020;
			// this is functionally fine but doesnt emit the same assembly
			// lacks some register shuffling
			sceSdSetAddr( ((a0*2)+0x15)*2 | 0x2141, a0*0x2000+0x6020 );
			sceSdVoiceTrans( 1, 0, str2_trans_buf[a0]+str2_play_offset[a0], (u_char *)(spu_str2_start_ptr_r[a0]), 0x800 );
			str2_play_offset[a0] += 0x800;
			str2_unplay_size[a0] -= 0x800;
			if (!str2_mono_fg[a0]){
				str2_read_status[a0][str2_play_idx[a0]] = 0;
				str2_play_idx[a0]++;
			}
			str2_l_r_fg[a0] = 0;
			str2_counter[a0] += 0x800;
			str2_status[a0]++;
		}
		temp = 1;
		break;
	
	case 1:
		if (!str2_unplay_size[a0] || (str2_unplay_size[a0] & 0x80000000)){
			str2_status[a0]++;
		}
		if (!str2_l_r_fg[a0]){
			str2_trans_buf[a0][str2_play_offset[a0]+0x7F1] |= 1;
			sceSdVoiceTrans( 1, 0, str2_trans_buf[a0]+str2_play_offset[a0], (u_char*)(spu_str2_start_ptr_l[a0]), 0x800 );
			if (!str2_mono_fg[a0]){
				str2_play_offset[a0] += 0x800;
				str2_unplay_size[a0] -= 0x800;
			}
			str2_l_r_fg[a0] = 1;
		} else {
			str2_trans_buf[a0][str2_play_offset[a0]+0x7F1] |= 1;
			sceSdVoiceTrans( 1, 0, str2_trans_buf[a0]+str2_play_offset[a0], (u_char*)(spu_str2_start_ptr_r[a0]), 0x800 );
			str2_play_offset[a0] += 0x800;
			str2_unplay_size[a0] -= 0x800;
			str2_read_status[a0][str2_play_idx[a0]] = 0;
			str2_play_idx[a0]++;
			str2_l_r_fg[a0] = 1;
			str2_counter[a0] += 0x800;
			str2_status[a0]++;
		}
		temp = 1;
		break;
	
	case 2:
		if (str2_first_load[a0]){
			str2_first_load[a0] = 0;
		}
		if (str2_wait_fg[a0]){
			break;
		}
		if (sound_mono_fg){
			temp3 = temp4 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
							* se_pant[0x40 - vox_fader[a0].unk08]) / 0x7F) * str2_master_vol)
							/ 0x3FFF;
			// 0x14CC0
			// these are functionally fine but dont emit the same assembly
			// lacks some register shuffling
			sceSdSetParam( (((a0*2)+0x14)*2) | 1, temp3 );
			sceSdSetParam( (((a0*2)+0x14)*2) | 0x101, temp4 );
			sceSdSetParam( (((a0*2)+0x15)*2) | 1, (unsigned)temp3 / 3 );
			sceSdSetParam( (((a0*2)+0x15)*2) | 0x101, (unsigned)temp3 / 3 );
			vox_fader[a0].unk04 = vox_fader[a0].unk00;
			vox_fader[a0].unk0C = vox_fader[a0].unk08;
		} else {
			if (str2_mono_fg[a0]){
				temp3 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
							* se_pant[0x40 - vox_fader[a0].unk08]) / 0x7F) * str2_master_vol)
							/ 0x3FFF;
				temp4 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
							* se_pant[vox_fader[a0].unk08]) / 0x7F) * str2_master_vol)
							/ 0x3FFF;
				// 0x1508C
				// these are functionally fine but dont emit the same assembly
				// lacks some register shuffling
				sceSdSetParam( (((a0*2)+0x14)*2) | 1, temp3 );
				sceSdSetParam( (((a0*2)+0x14)*2) | 0x101, temp4 );
				sceSdSetParam( (((a0*2)+0x15)*2) | 1, (unsigned)temp3 / 3 );
				sceSdSetParam( (((a0*2)+0x15)*2) | 0x101, (unsigned)temp3 / 3 );
				vox_fader[a0].unk04 = vox_fader[a0].unk00;
				vox_fader[a0].unk0C = vox_fader[a0].unk08;
			} else {
				temp3 = temp4 = (((unsigned)(str2_volume[a0]
								* se_pant[0xFC] / 0x7F)) * str2_master_vol)
								/ 0x3FFF;
				// 0x152C8
				// these are functionally fine but dont emit the same assembly
				// lacks some register shuffling
				sceSdSetParam( (((a0*2)+0x14)*2) | 1, temp3 );
				sceSdSetParam( (((a0*2)+0x14)*2) | 0x101, 0 );
				sceSdSetParam( (((a0*2)+0x15)*2) | 1, 0 );
				sceSdSetParam( (((a0*2)+0x15)*2) | 0x101, temp4 );
				vox_fader[a0].unk04 = vox_fader[a0].unk00;
				vox_fader[a0].unk0C = vox_fader[a0].unk08;
			}
		}
		sceSdSetParam( ((a0*2)+0x14)*2 | 0x201, (u_int)((u_short)str2_pitch[a0]*str2_master_pitch) / 0x1000 );
		sceSdSetAddr( ((a0*2)+0x14)*2 | 0x2041, a0*0x2000+0x5020 );
		// 0x15470
		// these are functionally fine but dont emit the same assembly
		// lacks some register shuffling
		sceSdSetParam( ((a0*2)+0x14)*2 | 0x301, 0xFF );
		sceSdSetParam( ((a0*2)+0x14)*2 | 0x401, 0x07 );
		sceSdSetParam( ((a0*2)+0x15)*2 | 0x201, (u_int)((u_short)str2_pitch[a0]*str2_master_pitch) / 0x1000 );
		sceSdSetAddr( ((a0*2)+0x15)*2 | 0x2041, a0*0x2000+0x6020 );
		// 0x155A0
		// these are functionally fine but dont emit the same assembly
		// lacks some register shuffling
		sceSdSetParam( ((a0*2)+0x15)*2 | 0x301, 0xFF );
		sceSdSetParam( ((a0*2)+0x15)*2 | 0x401, 0x07 );
		if (!a0){
			sceSdSetSwitch(0x1501, 0x30);
		} else {
			sceSdSetSwitch(0x1501, 0xC0);
		}
		spu_str2_idx[a0] = mute2_l_r_fg[a0] = 0;
		str2_next_idx[a0] = 0x800;
		str2_status[a0]++;
		if (str2_unplay_size[a0] || !(str2_unplay_size[a0] & 0x80000000)){
			str2_off_ctr[a0] = 0x1F;
			str2_status[a0]++;
		}
		break;
	
	case 3:
		if (sceSdGetParam(((a0*2)+0x14)*2 | 0x501) == 0){
			str2_off_ctr[a0] = -1;
			str2_status[a0]++;
			break;
		}
		if ((vox_fader[a0].unk00 == vox_fader[a0].unk04) || (vox_fader[a0].unk08 == vox_fader[a0].unk0C)){
			if (sound_mono_fg){
				temp3 = temp4 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
								* se_pant[0x80]) / 0x7F) * str2_master_vol)
								/ 0x3FFF;
				// 0x159F0
				// these are functionally fine but dont emit the same assembly
				// lacks some register shuffling
				sceSdSetParam( (((a0*2)+0x14)*2) | 0x0001, temp3 );
				sceSdSetParam( (((a0*2)+0x14)*2) | 0x0101, temp4 );
				sceSdSetParam( (((a0*2)+0x15)*2) | 0x0001, temp3 );
				sceSdSetParam( (((a0*2)+0x15)*2) | 0x0101, temp4 );
				vox_fader[a0].unk04 = vox_fader[a0].unk00;
				vox_fader[a0].unk0C = vox_fader[a0].unk08;
			} else {
				if(str2_mono_fg[a0]) {
					temp3 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
								* se_pant[0x40 - vox_fader[a0].unk08]) / 0x7F) * str2_master_vol)
								/ 0x3FFF;
					temp4 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
								* se_pant[vox_fader[a0].unk08]) / 0x7F) * str2_master_vol)
								/ 0x3FFF;
					// 0x15D80
					// these are functionally fine but dont emit the same assembly
					// lacks some register shuffling
					sceSdSetParam( (((a0*2)+0x14)*2) | 0x001, temp3 );
					sceSdSetParam( (((a0*2)+0x14)*2) | 0x101, temp4 );
					sceSdSetParam( (((a0*2)+0x15)*2) | 0x001, temp3 );
					sceSdSetParam( (((a0*2)+0x15)*2) | 0x101, temp3 );
					vox_fader[a0].unk04 = vox_fader[a0].unk00;
					vox_fader[a0].unk0C = vox_fader[a0].unk08;
				}
			}
		}
		spu_str2_idx[a0] = sceSdGetAddr( ((a0*2)+0x14)*2 | 0x2241 );
		spu_str2_idx[a0] = (spu_str2_idx[a0] - 0x5020) * 0x1FFF;
		if (spu_str2_idx[a0] >= 0x1000 || (spu_str2_idx[a0] & 0x80000000)){
			break;
		}
		if (!str2_mute_fg[a0]){
			str2_play_counter[a0]++;
		}
		if ((spu_str2_idx[a0] & 0x800) == str2_next_idx[a0] || str2_l_r_fg[a0] || !mute2_l_r_fg[a0]){
			temp = 1;
			if (str2_read_status[a0][str2_play_idx[a0]] && !mute2_l_r_fg[a0]){
				str2_mute_fg[a0] = 0;
				if (str2_l_r_fg[a0]){
					str2_counter[a0] += 0x800;
				}
				if (str2_mono_fg[a0]){
					str2_mono_offset[a0] = 0;
				}
				if (spu_str2_idx[a0] >= 0x800){
					if (!str2_l_r_fg[a0]){
						sceSdVoiceTrans( 1, 0, str2_trans_buf[a0]+str2_play_offset[a0], (u_char *)(spu_str2_start_ptr_l[a0]), 0x800 );
						str2_l_r_fg[a0] = 1;
					} else {
						sceSdVoiceTrans( 1, 0, str2_trans_buf[a0]+str2_play_offset[a0], (u_char *)(spu_str2_start_ptr_r[a0]), 0x800 );
						str2_next_idx[a0] = (str2_next_idx[a0] + 0x800) & 0xFFF;
						str2_l_r_fg[a0] = 0;
						if (str2_mono_fg[a0]){
							str2_read_status[a0][str2_play_idx[a0]] = 0;
							str2_play_idx[a0]++;
							if (str2_play_idx[a0] == 8){
								str2_play_idx[a0] = 0;
							}
						}
						if (str2_mono_fg[a0]){
							str2_mono_offset[a0] = 1;
						}
					}
				} else {
					str2_trans_buf[a0][str2_play_offset[a0]+0x7F1] |= 1;
					if (!str2_l_r_fg[a0]){
						sceSdVoiceTrans( 1, 0, str2_trans_buf[a0]+str2_play_offset[a0], (u_char *)(spu_str2_start_ptr_l[a0]), 0x800 );
						str2_l_r_fg[a0] = 1;
					} else {
						str2_next_idx[a0] = (str2_next_idx[a0] + 0x800) & 0xFFF;
						sceSdVoiceTrans( 1, 0, str2_trans_buf[a0]+str2_play_offset[a0], (u_char *)(spu_str2_start_ptr_r[a0]), 0x800 );
						str2_l_r_fg[a0] = 0;
						str2_read_status[a0][str2_play_idx[a0]] = 0;
						str2_play_idx[a0]++;
						if (str2_play_idx[a0] == 8){
							str2_play_idx[a0] = 0;
						}
						if (str2_mono_fg[a0]){
							str2_mono_offset[a0] = 1;
						}
					}
				}
				if (str2_mono_fg[a0]){
					if (str2_mono_offset[a0]){
						str2_play_offset[a0] += 0x800;
						if (str2_play_offset[a0] == 0x8000){
							str2_play_offset[a0] = 0;
						}
						if (str2_unplay_size[a0] > 0x800){
							str2_unplay_size[a0] -= 0x800;
						} else {
							str2_off_ctr[a0] = 0x1F;
							str2_play_offset[a0] = 0;
							str2_status[a0]++;
						}
					}
				} else {
					str2_play_offset[a0] += 0x800;
					if (str2_play_offset[a0] == 0x8000){
						str2_play_offset[a0] = 0;
					}
					if (str2_unplay_size[a0] > 0x800){
						str2_unplay_size[a0] -= 0x800;
					} else {
						str2_off_ctr[a0] = 0x1F;
						str2_play_offset[a0] = 0;
						str2_status[a0]++;
					}
				}
			} else {
				str2_unplay_size[a0] = str2_unload_size[a0];
				str2_mute_fg[a0] = 1;
				if (spu_str2_idx[a0] >= 0x800){
					dummy_data[1] = 6;
					dummy_data[0x7F1] = 2;
					if (!mute2_l_r_fg[a0]){
						sceSdVoiceTrans( 1, 0, dummy_data, (u_char *)(spu_str2_start_ptr_l[a0]), 0x800 );
						mute2_l_r_fg[a0] = 1;
					} else {
						sceSdVoiceTrans( 1, 0, dummy_data, (u_char *)(spu_str2_start_ptr_r[a0]), 0x800 );
						str2_next_idx[a0] = (str2_next_idx[a0] + 0x800) & 0xFFF;
						mute2_l_r_fg[a0] = 1;
					}
				} else {
					dummy_data[1] = 2;
					dummy_data[0x7F1] = 3;
					if (!mute2_l_r_fg[a0]){
						mute2_l_r_fg[a0] = 1;
						sceSdVoiceTrans( 1, 0, dummy_data, (u_char *)(spu_str2_start_ptr_l[a0])+0x800, 0x800 );
					} else {
						mute2_l_r_fg[a0] = 0;
						str2_next_idx[a0] = (str2_next_idx[a0] + 0x800) & 0xFFF;
						sceSdVoiceTrans( 1, 0, dummy_data, (u_char *)(spu_str2_start_ptr_r[a0])+0x800, 0x800 );
					}
				}
			}
		}
		break;
	
	case 4:
		str2_counter[a0] += 0x80;
		if ((str2_off_ctr[a0] -= 1) == -2){
			str2_tr_off(a0);
			str2_status[a0]++;
		}
		break;
	
	case 5:
		str2_counter[a0] += 0x80;
		temp2 = 1;
		break;
	}
	return (temp | temp2);
}

void str2_int( void )
{
	if (sceSdVoiceTransStatus( 1, 0 ) == 1){
		if (Str2SpuTrans( 0 )){
			WakeupThread( id_SdEELoad );
		} else if (Str2SpuTrans(1)){
			WakeupThread( id_SdEELoad );
		}
	}
	str2_spuwr();
}
