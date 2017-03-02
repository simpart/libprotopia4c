/**
 * @file   udp.h
 * @brief  show udp header
 */
#ifndef _DUMPUDP_H_
#define _DUMPUDP_H_

/*** include ***/
#include <common.h>
#include <packet/struct.h>
#include <packet/capsule/udp.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

/*** define ***/

/*** prototype ***/
void dmp_udphdr(udphdr_t *);

#endif
/* end of file */
