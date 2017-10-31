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
int pia_eth_issrc  (uint8_t *, uint8_t *);
int pia_eth_isdst  (uint8_t *, uint8_t *);
int pia_eth_isip (uint8_t *);
int pia_eth_isarp (uint8_t *);
int pia_eth_isprot (uint8_t *, uint16_t);
/* dump */
int pia_eth_dump (pia_ethhdr_t *);
int pia_eth_dump_detail (pia_ethhdr_t *);
/* header */
int  pia_eth_setdefmac (uint8_t *, uint8_t *);
int  pia_eth_setdeftype (uint16_t);
int  pia_eth_setmac (pia_ethhdr_t *, uint8_t *, uint8_t *);
int  pia_eth_settype (pia_ethhdr_t *, uint16_t);
int  pia_eth_gethdr (uint8_t *, size_t);
int  pia_eth_gethdr_ip (uint8_t *, size_t);
int  pia_eth_gethdr_arp (uint8_t *, size_t);
uint8_t * pia_eth_getconts (uint8_t *);

#endif
