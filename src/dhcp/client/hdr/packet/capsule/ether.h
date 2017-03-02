/**
 * @file ip.h
 */
#ifndef _CAPSLETHER_H_
#define _CAPSLETHER_H_

/*** include ***/
#include <common.h>
#include <netinet/ip.h>
#include <linux/if_ether.h>
#include <packet/struct.h>

/*** define ***/
#define DCEH_MYMAC_1 0x52
#define DCEH_MYMAC_2 0x54
#define DCEH_MYMAC_3 0x00
#define DCEH_MYMAC_4 0xbd
#define DCEH_MYMAC_5 0x58
#define DCEH_MYMAC_6 0x5f

/*** prototype ***/
u_char * ether_capsuling(ethhdr_t * , u_char *, u_int32_t); 

#endif
/* end of file */
