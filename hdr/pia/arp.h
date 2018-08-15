/**
 * @file arp.h
 * @brief defined arp protocol
 * @author simpart
 */
#include "pia/com.h"
#include "pia/eth.h"
#include "pia/ip.h"

#ifndef __PIAARP_H__
#define __PIAARP_H__

/*** define ***/
/* operation type */
#define PIAARP_OP_REQ 1 //! request
#define PIAARP_OP_REP 2 //! reply

/* hardware type */
#define PIAARP_HTYPE_ETH 1  //! Ethernet

#define __PIAARP_STYLE__ MAC_IPV4

/*** struct ***/
typedef struct piaarp_hdr {
    uint16_t htype;    //! Hardware Type 
    uint16_t ptype;    //! Protocol Type
    uint8_t  hlen;     //! Hardware Address Length
    uint8_t  plen;     //! Protocol Address Length
    uint16_t op;       //! Operation Code
#if __PIAARP_STYLE__ == MAC_IPV4
    uint8_t  shaddr[PIAETH_MACSIZ]; //! source hardware address
    uint8_t  spaddr[PIAIP_IPSIZ];   //! source protocol address
    uint8_t  dhaddr[PIAETH_MACSIZ]; //! destination hardware address
    uint8_t  dpaddr[PIAIP_IPSIZ];   //! destination protocol address
    uint8_t  pad[18];  //! padding
#endif
} piaarp_hdr_t;

/*** prototype ***/
/* init */
int piaarp_init (void);

/* header */
int piaarp_getfrm (uint8_t *, size_t, uint8_t);
int piaarp_gethdr (piaarp_hdr_t *, size_t, uint8_t);

/* dump */
int piaarp_dump       (piaarp_hdr_t *);
int piaarp_dumpdtl    (piaarp_hdr_t *);
int piaarp_dump_htype (piaarp_hdr_t *);
int piaarp_dump_ptype (piaarp_hdr_t *);

/* classifier */
int piaarp_isrequest (piaarp_hdr_t *);
int piaarp_isreply   (piaarp_hdr_t *);
#endif
/* end of file */
