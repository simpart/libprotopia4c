/**
 * @file icmp.h
 * @brief defined icmp protocol
 * @author simpart
 */
#include "pia/com.h"
#include "pia/ip.h"

#ifndef __PIAICM_H__
#define __PIAICM_H__

/*** define ***/
#define PIAICM_MAXDAT 64
#define PIAICM_DATDEFSIZ 56 // 32
#define PIAICM_ECHREQ_DEFSIZ sizeof(piaicm_hdr_t) + sizeof(piaicm_echo_t) + g_piaicm_dat.size

/**
 * icmp type defined
 */
#define PIAICM_TYPE_ECHOREP  0x0  //! echo reply
#define PIAICM_TYPE_DSTUNRCH 0x3  //! destination unreachable
#define PIAICM_TYPE_REDIRECT 0x5  //! redirect
#define PIAICM_TYPE_ECHOREQ  0x8  //! echo request
#define PIAICM_TYPE_TMEXCD   0x11 //! time exceeded

/**
 * icmp code for destination unreachable
 */
#define PIAICM_DUNR_NET    0x0 //! net unreachable
#define PIAICM_DUNR_HST    0x1 //! host unreachable
#define PIAICM_DUNR_PROT   0x2 //! protocol unreachable
#define PIAICM_DUNR_PORT   0x3 //! port unreachable
#define PIAICM_DUNR_DFSET  0x4 //! fragment needed and df was set
#define PIAICM_DUNR_SRCRT  0x5 //! source route failed
#define PIAICM_DUNR_DNWUK  0x6 //! destination network unknown
#define PIAICM_DUNR_DHTUK  0x7 //! destination host unknown
#define PIAICM_DUNR_SHISO  0x8 //! source host isolated
#define PIAICM_DUNR_DNWPHD 0x9 //! communication with destination network is administratively prohibited
#define PIAICM_DUNR_DHTPHD 0xA //! communication with destinaltion host is administratively prohibited
#define PIAICM_DUNR_DNWTOS 0xB //! destination network unreachable for tos
#define PIAICM_DUNR_DHTTOS 0xC //! destination host unreachable for tos
#define PIAICM_DUNR_COMPHD 0xD //! communication administratively prohibited
#define PIAICM_DUNR_HTPRCD 0xE //! host precedence violation
#define PIAICM_DUNR_PRCDCF 0xF //! precedence cutoff in effect

/**
 * icmp code for redirect
 */
#define PIAICM_RDCT_DGNW 0x0 //! redirect datagram for the network
#define PIAICM_RDCT_DGHT 0x1 //! redirect datagram for the host
#define PIAICM_RDCT_DGTN 0x2 //! redirect datagram for the tos and network
#define PIAICM_RDCT_DGTH 0x3 //! redirect datagram for the tos and host

/**
 * icmp code for time exceeded
 */
#define PIAICM_TMEX_TTL 0x0 //! time to live exceeded in transit
#define PIAICM_TMEX_FGR 0x1 //! fragment reassembly time exceeded

/*** struct ***/
typedef struct piaicm_hdr {
    uint8_t  type;
    uint8_t  code;
    uint16_t chksum;
} piaicm_hdr_t;

typedef struct piaicm_echo {
    uint16_t id;
    uint16_t seq;
} piaicm_echo_t;

typedef struct piaicm_dat {
    uint8_t data[PIAICM_MAXDAT];
    uint8_t size;
} piaicm_dat_t;

/*** prototype ***/
/* init */
int piaicm_init(void);

/* dump */
uint8_t      piaicm_dump        (piaicm_hdr_t *);
uint8_t      piaicm_dumpdtl     (piaip_v4hdr_t *);
const char * piaicm_gettype_str (piaicm_hdr_t *);
const char * piaicm_getcode_str (piaicm_hdr_t *);
uint8_t      piaicm_dump_type   (piaicm_hdr_t *);
uint8_t      piaicm_dump_id     (piaicm_hdr_t *);
uint8_t      piaicm_dump_seq    (piaicm_hdr_t *);
uint8_t      piaicm_dump_dat    (piaicm_hdr_t *, size_t);

/* classifier */
uint8_t piaicm_isecho    (piaicm_hdr_t *);
uint8_t piaicm_isrequest (piaicm_hdr_t *);
uint8_t piaicm_isreply   (piaicm_hdr_t *);
uint8_t piaicm_istype    (piaicm_hdr_t *, uint8_t);

/* message */
int       piaicm_setdef_type  (uint8_t);
int       piaicm_setdef_code  (uint8_t); 
void      piaicm_incdef_seq   (void);
int       piaicm_getfrm       (uint8_t *,      size_t);
int       piaicm_getpkt       (uint8_t *,      size_t);
int       piaicm_getmsg       (piaicm_hdr_t *, size_t);
uint16_t  piaicm_getid        (piaicm_echo_t *);
uint16_t  piaicm_getseq       (piaicm_echo_t *);
uint8_t * piaicm_seekecho     (piaicm_hdr_t *);
uint8_t * piaicm_seekecho_dat (piaicm_echo_t *);
#endif
/* end of file */
