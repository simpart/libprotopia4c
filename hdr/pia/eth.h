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

/*** prototype ***/
/* init */
int  pia_eth_init   (void);
/* classifier */
int pia_eth_issrc  (pia_ethhdr_t *, uint8_t *);
int pia_eth_isdst  (pia_ethhdr_t *, uint8_t *);
int pia_eth_isip (pia_ethhdr_t *);
int pia_eth_isarp (pia_ethhdr_t *);
int pia_eth_isprot (pia_ethhdr_t *, uint16_t);
/* dump */
int pia_eth_dump (pia_ethhdr_t *);
int pia_eth_dump_detail (pia_ethhdr_t *);
/* header */
int  pia_eth_setdefmac (uint8_t *, uint8_t *);
int  pia_eth_setdeftype (uint16_t);
int  pia_eth_setmac (pia_ethhdr_t *, uint8_t *, uint8_t *);
int  pia_eth_settype (pia_ethhdr_t *, uint16_t);
int  pia_eth_gethdr (pia_ethhdr_t *, size_t);
int  pia_eth_gethdr_ip (pia_ethhdr_t *, size_t);
int  pia_eth_gethdr_arp (pia_ethhdr_t *, size_t);
uint8_t * pia_eth_seekpld (pia_ethhdr_t *);
#endif
