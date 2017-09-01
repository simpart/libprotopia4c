/**
 * @file ether.h
 * @brief defined ethernet proto
 * @author simpart
 */
#include "pia/common.h"

#ifndef __ETHER_H__
#define __ETHER_H__

/*** define ***/
#define PIA_ETH_IP  0x800
#define PIA_ETH_ARP 0x806


/*** struct ***/
typedef struct pia_eth_hdr {
    uint8_t  dmac[6];
    uint8_t  smac[6];
    uint16_t type;
} pia_eth_hdr_t;

typedef struct pia_eth_frm {
    pia_eth_hdr_t hdr;  /* header */
    uint8_t *     pld;  /* payload */
} pia_eth_frm_t;

/*** prototype ***/
void          pia_eth_dump (pia_eth_hdr_t *);
int           pia_eth_setmac (uint8_t *dmac, uint8_t *smac);
pia_eth_hdr_t pia_eth_gethdr (uint16_t type);


#endif
