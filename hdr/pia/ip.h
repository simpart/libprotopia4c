/**
 * @file ip.h
 * @brief defined ip proto
 * @author simpart
 */
#include "pia/com.h"

#ifndef __PIAIP_H__
#define __PIAIP_H__

/*** define ***/
#define PIAIP_IPSIZ 4  //! address size (version4)
/**
 * @brief data area protocol type
 */
#define PIAIP_TYPE_ICMP 0x01
#define PIAIP_TYPE_TCP  0x06
#define PIAIP_TYPE_UDP  0x17
/**
 * @brief tos dump type
 */
#define PIAIP_TOSDMP PIAIP_PREC 
#define PIAIP_PREC  0x10   //! ip precedence
#define PIAIP_DSCP  0x11   //! dscp

#define PIAIP_CSUMMODE_MANU 0x100 //! manual mode
#define PIAIP_CSUMMODE_AUTO 0x101 //! auto mode
#define PIAIP_CSUMMODE PIAIP_CSUMMODE_AUTO

/*** struct ***/
typedef struct piaip_v4hdr {
#if __PIA_BYTEORDER__ == PIA_BYOR_LITED
    uint8_t  hlen:4;
    uint8_t  ver:4;
#else
    uint8_t  ver:4;
    uint8_t  hlen:4;
#endif
    uint8_t  tos;
    uint16_t total;
    uint16_t id;
    uint16_t frag_off;
    uint8_t  ttl;
    uint8_t  prot;
    uint16_t chksum;
    uint8_t  sip[PIAIP_IPSIZ];
    uint8_t  dip[PIAIP_IPSIZ];
} piaip_v4hdr_t;

/*** global ***/
extern piaip_v4hdr_t g_piaip_v4hdr;
extern uint32_t g_seq;

/*** prototype ***/
/* init */
int piaip_init (void);

/* dump */
int          piaip_dump         (piaip_v4hdr_t *);
int          piaip_dumpdtl      (piaip_v4hdr_t *);
int          piaip_dumpv4       (piaip_v4hdr_t *);
int          piaip_dumpv6       (piaip_v4hdr_t *);
int          piaip_dump_ver     (piaip_v4hdr_t *);
int          piaip_dump_hlen    (piaip_v4hdr_t *);
int          piaip_dumptos      (piaip_v4hdr_t *, int);
int          piaip_dump_fragoff (piaip_v4hdr_t *);
const char * piaip_dump_protstr (piaip_v4hdr_t *);
int          piaip_dump_prot    (piaip_v4hdr_t *);
int          piaip_dump_ipv4    (piaip_v4hdr_t *);
int          piaip_dump_tos     (piaip_v4hdr_t *, int);
int          piaip_dump_tosprec (piaip_v4hdr_t *);
int          piaip_dump_tosdscp (piaip_v4hdr_t *);

/* header */
int       piaip_setdefipv4    (uint8_t *      , uint8_t *);
int       piaip_setipv4       (piaip_v4hdr_t *, uint8_t *, uint8_t *);
int       piaip_getfrm        (uint8_t *      , size_t   , int);
void      piaip_setdefip      (uint8_t *      , uint8_t *);
void      piaip_setip         (piaip_v4hdr_t *, uint8_t *, uint8_t *);
int       piaip_sethdrlen     (piaip_v4hdr_t *, size_t);
int       piaip_gethdrlen     (piaip_v4hdr_t *);
uint16_t  piaip_gettotal      (piaip_v4hdr_t *);
int       piaip_settotal      (piaip_v4hdr_t *, uint16_t);
uint16_t  piaip_getid         (piaip_v4hdr_t *);
int       piaip_updid         (piaip_v4hdr_t *);
int       piaip_setprot       (piaip_v4hdr_t *, int8_t);
uint8_t   piaip_getprot       (piaip_v4hdr_t *);
int       piaip_addopt        (piaip_v4hdr_t *, uint8_t *, size_t);
int       piaip_getpldsize    (piaip_v4hdr_t *);
int       piaip_setpldsize    (piaip_v4hdr_t *, size_t);
int       piaip_updchksum     (piaip_v4hdr_t *);
int       piaip_capsule       (piaip_v4hdr_t *, uint8_t *, size_t);
int       piaip_getv4hdr      (piaip_v4hdr_t *, size_t);
int       piaip_getv4hdr_tcp  (piaip_v4hdr_t *, size_t);
int       piaip_getv4hdr_udp  (piaip_v4hdr_t *, size_t);
int       piaip_getv4hdr_icmp (piaip_v4hdr_t *, size_t);
int       piaip_incid         (piaip_v4hdr_t *);
uint8_t * piaip_seekpld       (piaip_v4hdr_t *);

/* classifier */
int piaip_isv4     (piaip_v4hdr_t *);
int piaip_isv6     (piaip_v4hdr_t *);
int piaip_istos    (piaip_v4hdr_t *, uint8_t);
int pisip_issetopt (piaip_v4hdr_t *);
int piaip_isfgmt   (piaip_v4hdr_t *);
int piaip_isalived (piaip_v4hdr_t *);
int piaip_isicmp   (piaip_v4hdr_t *);
int piaip_istcp    (piaip_v4hdr_t *);
int piaip_isudp    (piaip_v4hdr_t *);
int piaip_isprot   (piaip_v4hdr_t *, uint8_t);
int piaip_issrc    (piaip_v4hdr_t *, uint8_t *);
int piaip_isdst    (piaip_v4hdr_t *, uint8_t *);
int piaip_is3way   (piaip_v4hdr_t *);
/* util */
#endif
/* end of file */
