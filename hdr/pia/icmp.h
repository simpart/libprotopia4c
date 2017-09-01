/**
 * @file ether.h
 * @brief defined ethernet proto
 * @author simpart
 */
#include "pia/common.h"

#ifndef __ICMP_H__
#define __ICMP_H__

/*** struct ***/
typedef struct pia_icmp_hdr {
    uint8_t  type;
    uint8_t  code;
    uint8_t  chksum;
    uint16_t id;
    uint16_t seq;
} pia_icmp_hdr_t;

/*** prototype ***/
size_t pia_icmp_getecho (uint8_t *, size_t, int);
#endif
