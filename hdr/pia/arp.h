/**
 * @file arp.h
 * @brief defined arp protocol
 * @author simpart
 */
#include "pia/com.h"
#include "pia/eth.h"
#include "pia/ip.h"

#ifndef __ARP_H__
#define __ARP_H__

/*** define ***/
/* operation type */
#define PIA_ARP_OP_REQ 1
#define PIA_ARP_OP_REP 2

/* hardware type */
#define PIA_ARP_HTYPE_ETH 1  //! Ethernet

#define __PIA_ARP_STYLE__ MAC_IPV4

/*** struct ***/
typedef struct pia_arphdr {
    uint16_t htype;    //! Hardware Type 
    uint16_t ptype;    //! Protocol Type
    uint8_t  hlen;     //! Hardware Address Length
    uint8_t  plen;     //! Protocol Address Length
    uint16_t op;       //! Operation Code
#if __PIA_ARP_STYLE__ == MAC_IPV4
    uint8_t  shaddr[PIA_ETH_MACSIZE]; // source hardware address
    uint8_t  spaddr[PIA_IP_IPSIZE];   // source protocol address
    uint8_t  dhaddr[PIA_ETH_MACSIZE]; // destination hardware address
    uint8_t  dpaddr[PIA_IP_IPSIZE];   // destination protocol address
    uint8_t  pad[18];  //! padding
#endif
} pia_arphdr_t;

/*** prototype ***/
/* init */
int pia_arp_init (void);
/* header */
int pia_arp_getfrm (uint8_t *, size_t, uint8_t);
int pia_arp_gethdr (pia_arphdr_t *, size_t, uint8_t);
/* dump */
int pia_arp_dump (pia_arphdr_t *);
int pia_arp_dump_detail (pia_arphdr_t *);
int pia_arp_dump_htype (pia_arphdr_t *);
int pia_arp_dump_ptype (pia_arphdr_t *);
/* classifier */
int pia_arp_isrequest (pia_arphdr_t *);
int pia_arp_isreply (pia_arphdr_t *);
#endif
/* end of file */
