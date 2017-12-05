/**
 * @file tcp.h
 * @brief defined tcp proto
 * @author simpart
 */
#include "pia/com.h"

#ifndef __PIA_TCP_H__
#define __PIA_TCP_H__

/*** define ***/
/**
 * @brief tcp header size without option area
 */
#define PIA_TCP_NOPTSIZ 20
/**
 * @brief value of port type
 */
#define PIA_TCP_SPORT  0x100
#define PIA_TCP_DPORT  0x101
/**
 * @brief value of controll flag
 **/
#define PIA_TCP_FINFLG 0x01
#define PIA_TCP_SYNFLG 0x02
#define PIA_TCP_RSTFLG 0x04
#define PIA_TCP_PSHFLG 0x08
#define PIA_TCP_ACKFLG 0x10  // 16
#define PIA_TCP_URGFLG 0x20  // 32
/**
 * @brief value of option type
 */
#define PIA_TCP_OPTEND  0x00  //! End Of Option List
#define PIA_TCP_OPTNOO  0x01  //! No Operation
#define PIA_TCP_OPTMSS  0x02  //! Maximum Segment Size
#define PIA_TCP_OPTWINS 0x03  //! Window Scale
#define PIA_TCP_OPTSAPM 0x04  //! SACK Permitted
#define PIA_TCP_OPTSACK 0x05  //! SACK
#define PIA_TCP_OPTTMSP 0x08  //! Time Stamp

#define PIA_TCP_OPTOVR -2 //! return value for getoption

/*** struct ***/
typedef struct pia_tcphdr {
    uint16_t sport;
    uint16_t dport;
    uint32_t seq;
    uint32_t chkack;
#if __PIA_BYTEORDER__ == PIA_BYOR_LITED
    uint8_t rsrv_1:4;
    uint8_t offset:4;
    uint8_t ctlflg:6;
    uint8_t rsrv_2:2;
#else
    uint8_t offset:4;
    uint8_t rsrv_1:4;
    uint8_t rsrv_2:2;
    uint8_t ctlflg:6;
#endif
    uint16_t winsiz;
    uint16_t chksum;
    uint16_t urgptr;
} pia_tcphdr_t;

typedef struct pia_tcpopt {
    uint8_t type;
    uint8_t len;
    uint8_t *val;
} pia_tcpopt_t;

/*** global ***/

/*** prototype ***/
/* init */
/* dump */
int pia_tcp_dump (pia_tcphdr_t *);
int pia_tcp_dump_detail (pia_tcphdr_t *);
int pia_tcp_dump_port (pia_tcphdr_t *);
int pia_tcp_dump_cflag (pia_tcphdr_t *);
int pia_tcp_dump_opt(pia_tcphdr_t *);
int pia_tcp_dump_opttmsp(pia_tcpopt_t *);
/* header */
uint16_t pia_tcp_getport (pia_tcphdr_t *, int);
uint32_t pia_tcp_getseq (pia_tcphdr_t *);
uint32_t pia_tcp_getchkack (pia_tcphdr_t *);
uint8_t pia_tcp_getoffset(pia_tcphdr_t *);
uint16_t pia_tcp_getwinsiz (pia_tcphdr_t *);
uint16_t pia_tcp_geturgptr (pia_tcphdr_t *);
int pia_tcp_getopt (pia_tcphdr_t *, pia_tcpopt_t *, int);
/* classifier */
int pia_tcp_issyn (pia_tcphdr_t *);
int pia_tcp_issynack (pia_tcphdr_t *);
int pia_tcp_isfin (pia_tcphdr_t *);
int pia_tcp_isctlflg (pia_tcphdr_t *, uint8_t);
int pia_tcp_isurg (pia_tcphdr_t *);
int pia_tcp_existsopt(pia_tcphdr_t *);
int pia_tcp_isvalidopt (pia_tcpopt_t *);
#endif
/* end of file */
