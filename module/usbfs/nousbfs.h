/*
 * KCEJ USB File System (for PlayStation 2)
 * Copyright (C) Konami Computer Entertainment Japan
 * Codebase Restoration by Joy Division
 */
/* ver."ZONE OF THE ENDERS"
 */
#ifndef INCLUDED_NOUSBFS_H
#define INCLUDED_NOUSBFS_H

#include <sys/types.h>

extern int pcInit( void );
extern int pcOpen( char *path, int flags );
extern int pcClose( int fd );
extern ssize_t pcRead( int fd, void *buf, size_t count );
extern ssize_t pcWrite( int fd, void *buf, size_t count );
extern u_int pcLseek( int fd, u_int offset, int whence );

#endif /* END OF FILE */
