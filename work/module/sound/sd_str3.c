/*
 * Sound Driver for PS2 IOP
 * Stream System Module 3
 *
 * ver.ZONE OF THE ENDERS
 */
#include <sys/types.h>
#include <kernel.h>
#include <libsd.h>
#include "sd_incl.h"

void lnr_tr_off( void )
{
	lnr_keyoffs = 1;
}

void lnr_spuwr( void )
{
	if (lnr_keyoffs){
		sceSdBlockTrans( 1, 2, 0, 0 );
		sceSdSetProgram( 0x0F81, 0 );
		sceSdSetParam( 0x1081, 0 );
		lnr_keyoffs = 0;
	}
}

int StartLnrEEStream( void )
{
	int temp, temp2;
	
	lnr8_read_disable = 0;
	lnr8_fp = EEOpen(lnr8_load_code);
	
	if (lnr8_fp < 0){
		lnr8_load_code = 0;
		lnr8_first_load = 0;
		lnr8_fp = 0;
		return -1;
	}
	
	lnr8_wave_size = lnr8_unplay_size = lnr8_unload_size = ee_addr[24].unk14;
	lnr_volume = 0x7F;
	lnr8_read_idx = 0;
	temp = EERead( lnr8_fp, lnr8_buf+lnr8_read_idx*0x4000, lnr8_read_idx, 0x4000 );
	
	for (temp2 = 0 ; temp2 < 0x10 ; temp2++){
		lnr8_read_status[lnr8_read_idx*16+temp2] = 1;
	}
	
	lnr8_read_idx++;
	
	if (temp < lnr8_unload_size){
		lnr8_unload_size -= temp;
	} else {
		lnr8_unload_size = 0;
	}
	
	if (lnr8_unload_size){
		temp = EERead( lnr8_fp, lnr8_buf+lnr8_read_idx*0x4000, lnr8_read_idx, 0x4000 );
		
		for (temp2 = 0 ; temp2 < 0x10 ; temp2++){
			lnr8_read_status[lnr8_read_idx*16+temp2] = 1;
		}
		
		lnr8_read_idx = lnr8_read_idx+1 & 1;
		
		if (temp < lnr8_unload_size){
			lnr8_unload_size -= temp;
		} else {
			lnr8_unload_size = 0;
		}
	}
	
	lnr8_trans_buf = lnr8_buf;
	return 0;
}

// FIXME
// control flow is not 100% certain
void LnrEELoad( void )
{
	int temp, temp2, temp3, temp4;
	
	if (lnr8_status < 3 || lnr8_status > 5){
		// EMPTY
	} else {
		for (temp2 = 0 ; temp2 < 2 ; temp2++){
			if (lnr8_unload_size){
				temp4 = 0;
				for (temp3 = 0 ; temp3 < 0x10 ; temp3++){
					temp4 |= lnr8_read_status[lnr8_read_idx*16+temp2];
				}
				if (!temp4){
					// wait for 1 vblank
					WaitVblankStart();
					WaitVblankEnd();
					
					if (lnr8_unload_size > 0x4000){
						temp = EERead( lnr8_fp, lnr8_buf+lnr8_read_idx*0x4000, lnr8_read_idx, 0x4000 );
						if (temp){
							for (temp3 = 0 ; temp3 < 0x10 ; temp3++){
								lnr8_read_status[lnr8_read_idx*16+temp2] = 1;
							}
							lnr8_read_idx = lnr8_read_idx+1 & 1;
							lnr8_unload_size -= 0x4000;
						}
					} else {
						temp = EERead( lnr8_fp, lnr8_buf+lnr8_read_idx*0x4000, lnr8_read_idx, 0x4000 );
						if (temp){
							for (temp3 = 0 ; temp3 < 0x10 ; temp3++){
								lnr8_read_status[lnr8_read_idx*16+temp2] = 1;
							}
							lnr8_read_idx = lnr8_read_idx+1 & 1;
							lnr8_unload_size = 0;
						}
					}
				}
			}
		}
	}
}

void lnr_load( void )
{
	switch (lnr8_status-1){
	case 0:
		if (ee_addr[6].unk0C < 2 || (ee_addr[6].unk0C && ee_addr[6].unk14 > 0x4000)){
			if (StartLnrEEStream()){
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

void lnr_trans_init( void )
{
	lnr_val[1] = 0;
	lnr_val[0] = 0;
}

void lnr_trans_0( u_short *a0, u_int a1 )
{
	int temp;
	
	for (temp = 0 ; temp < a1 ; temp++){
		a0[temp] = 0;
	}
}

void lnr_trans( u_short *a0, char *a1, u_int a2 )
{
	int temp, temp2;
	u_short temp3, temp4;
	
	temp3 = lnr_val[0];
	temp4 = lnr_val[1];
	
	for (temp2 = 0 ; temp2 < a2 ; temp2+=0x200){
		for (temp = 0 ; temp < 0x100 ; temp++){
			// FIXME
			// this statement might be wrong
			temp3 = a0[(temp<<1)+temp2] = ((short)(((a1[0] & 0xF8) * 256)) >> ((char)((u_char *)a1)[0] & 0x7))+temp3;
			a1++;
			temp4 = a0[(temp<<1)+temp2+0x100] = ((short)(((a1[0] & 0xF8) * 256)) >> ((char)((u_char *)a1)[0] & 0x7))+temp4;
			a1++;

		}
	}
	lnr_val[0] = temp3;
	lnr_val[1] = temp4;
}

int lnrSpuTrans( void )
{
	int temp = 0, temp2 = 0;
	
	if (lnr8_stop_fg && lnr8_status >= 2){
		lnr8_status = 7;
		lnr_tr_off();
		lnr8_stop_fg = 0;
	}
	
	switch (lnr8_status-2){
	case 0:
		lnr8_play_idx = 0;
		lnr8_play_ofst = 0;
		lnr_trans_init();
		lnr_trans(lnr16_buf, lnr8_trans_buf, 0x400);
		lnr8_play_ofst = 0x400;
		lnr8_unplay_size -= 0x400;
		lnr8_read_status[lnr8_play_idx] = 0;
		lnr8_play_idx++;
		lnr8_counter += 0x200;
		lnr8_status++;
		temp = 1;
		break;
	
	case 1:
		if (!lnr8_unplay_size || (lnr8_unplay_size & 0x80000000)){
			lnr8_status++;
		}
		lnr_trans(lnr16_buf+0x400, lnr8_trans_buf+lnr8_play_ofst, 0x400);
		lnr8_play_ofst += 0x400;
		lnr8_unplay_size -= 0x400;
		lnr8_read_status[lnr8_play_idx] = 0;
		lnr8_play_idx++;
		lnr8_counter += 0x200;
		lnr8_status++;
		temp = 1;
		break;
	
	case 2:
		if (lnr8_first_load){
			lnr8_first_load = 0;
		}
		if (str2_wait_fg[1]){
		} else {
			lnr8_fade_vol = 1;
			sceSdSetParam( 0xF81, lnr8_fade_vol * 32767 / 2 );
			sceSdSetParam( 0x1081, lnr8_fade_vol * 32767 / 2 );
			lnr8_fade_vol++;
			sceSdBlockTrans( 1, 0x10, (u_char *)lnr16_buf, 0x1000 );
			lnr16_next_ofst = 0x800;
			lnr8_status++;
			if (!lnr8_unplay_size || (lnr8_unplay_size & 0x80000000)){
				lnr8_off_ctr = lnr8_wave_size >> 9;
				lnr8_status++;
			}
		}
		break;
	
	case 3:
		if (lnr8_fade_vol < 3){
			sceSdSetParam( 0xF81, lnr8_fade_vol * 32767 / 2 );
			sceSdSetParam( 0x1081, lnr8_fade_vol * 32767 / 2 );
			lnr8_fade_vol++;
		}
		spu_lnr16_idx = sceSdBlockTransStatus(1, 0);
		spu_lnr16_idx = (spu_lnr16_idx & 0xFFFFFF) - (u_int)lnr16_buf;
		if ((spu_lnr16_idx < 0x1000) || (spu_lnr16_idx == 0x80000000)){
			break;
		}
		if ((spu_lnr16_idx & 0x800) == lnr16_next_ofst){
			temp = 1;
			if (lnr8_read_status[lnr8_play_idx]){
				lnr_trans( lnr16_buf+((-(spu_lnr16_idx / 0x800))*0x400), lnr8_trans_buf+lnr8_play_ofst, 0x400 );
				lnr8_play_ofst += 0x400;
				if (lnr8_play_ofst == 0x8000){
					lnr8_play_ofst = 0;
				}
				if (lnr8_unplay_size > 0x400){
					lnr8_unplay_size -= 0x400;
				} else {
					lnr8_off_ctr = 0x40;
					lnr8_play_ofst = 0;
					lnr8_status++;
				}
				lnr8_read_status[lnr8_play_idx] = 0;
				lnr8_play_idx++;
				if (lnr8_play_idx == 0x20){
					lnr8_play_idx = 0;
				}
				lnr8_counter += 0x200;
				lnr16_next_ofst = (lnr16_next_ofst+0x800) & 0xFFF;
			} else {
				lnr_trans_0(lnr16_buf+((-(spu_lnr16_idx / 0x800))*0x400), 0x400);
				lnr16_next_ofst = (lnr16_next_ofst+0x800) & 0xFFF;
			}
		}
		break;
	
	case 4:
		spu_lnr16_idx = sceSdBlockTransStatus(1, 0);
		spu_lnr16_idx = (spu_lnr16_idx & 0xFFFFFF) - (u_int)lnr16_buf;
		if ((spu_lnr16_idx < 0x1000) || (spu_lnr16_idx == 0x80000000)){
			break;
		}
		if ((spu_lnr16_idx & 0x800) == lnr16_next_ofst){
			lnr_trans_0(lnr16_buf+((-(spu_lnr16_idx / 0x800))*0x400), 0x400);
			lnr16_next_ofst = (lnr16_next_ofst+0x800) & 0xFFF;
		}
		lnr8_counter += 0x200;
		lnr8_off_ctr--;
		if (lnr8_off_ctr == -2){
			lnr8_status++;
		}
		break;
	
	case 5:
		lnr8_counter += 0x200;
		temp2 = 1;
		break;
	}
	return (temp | temp2);
}

void lnr_int( void )
{
	if (sceSdVoiceTransStatus( 1, 0 ) == 1){
		if (lnrSpuTrans()){
			WakeupThread( id_SdEELoad );
		}
	}
	lnr_spuwr();
}
