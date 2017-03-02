/**
 * @file   ip.h
 * @brief  show ip header
 */
#ifndef _DUMPIP_H_
#define _DUMPIP_H_

/*** include ***/
#include <common.h>
#include <packet/struct.h>
#include <packet/capsule/ip.h>

/*** define ***/

/*** prototype ***/
void dmp_iphdr(iphdr_t *);

#endif
/* end of file */
