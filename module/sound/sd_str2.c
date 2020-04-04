/*
 * Sound Driver for PS2 IOP
 * Stream System Module 2
 */
/* ver."ZONE OF THE ENDERS"
 */
#include <sys/types.h>
#include <kernel.h>
#include <libsd.h>

#include "sd_incl.h"
#include "sd_ext.h"

/*---------------------------------------------------------------------------*/



unsigned short str2_master_vol = 0x3FFF;
unsigned short str2_master_pitch = 0x1000;



unsigned int spu_str2_start_ptr_r[2];
unsigned int str2_iop_load_set[2];
unsigned int str2_wait_fg[2];
unsigned int str2_first_load[2];
unsigned int spu_str2_start_ptr_l[2];
unsigned int str2_off_ctr[2];
int str2_fp[2];
unsigned int str2_mono_fg[2];
unsigned short str2_volume[2];
unsigned int str2_l_r_fg[2];
unsigned int spu_str2_idx[2];
unsigned int str2_load_code[2];
unsigned int ee2_buf_idx[2];
unsigned int str2_play_offset[2];
unsigned int str2_stop_fg[2];
short str2_pitch[2];
unsigned int str2_unload_size[2];
unsigned int str2_mono_offset[2];
unsigned int str2_unplay_size[2];
unsigned int str2_next_idx[2];
unsigned int mute2_l_r_fg[2];
unsigned int str2_play_counter[2];
unsigned int str2_keyoffs;
unsigned int str2_mute_fg[2];
unsigned int str2_counter[2];
unsigned int str2_status[2];
unsigned char *str2_trans_buf[2];
unsigned int str2_play_idx[2];
unsigned int str2_read_disable[2];

u_char eeload2_buf[0x00010000];
u_int str2_read_status[2][8];

/*---------------------------------------------------------------------------*/

void str2_tr_off( u_int a0 )
{
	if( !a0 ){
		str2_keyoffs |= 0x300000;
	} else {
		str2_keyoffs |= 0xC00000;
	}
}

/*---------------------------------------------------------------------------*/

void str2_spuwr( void )
{
	if( str2_keyoffs ){
		sceSdSetSwitch( SD_CORE_1|SD_S_KOFF, str2_keyoffs );
		str2_keyoffs = 0;
	}
}

/*---------------------------------------------------------------------------*/

int StartEEStream( u_int a0 )
{
	int temp, i;

	str2_read_disable[a0] = 0;
	str2_tr_off( a0 );

	if( (str2_fp[a0] = EEOpen(str2_load_code[a0])) < 0 ){
		str2_fp[a0] = str2_first_load[a0] = str2_load_code[a0] = 0;
		str2_iop_load_set[a0] = 0;
		return -1;
	}

	str2_unplay_size[a0] = str2_unload_size[a0] = ee_addr[a0].unk14;
	str2_volume[a0] = 0x7F;
	ee2_buf_idx[a0] = 0;
	temp = EERead( str2_fp[a0], (uint *)(a0*0x8000+eeload2_buf+ee2_buf_idx[a0]*0x4000), ee2_buf_idx[a0], 0x4000 );

	for( i = 0 ; i < 4 ; i++ ){
		str2_read_status[a0][ee2_buf_idx[a0]*4+i] = 1;
	}

	ee2_buf_idx[a0]++;

	if( str2_unload_size[a0] > temp ){
		str2_unload_size[a0] -= temp;
	} else {
		str2_unload_size[a0] = 0;
	}

	for( i = 0 ; i < 4 ; i++ ){
		str2_read_status[a0][ee2_buf_idx[a0]*4+i] = 0;
	}

	str2_trans_buf[a0] = eeload2_buf+a0*0x8000;
	return 0;
}

/*---------------------------------------------------------------------------*/

void StrEELoad( u_int a0 )
{
	int temp, i, j, temp4;

	for( i = 0 ; i < 2 ; i++ ){
		if( str2_unload_size[a0] ){
			temp4 = 0;
			for( j = 0 ; j < 4 ; j++ ){
				temp4 |= str2_read_status[a0][ee2_buf_idx[a0]*4+j];
			}
			if( !temp4 ){
				// Wait for V-blank
				WaitVblankStart();
				WaitVblankEnd();

				if( str2_unload_size[a0] > 0x4000 ){
					temp = EERead( str2_fp[a0], (uint *)(a0*0x8000+eeload2_buf+ee2_buf_idx[a0]*0x4000), ee2_buf_idx[a0], 0x4000 );
					if( temp ){
						for( j = 0 ; j < 4 ; j++ ){
							str2_read_status[a0][ee2_buf_idx[a0]*4+j] = 1;
						}
						ee2_buf_idx[a0] = (ee2_buf_idx[a0]+1) & 1;
						str2_unload_size[a0] -= 0x4000;
					}
				} else {
					temp = EERead( str2_fp[a0], (uint *)(a0*0x8000+eeload2_buf+ee2_buf_idx[a0]*0x4000), ee2_buf_idx[a0], 0x4000 );
					if( temp ){
						for( j = 0 ; j < 4 ; j++ ){
							str2_read_status[a0][ee2_buf_idx[a0]*4+j] = 1;
						}
						ee2_buf_idx[a0] = (ee2_buf_idx[a0]+1) & 1;
						str2_unload_size[a0] = 0;
					}
					break;
				}
			}
		}
	}
}

/*---------------------------------------------------------------------------*/

void str2_load( void )
{
	int i;

	for( i = 0 ; i < 2 ; i++ ){
		switch( str2_status[i]-1 ){
		case 0:
			if( ee_addr[i].unk0C ){
				if( StartEEStream( i ) ){
					str2_status[i] = 0;
				} else {
					str2_l_r_fg[i] = 0;
					str2_status[i] = 2;
				}
			} else {
				//
				// EMPTY BLOCK
				//
			}
			break;

		case 1:
			if( ee_addr[i].unk0C > 1 ){
				StrEELoad( i );
				str2_status[i]++;
			} else {
				//
				// EMPTY BLOCK
				//
			}

		case 2:
		case 3:
		case 4:
		case 5:
			StrEELoad( i );
			break;

		case 6:
			break;

		case 7:
			ee_addr[i].unk10 = (u_char *)ee_addr[i].unk0C = str2_fp[i] = str2_status[i] = str2_load_code[i] = 0;
			break;
		}
	}
}

/*---------------------------------------------------------------------------*/

int Str2SpuTrans( int a0 )
{
	int temp = 0, temp2 = 0, temp3, temp4;

	if( a0 >= 2 ){
		return 0;
	}

	if( str2_stop_fg[a0] && str2_status[a0] >= 3 ){
		switch( str2_stop_fg[a0] ){
		case 1:
			sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_ADSR1, 0x00FF );
			sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_ADSR2, 0x0007 );
			sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_ADSR1, 0x00FF );
			sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_ADSR2, 0x0007 );
			str2_first_load[a0] = 0;
			str2_status[a0] = 8;
			break;

		case 2:
			sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_ADSR1, 0x00FF );
			sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_ADSR2, 0x000D );
			sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_ADSR1, 0x00FF );
			sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_ADSR2, 0x000D );
			break;
		}
		str2_tr_off(a0);
		str2_stop_fg[a0] = 0;

	} else if( str2_stop_fg[a0] && str2_status[a0] ){
		str2_first_load[a0] = 0;
		str2_status[a0] = 8;
		str2_stop_fg[a0] = 0;
	}

/* ///////////////////////////////////////////////////////////////////////// */
	switch( str2_status[a0]-3 ){
	case 0:
		if( !str2_l_r_fg[a0] ){
			str2_play_idx[a0] = 0;
			str2_play_offset[a0] = 0;
			spu_str2_start_ptr_l[a0] = a0 * 0x2000 + 0x5020;
			sceSdSetAddr( SD_CORE_1|(((a0*2)+20)<<1)|SD_VA_LSAX, a0*0x2000+0x5020 );
			sceSdVoiceTrans(
				1,                                    /* transfer channel */
				SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,  /* transfer mode    */
				str2_trans_buf[a0],                   /* IOP memory addr  */
				(u_char *)(spu_str2_start_ptr_l[a0]), /* SPU memory addr  */
				0x0800 );                             /* transfer size    */
			if( !str2_mono_fg[a0] ){
				str2_play_offset[a0] = 0x0800;
				str2_unplay_size[a0] -= 0x0800;
			}
			str2_l_r_fg[a0] = 1;
		} else {
			spu_str2_start_ptr_r[a0] = a0*0x2000+0x6020;
			sceSdSetAddr( SD_CORE_1|(((a0*2)+21)<<1)|SD_VA_LSAX, a0*0x2000+0x6020 );
			sceSdVoiceTrans(
				1,                                       /* transfer channel */
				SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,     /* transfer mode    */
				str2_trans_buf[a0]+str2_play_offset[a0], /* IOP memory addr  */
				(u_char *)(spu_str2_start_ptr_r[a0]),    /* SPU memory addr  */
				0x0800 );                                /* transfer size    */
			str2_play_offset[a0] += 0x0800;
			str2_unplay_size[a0] -= 0x0800;
			if( !str2_mono_fg[a0] ){
				str2_read_status[a0][str2_play_idx[a0]] = 0;
				str2_play_idx[a0]++;
			}
			str2_l_r_fg[a0] = 0;
			str2_counter[a0] += 0x0800;
			str2_status[a0]++;
		}
		temp = 1;
		break;
/* ///////////////////////////////////////////////////////////////////////// */
	case 1:
		if( !str2_unplay_size[a0] || (str2_unplay_size[a0] & 0x80000000) ){
			str2_status[a0]++;
		}
		if( !str2_l_r_fg[a0] ){
			str2_trans_buf[a0][str2_play_offset[a0]+0x07F1] |= 1;
			sceSdVoiceTrans(
				1,                                         /* transfer channel */
				SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,       /* transfer mode    */
				str2_trans_buf[a0]+str2_play_offset[a0],   /* IOP memory addr  */
				(u_char*)(spu_str2_start_ptr_l[a0])+0x800, /* SPU memory addr  */
				0x0800 );                                  /* transfer size    */
			if( !str2_mono_fg[a0] ){
				str2_play_offset[a0] += 0x0800;
				str2_unplay_size[a0] -= 0x0800;
			}
			str2_l_r_fg[a0] = 1;
		} else {
			str2_trans_buf[a0][str2_play_offset[a0]+0x07F1] |= 1;
			sceSdVoiceTrans(
				1,                                         /* transfer channel */
				SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,       /* transfer mode    */
				str2_trans_buf[a0]+str2_play_offset[a0],   /* IOP memory addr  */
				(u_char*)(spu_str2_start_ptr_r[a0])+0x800, /* SPU memory addr  */
				0x0800 );                                  /* transfer size    */
			str2_play_offset[a0] += 0x0800;
			str2_unplay_size[a0] -= 0x0800;
			str2_read_status[a0][str2_play_idx[a0]] = 0;
			str2_play_idx[a0]++;
			str2_l_r_fg[a0] = 0;
			str2_counter[a0] += 0x0800;
			str2_status[a0]++;
		}
		temp = 1;
		break;
/* ///////////////////////////////////////////////////////////////////////// */
	case 2:
		if( str2_first_load[a0] ){
			str2_first_load[a0] = 0;
		}
		if( str2_wait_fg[a0] ){
			break;
		}
		if( sound_mono_fg ){
			temp3 = temp4 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
							* se_pant[64 - vox_fader[a0].unk08]) / 0x7F) * str2_master_vol)
							/ 0x3FFF;
			sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_VOLL, temp3 );
			sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_VOLR, temp4 );
			sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_VOLL, (unsigned)temp3 / 3 );
			sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_VOLR, (unsigned)temp4 / 3 );
			vox_fader[a0].unk04 = vox_fader[a0].unk00;
			vox_fader[a0].unk0C = vox_fader[a0].unk08;
		} else {
			if( str2_mono_fg[a0] ){
				temp3 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
							* se_pant[64 - vox_fader[a0].unk08]) / 0x7F) * str2_master_vol)
							/ 0x3FFF;
				temp4 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
							* se_pant[vox_fader[a0].unk08]) / 0x7F) * str2_master_vol)
							/ 0x3FFF;
				sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_VOLL, temp3 );
				sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_VOLR, temp4 );
				sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_VOLL, (unsigned)temp3 / 3 );
				sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_VOLR, (unsigned)temp4 / 3 );
				vox_fader[a0].unk04 = vox_fader[a0].unk00;
				vox_fader[a0].unk0C = vox_fader[a0].unk08;
			} else {
				temp3 = temp4 = (((unsigned)(str2_volume[a0]
								* se_pant[0xFC] / 0x7F)) * str2_master_vol)
								/ 0x3FFF;
				sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_VOLL, temp3 );
				sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_VOLR, 0 );
				sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_VOLL, 0 );
				sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_VOLR, temp4 );
			}
		}
		sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_PITCH, (u_int)((u_short)str2_pitch[a0]*str2_master_pitch) / 0x1000 );
		sceSdSetAddr( SD_CORE_1|(((a0*2)+20)<<1)|SD_VA_SSA, a0*0x2000+0x5020 );
		sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_ADSR1, 0x00FF );
		sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_ADSR2, 0x0007 );
		sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_PITCH, (u_int)((u_short)str2_pitch[a0]*str2_master_pitch) / 0x1000 );
		sceSdSetAddr( SD_CORE_1|(((a0*2)+21)<<1)|SD_VA_SSA, a0*0x2000+0x6020 );
		sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_ADSR1, 0x00FF );
		sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_ADSR2, 0x0007 );
		if( !a0 ){
			sceSdSetSwitch( SD_CORE_1|SD_S_KON, 0x300000 );
		} else {
			sceSdSetSwitch( SD_CORE_1|SD_S_KON, 0xC00000 );
		}
		mute2_l_r_fg[a0] = 0;
		spu_str2_idx[a0] = 0;
		str2_next_idx[a0] = 0x0800;
		str2_status[a0]++;
		if( str2_unplay_size[a0] || !(str2_unplay_size[a0] & 0x80000000) ){
			str2_off_ctr[a0] = 0x1F;
			str2_status[a0]++;
		}
		break;
/* ///////////////////////////////////////////////////////////////////////// */
	case 3:
		if( sceSdGetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_ENVX ) == 0 ){
			str2_off_ctr[a0] = -1;
			str2_status[a0]++;
			break;
		}
		if((vox_fader[a0].unk00 == vox_fader[a0].unk04)
		|| (vox_fader[a0].unk08 == vox_fader[a0].unk0C)){
			if( sound_mono_fg ){
				temp3 = temp4 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
								* se_pant[0x80]) / 0x7F) * str2_master_vol)
								/ 0x3FFF;
				sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_VOLL, temp3 );
				sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_VOLR, temp4 );
				sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_VOLL, temp3 );
				sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_VOLR, temp4 );
				vox_fader[a0].unk04 = vox_fader[a0].unk00;
				vox_fader[a0].unk0C = vox_fader[a0].unk08;
			} else {
				if( str2_mono_fg[a0] ){
					temp3 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
								* se_pant[0x40 - vox_fader[a0].unk08]) / 0x7F) * str2_master_vol)
								/ 0x3FFF;
					temp4 = (((((unsigned)(str2_volume[a0] * vox_fader[a0].unk00) / 0x3F)
								* se_pant[vox_fader[a0].unk08]) / 0x7F) * str2_master_vol)
								/ 0x3FFF;
					sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_VOLL, temp3 );
					sceSdSetParam( SD_CORE_1|(((a0*2)+20)<<1)|SD_VP_VOLR, temp4 );
					sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_VOLL, temp3 );
					sceSdSetParam( SD_CORE_1|(((a0*2)+21)<<1)|SD_VP_VOLR, temp4 );
					vox_fader[a0].unk04 = vox_fader[a0].unk00;
					vox_fader[a0].unk0C = vox_fader[a0].unk08;
				}
			}
		}
		spu_str2_idx[a0] = sceSdGetAddr( SD_CORE_1|(((a0*2)+20)<<1)|SD_VA_NAX );
		spu_str2_idx[a0] -= 0x5020 + a0 * 0x2000;
		if( spu_str2_idx[a0] >= 0x1000 || (spu_str2_idx[a0] & 0x80000000) ){
			break;
		}
		if( !str2_mute_fg[a0] ){
			str2_play_counter[a0]++;
		}
		if( str2_next_idx[a0] == (spu_str2_idx[a0] & 0x0800) || str2_l_r_fg[a0] || !mute2_l_r_fg[a0] ){
			temp = 1;
			if( str2_read_status[a0][str2_play_idx[a0]] && !mute2_l_r_fg[a0] ){
				str2_mute_fg[a0] = 0;
				if( str2_l_r_fg[a0] ){
					str2_counter[a0] += 0x0800;
				}
				if( str2_mono_fg[a0] ){
					str2_mono_offset[a0] = 0;
				}
				if( spu_str2_idx[a0] >= 0x0800 ){
					if( !str2_l_r_fg[a0] ){
						sceSdVoiceTrans(
							1,                                       /* transfer channel */
							SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,     /* transfer mode    */
							str2_trans_buf[a0]+str2_play_offset[a0], /* IOP memory addr  */
							(u_char *)(spu_str2_start_ptr_l[a0]),    /* SPU memory addr  */
							0x0800 );                                /* transfer size    */
						str2_l_r_fg[a0] = 1;
					} else {
						sceSdVoiceTrans(
							1,                                       /* transfer channel */
							SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,     /* transfer mode    */
							str2_trans_buf[a0]+str2_play_offset[a0], /* IOP memory addr  */
							(u_char *)(spu_str2_start_ptr_r[a0]),    /* SPU memory addr  */
							0x0800 );                                /* transfer size    */
						str2_next_idx[a0] = (str2_next_idx[a0] + 0x0800) & 0x0FFF;
						str2_l_r_fg[a0] = 0;
						if( str2_mono_fg[a0] ){
							str2_read_status[a0][str2_play_idx[a0]] = 0;
							str2_play_idx[a0]++;
							if( str2_play_idx[a0] == 8 ){
								str2_play_idx[a0] = 0;
							}
						}
						if( str2_mono_fg[a0] ){
							str2_mono_offset[a0] = 1;
						}
					}
				} else {
					*(str2_trans_buf[a0]+str2_play_offset[a0]+0x07F1) |= 1;
					if( !str2_l_r_fg[a0] ){
						sceSdVoiceTrans(
							1,                                          /* transfer channel */
							SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,        /* transfer mode    */
							str2_trans_buf[a0]+str2_play_offset[a0],    /* IOP memory addr  */
							(u_char *)(spu_str2_start_ptr_l[a0])+0x800, /* SPU memory addr  */
							0x0800 );                                   /* transfer size    */
						str2_l_r_fg[a0] = 1;
					} else {
						str2_next_idx[a0] = (str2_next_idx[a0] + 0x0800) & 0x0FFF;
						sceSdVoiceTrans(
							1,                                          /* transfer channel */
							SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,        /* transfer mode    */
							str2_trans_buf[a0]+str2_play_offset[a0],    /* IOP memory addr  */
							(u_char *)(spu_str2_start_ptr_r[a0])+0x800, /* SPU memory addr  */
							0x0800 );                                   /* transfer size    */
						str2_l_r_fg[a0] = 0;
						str2_read_status[a0][str2_play_idx[a0]] = 0;
						str2_play_idx[a0]++;
						if( str2_play_idx[a0] == 8 ){
							str2_play_idx[a0] = 0;
						}
						if( str2_mono_fg[a0] ){
							str2_mono_offset[a0] = 1;
						}
					}
				}
				if( str2_mono_fg[a0] ){
					if( str2_mono_offset[a0] ){
						str2_play_offset[a0] += 0x0800;
						if( str2_play_offset[a0] == 0x8000 ){
							str2_play_offset[a0] = 0;
						}
						if( str2_unplay_size[a0] > 0x0800 ){
							str2_unplay_size[a0] -= 0x0800;
						} else {
							str2_off_ctr[a0] = 0x1F;
							str2_play_offset[a0] = 0;
							str2_status[a0]++;
						}
					}
				} else {
					str2_play_offset[a0] += 0x0800;
					if( str2_play_offset[a0] == 0x8000 ){
						str2_play_offset[a0] = 0;
					}
					if( str2_unplay_size[a0] > 0x0800 ){
						str2_unplay_size[a0] -= 0x0800;
					} else {
						str2_off_ctr[a0] = 0x1F;
						str2_play_offset[a0] = 0;
						str2_status[a0]++;
					}
				}
			} else {
				str2_unplay_size[a0] = str2_unload_size[a0];
				str2_mute_fg[a0] = 1;
				if( spu_str2_idx[a0] >= 0x0800 ){
					dummy_data[1] = 6;
					dummy_data[0x07F1] = 2;
					if( !mute2_l_r_fg[a0] ){
						sceSdVoiceTrans(
							1,                                    /* transfer channel */
							SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,  /* transfer mode    */
							dummy_data,                           /* IOP memory addr  */
							(u_char *)(spu_str2_start_ptr_l[a0]), /* SPU memory addr  */
							0x0800 );                             /* transfer size    */
						mute2_l_r_fg[a0] = 1;
					} else {
						sceSdVoiceTrans(
							1,                                    /* transfer channel */
							SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,  /* transfer mode    */
							dummy_data,                           /* IOP memory addr  */
							(u_char *)(spu_str2_start_ptr_r[a0]), /* SPU memory addr  */
							0x0800 );                             /* transfer size    */
						str2_next_idx[a0] = (str2_next_idx[a0] + 0x0800) & 0x0FFF;
						mute2_l_r_fg[a0] = 0;
					}
				} else {
					dummy_data[1] = 2;
					dummy_data[0x07F1] = 3;
					if( !mute2_l_r_fg[a0] ){
						mute2_l_r_fg[a0] = 1;
						sceSdVoiceTrans(
							1,                                           /* transfer channel */
							SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,         /* transfer mode    */
							dummy_data,                                  /* IOP memory addr  */
							(u_char *)(spu_str2_start_ptr_l[a0])+0x0800, /* SPU memory addr  */
							0x0800 );                                    /* transfer size    */
					} else {
						mute2_l_r_fg[a0] = 0;
						str2_next_idx[a0] = (str2_next_idx[a0] + 0x0800) & 0x0FFF;
						sceSdVoiceTrans(
							1,                                           /* transfer channel */
							SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,         /* transfer mode    */
							dummy_data,                                  /* IOP memory addr  */
							(u_char *)(spu_str2_start_ptr_r[a0])+0x0800, /* SPU memory addr  */
							0x0800 );                                    /* transfer size    */
					}
				}
			}
		}
		break;
/* ///////////////////////////////////////////////////////////////////////// */
	case 4:
		str2_counter[a0] += 0x80;
		if( --str2_off_ctr[a0] == -2 ){
			str2_tr_off( a0 );
			str2_status[a0]++;
		}
		break;
/* ///////////////////////////////////////////////////////////////////////// */
	case 5:
		str2_counter[a0] += 0x80;
		temp2 = 1;
		break;
	}
	return (temp | temp2);
}

/*---------------------------------------------------------------------------*/

void str2_int( void )
{
	if( sceSdVoiceTransStatus( 1, SD_TRANS_STATUS_CHECK ) == 1 ){
		if( Str2SpuTrans( 0 ) ){
			WakeupThread( id_SdEELoad );
		} else if( Str2SpuTrans(1) ){
			WakeupThread( id_SdEELoad );
		}
	}
	str2_spuwr();
}
