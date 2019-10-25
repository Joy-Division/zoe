/*
 * Multi-Task Scheduler for PS2
 * Public Interface
 */
#ifndef INC_MTS_H
#define INC_MTS_H

#include "global.h"

/*---------------------------------------------------------------------------*
 * Definitions
 *---------------------------------------------------------------------------*/

// ref.default.pdb
typedef struct {
	int value;
	int mask;
	int mode;
	int wait_threadid;
} MTS_EVENTFLAG;

/*---------------------------------------------------------------------------*
 * Prototypes
 *---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

/* MTS Main (mts.c) */
#if 0 // TODO
MTS_SetExceptionCallback
MTS_GetThreadId
MTS_ExitThread
MTS_NewThread
MTS_BootThread
MTS_Panic
#endif

/* MTS Exception (exception.c) */
void DEBUG_InitException( u_int );
int cprintf( char *format, ... );
int printf( char *format, ... );

#if 0 // TODO
DEBUG_SetExceptionCallback
DEBUG_ExceptionCallback
MTS_SetPrintFunc
excep_printf
#endif

/* MTS Stack Check (stackcheck.c) */
#if 0 // TODO
DEBUG_SetStackCheck
DEBUG_get_stack_size
DEBUG_ReleaseStack
DEBUG_GetStackUseSize
#endif

/* MTS Exception (exception_in.s) */
#if 0 // TODO
DEBUG_ExceptionIn
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/*---------------------------------------------------------------------------*/
#endif /* END OF FILE */
/*---------------------------------------------------------------------------*/
/* -*- indent-tabs-mode: t; tab-width: 4; mode: c; -*- */
/* vim: set noet ts=4 sw=4 ft=c ff=dos fenc=euc-jp : */
