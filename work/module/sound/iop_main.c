/*
 * Sound Driver for PS2 IOP
 * IOP Main Module
 *
 * ver.ZONE OF THE ENDERS
 */
#include <sys/types.h>
#include <kernel.h>
#include "sd_incl.h"

// TODO: from jsifman, replace once decompiled
extern u_int sif_send_mem( u_int *, u_int *, u_int );

void sd_set_status( void )
{
	u_int temp2, temp = 0;
	com_queue[131] = 0;
	
	if (sng_status == 3){
		temp |= 0x4000;
	}
	if (str2_iop_load_set[1]){
		temp |= 0x2000;
	}
	if (str2_iop_load_set[0]){
		temp |= 0x1000;
	}
	if (str2_load_code[1] || lnr8_load_code){
		temp |= 0x40;
	}
	if (str2_load_code[0] || str_load_code){
		temp |= 0x20;
	}
	if (str2_first_load[1] || lnr8_first_load){
		temp |= 0x10;
	}
	if (str2_first_load[0] || str_first_load){
		temp |= 0x8;
	}
	if (wave_load_code || pak_load_status){
		temp |= 0x4;
	}
	if (se_load_code || pak_load_status){
		temp |= 0x2;
	}
	if (sng_load_code || pak_load_status){
		temp |= 0x1;
	}
	for (temp2 = 0 ; temp2 < 0x10 ; temp2++){
		if (sd_sng_code_buf[temp2] > 0x01000000){
			temp |= 0x1; 
			break;
		}
	}

	temp &= 0x7FFFFFFF;
	com_queue[132] = temp;
	
	if (str_status){
		com_queue[133] = str_counter | str_counter_low;
	} else {
		com_queue[133] = str2_counter[0];
	}
	
	if (str2_status[1]){
		com_queue[134] = str2_counter[1];
	} else {
		com_queue[134] = lnr8_counter;
	}
	
	com_queue[135] = str2_play_counter[0];
	com_queue[136] = str2_play_counter[1];
	// these two assignments have register mismatches for the seccond summand
	com_queue[137] = (ee_addr[3] << 16) + ee_addr[4];
	com_queue[138] = (ee_addr[9] << 16) + ee_addr[10];
}

void sd_set_status( void )
{
	int *que = com_queue;
	
	if (que[139]){
		// the way the arguments get loaded doesnt seem to be right
		// also this if has an empty target that i cannot reproduce
		if (sif_send_mem( (u_int *)que[139], &que[131], 0x20 ) == 0);
	}
}

// TODO
void sif_callback_func( int *a0, int *a1 )
{
	int *temp = a1;
	
	if (!a0[3]){
		temp[139] = a0[4];
	} else {
		// BLOCK FOR 4CC
	// STRUCT ACCESS?
		// BELOW IS 500 ALL AFTER IS OK
		temp[129] = ((temp[129]+1) / 64) * 63;
		iWakeupThread( temp[130] );
	}
}

// TODO
void SdSet( void )
{
	int temp;
	int *que = com_queue;
	
	while (1){
		SleepThread();
		if (que[128] != que[129]){
			// CODE BLOCK STARTING AT 5B0
		// STRUCT ACCESS?
			// BELOW IS 5E0 ALL BELOW IS OK
			que[128] = ((que[128]+1) / 64) * 63;
			sd_set( temp );
		}
	}
	ExitThread();
}

void RecieveInit( int a0 )
{
	int *que = com_queue;
	
	que[129] = 0;
	que[128] = que[129];
	que[130] = a0;
	
	sif_set_callback_func( 1, sif_callback_func, com_queue );
	
	que[139] = 0;
}

int HIntHandler( u_int a0 )
{
	if (iWakeupThread( id_SdInt ));
	return 1;
}

void setTimer( void *a0 )
{
	u_int temp;
	struct SysClock clock;
	
	USec2SysClock( 0x1388, &clock );
	
	id_HSyncTim = AllocHardTimer( 1, 0x20, 1 );
	temp = GetHardTimerIntrCode( id_HSyncTim );
	
	RegisterIntrHandler( temp, 1, HIntHandler, a0 );
	SetTimerCompare( id_HSyncTim, clock.low );
	SetTimerMode( id_HSyncTim, 0x158 );
	EnableIntr( temp );
}

int createThread( void )
{
	u_int temp, temp2;
	void *temp3;
	u_int temp4, temp5;
	
	sd_mem_alloc();

	temp = 0x2000000;
	temp3 = SdMain;
	temp5 = 0x41;
	temp4 = 0x4000;
	temp2 = 0;
	id_SdMain = CreateThread( temp3 );
	if (0 >= id_SdMain){};
	StartThread( id_SdMain, 0 );

	temp = 0x2000000;
	temp3 = SdEELoad;
	temp5 = 0x40;
	temp4 = 0x4000;
	temp2 = 0;
	id_SdEELoad = CreateThread( temp3 );
	if (0 >= id_SdEELoad){};
	StartThread( id_SdEELoad, 0 );

	temp = 0x2000000;
	temp3 = SdSet;
	temp5 = 0x3F;
	temp4 = 0x2000;
	temp2 = 0;
	id_SdSet = CreateThread( temp3 );
	if (0 >= id_SdSet){};
	StartThread( id_SdSet, 0 );
	RecieveInt( id_SdSet );

	temp = 0x2000000;
	temp3 = SdInt;
	temp5 = 0x3E;
	temp4 = 0x4000;
	temp2 = 0;
	id_SdInt = CreateThread( temp3 );
	if (0 >= id_SdInt){};
	StartThread( id_SdInt, 0 );

	setTimer( common );
	SleepThread();

	return 0;
}

int start()
{
	u_int temp, temp2;
	void *temp3;
	u_int temp4, temp5, temp6;
	int temp7;

	FlushDcache();
	sceSdInit( 0 );
	CpuEnableIntr();
	EnableIntr( INUM_DMA_4 );
	EnableIntr( INUM_DMA_7 );
	EnableIntr( INUM_SPU );

	temp = 0x2000000;
	temp3 = createThread;
	temp5 = 0x40;
	temp4 = 0x4000;
	temp2 = 0;
	temp7 = CreateThread( temp3 );
	if (0 >= temp7) return 1;
	StartThread( temp7, 0 );
  
	return 0;
}
