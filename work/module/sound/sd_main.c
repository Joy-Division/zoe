/*
 * Sound Driver for PS2 IOP
 * Main Module
 *
 * ver.ZONE OF THE ENDERS
 */
#include <sys/types.h>
#include <kernel.h>
#include <libsd.h>
#include "sd_incl.h"

void SdMain( void )
{
	while (1){
		if (!pak_read_fg){
			SleepThread();
		} else {
			WaitVblankStart();
			WaitVblankEnd();
		}
		if (pak_load_status){
			LoadPakFile();
		}
		if (sng_load_code){
			LoadSngData( sng_load_code );
		}
		if (str_status){
			str_load();
		}
		if (se_load_code){
			LoadSeFile();
		}
		switch (wave_load_status){
		case 1:
			if (LoadWaveFile()){
				wave_load_status = 0;
			} else {
				wave_load_status = 2;
			}
			break;
		case 2:
			break;
		case 3:
			WaveCdLoad();
			break;
		}
	}
	SdTerm();
	ExitThread();
}

void SdEELoad( void )
{
	while (1){
		SleepThread();
		if (lnr8_status){
			lnr_load();
		}
		if (str2_status[0] || str2_status[1]){
			str2_load();
		}
	}
	ExitThread();
}

void SdInt( void )
{
	sd_init();
	
	while (1){
		SleepThread();
		IntSdMain();
		if (str_status >= 2){
			str_int();
		}
		if (str2_status[0] >= 3 || str2_status[1] >= 3){
			str2_int();
		}
		if (lnr8_status >= 2){
			lnr_int();
		}
		sd_set_status();
		sd_send_status();
	}
	ExitThread();
}

void sd_init( void )
{
	sceSdEffectAttr attr;
	u_int i;
	
	for (i = 0 ; i < 2 ; i++){
		sceSdSetParam( i | 0x980, 0 );
		sceSdSetParam( i | 0xA80, 0 );
		sceSdSetParam( i | 0x1300, 0 );
		sceSdSetParam( i | 0x1400, 0 );
		
		if (i == 0){
			sceSdSetParam( i | 0x800, 0x0FFF );
			sceSdSetAddr( i | 0x1D00, (u_int)(mem_str_buf+0x191F) );
		} else {
			sceSdSetParam( i | 0x800, 0x0FFC );
			sceSdSetAddr( i | 0x1D00, 0x1FFFFF );
		}
		
		attr.depth_L = 0;
		attr.depth_R = 0;
		attr.mode = 0x105;
		
		sceSdSetEffectAttr( i, &attr );
		sceSdSetCoreAddr( i | 2, 1 );
		sceSdSetParam( i | 0x0B80, 0x2000 );
		sceSdSetParam( i | 0x0C80, 0x2000 );
		sceSdSetSwitch( i | 0x1900, 0 );
		sceSdSetSwitch( i | 0x1B00, 0 );
		
		rev_bit_data[i] = 0;
		
		sceSdSetParam( i | 0x0980, 0x3FFF );
		sceSdSetParam( i | 0x0A80, 0x3FFF );
	}
	
	sceSdSetParam(i | 0xD80, 0x7FFF);
	sceSdSetParam(i | 0xE80, 0x7FFF);
	sceSdSetCoreAddr(0xA, 0x80);
	
	spu_wave_start_ptr[0] = 2;
	init_sng_work();
	wave_load_status = 0;
	
	for (i = 0 ; i < 0xC ; i++){
		mix_fader[i].unk04 = 0xFFFF;
		mix_fader[i].unk08 = 0xFFFF;
		mix_fader[i].unk00 = 0;
		mix_fader[i].unk0C = 0x20;
	}
	
	for (i = 0x10 ; i < 0x20 ; i++){
		// EMPTY
	}
	
	vox_fader[1].unk00 = 0x3F;
	vox_fader[0].unk00 = 0x3F;
	vox_fader[1].unk08 = 0x3F;
	vox_fader[1].unk08 = 0x3F;
}

void SdTerm( void )
{
	sceSdSetSwitch( 0x1600, 0x00FFFFFF );
	sceSdSetSwitch( 0x1601, 0x00FFFFFF );
}

void keyOff( u_int a0 )
{
	if (a0 < 0x18){
		sceSdSetSwitch( 0x1600, 1 << a0 );
	} else {
		sceSdSetSwitch( 0x1601, 1 << (a0-0x18) );
	}
}

void keyOn( u_int a0 )
{
	if (a0 < 0x18){
		sceSdSetSwitch( 0x1500, 1 << a0 );
	} else {
		sceSdSetSwitch( 0x1501, 1 << (a0-0x18) );
	}
}

// TODO: recheck the memory referenced here,
// find structs (if any) and correct types for pointers
// casts here are mostly done to simplify arithmetic
int sd_mem_alloc( void )
{
	voice_tbl = wave_header;
	se_exp_table = (u_int *)se_data_area;
	se_header = (u_char *)(se_exp_table)+0x800;
	se_data = (u_char *)(se_header)+0x1000;
	return 0;
}
