/*
 * ZONE OF THE ENDERS
 * Startup Module
 */
#include "global.h"
#include <stdlib.h>
#include <string.h>
#include <eekernel.h>
#include <libcdvd.h>
#include <libdev.h>
#include <libdma.h>
#include <libgraph.h>
#include <libmpeg.h>
#include <sifdev.h>
#include <sifrpc.h>

#define IN_MAIN_CC // for GV_InitSystem()

#include "zoe_libs.h"
//#include "../../module/mts/mts.h"
//#include "../include/libdg.h"
//#include "../include/libdm.h"
//#include "../include/libev.h"
//#include "../include/libfs.h"
//#include "../include/libgv.h"
//#include "../include/libhzd.h"
//#include "../include/libmcard.h"
//#include "../include/libscn.h"
//#include "../include/libsd.h"
//#include "../include/libstrm.h"
//#include "../include/libtrg.h"
//#include "../include/carl.h"

/*---------------------------------------------------------------------------*/

// TODO: move temporary prototypes
extern void NewInitLoad( char *, int ); /* bgsphere.cc */
extern void NewStartStage(); /* bgsphere.cc */
extern void NewDebugMode(); /* dbgmode.cc */

/*---------------------------------------------------------------------------*/

#if ( ZOE_DEMO_OCT2000 )
#define CDVD_MODE  SCECdCD
#else
#define CDVD_MODE  SCECdDVD
#endif

static int ReplaceImageFlag = true;

/*---------------------------------------------------------------------------*/
/* Version   | Status     | Oflag | I./R. | etc.                             */
/*-----------+------------+-------+-------+----------------------------------*/
/* SLPS99999 | UNTESTED   | O?    | NA/NA |                                  */
/* SLPM65019 | INCOMPLETE | O?    | NA/NA |                                  */
/*---------------------------------------------------------------------------*/
static void SifLoad()
{
	char *irx_list[] = {
		// SCE IOP modules
		"cdrom0:\\MODULES\\LIBSD.IRX;1",
		"cdrom0:\\MODULES\\SIO2MAN.IRX;1",
		"cdrom0:\\MODULES\\PADMAN.IRX;1",
		"cdrom0:\\MODULES\\MCMAN.IRX;1",
		"cdrom0:\\MODULES\\MCSERV.IRX;1",
		// KCEJ IOP modules
		"cdrom0:\\MODULES\\JSIFMAN.IRX;1",
		"cdrom0:\\MODULES\\CDBIOS.IRX;1",
		"cdrom0:\\MODULES\\NOUSBFS.IRX;1",
		"cdrom0:\\MODULES\\IOP_MAIN.IRX;1"
	};
#if ( ZOE_JPN )
	//
	// TODO: decompile
	//
#endif
	sceSifInitRpc( 0 );
	
	for ( int i=8 ; i >= 0 ; i-- ){
		printf( "Load module %s\n", irx_list[i] );
		
		if ( sceSifLoadModule( irx_list[i], 0, NULL ) < 0 ){
			printf( "Can't load module %s\n", irx_list[i] );
			exit( 0 );
		}
	}
}

/*---------------------------------------------------------------------------*/
/* Version   | Status     | Oflag | I./R. | etc.                             */
/*-----------+------------+-------+-------+----------------------------------*/
/* SLPS99999 | UNTESTED   | O?    | NA/NA |                                  */
/* SLPM65019 | UNTESTED   | O?    | NA/NA |                                  */
/*---------------------------------------------------------------------------*/
static void ResetIOP()
{
	char *IopReplaceModule = "cdrom0:\\MODULES\\IOPRP20.IMG;1";
	
	sceSifInitRpc( 0 );
	sceCdInit( SCECdINIT );
	sceCdMmode( CDVD_MODE );
	
#if ( ZOE_DEMO_OCT2000 )
	printf( "IopReplaceModule %s\n", IopReplaceModule );
#endif
	
	if ( ReplaceImageFlag ){
		while ( !sceSifRebootIop( IopReplaceModule ) );
		while ( !sceSifSyncIop() );
	}
	
	sceSifInitRpc( 0 );
	sceCdInit( SCECdINIT );
	sceCdMmode( CDVD_MODE );
	sceFsReset();
}

/*---------------------------------------------------------------------------*/
/* Version   | Status     | Oflag | I./R. | etc.                             */
/*-----------+------------+-------+-------+----------------------------------*/
/* SLPS99999 | UNTESTED   | O?    | NA/NA |                                  */
/* SLPM65019 | UNTESTED   | O?    | NA/NA |                                  */
/*---------------------------------------------------------------------------*/
void main()
{
	sceDevVif0Reset();
	sceDevVif1Reset();
	sceDevVu0Reset();
	sceDevVu1Reset();
	sceGsResetPath();

/*
 * The following COP0 Cache definitions were removed from eekernel.h in
 * version 2.3.0 (Jan.22,2003), however the functions are still present
 * within the "libkernl.a" static library.
 *
 * Pass "-DEEKERNEL_CACHEDEFS" to the compiler when building with a
 * PlayStation 2 Runtime Library Release which lacks these definitions.
 */
#ifdef EEKERNEL_CACHEDEFS
#define INST_CACHE  2
#define DATA_CACHE  1
#define CacheOn()   EnableCache(INST_CACHE | DATA_CACHE)
#define CacheOff()  DisableCache(INST_CACHE | DATA_CACHE)
int EnableCache(int);
int DisableCache(int);
#endif

	CacheOn();
	
	sceDmaReset( 1 );
	sceGsResetPath();
	sceGsResetGraph(
		0,
		SCE_GS_NOINTERLACE,
		SCE_GS_NTSC,
		SCE_GS_FRAME );
	
	DG_InitClean();
	
	ResetIOP(); // load IOPRP*.IMG
	SifLoad();  // load IRX modules
	
	sd_init();
	
#if ( ZOE_DEMO_OCT2000 )
	DEBUG_InitException(
		(((0x00010000+(s16)0x8000)
		+ (0x00200000+(s16)0x8000)) - 16) );
#endif
	
	GV_InitSystem();
	
	FS_StartDaemon();
	printf( "FS_StartDaemon\n" );
	
	DG_StartDaemon();
	printf( "DG_StartDaemon\n" );
	
	SCN_SYSTEM::InitSystem( 200, 200, 200 );
	
	MC_StartDaemon();
	printf( "MC_StartDaemon\n" );
	
	EV_StartDaemon();
	printf( "EV_StartDaemon\n" );
	
	TRG_OBJECT::StartDaemon();
	printf( "TRG_StartDaemon\n" );
	
	HZD_Init();
	
	MT_Init();
	
	DM_MANAGER::InitSystem();
	
	sceMpegInit();
	
	DG_DebugPrimDaemon( 40960 );
	
	cdbios_init();
	
	FS_CdLoadDirInfo( "\\ZOE.DAT;1", 32 );
	
	STRM_LoadPcmDir();
	
#if ( ZOE_DEMO_OCT2000 )
	NewInitLoad( "init", 0 );
#else // TODO: Known for ZOE_JPN, check others
	CR_SetStageLoad( "title", 1, "font.pak", 0 );
#endif
	
	NewStartStage();
	
#if ( ZOE_DEMO_OCT2000 )
	NewDebugMode();
#endif
	
	while (1){
		GV_ACTOR::Execute();
	}
}

/*---------------------------------------------------------------------------*
 * END OF FILE
 *---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: cpp; -*- */
/* vim: set noet ts=4 sw=4 ft=cpp ff=dos fenc=euc-jp : */
