/*
 * Sound Driver for PS2 IOP
 * Stream System Module 3
 *
 * ver."ZONE OF THE ENDERS"
 */
#include <sys/types.h>
#include <kernel.h>
#include <libsd.h>

#include "sd_incl.h"
#include "sd_ext.h"

/*---------------------------------------------------------------------------*/

unsigned int lnr8_read_idx;
unsigned short lnr_volume;
unsigned int lnr8_play_ofst;
unsigned int lnr8_load_code;
unsigned int lnr_keyoffs;
unsigned int lnr8_first_load;
unsigned short lnr_val[2];
unsigned char *lnr8_trans_buf;
unsigned int lnr8_play_idx;
unsigned int lnr16_next_ofst;
unsigned int lnr8_unload_size;
int lnr8_off_ctr;
unsigned int lnr8_fade_vol;
int lnr8_fp;
unsigned int lnr8_wave_size;
unsigned int lnr8_unplay_size;
unsigned int lnr8_stop_fg;
unsigned int spu_lnr16_idx;
unsigned int lnr8_read_disable;
unsigned int lnr8_counter;
unsigned int lnr8_status;

u_short lnr16_buf[0x0800];
u_int lnr8_read_status[32];
u_char lnr8_buf[0x8000];

/*---------------------------------------------------------------------------*/

void lnr_tr_off( void )
{
	lnr_keyoffs = 1;
}

/*---------------------------------------------------------------------------*/

void lnr_spuwr( void )
{
	if( lnr_keyoffs ){
		sceSdBlockTrans( 1, 2, 0, 0 );
		sceSdSetParam( 0x0F81, 0 );
		sceSdSetParam( 0x1081, 0 );
		lnr_keyoffs = 0;
	}
}

/*---------------------------------------------------------------------------*/

int StartLnrEEStream( void )
{
	int temp, i;
	
	lnr8_read_disable = 0;
	lnr8_fp = EEOpen( lnr8_load_code );
	
	if( lnr8_fp < 0 ){
		lnr8_load_code = 0;
		lnr8_first_load = 0;
		lnr8_fp = 0;
		return -1;
	}
	
	lnr8_wave_size = lnr8_unplay_size = lnr8_unload_size = ee_addr[24].unk14;
	lnr_volume = 0x7F;
	lnr8_read_idx = 0;
	temp = EERead( lnr8_fp, (u_int *)(lnr8_buf+lnr8_read_idx*0x4000), lnr8_read_idx, 0x4000 );
	
	for( i = 0 ; i < 16 ; i++ ){
		lnr8_read_status[lnr8_read_idx*16+i] = 1;
	}
	
	lnr8_read_idx++;
	
	if( temp < lnr8_unload_size ){
		lnr8_unload_size -= temp;
	} else {
		lnr8_unload_size = 0;
	}
	
	if( lnr8_unload_size ){
		temp = EERead( lnr8_fp, (u_int *)(lnr8_buf+lnr8_read_idx*0x4000), lnr8_read_idx, 0x4000 );
		
		for( i = 0 ; i < 16 ; i++ ){
			lnr8_read_status[lnr8_read_idx*16+i] = 1;
		}
		
		lnr8_read_idx = (lnr8_read_idx+1) & 1;
		
		if( temp < lnr8_unload_size ){
			lnr8_unload_size -= temp;
		} else {
			lnr8_unload_size = 0;
		}
	}
	
	lnr8_trans_buf = lnr8_buf;
	return 0;
}

/*---------------------------------------------------------------------------*/

// FIXME
// control flow is not 100% certain
void LnrEELoad( void )
{
	int temp, i, j, temp4;
	
	if( lnr8_status < 3 || lnr8_status > 5 ){
		return;
	}
	
	for( i = 0 ; i < 2 ; i++ ){
		if( lnr8_unload_size ){
			temp4 = 0;
			for( j = 0 ; j < 16 ; j++ ){
				temp4 |= lnr8_read_status[lnr8_read_idx*16+j];
			}
			if( !temp4 ){
				// Wait for 1 V-blank
				WaitVblankStart();
				WaitVblankEnd();
				
				if( lnr8_unload_size > 0x4000 ){
					temp = EERead( lnr8_fp, (u_int *)(lnr8_buf+lnr8_read_idx*0x4000), lnr8_read_idx, 0x4000 );
					if( temp ){
						for( j = 0 ; j < 16 ; j++ ){
							lnr8_read_status[lnr8_read_idx*16+j] = 1;
						}
						lnr8_read_idx = (lnr8_read_idx+1) & 1;
						lnr8_unload_size -= 0x4000;
					}
				} else {
					temp = EERead( lnr8_fp, (u_int *)(lnr8_buf+lnr8_read_idx*0x4000), lnr8_read_idx, 0x4000 );
					if( temp ){
						for( j = 0 ; j < 16 ; j++ ){
							lnr8_read_status[lnr8_read_idx*16+j] = 1;
						}
						lnr8_read_idx = (lnr8_read_idx+1) & 1;
						lnr8_unload_size = 0;
					}
					break;
				}
			}
		}
	}
}

/*---------------------------------------------------------------------------*/

void lnr_load( void )
{
	switch( lnr8_status-1 ){
	case 0:
		if( ee_addr[6].unk0C < 2 || (ee_addr[6].unk0C && ee_addr[6].unk14 > 0x4000) ){
			if( StartLnrEEStream() ){
				lnr8_status = 0;
			} else {
				lnr8_status = 2;
			}
		}
		break;
	
	case 1:
	case 2:
	case 3:
	case 4:
		LnrEELoad();
		break;
	
	case 5:
		break;
	
	case 6:
		lnr8_load_code = 0;
		lnr8_status = 0;
		lnr8_fp = 0;
		break;
	}
}

/*---------------------------------------------------------------------------*/

void lnr_trans_init( void )
{
	lnr_val[1] = 0;
	lnr_val[0] = 0;
}

/*---------------------------------------------------------------------------*/

void lnr_trans_0( u_short *a0, u_int a1 )
{
	int i;
	
	for( i = 0 ; i < a1 ; i++ ){
		a0[i] = 0;
	}
}

/*---------------------------------------------------------------------------*/

void lnr_trans( u_short *a0, char *a1, u_int a2 )
{
	int j, i;
	u_short temp3, temp4;
	
	temp3 = lnr_val[0];
	temp4 = lnr_val[1];
	
	for( i = 0 ; i < a2 ; i+=512 ){
		for( j = 0 ; j < 0x0100 ; j++ ){
			// the second LHS needs to be computed this way to produce matching assembly
			temp3 = *(a0+j+i) = ((short)(((a1[0] & 0xF8) * 256)) >> ((char)((u_char *)a1)[0] & 0x07))+temp3;
			a1++;
			temp4 = *(a0+j+i+0x100) = ((short)(((a1[0] & 0xF8) * 256)) >> ((char)((u_char *)a1)[0] & 0x07))+temp4;
			a1++;

		}
	}
	lnr_val[0] = temp3;
	lnr_val[1] = temp4;
}

/*---------------------------------------------------------------------------*/

int lnrSpuTrans( void )
{
	int temp = 0, temp2 = 0;
	
	if( lnr8_stop_fg && lnr8_status >= 2 ){
		lnr8_status = 7;
		lnr_tr_off();
		lnr8_stop_fg = 0;
	}

/* ///////////////////////////////////////////////////////////////////////// */
	switch( lnr8_status-2 ){
	case 0:
		lnr8_play_idx = 0;
		lnr8_play_ofst = 0;
		lnr_trans_init();
		lnr_trans( lnr16_buf, lnr8_trans_buf, 0x0400 );
		lnr8_play_ofst = 0x0400;
		lnr8_unplay_size -= 0x0400;
		lnr8_read_status[lnr8_play_idx] = 0;
		lnr8_play_idx++;
		lnr8_counter += 512;
		lnr8_status++;
		temp = 1;
		break;
/* ///////////////////////////////////////////////////////////////////////// */
	case 1:
		if( !lnr8_unplay_size || (lnr8_unplay_size & 0x80000000) ){
			lnr8_status++;
		}
		lnr_trans( lnr16_buf+0x0400, lnr8_trans_buf+lnr8_play_ofst, 0x0400 );
		lnr8_play_ofst += 0x0400;
		lnr8_unplay_size -= 0x0400;
		lnr8_read_status[lnr8_play_idx] = 0;
		lnr8_play_idx++;
		lnr8_counter += 512;
		lnr8_status++;
		temp = 1;
		break;
/* ///////////////////////////////////////////////////////////////////////// */
	case 2:
		if( lnr8_first_load ){
			lnr8_first_load = 0;
		}
		if( str2_wait_fg[1] ){
			// EMPTY BLOCK
			break;
		}
		lnr8_fade_vol = 1;
		sceSdSetParam( 0x0F81, lnr8_fade_vol * 32767 / 2 );
		sceSdSetParam( 0x1081, lnr8_fade_vol * 32767 / 2 );
		lnr8_fade_vol++;
		sceSdBlockTrans( 1, 16, (u_char *)lnr16_buf, 0x1000 );
		lnr16_next_ofst = 0x0800;
		lnr8_status++;
		if( !lnr8_unplay_size || (lnr8_unplay_size & 0x80000000) ){
			lnr8_off_ctr = lnr8_wave_size >> 9;
			lnr8_status++;
		}
		break;
/* ///////////////////////////////////////////////////////////////////////// */
	case 3:
		if( lnr8_fade_vol < 3 ){
			sceSdSetParam( 0x0F81, lnr8_fade_vol * 32767 / 2 );
			sceSdSetParam( 0x1081, lnr8_fade_vol * 32767 / 2 );
			lnr8_fade_vol++;
		}
		spu_lnr16_idx = sceSdBlockTransStatus( 1, 0 );
		spu_lnr16_idx = (spu_lnr16_idx & 0x00FFFFFF) - (u_int)lnr16_buf;
		if( (spu_lnr16_idx >= 0x1000) || (spu_lnr16_idx == 0x80000000) ){
			break;
		}
		if( lnr16_next_ofst == (spu_lnr16_idx & 0x0800) ){
			temp = 1;
			if( lnr8_read_status[lnr8_play_idx] ){
				lnr_trans( lnr16_buf+((~(spu_lnr16_idx / 0x0800) & 1)*0x0400), lnr8_trans_buf+lnr8_play_ofst, 0x0400 );
				lnr8_play_ofst += 0x0400;
				if( lnr8_play_ofst == 0x8000 ){
					lnr8_play_ofst = 0;
				}
				if( lnr8_unplay_size > 0x0400 ){
					lnr8_unplay_size -= 0x0400;
				} else {
					lnr8_off_ctr = 64;
					lnr8_play_ofst = 0;
					lnr8_status++;
				}
				lnr8_read_status[lnr8_play_idx] = 0;
				lnr8_play_idx++;
				if( lnr8_play_idx == 32 ){
					lnr8_play_idx = 0;
				}
				lnr8_counter += 512;
				lnr16_next_ofst = (lnr16_next_ofst+0x0800) & 0x0FFF;
			} else {
				lnr_trans_0( lnr16_buf+((~(spu_lnr16_idx / 0x0800) & 1)*0x0400), 0x0400 );
				lnr16_next_ofst = (lnr16_next_ofst+0x800) & 0x0FFF;
			}
		}
		break;
/* ///////////////////////////////////////////////////////////////////////// */
	case 4:
		spu_lnr16_idx = sceSdBlockTransStatus( 1, 0 );
		spu_lnr16_idx = (spu_lnr16_idx & 0x00FFFFFF) - (u_int)lnr16_buf;
		if( (spu_lnr16_idx >= 0x1000) || (spu_lnr16_idx & 0x80000000) ){
			break;
		}
		if( lnr16_next_ofst == (spu_lnr16_idx & 0x0800) ){
			lnr_trans_0( lnr16_buf+((~(spu_lnr16_idx / 0x0800) & 1)*0x0400), 0x0400 );
			lnr16_next_ofst = (lnr16_next_ofst+0x0800) & 0x0FFF;
		}
		lnr8_counter += 512;
		if( --lnr8_off_ctr == -2 ){
			lnr8_status++;
		}
		break;
/* ///////////////////////////////////////////////////////////////////////// */
	case 5:
		lnr8_counter += 512;
		temp2 = 1;
		break;
	}
	return (temp | temp2);
}

/*---------------------------------------------------------------------------*/

void lnr_int( void )
{
	if( sceSdVoiceTransStatus( 1, SD_TRANS_STATUS_CHECK ) == 1 ){
		if( lnrSpuTrans() ){
			WakeupThread( id_SdEELoad );
		}
	}
	lnr_spuwr();
}

/*---------------------------------------------------------------------------*
 * END OF FILE
 *---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=euc-jp : */
