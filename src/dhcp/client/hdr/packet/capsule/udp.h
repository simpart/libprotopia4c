/**
 * @file   udp.h
 * @brief  cupsuling with udp header
 */
#ifndef _CAPSLUDP_H_
#define _CAPSLUDP_H_

/*** include ***/
#include <common.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <packet/struct.h>
#include <packet/capsule/dhcp.h>
#include <arpa/inet.h>

/*** define ***/

/*** enum ***/
typedef enum Eudp_dhcp {
    EUDP_DHCP_DISC,
    EUDP_DHCP_OFFR,
    EUDP_DHCP_REQS,
    EUDP_DHCP_XACK
}Eudp_dhcp_t;

/*** prototype ***/
u_char * udp_capsuling(dummy_udphdr_t *, udphdr_t *, u_char *);
int udp_get_chksum(u_char * , int);

#endif
/* end of file */
