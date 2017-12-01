/**
 * @file tcp.h
 * @brief defined tcp proto
 * @author simpart
 */
#include "pia/com.h"

#ifndef __PIA_TCP_H__
#define __PIA_TCP_H__

/*** define ***/
#define PIA_TCP_SPORT  0x100
#define PIA_TCP_DPORT  0x101

/*** struct ***/
typedef struct pia_tcphdr {
    uint16_t sport;
    uint16_t dport;
    uint32_t seq;
    uint32_t chkack;
#if PIA_BYTEORDER__ == PIA_BYOR_LITED
    uint8_t offset:4;
    uint8_t rsrv_1:4;
    uint8_t rsrv_2:2;
    uint8_t ctlflg:6;
#else
    uint8_t ctlflg:6;
    uint8_t rsrv_1:2;
    uint8_t rsrv_2:2;
    uint8_t offset:4;
#endif
    uint16_t winsiz;
    uint16_t chksum;
    uint16_t urgptr;
} pia_tcphdr_t;

/*** global ***/

/*** prototype ***/
/* init */
/* dump */
int pia_tcp_dump (pia_tcphdr_t *);
int pia_tcp_dump_detail (pia_tcphdr_t *);
int pia_tcp_dump_port (pia_tcphdr_t *);
/* header */
uint16_t pia_tcp_getport (pia_tcphdr_t *, int);
/* classifier */
#endif
/* end of file */
