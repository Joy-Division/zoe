/*
 * Sound Driver for PS2 IOP
 * File Format Handler
 *
 * ver.ZONE OF THE ENDERS
 */
#include <sys/types.h>
#include <stdio.h>
#include <kernel.h>
#include "sd_incl.h"
#include "sd_ext.h"

static unsigned int pakcd_pos;

u_int pak_cd_read_fg = 0;
u_int save_wvx1 = -1, save_wvx2 = -1;
u_int save_efx = -1;
u_int save_mdx = -1;

void LoadPakFile( void )
{
	u_int *temp = pak_header;
	
	switch( pak_load_status-1 ){
	case 0:
		if( pak_read_fg ){
			if( pak_fp ){
				PcmClose( pak_fp );
				pak_fp = 0;
		}
			pak_read_fg = 0;
		}
		pak_fp = PcmOpen( pak_load_code, 5 );
		if( pak_fp < 0 ){
			
			// wait for 4 vblanks
			WaitVblankStart(); WaitVblankEnd();
			WaitVblankStart(); WaitVblankEnd();
			WaitVblankStart(); WaitVblankEnd();
			WaitVblankStart(); WaitVblankEnd();
			
			pak_load_code = 0;
			pak_fp = 0;
			pak_load_status = 0;
			break;
		} else {
			// EMPTY
		}
		pak_read_fg = 1;
		PcmRead( pak_fp, pak_header, 0x0800 );
		if( temp[0] ){
			if( temp[1] != save_wvx1 && temp[1] != save_wvx2 ){
				d1E0E4[0] = (temp[2] - temp[0]) << 11;
				save_wvx1 = temp[1];
				wave_load_code = 0xFEFFFFFE;
				wave_load_status = 1;
				pak_load_status = 2;
			} else {
				PcmLseek( pak_fp, (temp[2] - temp[0]) << 11, 1 );
				pak_load_status = 3;
			}
		} else {
			pak_load_status = 9;
		}
		break;
	
	case 1:
		if( !wave_load_status ){
			pak_load_status = 3;
		}
		break;
	
	case 2:
		if( temp[2] ){
			if( temp[3] != save_wvx1 && temp[3] != save_wvx2 ){
				d1E0E4[0] = (temp[4] - temp[2]) << 11;
				save_wvx2 = temp[3];
				wave_load_code = 0xFEFFFFFF;
				wave_load_status = 1;
				pak_load_status = 4;
			} else {
				PcmLseek( pak_fp, (temp[4] - temp[2]) << 11, 1 );
				pak_load_status = 4;
			}
		} else {
			pak_load_status = 9;
		}
		break;
	
	case 3:
		if( !wave_load_status ){
			pak_load_status = 5;
		}
		break;
	
	case 4:
		if( temp[4] ){
			if( temp[5] != save_efx ){
				save_efx = temp[5];
				se_load_code = 0x02FFFFFF;
				PcmRead( pak_fp, se_exp_table, (temp[6] - temp[4]) << 11 );
				se_load_code = 0;
			} else {
				PcmLseek( pak_fp, (temp[6] - temp[4]) << 11, 1 );
			}
		} else {
			// EMPTY
		}
		pak_load_status = 6;
		break;
	
	case 5:
		if( temp[6] ){
			if( temp[7] != save_mdx ){
				save_mdx = temp[7];
				d1E0E4[1] = 0x010000FF;
				pak_load_status = 7;
			} else {
				pak_load_status = 9;
			}
		} else {
			pak_load_status = 9;
		}
		break;
	
	case 6:
		if( d1E0E4[1] ){
			break;
		} else {
			pak_load_status = 8;
		}
		break;
	
	case 7:
		if( sng_load_code ){
			break;
		} else {
			pak_load_status = 9;
		}
		break;
	
	case 8:
		pak_read_fg = 0;
		PcmClose( pak_fp );
		pak_fp = 0;
		pak_load_status = 0;
		break;
	}
}

char *sd_path_sd1[6] = {
    "\\DUMMY\\",
    "host0:./sound/vox1/",
    "host0:./sound/wvx1/",
    "host0:./sound/mdx1/",
    "host0:./sound/efx1/",
    "host0:./sound/sdx1/"
};

int LoadSeFile( void )
{
	if( se_fp ){
		PcmClose( se_fp );
		se_fp = 0;
	}
	
	se_fp = PcmOpen( se_load_code, 4 );
	
	if( se_fp < 0 ){
		se_load_code = 0;
		se_fp = 0;
		return -1;
	}
	
	PcmRead( se_fp, se_exp_table, 0x4800 );
	PcmClose( se_fp );
	
	se_load_code = 0;
	se_fp = 0;
	return 0;
}

int LoadSngData()
{
	int temp;
	
	sng_fp = PcmOpen( sng_load_code, 3 );
	
	if( sng_fp < 0 ){
		sng_load_code = 0;
		sng_fp = 0;
		return -1;
	}
	
	temp = PcmRead( sng_fp, sng_data, 2 );
	
	PcmClose( sng_fp );
	
	sng_load_code = 0;
	sng_fp = 0;
	return 0;
}

void set_voice_tbl( u_int *a0, u_int a1, u_int a2 )
{
	int temp, temp2;
	u_int temp3 = 0, temp4;
	
	temp = -1;
	
	for( temp4 = a2 >> 4 ; (a1 >> 4) < temp4 ; temp4++ ){
		temp2 = a0[temp4];
		if( !temp3 && (temp2 < temp) ){
			temp3 = 1;
			break;
		} else {
			temp = temp2;
		}
	}
	
	memcpy( (u_char *)voice_tbl + a2, a0, temp4 * 16 );
	
	if( temp3 ){
		memcpy( drum_tbl, temp4*4 + a0, temp4*4 - a1 );
	}
}

int LoadWaveFile( void )
{
	u_int temp, temp2, temp3, temp4;
	
	if( wave_fp ){
		PcmClose( wave_fp );
	}
	
	wave_fp = PcmOpen( wave_load_code, 2 );
	
	if( wave_fp < 0 ){
		wave_fp = 0;
		
		// wait for 4 vblanks
		WaitVblankStart(); WaitVblankEnd();
		WaitVblankStart(); WaitVblankEnd();
		WaitVblankStart(); WaitVblankEnd();
		WaitVblankStart(); WaitVblankEnd();
		
		wave_load_code = 0;
		return -1;
	}
	
	if( wave_load_code < 0xFEFFFFFD ){
		temp = 0x00018000;
	} else if( d1E0E4[0] < 0x00017FFF ){
		temp = d1E0E4[0];
	} else {
		temp = 0x00018000;
	}
	
	PcmRead( wave_fp, cdload_buf, temp );
	
	temp4 =  cdload_buf[0] << 24;
	temp4 |= cdload_buf[1] << 16;
	temp4 |= cdload_buf[2] << 8;
	temp4 |= cdload_buf[3];
	
	temp3 =  cdload_buf[4] << 24;
	temp3 |= cdload_buf[5] << 16;
	temp3 |= cdload_buf[6] << 8;
	temp3 |= cdload_buf[7];

	wave_load_ptr = cdload_buf+16;
	set_voice_tbl( (u_int *)wave_load_ptr, temp3, temp4 );
	wave_load_ptr += temp3;

	spu_load_offset =  wave_load_ptr[0] << 24;
	spu_load_offset |= wave_load_ptr[1] << 16;
	spu_load_offset |= wave_load_ptr[2] << 8;
	spu_load_offset |= wave_load_ptr[3];
	
	wave_unload_size =  wave_load_ptr[4] << 24;
	wave_unload_size |= wave_load_ptr[5] << 16;
	wave_unload_size |= wave_load_ptr[6] << 8;
	wave_unload_size |= wave_load_ptr[7];

	wave_load_ptr += 16;

	if( (0x00017FE0 - temp3) < wave_unload_size ){
		wave_load_size = 0x00017FE0 - temp3;
	} else {
		wave_load_size = wave_unload_size;
	}

	wave_unload_size = wave_unload_size - wave_load_size;
	wave_save_code = wave_load_code;

	if( temp4 >= 0x1000 ){
		memcpy( mem_str_buf, wave_load_ptr, wave_load_size );
		temp2 = wave_load_size;
		while( wave_unload_size ){
			if( wave_unload_size >= 0x00018000 ){
				PcmRead( wave_fp, cdload_buf, 1 );
				wave_load_size = 0x00018000;
				wave_unload_size -= 0x00018000;
			} else if( wave_unload_size ){
				PcmRead( wave_fp, cdload_buf, wave_unload_size );
				wave_load_size = wave_unload_size;
				wave_unload_size = 0;
			}
			memcpy( mem_str_buf+temp2, cdload_buf, wave_load_size );
			temp2 += wave_load_size;
			if( temp2 > 0x000A0000 ){
				break;
			}
		}
		PcmClose( wave_fp );
		wave_fp = 0;
		wave_load_code = 0;
		return 1;
		return; // NOTICE
	}
	return 0;
}

void WaveCdLoad( void )
{
	// wait for 3 vblanks
	WaitVblankEnd();
	WaitVblankStart(); WaitVblankEnd();
	WaitVblankStart(); WaitVblankEnd();
	WaitVblankStart(); WaitVblankEnd();
	
	if( wave_unload_size > 0x00018000 ){
		PcmRead( wave_fp, cdload_buf, 0x00018000 );
		wave_load_ptr = cdload_buf;
		wave_load_size = 0x00018000;
		wave_unload_size -= 0x00018000;
		wave_load_status = 2;
	} else if( wave_unload_size ){
		PcmRead( wave_fp, cdload_buf, wave_unload_size );
		wave_load_ptr = cdload_buf;
		wave_load_size = wave_unload_size;
		wave_unload_size = 0;
		wave_load_status = 2;
	} else {
		wave_load_status = 0;
		PcmClose( wave_fp );
		wave_fp = 0;
		wave_load_code = 0;
	}
}

void WaveSpuTrans( void )
{
	int temp;
	
	if( wave_load_status == 2 ){
		temp = sceSdVoiceTrans( 0, 0, wave_load_ptr, spu_wave_start_ptr+spu_load_offset, wave_load_size );
		if( temp < 0 ){
			// EMPTY
		} else {
			spu_load_offset += wave_load_size;
		}
		wave_load_status += 1;
	}
}

/* ------------------------------- */
/* Name Format | Type  | Content   */
/* ------------+-------+---------- */
/* sg%06x.mdx  | Song  | Seq.Data  */
/* se%06x.efx  | SE    | Seq.Data  */
/* vc%06x.pcm  | Voice | Stream    */
/* wv%06x.wvx  | Wave  | Bank      */
/* pk%06x.sdx  | Pack  | Container */
/* ------------------------------- */
void code2name( u_int code, char *name )
{
	if( code > 0x00FFFFFF && code <= 0x0100FFFF ){
		name[ 0] = 's';
		name[ 1] = 'g';
		name[ 2] = num2char( (code >> 20) & 0x0F );
		name[ 3] = num2char( (code >> 16) & 0x0F );
		name[ 4] = num2char( (code >> 12) & 0x0F );
		name[ 5] = num2char( (code >>  8) & 0x0F );
		name[ 6] = num2char( (code >>  4) & 0x0F );
		name[ 7] = num2char( (code      ) & 0x0F );
		name[ 8] = '.';
		name[ 9] = 'm';
		name[10] = 'd';
		name[11] = 'x';
		name[12] = 0;
	} else if( code > 0x01FFFFFF && code <= 0x0200FFFF ){
		name[ 0] = 's';
		name[ 1] = 'e';
		name[ 2] = num2char( (code >> 20) & 0x0F );
		name[ 3] = num2char( (code >> 16) & 0x0F );
		name[ 4] = num2char( (code >> 12) & 0x0F );
		name[ 5] = num2char( (code >>  8) & 0x0F );
		name[ 6] = num2char( (code >>  4) & 0x0F );
		name[ 7] = num2char( (code      ) & 0x0F );
		name[ 8] = '.';
		name[ 9] = 'e';
		name[10] = 'f';
		name[11] = 'x';
		name[12] = 0;
	} else {
		if( code > 0xEFFFFFFF && code <= 0xF0FFFFFF ){
			name[ 0] = 'v';
			name[ 1] = 'c';
			name[ 2] = num2char( (code >> 20) & 0x0F );
			name[ 3] = num2char( (code >> 16) & 0x0F );
			name[ 4] = num2char( (code >> 12) & 0x0F );
			name[ 5] = num2char( (code >>  8) & 0x0F );
			name[ 6] = num2char( (code >>  4) & 0x0F );
			name[ 7] = num2char( (code      ) & 0x0F );
			name[ 8] = '.';
			name[ 9] = 'p';
			name[10] = 'c';
			name[11] = 'm';
			name[12] = 0;
		}
		if( code > 0xFDFFFFFF && code <= 0xFE00FFFF ){
			name[ 0] = 'w';
			name[ 1] = 'v';
			name[ 2] = num2char( (code >> 20) & 0x0F );
			name[ 3] = num2char( (code >> 16) & 0x0F );
			name[ 4] = num2char( (code >> 12) & 0x0F );
			name[ 5] = num2char( (code >>  8) & 0x0F );
			name[ 6] = num2char( (code >>  4) & 0x0F );
			name[ 7] = num2char( (code      ) & 0x0F );
			name[ 8] = '.';
			name[ 9] = 'w';
			name[10] = 'v';
			name[11] = 'x';
			name[12] = 0;
		}
		if( code > 0xFE7FFFFF && code <= 0xFEFFFFFF ){
			name[ 0] = 'p';
			name[ 1] = 'k';
			name[ 2] = num2char( (code >> 20) & 0x0F );
			name[ 3] = num2char( (code >> 16) & 0x0F );
			name[ 4] = num2char( (code >> 12) & 0x0F );
			name[ 5] = num2char( (code >>  8) & 0x0F );
			name[ 6] = num2char( (code >>  4) & 0x0F );
			name[ 7] = num2char( (code      ) & 0x0F );
			name[ 8] = '.';
			name[ 9] = 's';
			name[10] = 'd';
			name[11] = 'x';
			name[12] = 0;
		}
	}
}

char num2char( u_int num )
{
	num &= 0x0F;
	
	if( num < 0x0A ){
		num += 0x30;
	} else {
		num += 0x57;
	}
	return num;
}

void str_cat( char *a0, char *a1 )
{
	u_int i;
	
	for( i = 0 ; i < 256 ; i++ ){
		if( !a0[i] ) break;
	}
	if( i < 256 ){
		strcpy( a0+i, a1 );
	}
}

int PcmOpen( u_int a0, u_int a1 )
{
	int temp3;
	char temp[128], temp2[16];
	
	if( pak_read_fg ){
		return pak_fp;
	}
	if( pak_cd_read_fg ){
		cdOpen();
		pakcd_pos = pak_load_code;
		return 1;
	}
	if( a1 != 5 || !path_name[0] ){
		strcpy( temp, sd_path_sd1[a1] );
	} else {
		strcpy( temp, path_name );
	}
	
	code2name( a0, temp2 );
	str_cat( temp, temp2 );
	
	if( !pak_read_fg ){
		// EMPTY
	}
	
	temp3 = pcOpen( temp, 1 );
	
	if( temp3 < 0 ){
		printf( "PcmOpen Error(%x)\n", temp3 );
	}
	return temp3;
}

int PcmRead( int a0, void *a1, int a2 )
{
	int temp3;
	int temp;
	
	a2 = (a2 + 0x07FF) & 0xFFFFF800;
	
	if( pak_cd_read_fg ){
		cdRead( pakcd_pos, a1, a2 );
		//~ if( a2 < 0 );
		pakcd_pos += a2/2048;
		return a2;
	}
	
	temp3 = pcRead( a0, a1, a2 );
	
	if( temp3 <= 0 ){
		printf( "PcmRead Error(%x:size=%x)\n", temp3, a2 );
	}
	return temp3;
}

int PcmLseek( int a0, u_int a1, u_int a2 )
{
	int temp3;
	
	if( pak_cd_read_fg ){
		if( a2 == 1 ){
			pakcd_pos += a1 >> 11;
		}
		return a0;
	}
	
	temp3 = pcLseek( a0, a1, a2 );
	
	if( temp3 < 0 ){
		printf( "CD Seek Error(%x)\n", temp3 );
		return temp3;
		return; // NOTICE
	}
	return a0;
}

int PcmClose( int a0 )
{
	int temp3 = 0;
	
	if( pak_cd_read_fg ){
		if( !pak_read_fg ){
			cdClose();
		}
		return temp3;
	}
	if( !pak_read_fg ){
		temp3 = pcClose( a0 );
		if( temp3 < 0 ){
			printf( "PcmClose Error(%x)\n", temp3 );
		}
	}
	return temp3;
}

int EEOpen( int a0 )
{
	u_int temp, *temp2;
	
	if( (a0 & 0xFF000000) == 0xF5000000 ){
		temp = 1;
	} else if( (a0 & 0xFF000000) == 0xF4000000 ){
		temp = 2;
	}
	temp2 = (pak_header+0x01FA)+(6*temp);
	return temp;
}

int EERead( u_int a0, u_int *a1, u_int a2, u_int a3 )
{
	u_int *temp3, *temp2, temp = 0;
	
	if( a0 != 1 && a0 != 2 ){
		str2_iop_load_set[a0-1] = 0;
		return 0;
	}
	
	temp2 = (pak_header+506)+(a0*6);
	
	if( temp2[3] <= temp2[4] ){
		str2_iop_load_set[a0-1] = 0;
		return 0;
	}
	
	temp3 = sif_get_mem(a1, temp2[1] << 4, a3);
	
	while( 1 ){
		DelayThread( 0x2710 );
		if( temp3[0] & 0x80000000 ){
			break;
		}
		temp++;
		if( !(temp & 0xFFFF) ){
			// EMPTY
		}
	}
	
	if( temp2[3] ){
		// the triple load here is in the wrong order
		// should be v1, v0, v1
		// is v0, v0, v1
		temp2[4]++;
	}
	
	sif_rv_release_queue( temp3 );
	str2_iop_load_set[a0-1] = 0;
	return a2;
}

/*---------------------------------------------------------------------------*
 * END OF FILE
 *---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=euc-jp : */
