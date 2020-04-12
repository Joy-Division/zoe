/*
 * Sound Driver (for PlayStation 2) by K.Muraoka
 * Copyright (C) Konami Computer Entertainment Japan
 * Codebase Restoration by Joy Division
 */
/* ver."ZONE OF THE ENDERS"
 */
#ifndef INCLUDED_SD_EE_H
#define INCLUDED_SD_EE_H

#if defined(__cplusplus)
extern "C" {
#endif

int  sd_init( void );   // TODO: check types
void sd_set_cli( int ); // TODO: check types
int  sd_status( void ); // TODO: check types

#if defined(__cplusplus)
}
#endif

#endif /* END OF FILE */
