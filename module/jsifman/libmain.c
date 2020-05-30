#include <sys/types.h>
#include <sif.h>
#include <sifcmd.h>

/* for IOP ONLY */
#if defined(__R3000__)
#include <kernel.h>
ModuleInfo Module = { "KCEJ_SIF_MANAGER", 0x0101 };
#endif /* __R3000__ */

int sif_set_callback_func( u_int a0, sceSifCmdHandler a1, void *a2 )
{
	//
	// PLACEHOLDER
	//
}

void sif_send_packet_and_data()
{
	//
	// PLACEHOLDER
	//
}

void i_sif_send_packet_and_data()
{
	//
	// PLACEHOLDER
	//
}

void sif_send_direct()
{
	//
	// PLACEHOLDER
	//
}

void i_sif_send_direct()
{
	//
	// PLACEHOLDER
	//
}

u_int i_sif_send_mem( u_int *a0, volatile void *a1, u_int a2 )
{
	//
	// PLACEHOLDER
	//
}

u_int sif_send_mem( u_int *a0, volatile void *a1, u_int a2 )
{
	//
	// PLACEHOLDER
	//
}

int sif_check_status( u_int a0 )
{
	//
	// PLACEHOLDER
	//
}

void sif_init()
{
	//
	// PLACEHOLDER
	//
}

#if defined(__R3000__)
int KCEJ_sifman_init()
{
	//
	// PLACEHOLDER
	//
}
#endif /* __R3000__ */
