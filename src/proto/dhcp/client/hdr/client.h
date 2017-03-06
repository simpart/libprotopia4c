/**
 * @file   client.h
 * @brief  client header
 */
#ifndef _CLIENT_H_
#define _CLIENT_H_

/* include */
#include <common.h>
#include <packet/struct.h>
#include <packet/send.h>
#include <netinet/udp.h>
#include <packet/capsule/dhcp.h>
#include <packet/capsule/udp.h>
#include <packet/capsule/ip.h>
#include <packet/capsule/ether.h>
#include <packet/dump/dhcp.h>
#include <packet/dump/udp.h>
#include <packet/dump/ip.h>
#include <packet/dump/ether.h>

/*** prototype ***/
int clt_start (void);
int clt_discover (void);
u_char * clt_get_udpdiscv(u_char *);
u_char * clt_get_ipdiscv(u_char *);
u_char * clt_get_etherdiscv(u_char *);

#endif
/* end of file */
