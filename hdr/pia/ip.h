/**
 * @file ip.h
 * @brief defined ip proto
 * @author simpart
 */
#include "pia/common.h"

#ifndef __IP_H__
#define __IP_H__

/*** struct ***/
typedef struct pia_ip_hdr {
#if __BYTE_ORDER == __BIG_ENDIAN
    uint8_t version:4;
    uint8_t ihl:4;
#else
    uint8_t ihl:4;
    uint8_t version:4;
#endif
    uint8_t  tos;
    uint16_t total;
    uint16_t id;
    uint16_t flag_off;
    uint8_t  ttl;
    uint8_t  prot;
    uint16_t chksum;
    uint32_t sip;
    uint32_t dip;
}

/* prototype */
int pia_isip (pkt);

#endif
/* end of file */
