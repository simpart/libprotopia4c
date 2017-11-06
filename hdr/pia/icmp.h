/**
 * @file ether.h
 * @brief defined ethernet proto
 * @author simpart
 */
#include "pia/com.h"
#include "pia/ip.h"

#ifndef __ICMP_H__
#define __ICMP_H__

/*** define ***/
#define PIA_ICMP_MAXDAT 64
#define PIA_ICMP_DATDEFSIZ 56 // 32
#define PIA_ICMP_ECHREQ_DEFSIZE sizeof(pia_icmphdr_t) + sizeof(pia_icmpecho_t) + g_pia_icmpdat.size

/**
 * icmp type defined
 */
#define PIA_ICMP_ECHOREP  0x0  //! echo reply
#define PIA_ICMP_DSTUNRCH 0x3  //! destination unreachable
#define PIA_ICMP_REDIRECT 0x5  //! redirect
#define PIA_ICMP_ECHOREQ  0x8  //! echo request
#define PIA_ICMP_TMEXCD   0x11 //! time exceeded

/**
 * icmp code for destination unreachable
 */
#define PIA_ICMP_DUNR_NET    0x0 //! net unreachable
#define PIA_ICMP_DUNR_HST    0x1 //! host unreachable
#define PIA_ICMP_DUNR_PROT   0x2 //! protocol unreachable
#define PIA_ICMP_DUNR_PORT   0x3 //! port unreachable
#define PIA_ICMP_DUNR_DFSET  0x4 //! fragment needed and df was set
#define PIA_ICMP_DUNR_SRCRT  0x5 //! source route failed
#define PIA_ICMP_DUNR_DNWUK  0x6 //! destination network unknown
#define PIA_ICMP_DUNR_DHTUK  0x7 //! destination host unknown
#define PIA_ICMP_DUNR_SHISO  0x8 //! source host isolated
#define PIA_ICMP_DUNR_DNWPHD 0x9 //! communication with destination network is administratively prohibited
#define PIA_ICMP_DUNR_DHTPHD 0xA //! communication with destinaltion host is administratively prohibited
#define PIA_ICMP_DUNR_DNWTOS 0xB //! destination network unreachable for tos
#define PIA_ICMP_DUNR_DHTTOS 0xC //! destination host unreachable for tos
#define PIA_ICMP_DUNR_COMPHD 0xD //! communication administratively prohibited
#define PIA_ICMP_DUNR_HTPRCD 0xE //! host precedence violation
#define PIA_ICMP_DUNR_PRCDCF 0xF //! precedence cutoff in effect

/**
 * icmp code for redirect
 */
#define PIA_ICMP_RDCT_DGNW 0x0 //! redirect datagram for the network
#define PIA_ICMP_RDCT_DGHT 0x1 //! redirect datagram for the host
#define PIA_ICMP_RDCT_DGTN 0x2 //! redirect datagram for the tos and network
#define PIA_ICMP_RDCT_DGTH 0x3 //! redirect datagram for the tos and host

/**
 * icmp code for time exceeded
 */
#define PIA_ICMP_TMEX_TTL 0x0 //! time to live exceeded in transit
#define PIA_ICMP_TMEX_FGR 0x1 //! fragment reassembly time exceeded

/*** struct ***/
typedef struct pia_icmphdr {
    uint8_t  type;
    uint8_t  code;
    uint16_t chksum;
} pia_icmphdr_t;

typedef struct pia_icmpecho {
    uint16_t id;
    uint16_t seq;
} pia_icmpecho_t;

typedef struct pia_icmpdat {
    uint8_t data[PIA_ICMP_MAXDAT];
    uint8_t size;
} pia_icmpdat_t;

/*** prototype ***/
/* init */
int pia_icmp_init(void);
/* dump */
uint8_t pia_icmp_dump (pia_icmphdr_t *);
uint8_t pia_icmp_dump_detail (pia_ipv4hdr_t *);
char * pia_icmp_gettype_str (pia_icmphdr_t *);
char * pia_icmp_getcode_str (pia_icmphdr_t *);
uint8_t pia_icmp_dump_type (pia_icmphdr_t *);
uint8_t pia_icmp_dump_id(pia_icmphdr_t *);
uint8_t pia_icmp_dump_seq(pia_icmphdr_t *);
uint8_t pia_icmp_dump_dat(pia_icmphdr_t *, size_t);
/* classifier */
uint8_t pia_icmp_isecho (pia_icmphdr_t *);
uint8_t pia_icmp_isrequest (pia_icmphdr_t *);
uint8_t pia_icmp_isreply (pia_icmphdr_t *);
uint8_t pia_icmp_istype (pia_icmphdr_t *, uint8_t);
/* message */
int pia_icmp_setdef_type (uint8_t);
int pia_icmp_setdef_code (uint8_t); 
void pia_icmp_incdef_seq (void);
int pia_icmp_getfrm (uint8_t *, size_t);
int pia_icmp_getpkt (uint8_t *, size_t);
int pia_icmp_getmsg (pia_icmphdr_t *, size_t);
uint16_t pia_icmp_getid (pia_icmpecho_t *);
uint16_t pia_icmp_getseq (pia_icmpecho_t *);
uint8_t * pia_icmp_seekecho (pia_icmphdr_t *);
uint8_t * pia_icmp_seekecho_dat (pia_icmpecho_t *);
#endif
/* end of file */
