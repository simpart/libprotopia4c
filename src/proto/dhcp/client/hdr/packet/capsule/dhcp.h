/**
 * @file   dhcp.h
 * @brief  create dhcp message header
 */
#ifndef _CAPSLDHCP_H_
#define _CAPSLDHCP_H_

/*** include ***/
#include <common.h>
#include <time.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <packet/struct.h>

/*** define ***/
#define DCDH_MAC_1 0x52
#define DCDH_MAC_2 0x54
#define DCDH_MAC_3 0x00
#define DCDH_MAC_4 0xbd
#define DCDH_MAC_5 0x58
#define DCDH_MAC_6 0x5f

#define DCDH_FIRST_REQADDR1 192
#define DCDH_FIRST_REQADDR2 168
#define DCDH_FIRST_REQADDR3 1
#define DCDH_FIRST_REQADDR4 104

/*** prototype ***/
dhcpmsg_t * cdh_get_discover(void);
dhcpmsg_t * cdh_get_discover_pri(void);
void cdh_setopt_msgtype(dhcpmsg_t **, u_int16_t, u_int16_t);
void cdh_setopt_reqaddr (dhcpmsg_t **, u_char *, u_int16_t);
void cdh_setopt_reqconts(dhcpmsg_t **, u_char *, u_int16_t, u_int16_t);
#endif
/* end of file */
