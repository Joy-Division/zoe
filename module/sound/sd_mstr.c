#include <sys/types.h>
#include <kernel.h>
#include <libsd.h>

#include "sd_incl.h"
#include "sd_ext.h"
#include "sd_debug.h"

u_char wave_header[0x2000]; /* 8KB */
u_char sng_data[0x00020000];
u_char se_data_area[0x4800];
u_char cdload_buf[0x18000];

/*---------------------------------------------------------------------------*/

void init_mem_str_w( void )
{
	int i;

	for( i = 0 ; i < 12 ; i++ ){
		mem_str_w[i].unk00 = 0;
	}
}

/*---------------------------------------------------------------------------*/

int MemSpuTransWithNoLoop( u_int a0 )
{
	int temp2 = 0;
	u_int temp3;
	struct unkstr24 *temp4;
	u_short temp5;

	a0 -= 32;
	temp4 = &mem_str_w[a0];

///////////////////////////////////////////////////////////////////////////////
	switch( (temp4->unk00 & 0xF)-2 ){
	case 0:
		temp4->unk04 = temp4->unk08 = voice_tbl[temp4->unk0C+1].addr - voice_tbl[temp4->unk0C].addr;
		temp4->unk10 = mem_str_buf+voice_tbl[temp4->unk0C].addr;
		temp4->unk10[17] = 0;
		temp4->unk10[temp4->unk04-0x1F] = 1;

		sceSdSetAddr( SD_CORE_1|((a0+8)<<1)|SD_VA_LSAX, a0*0x1000+0x9020 );
		sceSdVoiceTrans(
			0,										// transfer channel
			SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,	// transfer mode
			temp4->unk10,							// IOP memory addr
			(u_char *)(a0*0x1000+0x9020),			// SPU memory addr
			0x800									// transfer size
		);
		temp4->unk10 += 0x0800;
		temp4->unk08 -= 0x0800;
		temp4->unk00++;
		temp2 = 1;
		break;
///////////////////////////////////////////////////////////////////////////////
	case 1:
		if( !temp4->unk08 || temp4->unk08 & 0x80000000 ){
			temp4->unk00++;
		}else{
			if( temp4->unk08 > 0x0800 && temp4->unk10[0x07F1] != 1 ){
				temp4->unk10[0x07F1] |= 3;
			}
			sceSdVoiceTrans(
				0,										// transfer channel
				SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,	// transfer mode
				temp4->unk10,							// IOP memory addr
				(u_char *)(a0*0x1000+0x9820),			// SPU memory addr
				0x0800									// transfer size
			);
			temp4->unk10 += 0x0800;
			temp4->unk08 -= 0x0800;
			temp4->unk00++;
			temp2 = 1;
		}
		break;
///////////////////////////////////////////////////////////////////////////////
	case 2:
		sceSdSetAddr( SD_CORE_1|((a0+8)<<1)|SD_VA_SSA, a0*0x1000+0x9020 );
		keyon();
		temp4->unk14 = 0x0800;
		temp4->unk00++;
		if( !temp4->unk08 || temp4->unk08 & 0x80000000 ){
			temp4->unk00++;
		}
		break;
///////////////////////////////////////////////////////////////////////////////
	case 3:
		temp5 = sceSdGetParam( SD_CORE_1|((a0+8)<<1)|SD_VP_ENVX );
		if( !temp5 ){
			temp4->unk00++;
		}
		temp3 = sceSdGetAddr( (SD_CORE_1|((a0+8)<<1)|SD_VA_NAX) );
		temp3 -= 0x9020 + (a0*0x1000);
		if( temp3 >= 0x1000 ){
			PRINTF(( "ERROR:MemoryStreamingAddress(%x)\n", temp3 ));
			break;
		}
		if( temp4->unk14 == (temp3 & 0x0800) ){
			temp2 = 1;
			if( temp3 >= 0x0800 ){
				sceSdVoiceTrans(
					0,										// transfer channel
					SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,	// transfer mode
					temp4->unk10,							// IOP memory addr
					(u_char *)(a0*0x1000+0x9020),			// SPU memory addr
					0x0800									// transfer size
				);
				temp4->unk14 = 0;
			}else{
				if( temp4->unk08 > 0x0800 && temp4->unk10[0x07F1] != 1 ){
					temp4->unk10[0x07F1] |= 3;
				}
				sceSdVoiceTrans(
					0,										// transfer channel
					SD_TRANS_MODE_WRITE|SD_TRANS_BY_DMA,	// transfer mode
					temp4->unk10,							// IOP memory addr
					(u_char *)(a0*0x1000+0x9820),			// SPU memory addr
					0x0800									// transfer size
				);
				temp4->unk14 = 0x0800;
			}
			temp4->unk10 += 0x0800;
			if( temp4->unk08 > 0x0800 ){
				temp4->unk08 -= 0x0800;
			}else{
				temp4->unk00++;
			}
		}else{
			//
			// EMPTY BLOCK
			//
		}
		break;
///////////////////////////////////////////////////////////////////////////////
	case 4:
		temp4->unk00++;
		break;
///////////////////////////////////////////////////////////////////////////////
	case 5:
		break;
	}
	return temp2;
}
