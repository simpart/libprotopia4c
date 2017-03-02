/**
 * @file ip.h
 */
#ifndef _CAPSLIP_H_
#define _CAPSLIP_H_

/*** include ***/
#include <common.h>
#include <netinet/ip.h>
#include <packet/struct.h>

/*** prototype ***/
u_char * ip_capsuling(
             iphdr_t *,
             u_char *,
             u_int32_t
         );
int ip_chksum( iphdr_t * );


#endif
/* end of file */
