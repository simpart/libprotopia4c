/**
 * @file tcp.h
 * @brief defined tcp proto
 * @author simpart
 */
#include "pia/com.h"

#ifndef __PIATCP_H__
#define __PIATCP_H__

/*** define ***/
/**
 * @brief tcp header size without option area
 */
#define PIATCP_NOPTSIZ 20
/**
 * @brief value of port type
 */
#define PIATCP_PORT_SRC  0x100 //! source port
#define PIATCP_PORT_DST  0x101 //! destination port
/**
 * @brief value of controll flag
 **/
#define PIATCP_CFLG_FIN 0x01
#define PIATCP_CFLG_SYN 0x02
#define PIATCP_CFLG_RST 0x04
#define PIATCP_CFLG_PSH 0x08
#define PIATCP_CFLG_ACK 0x10  // 16
#define PIATCP_CFLG_URG 0x20  // 32
/**
 * @brief value of option type
 */
#define PIATCP_OPT_END  0x00  //! End Of Option List
#define PIATCP_OPT_NO   0x01  //! No Operation
#define PIATCP_OPT_MSS  0x02  //! Maximum Segment Size
#define PIATCP_OPT_WINS 0x03  //! Window Scale
#define PIATCP_OPT_SAPM 0x04  //! SACK Permitted
#define PIATCP_OPT_SACK 0x05  //! SACK
#define PIATCP_OPT_TMSP 0x08  //! Time Stamp

#define PIATCP_RET_OPTOVR -2 //! return value for getoption

/*** struct ***/
typedef struct piatcp_hdr {
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
} piatcp_hdr_t;

typedef struct piatcp_opt {
    uint8_t type;
    uint8_t len;
    uint8_t *val;
} piatcp_opt_t;

/*** global ***/

/*** prototype ***/
/* init */

/* dump */
int piatcp_dump         (piatcp_hdr_t *);
int piatcp_dump_detail  (piatcp_hdr_t *);
int piatcp_dump_port    (piatcp_hdr_t *);
int piatcp_dump_cflag   (piatcp_hdr_t *);
int piatcp_dump_opt     (piatcp_hdr_t *);
int piatcp_dump_opttmsp (piatcp_opt_t *);

/* header */
uint16_t piatcp_getport   (piatcp_hdr_t *, int);
uint32_t piatcp_getseq    (piatcp_hdr_t *);
uint32_t piatcp_getchkack (piatcp_hdr_t *);
uint8_t  piatcp_getoffset (piatcp_hdr_t *);
uint16_t piatcp_getwinsiz (piatcp_hdr_t *);
uint16_t piatcp_geturgptr (piatcp_hdr_t *);
int      piatcp_getopt    (piatcp_hdr_t *, piatcp_opt_t *, int);

/* classifier */
int piatcp_issyn      (piatcp_hdr_t *);
int piatcp_isack      (piatcp_hdr_t *);
int piatcp_isrst      (piatcp_hdr_t *);
int piatcp_issynack   (piatcp_hdr_t *);
int piatcp_isfinack   (piatcp_hdr_t *);
int piatcp_isctlflg   (piatcp_hdr_t *, uint8_t);
int piatcp_isurg      (piatcp_hdr_t *);
int piatcp_existsopt  (piatcp_hdr_t *);
int piatcp_isvalidopt (piatcp_opt_t *);
#endif
/* end of file */
