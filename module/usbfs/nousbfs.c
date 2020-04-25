/*
 * KCEJ USB File System (for PlayStation 2)
 * Copyright (C) Konami Computer Entertainment Japan
 * Codebase Restoration by Joy Division
 */
/* ver."ZONE OF THE ENDERS"
 */
#include <stdio.h>
#include <sys/types.h>
#include <kernel.h>

int pcInit( void )
{
	return 0;
}

int pcOpen( char *path, int flags )
{
	return open( path, flags );
}

int pcClose( int fd )
{
	return close( fd );
}

ssize_t pcRead( int fd, void *buf, size_t count )
{
	return read( fd, buf, count );
}

ssize_t pcWrite( int fd, void *buf, size_t count )
{
	return write( fd, buf, count );
}

u_int pcLseek( int fd, u_int offset, int whence )
{
	return lseek( fd, offset, whence );
}

int start()
{
	extern libhead usbfs_entry;

	if( RegisterLibraryEntries( &usbfs_entry ) )
		return 1;

	printf( "USB FILE DO NOT USE\n" );
	return 0;
}
