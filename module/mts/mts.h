/*
 * Multi-Task Scheduler (for PlayStation 2)
 * Copyright (C) Konami Computer Entertainment Japan
 * Codebase Restoration by Joy Division
 */
/* ver."ZONE OF THE ENDERS"
 */
#ifndef INCLUDED_MTS_H
#define INCLUDED_MTS_H

#include "global.h"

#if defined(__cplusplus)
extern "C" {
#endif

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

/* ---------------- */
/* MTS Main (mts.c) */
/* ---------------- */
#if 0 // TODO
MTS_SetExceptionCallback();
MTS_GetThreadId();
MTS_ExitThread();
MTS_NewThread();
MTS_BootThread();
MTS_Panic();
#endif

/* --------------------------- */
/* MTS Exception (exception.c) */
/* --------------------------- */
void DEBUG_InitException( u_int );
int cprintf( char *format, ... );
int printf( char *format, ... );

#if (0) // TODO
DEBUG_SetExceptionCallback();
DEBUG_ExceptionCallback();
MTS_SetPrintFunc();
excep_printf();
#endif

/* ------------------------------ */
/* MTS Stack Check (stackcheck.c) */
/* ------------------------------ */
#if (0) // TODO
DEBUG_SetStackCheck();
DEBUG_get_stack_size();
DEBUG_ReleaseStack();
DEBUG_GetStackUseSize();
#endif

/* ------------------------------ */
/* MTS Exception (exception_in.s) */
/* ------------------------------ */
#if (0) // TODO
DEBUG_ExceptionIn();
#endif

#if defined(__cplusplus)
}
#endif

#endif /* END OF FILE */
