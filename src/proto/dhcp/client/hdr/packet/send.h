/**
 * @file   send.h
 * @brief  packet send header
 */
#ifndef _PKTSEND_H_
#define _PKTSEND_H_

/*** include ***/
#include <common.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <sys/ioctl.h> 
#include <net/if.h> 

/*** define ***/
#define DPSD_IFNAME "eth0"

/*** prototype ***/
int psd_init (void);
int psd_sendpkt(u_char *, u_int32_t);

#endif
/* end of file */
