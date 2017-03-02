/**
 * @file   ip.h
 * @brief  show ip header
 */
#ifndef _DUMPETHER_H_
#define _DUMPETHER_H_

/*** include ***/
#include <common.h>
#include <packet/capsule/ether.h>
#include <packet/struct.h>

/*** define ***/

/*** prototype ***/
void dmp_ethhdr(ethhdr_t *);

#endif
/* end of file */
