/**
 * @file header.c
 * @author simpart
 */
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
 * set src/dest address to ip header
 * 
 * @param sip : source ip address
 * @param dip : dest ip address
 */
int pia_ip_setdefipv4 (uint8_t *sip, uint8_t *dip) {
    uint8_t cmp_mac[PIA_IP_IPSIZE] = {0};
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
    } else if ( (0 != memcmp(&(g_pia_ipv4hdr.sip[0]), &cmp_mac[0], PIA_IP_IPSIZE)) &&
                (0 != memcmp(&(g_pia_ipv4hdr.dip[0]), &cmp_mac[0], PIA_IP_IPSIZE))) {
        g_pia_ip_setaddr = PIA_TRUE;
    }
    return PIA_OK;
}

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

int pia_ip_getfrm (uint8_t *buf, size_t max, int prot) {
    pia_ipv4hdr_t *ip_hdr = NULL;
    if ((NULL == buf) || (sizeof(pia_ethhdr_t)+sizeof(pia_ipv4hdr_t) > max)) {
        return PIA_NG;
    }
    /* get ether header */
    pia_eth_gethdr_ip(buf, max);
    buf += (sizeof(pia_ethhdr_t));  // seek to top of ip header address

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
 */
int pia_ip_getv4hdr (pia_ipv4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(pia_ipv4hdr_t) > max) ||
         (PIA_FALSE == g_pia_ip_setaddr) ) {
        return PIA_NG;
    }
    
    g_pia_ipv4hdr.id++; 
    g_pia_ipv4hdr.chksum = pia_checksum(
                           (uint16_t *) &g_pia_ipv4hdr,
                           sizeof(pia_ipv4hdr_t)
                       );
    memcpy(buf, &g_pia_ipv4hdr, sizeof(pia_ipv4hdr_t));
    
    return PIA_OK;
}



/**
 * get ip header for tcp
 *
 */
int pia_ip_getv4hdr_tcp (pia_ipv4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(pia_ipv4hdr_t) > max) ||
         (PIA_FALSE == g_pia_ip_setaddr) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ipv4hdr_tcp, sizeof(pia_ipv4hdr_t));
    return PIA_OK;
}

int pia_ip_getv4hdr_udp (pia_ipv4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(pia_ipv4hdr_t) > max) ||
         (PIA_FALSE == g_pia_ip_setaddr) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ipv4hdr_udp, sizeof(pia_ipv4hdr_t));
    return PIA_OK;
}

/**
 * get ip header for icmp
 *
 */
int pia_ip_getv4hdr_icmp (pia_ipv4hdr_t *buf, size_t max) {
    if ( (NULL == buf) ||
         (sizeof(pia_ipv4hdr_t) > max) ||
         (PIA_FALSE == g_pia_ip_setaddr) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ipv4hdr_icmp, sizeof(pia_ipv4hdr_t));
    return PIA_OK;
}
/* end of file */
