/**
 * @file ether.h
 * @brief defined ethernet proto
 * @author simpart
 */
#include "pia/common.h"

#ifndef __ETHER_H__
#define __ETHER_H__


typedef struct piast_ether_hdr {
    uchar dmac[6];
    uchar smac[6];
    uchar type[2];
} piast_ether_hdr_t;

typedef struct piast_ether {
    piast_ether_hdr_t hdr;
    pkt               pld;
} piast_ether_t;

/*** prototype ***/
void pia_dmp_ether(piast_ether_hdr_t *);

#endif
