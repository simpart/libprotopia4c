/**
 * @file ip.h
 * @brief defined ip proto
 * @author simpart
 */
#include "pia/com.h"

#ifndef __IP_H__
#define __IP_H__

/*** define ***/
#define PIA_IP_IPSIZE 4
#define PIA_IP_ICMP 0x01
#define PIA_IP_TCP  0x06
#define PIA_IP_UDP  0x17

/*** struct ***/
typedef struct pia_ipv4hdr {
#if __BYTE_ORDER == __BIG_ENDIAN
    uint8_t ver:4;
    uint8_t hlen:4;
#else
    uint8_t hlen:4;
    uint8_t ver:4;
#endif
    uint8_t  tos;
    uint16_t total;
    uint16_t id;
    uint16_t flag_off;
    uint8_t  ttl;
    uint8_t  prot;
    uint16_t chksum;
    uint8_t  sip[PIA_IP_IPSIZE];
    uint8_t  dip[PIA_IP_IPSIZE];
} pia_ipv4hdr_t;

/*** global ***/
extern pia_ipv4hdr_t g_pia_ipv4hdr;
extern uint8_t  g_icmp_data[32];
extern uint32_t g_seq;

/* prototype */
int      pia_isip (pkt);
int      pia_ip_init (void);
void     pia_ip_setip (uint8_t *, uint8_t *);
int      pia_ip_getv4hdr (uint8_t *, size_t);
int      pia_ip_getv4hdr_tcp (uint8_t *, size_t);
int      pia_ip_getv4hdr_udp (uint8_t *, size_t);
int      pia_ip_getv4hdr_icmp (uint8_t *, size_t);
uint16_t pia_ip_getid (void);
#endif
/* end of file */
