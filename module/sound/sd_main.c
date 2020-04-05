/*
 * Sound Driver for PS2 IOP
 * Main Module (Internal)
 */
/* ver."ZONE OF THE ENDERS"
 */
#include <sys/types.h>
#include <kernel.h>
#include <libsd.h>

#include "sd_incl.h"
#include "sd_ext.h"

/*---------------------------------------------------------------------------*/

void SdMain( void )
{
	while( 1 ){
		if( !pak_read_fg ){
			SleepThread();
		} else {
			// Wait for V-blank
			WaitVblankStart();
			WaitVblankEnd();
		}
		if( pak_load_status ){
			LoadPakFile();
		}
		if( sng_load_code ){
			LoadSngData( sng_load_code );
		}
		if( str_status ){
			str_load();
		}
		if( se_load_code ){
			LoadSeFile();
		}
		switch( wave_load_status ){
		case 1:
			if( LoadWaveFile() ){
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

/*---------------------------------------------------------------------------*/

void SdEELoad( void )
{
	while( 1 ){
		SleepThread();
		if( lnr8_status ){
			lnr_load();
		}
		if( str2_status[0] || str2_status[1] ){
			str2_load();
		}
	}
	ExitThread();
}

/*---------------------------------------------------------------------------*/

void SdInt( void )
{
	sd_init();

	while( 1 ){
		SleepThread();
		IntSdMain();
		if( str_status >= 2 ){
			str_int();
		}
		if( str2_status[0] >= 3 || str2_status[1] >= 3 ){
			str2_int();
		}
		if( lnr8_status >= 2 ){
			lnr_int();
		}
		sd_set_status();
		sd_send_status();
	}
	ExitThread();
}

/*---------------------------------------------------------------------------*/

void sd_init( void )
{
	sceSdEffectAttr r_attr;
	int i;

	/* i = SPU CORE ID */
	for( i = 0 ; i < 2 ; i++ ){
		sceSdSetParam( i|SD_P_MVOLL, 0 );
		sceSdSetParam( i|SD_P_MVOLR, 0 );
		sceSdSetSwitch( i|SD_S_PMON, 0 );
		sceSdSetSwitch( i|SD_S_NON, 0 );

		if( i == 0 ){
			sceSdSetParam( i|SD_P_MMIX, 0x0FFF );
			sceSdSetAddr( i|SD_A_EEA, 0x0001FFFF );
		} else {
			sceSdSetParam( i|SD_P_MMIX, 0x0FFC );
			sceSdSetAddr( i|SD_A_EEA, 0x001FFFFF );
		}

		r_attr.depth_L = 0;
		r_attr.depth_R = 0;
		r_attr.mode = SD_REV_MODE_HALL | SD_REV_MODE_CLEAR_WA;

		sceSdSetEffectAttr( i, &r_attr );
		sceSdSetCoreAttr( i|SD_C_EFFECT_ENABLE, SD_SPDIF_OUT_BITSTREAM );
		sceSdSetParam( i|SD_P_EVOLL, 0x2000 );
		sceSdSetParam( i|SD_P_EVOLR, 0x2000 );
		sceSdSetSwitch( i|SD_S_VMIXEL, 0 );
		sceSdSetSwitch( i|SD_S_VMIXER, 0 );

		rev_bit_data[i] = 0;

		sceSdSetParam( i|SD_P_MVOLL, 0x3FFF );
		sceSdSetParam( i|SD_P_MVOLR, 0x3FFF );
	}

	sceSdSetParam( i|SD_P_AVOLL, 0x7FFF );
	sceSdSetParam( i|SD_P_AVOLR, 0x7FFF );
	sceSdSetCoreAttr( SD_C_SPDIF_MODE, SD_SPDIF_COPY_PROHIBIT );

	spu_wave_start_ptr = (u_char *)0x20000;
	init_sng_work();
	wave_load_status = 0;

	for( i = 0 ; i < 12 ; i++ ){
		se_playing[i].code = 0;
	}

	for( i = 0 ; i < 16 ; i++ ){
		mix_fader[i].unk04 = 0xFFFF;
		mix_fader[i].unk08 = 0xFFFF;
		mix_fader[i].unk00 = 0;
		mix_fader[i].unk0C = 0x20;
	}

	for( i = 16 ; i < 32 ; i++ ){
		mix_fader[i].unk04 = 0;
		mix_fader[i].unk08 = 0;
		mix_fader[i].unk00 = 0;
		mix_fader[i].unk0C = 0x20;
	}

	vox_fader[1].unk00 = 0x3F;
	vox_fader[0].unk00 = 0x3F;
	vox_fader[1].unk08 = 0x20;
	vox_fader[0].unk08 = 0x20;
}

/*---------------------------------------------------------------------------*/

void SdTerm( void )
{
	sceSdSetSwitch( SD_CORE_0|SD_S_KOFF, 0x00FFFFFF );
	sceSdSetSwitch( SD_CORE_1|SD_S_KOFF, 0x00FFFFFF );
}

/*---------------------------------------------------------------------------*/

void keyOff( u_int a0 )
{
	if( a0 < 24 ){
		sceSdSetSwitch( SD_CORE_0|SD_S_KOFF, 1 << a0 );
	} else {
		sceSdSetSwitch( SD_CORE_1|SD_S_KOFF, 1 << (a0-24) );
	}
}

/*---------------------------------------------------------------------------*/

void keyOn( u_int a0 )
{
	if( a0 < 24 ){
		sceSdSetSwitch( SD_CORE_0|SD_S_KON, 1 << a0 );
	} else {
		sceSdSetSwitch( SD_CORE_1|SD_S_KON, 1 << (a0-24) );
	}
}

/*---------------------------------------------------------------------------*/

int sd_mem_alloc( void )
{
	voice_tbl = wave_header;
	se_exp_table = (u_char *)se_data_area;
	se_header = (struct SETBL *)(se_exp_table+2048);
	se_data = (u_char *)(se_header)+4096;
	return 0;
}
