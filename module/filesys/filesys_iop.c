#include <sys/types.h>
#include <kernel.h>
#include <sifcmd.h> // for sceSifCmdHdr

#include "nousbfs.h"
//#include "jsifman.h"

// TODO: from jsifman, replace once decompiled
extern u_int sif_send_mem( u_int *, volatile void *, u_int );
extern void sif_set_callback_func( u_int, void (*)(void*, volatile void*), void* );
extern void sif_rv_release_queue();
extern int sif_check_status( u_int );
extern u_int *sif_get_mem( void *, u_int, u_int );

/*---------------------------------------------------------------------------*/

ModuleInfo Module = { "ZOE_FILESYS", 0x0101 };

// from LibFS, DO NOT CHANGE!!
typedef struct _FS_FILEINFO {
	sceSifCmdHdr hdr;
	int		status;
	int		size;
	void*	pBuf;
	int		sizeRead;
	int		pos;
	char	nmFile[60];
} FS_FILEINFO;

struct Work {
	FS_FILEINFO fileinfo;
	int		unk60;
	int		unk64;
	u_int	unk68;		// UNUSED
	int		unk6C;		// fd
	u_int*	unk70[2];	// mem ptr
	int		unk78;		// thread ID
	int		unk7C;
	u_char	unk80[16];	// UNUSED
};

struct Work work;

/*---------------------------------------------------------------------------*/

void LoadDaemonThread( void )
{
	int temp20;
	int temp1C;
	int temp18;		// count
	int temp14;
	int temp10;

	while( 1 )
	{
		SleepThread();

		switch( work.unk7C )
		{
		case 0: // fallthrough
		case 4:
			work.unk60 = work.fileinfo.pBuf;

			if( (work.unk6C = pcOpen( work.fileinfo.nmFile, O_RDONLY )) < 0 ){
				work.fileinfo.status = 4;
				sif_send_mem( work.unk60, &work, 0x60 );
				break;
			}

			work.fileinfo.size = pcLseek( work.unk6C, 0, 2 );

			if( !work.unk7C ){
				pcLseek( work.unk6C, 0, 0 );
				work.fileinfo.pos = 0;
			}else{
				pcLseek( work.unk6C, work.fileinfo.pos, 0 );
			}

			work.fileinfo.status = 0;
			sif_send_mem( work.unk60, &work, 0x60 );
			break;

		case 1:
			temp20 = work.fileinfo.sizeRead;
			temp1C = 0;
			temp14 = 0;
			temp10 = work.fileinfo.pBuf;
			work.fileinfo.status = 2;

			sif_send_mem( work.unk60, &work, 0x60 );

			while( temp20 > 0 && work.unk7C != 3 ){
				temp18 = (temp20 > 0x8000) ? 0x8000 : temp20;
				work.fileinfo.pos += pcRead( work.unk6C, work.unk70[temp1C], temp18 );
				work.unk64 -= temp18;

				if( temp14 ){
					while( sif_check_status(temp14) >= 0 );
				}

				do {
					temp14 = sif_send_mem( temp10, work.unk70[temp1C], (temp18+0xF) & 0xFFFFFFF0 );
				} while( !temp14 );

				temp20 -= temp18;
				temp10 += temp18;
				temp1C ^= 1;
			}

			if( temp14 ){
				while( sif_check_status( temp14 ) >= 0 );
			}

			work.fileinfo.status = 0;
			sif_send_mem( work.unk60, &work, 0x60 );
			break;

		case 2:
			pcClose( work.unk6C );
			work.fileinfo.status = 0;
			sif_send_mem( work.unk60, &work, 0x60 );
			work.unk6C = -1;
			break;

		case 3:
			if( work.unk6C >= 0 ){
				pcClose( work.unk6C );
				work.unk6C = -1;
			}
			work.fileinfo.status = 0;
			sif_send_mem( work.unk60, &work, 0x60 );
			break;
		}
	}
}

/*---------------------------------------------------------------------------*/

void CallBackFunc( struct Work *a0, volatile struct Work *a1 )
{
	volatile struct Work *temp = a1;
	temp->unk7C = a0->fileinfo.hdr.opt;

	switch( temp->unk7C )
	{
	case 4: // fallthrough
	case 0:
		if( temp->unk6C > 0 ) break;
		temp->unk6C = -1;
		temp->fileinfo = a0->fileinfo;
		break;
	case 1:
		if( temp->unk6C < 0 ) break;
		temp->fileinfo = a0->fileinfo;
		break;
	case 2:
		if( temp->unk6C < 0 ) break;
		temp->fileinfo = a0->fileinfo;
		break;
	default:
		break;
	}

	iWakeupThread( temp->unk78 );
}

/*---------------------------------------------------------------------------*/

int FS_StartDaemonIOP( void )
{
	struct ThreadParam param;
	int tid;

	work.unk70[0] = AllocSysMemory( 0, 0x8000, 0 );
	work.unk70[1] = AllocSysMemory( 0, 0x8000, 0 );
	work.unk6C = -1;

	param.attr         = TH_C;
	param.entry        = LoadDaemonThread;
	param.initPriority = 0x52;
	param.stackSize    = 0x1000;	// 4KB
	tid = CreateThread( &param );

	if( tid > 0 ){
		work.unk78 = tid;
		StartThread( tid, 0 );
		sif_set_callback_func( 2, CallBackFunc, &work );
	}else{
		return NO_RESIDENT_END;
	}
	return RESIDENT_END;
}
