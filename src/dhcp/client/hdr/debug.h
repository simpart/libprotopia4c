/**
 * @file debug.h
 * @brief debug printer
 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

/*** include ***/
#include <common.h>
#include <time.h>
#include <packet/capsule/ether.h>
#include <packet/capsule/ip.h>
#include <packet/capsule/udp.h>
#include <packet/capsule/dhcp.h>
#include <packet/dump/dhcp.h>
#include <packet/dump/udp.h>
#include <packet/dump/ip.h>
#include <packet/dump/ether.h>

/*** define ***/
#define DDBG_PRINT(msg) dbg_print(__FILE__, __LINE__, (msg))

/*** prototype ***/
void dbg_print(char *, int, char *);
void dbg_printdhcp(ethhdr_t *);

#endif
/* end of file */
