#ifndef INCLUDED_JSIFMAN_H
#define INCLUDED_JSIFMAN_H

#include <sys/types.h>
#include <sifcmd.h>

/* libmain.c */
int sif_set_callback_func( u_int a0, sceSifCmdHandler a1, void *a2 );
void sif_send_packet_and_data();
void i_sif_send_packet_and_data();
void sif_send_direct();
void i_sif_send_direct();
u_int i_sif_send_mem( u_int *a0, volatile void *a1, u_int a2 );
u_int sif_send_mem( u_int *a0, volatile void *a1, u_int a2 );
int sif_check_status( u_int a0 );
void sif_init();

/* rvman.c */
void sif_init_rv_man();
void sif_rv_get_queue();
void sif_rv_call_func();
void sif_rv_return_value();
void i_sif_rv_return_value();
void sif_rv_release_queue();
u_int *sif_get_mem( void *a0, u_int a1, u_int a2 );

#endif /* END OF FILE */
