/**
 * @file   dhcp.h
 * @brief  create dhcp message header
 */
#ifndef _DUMPDHCP_H_
#define _DUMPDHCP_H_

/*** include ***/
#include <common.h>
#include <packet/capsule/dhcp.h>
#include <packet/struct.h>

/*** define ***/

/*** prototype ***/
void dmp_discover(dhcpmsg_t *);

#endif
/* end of file */
