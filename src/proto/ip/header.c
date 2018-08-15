/**
 * @file ip/header.c
 * @brief header function for ip header
 * @author simpart
 */
/***include  ***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pia/com.h"
#include "pia/ip.h"
#include "pia/eth.h"

/*** global ***/
extern piaip_v4hdr_t g_piaip_v4hdr;
extern piaip_v4hdr_t g_piaip_v4hdr_tcp;
extern piaip_v4hdr_t g_piaip_v4hdr_udp;
extern piaip_v4hdr_t g_piaip_v4hdr_icmp;
extern int g_piaip_setaddr;

/*** function ***/
/**
 * set default ip address,set to global area
 * 
 * @param sip : source ip address
 * @param dip : dest ip address
 * @return PIA_OK proccessing success
 */
int piaip_setdefipv4 (uint8_t *sip, uint8_t *dip) {
    uint8_t cmp_ip[PIAIP_IPSIZ] = {0};
    
    /* set src ip */
    if (NULL != sip) {
        memcpy(g_piaip_v4hdr.sip,      sip, PIAIP_IPSIZ);
        memcpy(g_piaip_v4hdr_tcp.sip,  sip, PIAIP_IPSIZ);
        memcpy(g_piaip_v4hdr_udp.sip,  sip, PIAIP_IPSIZ);
        memcpy(g_piaip_v4hdr_icmp.sip, sip, PIAIP_IPSIZ);
    }
    /* set dest ip */
    if (NULL != dip) {
        memcpy(g_piaip_v4hdr.dip,      dip, PIAIP_IPSIZ);
        memcpy(g_piaip_v4hdr_tcp.dip,  dip, PIAIP_IPSIZ);
        memcpy(g_piaip_v4hdr_udp.dip,  dip, PIAIP_IPSIZ);
        memcpy(g_piaip_v4hdr_icmp.dip, dip, PIAIP_IPSIZ);
    }
    /* update init flag */
    if ((NULL != sip) && (NULL != dip)) {
        g_piaip_setaddr = PIA_TRUE;
    } else if ( (0 != memcmp(&(g_piaip_v4hdr.sip[0]), &cmp_ip[0], PIAIP_IPSIZ)) &&
                (0 != memcmp(&(g_piaip_v4hdr.dip[0]), &cmp_ip[0], PIAIP_IPSIZ))) {
        g_piaip_setaddr = PIA_TRUE;
    }
    
    piaip_updchksum(&g_piaip_v4hdr);
    piaip_updchksum(&g_piaip_v4hdr_tcp);
    piaip_updchksum(&g_piaip_v4hdr_udp);
    piaip_updchksum(&g_piaip_v4hdr_icmp);
    
    return PIA_OK;
}

/**
 * set ip address,set to parameter header
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @param[in] sip : head pointer to source ip address
 * @param[in] dip : head pointer to destination ip address
 * @return PIA_OK : set ipaddress is success
 * @return PIA_NG : set ipaddress failed
 */
int piaip_setipv4 (piaip_v4hdr_t *ip_hdr, uint8_t *sip, uint8_t *dip) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    /* set src ip */
    if (NULL != sip) {
        memcpy(ip_hdr->sip, sip, PIAIP_IPSIZ);
    }
    /* set dest ip */
    if (NULL != dip) {
        memcpy(ip_hdr->dip, dip, PIAIP_IPSIZ);
    }
    
    piaip_updchksum(ip_hdr);
    
    return PIA_OK;
}

/**
 * set header length
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @param[in] byte : new header length
 * @return PIA_OK : success
 * @return PIA_NG : failed
 * @note total length and checksum is recalculated
 */
int piaip_sethdrlen (piaip_v4hdr_t * ip_hdr, size_t byte) {
    int diff = 0;
    
    /* check parameter */
    if ((NULL == ip_hdr) || (0 != (byte%4)) ) {
        return PIA_NG;
    }
    
    diff = byte - piaip_gethdrlen(ip_hdr);
    ip_hdr->hlen  =  (byte/4);
    ip_hdr->total = PIA_M_BYTORD16(PIA_M_BYTORD16(((ip_hdr->total) + diff)));
    piaip_updchksum(ip_hdr);
    return PIA_OK;
}

/**
 * get header length
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @return header length (byte)
 * @return PIA_NG : failed
 */
int piaip_gethdrlen (piaip_v4hdr_t * ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    return ip_hdr->hlen * 4;
}

uint16_t piaip_gettotal (piaip_v4hdr_t * ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    return PIA_M_BYTORD16(ip_hdr->total);
}

int piaip_settotal (piaip_v4hdr_t * ip_hdr, uint16_t size) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    ip_hdr->total = PIA_M_BYTORD16(size);
    piaip_updchksum(ip_hdr);
    
    return PIA_OK;
}

uint16_t piaip_getid (piaip_v4hdr_t * ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    return PIA_M_BYTORD16(ip_hdr->id);
}

int piaip_updid (piaip_v4hdr_t * ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    ip_hdr->id = PIA_M_BYTORD16(pia_random(PIA_RANDOM_16));
    piaip_updchksum(ip_hdr);
    return PIA_OK;
}

int piaip_setprot (piaip_v4hdr_t * ip_hdr, int8_t prot) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    ip_hdr->prot = prot;
    piaip_updchksum(ip_hdr);
    return PIA_OK;
}

uint8_t piaip_getprot (piaip_v4hdr_t * ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    return ip_hdr->prot;
}

int piaip_addopt (piaip_v4hdr_t * ip_hdr, uint8_t *opt, size_t opt_siz) {
    int      pld_siz = 0;
    uint8_t *pld_buf = NULL;
    uint8_t *seek    = NULL;
    
    if ((NULL == ip_hdr) || (NULL == opt)) {
        return PIA_NG;
    }
    
    /* get payload size */
    pld_siz = piaip_getpldsize(ip_hdr);
    if (PIA_NG == pld_siz) {
        return PIA_NG;
    }
    
    /* buffering payload */
    seek = piaip_seekpld(ip_hdr);
    if (NULL == seek) {
        return PIA_NG;
    }
    pld_buf = (uint8_t *) malloc(pld_siz);
    if (NULL == pld_buf) {
        return PIA_NG;
    }
    memcpy(pld_buf, seek, pld_siz);

    /* add option */
    memset(seek, 0x00, pld_siz);
    memcpy(seek, opt, opt_siz);

    /* update header value */
    piaip_sethdrlen (
        ip_hdr,
        piaip_gethdrlen(ip_hdr) + opt_siz
    );

    seek = piaip_seekpld(ip_hdr);
    
    /* link payload */
    memcpy(seek, pld_buf, pld_siz);

    free(pld_buf);
    return PIA_OK;
}

/**
 * get payload size
 *
 * @param[in] ip_hdr : head pointer to ip header
 * @return total length (byte)
 * @return PIA_NG : failed
 */
int piaip_getpldsize (piaip_v4hdr_t * ip_hdr) {
    uint16_t total = 0;
    
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    total = PIA_M_BYTORD16(ip_hdr->total);
    return total - (ip_hdr->hlen*4);
}

int piaip_setpldsize (piaip_v4hdr_t * ip_hdr, size_t size) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    ip_hdr->total = PIA_M_BYTORD16(((ip_hdr->hlen*4) + size));
    piaip_updchksum(ip_hdr);
    return PIA_OK;
}

int piaip_updchksum (piaip_v4hdr_t * ip_hdr) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    ip_hdr->chksum = pia_checksum((uint16_t *)ip_hdr, ip_hdr->hlen*4);
    
    return PIA_OK;
}

int piaip_capsule (piaip_v4hdr_t * ip_hdr, uint8_t *pld, size_t siz) {
    uint8_t *seek = NULL;
    
    if ((NULL == ip_hdr) || (NULL == pld)) {
        return PIA_NG;
    }
    seek = piaip_seekpld(ip_hdr);
    if (NULL == seek) {
        return PIA_NG;
    }
    /* add payload */
    memcpy(seek, pld, siz);
    piaip_settotal(
        ip_hdr,
        piaip_gethdrlen(ip_hdr) + siz
    );
    
    return PIA_OK;
}

/**
 * get ether frame with ip header
 * 
 * @param[out] buf : frame buffer
 * @param[in] max : buffer size
 * @param[in] prot : protocol value (PIA_IP_XX or number)
 * @return PIA_OK proccessing success
 * @return PIA_NG proccessing failed
 */
int piaip_getfrm (uint8_t *buf, size_t max, int prot) {
    piaip_v4hdr_t *ip_hdr = NULL;
    /* check parameter */
    if ((NULL == buf) || (sizeof(piaeth_hdr_t)+sizeof(piaip_v4hdr_t) > max)) {
        return PIA_NG;
    }
    /* get ether header */
    piaeth_gethdr_ip((piaeth_hdr_t *)buf, max);
    buf += (sizeof(piaeth_hdr_t));  // seek to head pointer to ip header

    /* get ip header */
    if (PIAIP_TYPE_ICMP == prot) {
        /* get icmp protocol ip header */
        piaip_getv4hdr_icmp(
            (piaip_v4hdr_t *)buf,
            max-(sizeof(piaeth_hdr_t))
        );
    } else if (PIAIP_TYPE_TCP == prot) {
        /* get tcp protocol ip header */
        piaip_getv4hdr_tcp(
            (piaip_v4hdr_t *)buf,
            max-(sizeof(piaeth_hdr_t))
        );
    } else if (PIAIP_TYPE_UDP == prot) {
        /* get udp protocol ip header */
        piaip_getv4hdr_udp(
            (piaip_v4hdr_t *)buf,
            max-(sizeof(piaeth_hdr_t))
        );
    } else {
        piaip_getv4hdr(
            (piaip_v4hdr_t *)buf,
            max-(sizeof(piaeth_hdr_t))
        );
        ip_hdr = (piaip_v4hdr_t *) buf;
        ip_hdr->prot = prot;
    }
    
    return PIA_OK;
}

/**
 * get ipv4 header
 * 
 * @param[in] buf : header buffer
 * @param[in] max : buffer size
 * @return PIA_OK proccessing success
 * @return PIA_NG proccessing failed
 */
int piaip_getv4hdr (piaip_v4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(piaip_v4hdr_t) > max) ||
         (PIA_FALSE == g_piaip_setaddr) ) {
        return PIA_NG;
    }
    
    g_piaip_v4hdr.chksum = pia_checksum(
                           (uint16_t *) &g_piaip_v4hdr,
                           sizeof(piaip_v4hdr_t)
                       );
    memcpy(buf, &g_piaip_v4hdr, sizeof(piaip_v4hdr_t));
    piaip_incid(&g_piaip_v4hdr);
    return PIA_OK;
}

/**
 * get ipv4 header
 * 
 * @param[in] buf : ip heaer buffer
 * @param[in] max : buffer size
 * @note protocol value is set PIA_IP_TCP (0x06)
 * @return PIA_OK proccessing success
 * @return PIA_NG proccessing failed
 */
int piaip_getv4hdr_tcp (piaip_v4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(piaip_v4hdr_t) > max) ||
         (PIA_FALSE == g_piaip_setaddr) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_piaip_v4hdr_tcp, sizeof(piaip_v4hdr_t));
    piaip_incid(&g_piaip_v4hdr_tcp);
    return PIA_OK;
}

/**
 * get ipv4 header
 * 
 * @param[in] buf : ip heaer buffer
 * @param[in] max : buffer size
 * @note protocol value is set PIA_IP_UDP (0x17)
 * @return PIA_OK proccessing success
 * @return PIA_NG proccessing failed
 */
int piaip_getv4hdr_udp (piaip_v4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(piaip_v4hdr_t) > max) ||
         (PIA_FALSE == g_piaip_setaddr) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_piaip_v4hdr_udp, sizeof(piaip_v4hdr_t));
    piaip_incid(&g_piaip_v4hdr_udp);
    return PIA_OK;
}

/**
 * get ipv4 header
 * 
 * @param[in] buf : ip heaer buffer
 * @param[in] max : buffer size
 * @note protocol value is set PIA_IP_ICMP (0x01)
 * @return PIA_OK proccessing success
 * @return PIA_NG proccessing failed
 */
int piaip_getv4hdr_icmp (piaip_v4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(piaip_v4hdr_t) > max) ||
         (PIA_FALSE == g_piaip_setaddr) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_piaip_v4hdr_icmp, sizeof(piaip_v4hdr_t));
    piaip_incid(&g_piaip_v4hdr_icmp);
    return PIA_OK;
}

int piaip_incid (piaip_v4hdr_t * ip_hdr) {
    uint16_t id = 0;
    
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    id = PIA_M_BYTORD16(ip_hdr->id);
    id++;
    ip_hdr->id = PIA_M_BYTORD16(id);
    return PIA_OK;
}

/**
 * seek to payload
 * 
 * @param[in] ip_hdr : head pointer to ip header
 */
uint8_t * piaip_seekpld (piaip_v4hdr_t * ip_hdr) {
    if (NULL == ip_hdr) {
        return NULL;
    }
    return ((uint8_t *) ip_hdr) + (ip_hdr->hlen*4);
}
/* end of file */
