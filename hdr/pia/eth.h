/**
 * @file eth.h
 * @brief defined ethernet header
 * @author simpart
 */
#include "pia/com.h"

#ifndef __PIAETH_H__
#define __PIAETH_H__

/*** define ***/
#define PIAETH_TYPE_IP  0x800
#define PIAETH_TYPE_ARP 0x806
#define PIAETH_MACSIZ   6
#define PIAETH_MAXSIZ   1518  // ethernet frame max size (byte)

/*** struct ***/
typedef struct piaeth_hdr {
    uint8_t  dmac[PIAETH_MACSIZ];
    uint8_t  smac[PIAETH_MACSIZ];
    uint16_t type;
} piaeth_hdr_t;

/*** prototype ***/
/* init */
int piaeth_init   (void);

/* classifier */
int piaeth_issrc   (piaeth_hdr_t *, uint8_t *);
int piaeth_isdst   (piaeth_hdr_t *, uint8_t *);
int piaeth_isbcast (piaeth_hdr_t *);
int piaeth_isip    (piaeth_hdr_t *);
int piaeth_isarp   (piaeth_hdr_t *);
int piaeth_isprot  (piaeth_hdr_t *, uint16_t);

/* dump */
int piaeth_dump    (piaeth_hdr_t *);
int piaeth_dumpdtl (piaeth_hdr_t *);

/* header */
int       piaeth_setdefmac  (uint8_t *, uint8_t *);
int       piaeth_setdeftype (uint16_t);
int       piaeth_setmac     (piaeth_hdr_t *, uint8_t *, uint8_t *);
int       piaeth_settype    (piaeth_hdr_t *, uint16_t);
int       piaeth_gethdr     (piaeth_hdr_t *, size_t);
int       piaeth_gethdr_ip  (piaeth_hdr_t *, size_t);
int       piaeth_gethdr_arp (piaeth_hdr_t *, size_t);
uint8_t * piaeth_seekpld    (piaeth_hdr_t *);
#endif
