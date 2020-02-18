/*
 * Sound Driver for PS2 IOP
 * IOP Main Module
 *
 * ver."ZONE OF THE ENDERS"
 */
#include <sys/types.h>
#include <kernel.h>
#include <libsd.h>

#include "sd_incl.h"
#include "sd_ext.h"

/*---------------------------------------------------------------------------*/

static int com_queue[140];

char name[6] = "SOUND";

ModuleInfo Module = { name, 0x0101 };

/*---------------------------------------------------------------------------*/

void sd_set_status( void )
{
	u_int i, temp = 0;
	com_queue[131] = 0;
	
	if( sng_status == 3 ){
		temp |= 0x4000;
	}
	if( str2_iop_load_set[1] ){
		temp |= 0x2000;
	}
	if( str2_iop_load_set[0] ){
		temp |= 0x1000;
	}
	if( str2_load_code[1] || lnr8_load_code ){
		temp |= 0x0040;
	}
	if( str2_load_code[0] || str_load_code ){
		temp |= 0x0020;
	}
	if( str2_first_load[1] || lnr8_first_load ){
		temp |= 0x0010;
	}
	if( str2_first_load[0] || str_first_load ){
		temp |= 0x0008;
	}
	if( wave_load_code || pak_load_status ){
		temp |= 0x0004;
	}
	if( se_load_code || pak_load_status ){
		temp |= 0x0002;
	}
	if( sng_load_code || pak_load_status ){
		temp |= 0x0001;
	}
	
	for( i = 0 ; i < 16 ; i++ ){
		if( sd_sng_code_buf[i] > 0x01000000 ){
			temp |= 0x0001;
			break;
		}
	}

	temp &= 0x7FFFFFFF;
	com_queue[132] = temp;
	
	if( str_status ){
		com_queue[133] = str_counter | str_counter_low;
	} else {
		com_queue[133] = str2_counter[0];
	}
	
	if( str2_status[1] ){
		com_queue[134] = str2_counter[1];
	} else {
		com_queue[134] = lnr8_counter;
	}
	
	com_queue[135] = str2_play_counter[0];
	com_queue[136] = str2_play_counter[1];
	// these two assignments have register mismatches for the seccond summand
	com_queue[137] = (ee_addr[0].unk0C << 16) + (int)ee_addr[0].unk10;
	com_queue[138] = (ee_addr[1].unk0C << 16) + (int)ee_addr[1].unk10;
}

/*---------------------------------------------------------------------------*/

void sd_send_status( void )
{
	volatile struct unkstrbig *que = (struct unkstrbig *)com_queue;
	
	if( que->unk22C ){
		// the way the arguments get loaded doesnt seem to be right
		// also this if has an empty target that i cannot reproduce
		if( sif_send_mem( (u_int *)que->unk22C, &que->unk20C, 32 ) == 0 );
	}
	else {
	}
}

/*---------------------------------------------------------------------------*/

// NOMATCH: see inside
static void sif_callback_func( struct unkstr24 *a0, volatile struct unkstrbig *a1 )
{
	volatile struct unkstrbig *temp = a1;
	
	if( !a0->unk0C ){
		temp->unk22C = (u_int)a0[0].unk10;
	} else {
		temp->unk000[temp->unk204].unk04 = a0[0].unk0C;
		temp->unk204 = ((temp->unk204+1) / 64) * 63; // this has the wrong registers
		iWakeupThread( temp->unk208 );
	}
}

/*---------------------------------------------------------------------------*/

// NOMATCH: see inside
void SdSet( void )
{
	int temp;
	volatile struct unkstrbig *que = (struct unkstrbig *)com_queue;
	
	while( 1 ){
		SleepThread();
		if( que->unk200 != que->unk204 ){
			temp = que->unk000[que->unk200].unk04;
			que->unk200 = ((que->unk200+1) / 64) * 63; // this has the wrong registers
			sd_set( temp );
		}
	}
	ExitThread();
}

/*---------------------------------------------------------------------------*/

static void RecieveInit( int a0 )
{
	volatile struct unkstrbig *que = (struct unkstrbig *)com_queue;
	
	que->unk200 = que->unk204 = 0;
	que->unk208 = a0;
	
	sif_set_callback_func( 1, (void (*)(void *, int *))sif_callback_func, com_queue );
	
	que->unk22C = 0;
}

/*---------------------------------------------------------------------------*/

int HIntHandler( u_int a0 )
{
	if( iWakeupThread( id_SdInt ) );
	return 1;
}

/*---------------------------------------------------------------------------*/

void setTimer( void *a0 )
{
	u_int intr_code;
	struct SysClock clock;
	
	USec2SysClock( 5000, &clock );
	
	id_HSyncTim = AllocHardTimer( 1, 32, 1 );
	intr_code = GetHardTimerIntrCode( id_HSyncTim );
	
	RegisterIntrHandler( intr_code, 1, HIntHandler, a0 );
	SetTimerCompare( id_HSyncTim, clock.low );
	SetTimerMode( id_HSyncTim, tZRET_1|tCMP_1|tREPT_1|tEXTC_1 );
	EnableIntr( intr_code );
}

/*---------------------------------------------------------------------------*/

int createThread( void )
{
	struct ThreadParam param;
	
	sd_mem_alloc();

	param.attr         = TH_C;
	param.entry        = SdMain;
	param.initPriority = 0x41;
	param.stackSize    = 0x4000;
	param.option       = 0;
	id_SdMain = CreateThread( &param );
	if( 0 >= id_SdMain ){};
	StartThread( id_SdMain, 0 );

	param.attr         = TH_C;
	param.entry        = SdEELoad;
	param.initPriority = 0x40;
	param.stackSize    = 0x4000;
	param.option       = 0;
	id_SdEELoad = CreateThread( &param );
	if( 0 >= id_SdEELoad ){};
	StartThread( id_SdEELoad, 0 );

	param.attr         = TH_C;
	param.entry        = SdSet;
	param.initPriority = 0x3F;
	param.stackSize    = 0x2000;
	param.option       = 0;
	id_SdSet = CreateThread( &param );
	if( 0 >= id_SdSet ){};
	StartThread( id_SdSet, 0 );
	RecieveInit( id_SdSet );

	param.attr         = TH_C;
	param.entry        = SdInt;
	param.initPriority = 0x3E;
	param.stackSize    = 0x4000;
	param.option       = 0;
	id_SdInt = CreateThread( &param );
	if( 0 >= id_SdInt ){};
	StartThread( id_SdInt, 0 );

	setTimer( common );
	SleepThread();

	return 0;
}

/*---------------------------------------------------------------------------*/

int start()
{
	struct ThreadParam param;
	int tid;

	FlushDcache();
	sceSdInit( SD_INIT_COLD );  /* initialize all */
	CpuEnableIntr();
	EnableIntr( INUM_DMA_4 );   /* CORE0 DMA interrupt */
	EnableIntr( INUM_DMA_7 );   /* CORE1 DMA interrupt */
	EnableIntr( INUM_SPU );     /* SPU2 interrupt */

	param.attr         = TH_C;
	param.entry        = createThread;
	param.initPriority = 0x40;
	param.stackSize    = 0x400;
	param.option       = 0;
	tid = CreateThread( &param );
	if( 0 >= tid ) return 1;
	StartThread( tid, 0 );
  
	return RESIDENT_END;
}

/*---------------------------------------------------------------------------*
 * END OF FILE
 *---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=unix fenc=euc-jp : */
