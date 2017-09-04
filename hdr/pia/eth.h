/**
 * @file eth.h
 * @brief defined ethernet header
 * @author simpart
 */
#include "pia/com.h"

#ifndef __ETHER_H__
#define __ETHER_H__

/*** define ***/
#define PIA_ETH_IP  0x800
#define PIA_ETH_ARP 0x806


#define PIA_ETH_MACSIZE 6

/*** struct ***/
typedef struct pia_ethhdr {
    uint8_t  dmac[PIA_ETH_MACSIZE];
    uint8_t  smac[PIA_ETH_MACSIZE];
    uint16_t type;
} pia_ethhdr_t;

typedef struct pia_ethfrm {
    pia_ethhdr_t hdr;  /* header */
    uint8_t *     pld;  /* payload */
} pia_ethfrm_t;

/*** prototype ***/
void pia_eth_dump (uint8_t *);
int  pia_eth_init (void);
int  pia_eth_setmac (uint8_t *, uint8_t *);
int pia_eth_settype (uint16_t);
int  pia_eth_gethdr (uint8_t *, size_t);
int  pia_eth_gethdr_ip (uint8_t *, size_t);
#endif
