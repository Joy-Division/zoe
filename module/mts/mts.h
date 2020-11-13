#ifndef INCLUDED_MTS_H
#define INCLUDED_MTS_H

#include <sys/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*===========================================================================*/
/* Macro & Type Defines                                                      */
/*===========================================================================*/

typedef struct {
	int value;
	int mask;
	int mode;
	int wait_threadid;
} MTS_EVENTFLAG;

/*===========================================================================*/
/* Public Functions                                                          */
/*===========================================================================*/

/* mts.c */
#if (0)
MTS_SetExceptionCallback();
MTS_GetThreadId();
MTS_ExitThread();
MTS_NewThread();
MTS_BootThread();
MTS_Panic();
#endif

/* exception.c */
//DEBUG_SetExceptionCallback();
//DEBUG_ExceptionCallback();
void DEBUG_InitException( u_int );
//MTS_SetPrintFunc();
int cprintf( char *format, ... );
int printf( char *format, ... );
//excep_printf();

/* exception_in.s */
#if (0)
DEBUG_ExceptionIn();
#endif

/* stackcheck.c */
#if (0)
DEBUG_SetStackCheck();
DEBUG_get_stack_size();
DEBUG_ReleaseStack();
DEBUG_GetStackUseSize();
#endif

#if defined(__cplusplus)
}
#endif

#endif /* END OF FILE */
