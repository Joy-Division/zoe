#ifndef INCLUDED_SD_EE_H
#define INCLUDED_SD_EE_H

#if defined(__cplusplus)
extern "C" {
#endif

// TODO: Determine argument/return types,
// and fix the following provisional declarations.

int  sd_init( void );
void sd_set_cli( int );
int  sd_status( void );

#if defined(__cplusplus)
}
#endif

#endif /* END OF FILE */
