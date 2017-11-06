/**
 * @file ip/header.c
 * @brief header function for ip header
 * @author simpart
 */
/***include  ***/
#include <stdio.h>
#include <string.h>
#include "pia/com.h"
#include "pia/ip.h"
#include "pia/eth.h"

/*** global ***/
extern pia_ipv4hdr_t g_pia_ipv4hdr;
extern pia_ipv4hdr_t g_pia_ipv4hdr_tcp;
extern pia_ipv4hdr_t g_pia_ipv4hdr_udp;
extern pia_ipv4hdr_t g_pia_ipv4hdr_icmp;
extern int g_pia_ip_setaddr;

/*** function ***/
/**
 * set default ip address,set to global area
 * 
 * @param sip : source ip address
 * @param dip : dest ip address
 * @return PIA_OK proccessing success
 */
int pia_ip_setdefipv4 (uint8_t *sip, uint8_t *dip) {
    uint8_t cmp_ip[PIA_IP_IPSIZE] = {0};
    /* set src ip */
    if (NULL != sip) {
        memcpy(g_pia_ipv4hdr.sip,      sip, PIA_IP_IPSIZE);
        memcpy(g_pia_ipv4hdr_tcp.sip,  sip, PIA_IP_IPSIZE);
        memcpy(g_pia_ipv4hdr_udp.sip,  sip, PIA_IP_IPSIZE);
        memcpy(g_pia_ipv4hdr_icmp.sip, sip, PIA_IP_IPSIZE);
    }
    /* set dest ip */
    if (NULL != dip) {
        memcpy(g_pia_ipv4hdr.dip,      dip, PIA_IP_IPSIZE);
        memcpy(g_pia_ipv4hdr_tcp.dip,  dip, PIA_IP_IPSIZE);
        memcpy(g_pia_ipv4hdr_udp.dip,  dip, PIA_IP_IPSIZE);
        memcpy(g_pia_ipv4hdr_icmp.dip, dip, PIA_IP_IPSIZE);
    }
    /* update init flag */
    if ((NULL != sip) && (NULL != dip)) {
        g_pia_ip_setaddr = PIA_TRUE;
    } else if ( (0 != memcmp(&(g_pia_ipv4hdr.sip[0]), &cmp_ip[0], PIA_IP_IPSIZE)) &&
                (0 != memcmp(&(g_pia_ipv4hdr.dip[0]), &cmp_ip[0], PIA_IP_IPSIZE))) {
        g_pia_ip_setaddr = PIA_TRUE;
    }
    return PIA_OK;
}

/**
 * set ip address,set to parameter header
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @param[in] sip : head pointer to source ip address
 * @param[in] dip : head pointer to destination ip address
 * @return PIA_OK : proccessing success
 * @return PIA_NG : proccessing failed
 */
int pia_ip_setipv4 (pia_ipv4hdr_t *ip_hdr, uint8_t *sip, uint8_t *dip) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    /* set src ip */
    if (NULL != sip) {
        memcpy(ip_hdr->sip, sip, PIA_IP_IPSIZE);
    }
    /* set dest ip */
    if (NULL != dip) {
        memcpy(ip_hdr->dip, dip, PIA_IP_IPSIZE);
    }
    return PIA_OK;
}

int pia_ip_getpldsize (pia_ipv4hdr_t * ip_hdr) {
    uint16_t total = 0;
    
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    total = pia_ntohs(ip_hdr->total);
    return total - (ip_hdr->hlen*4);
}

int pia_ip_pldsize (pia_ipv4hdr_t * ip_hdr, size_t size) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    ip_hdr->total = pia_htons((ip_hdr->hlen*4) + size);
    pia_ip_updchksum(ip_hdr);
    return PIA_OK;
}

int pia_ip_updchksum (pia_ipv4hdr_t * ip_hdr) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    ip_hdr->chksum = pia_checksum((uint16_t *)ip_hdr, ip_hdr->hlen*4);
    
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
int pia_ip_getfrm (uint8_t *buf, size_t max, int prot) {
    pia_ipv4hdr_t *ip_hdr = NULL;
    /* check parameter */
    if ((NULL == buf) || (sizeof(pia_ethhdr_t)+sizeof(pia_ipv4hdr_t) > max)) {
        return PIA_NG;
    }
    /* get ether header */
    pia_eth_gethdr_ip((pia_ethhdr_t *)buf, max);
    buf += (sizeof(pia_ethhdr_t));  // seek to head pointer to ip header

    /* get ip header */
    if (PIA_IP_ICMP == prot) {
        /* get icmp protocol ip header */
        pia_ip_getv4hdr_icmp(
            (pia_ipv4hdr_t *)buf,
            max-(sizeof(pia_ethhdr_t))
        );
    } else if (PIA_IP_TCP == prot) {
        /* get tcp protocol ip header */
        pia_ip_getv4hdr_tcp(
            (pia_ipv4hdr_t *)buf,
            max-(sizeof(pia_ethhdr_t))
        );
    } else if (PIA_IP_UDP == prot) {
        /* get udp protocol ip header */
        pia_ip_getv4hdr_udp(
            (pia_ipv4hdr_t *)buf,
            max-(sizeof(pia_ethhdr_t))
        );
    } else {
        pia_ip_getv4hdr(
            (pia_ipv4hdr_t *)buf,
            max-(sizeof(pia_ethhdr_t))
        );
        ip_hdr = (pia_ipv4hdr_t *) buf;
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
int pia_ip_getv4hdr (pia_ipv4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(pia_ipv4hdr_t) > max) ||
         (PIA_FALSE == g_pia_ip_setaddr) ) {
        return PIA_NG;
    }
    
    g_pia_ipv4hdr.chksum = pia_checksum(
                           (uint16_t *) &g_pia_ipv4hdr,
                           sizeof(pia_ipv4hdr_t)
                       );
    memcpy(buf, &g_pia_ipv4hdr, sizeof(pia_ipv4hdr_t));
    pia_ip_incid(&g_pia_ipv4hdr);
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
int pia_ip_getv4hdr_tcp (pia_ipv4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(pia_ipv4hdr_t) > max) ||
         (PIA_FALSE == g_pia_ip_setaddr) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ipv4hdr_tcp, sizeof(pia_ipv4hdr_t));
    pia_ip_incid(&g_pia_ipv4hdr_tcp);
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
int pia_ip_getv4hdr_udp (pia_ipv4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(pia_ipv4hdr_t) > max) ||
         (PIA_FALSE == g_pia_ip_setaddr) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ipv4hdr_udp, sizeof(pia_ipv4hdr_t));
    pia_ip_incid(&g_pia_ipv4hdr_udp);
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
int pia_ip_getv4hdr_icmp (pia_ipv4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(pia_ipv4hdr_t) > max) ||
         (PIA_FALSE == g_pia_ip_setaddr) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ipv4hdr_icmp, sizeof(pia_ipv4hdr_t));
    pia_ip_incid(&g_pia_ipv4hdr_icmp);
    return PIA_OK;
}

int pia_ip_incid (pia_ipv4hdr_t * ip_hdr) {
    uint16_t id = 0;
    
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    id = pia_ntohs(ip_hdr->id);
    id++;
    ip_hdr->id = pia_htons(id);
    return PIA_OK;
}

/**
 * seek to payload
 * 
 * @param[in] ip_hdr : head pointer to ip header
 */
uint8_t * pia_ip_seekpld (pia_ipv4hdr_t * ip_hdr) {
    if (NULL == ip_hdr) {
        return NULL;
    }
    return ((uint8_t *) ip_hdr) + (ip_hdr->hlen*4);
}
/* end of file */
