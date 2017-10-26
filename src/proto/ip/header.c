/**
 * @file header.c
 * @author simpart
 */
#include <string.h>
#include "pia/com.h"
#include "pia/ip.h"
#include "pia/eth.h"

/*** global ***/
pia_ipv4hdr_t g_ipv4hdr;
pia_ipv4hdr_t g_ipv4hdr_tcp;
pia_ipv4hdr_t g_ipv4hdr_icmp;

/*** function ***/
/**
 * set src/dest address to ip header
 * 
 * @param sip : source ip address
 * @param dip : dest ip address
 */
int pia_ip_setipv4 (uint8_t *sip, uint8_t *dip) {
    
    if ((NULL == sip) || (NULL == dip)) {
        return PIA_NG;
    }
    
    /* set dest ip */
    memcpy(g_ipv4hdr.dip,      dip, sizeof(g_ipv4hdr.dip));
    memcpy(g_ipv4hdr_tcp.dip,  dip, sizeof(g_ipv4hdr_tcp.dip));
    memcpy(g_ipv4hdr_icmp.dip, dip, sizeof(g_ipv4hdr_icmp.dip));
    
    /* set src ip */
    memcpy(g_ipv4hdr.sip,      sip, sizeof(g_ipv4hdr.sip));
    memcpy(g_ipv4hdr_tcp.sip,  sip, sizeof(g_ipv4hdr_tcp.sip));
    memcpy(g_ipv4hdr_icmp.sip, sip, sizeof(g_ipv4hdr_icmp.sip));
    
    return PIA_OK;
}

/**
 * get ipv4 header
 *
 */
int pia_ip_getv4hdr (uint8_t *buf, size_t max) {
    if ((NULL == buf) || (sizeof(pia_ipv4hdr_t) > max)) {
        return PIA_NG;
    }
    
    g_ipv4hdr.chksum = pia_checksum(
                           (uint16_t *) &g_ipv4hdr,
                           sizeof(pia_ipv4hdr_t)
                       );
    memcpy(buf, &g_ipv4hdr, sizeof(pia_ipv4hdr_t));
    
    return PIA_OK;
}

/**
 * get ip header for tcp
 *
 */
int pia_ip_getv4hdr_tcp (uint8_t *buf, size_t max) {
    pia_ipv4hdr_t *iphdr;
    
    if ( (NULL == buf) ||
         (sizeof(pia_ethhdr_t) + (sizeof(pia_ipv4hdr_t)) > max) ) {
        return PIA_NG;
    }
    
    if(PIA_OK != pia_ip_getv4hdr(buf, max)) {
        return PIA_NG;
    }
    
    iphdr = (pia_ipv4hdr_t *) (buf + sizeof(pia_ethhdr_t) + sizeof(pia_ipv4hdr_t));
    iphdr->prot = PIA_IP_TCP;
    
    return PIA_OK;
}

int pia_ip_getv4hdr_udp (uint8_t *buf, size_t max) {
    pia_ipv4hdr_t *iphdr;

    if ( (NULL == buf) ||
         (sizeof(pia_ethhdr_t) + (sizeof(pia_ipv4hdr_t)) > max) ) {
        return PIA_NG;
    }
    
    if(PIA_OK != pia_ip_getv4hdr(buf, max)) {
        return PIA_NG;
    }
    
    iphdr = (pia_ipv4hdr_t *) (buf + sizeof(pia_ethhdr_t) + sizeof(pia_ipv4hdr_t));
    iphdr->prot = PIA_IP_UDP;
    
    return PIA_OK;
}

/**
 * get ip header for icmp
 *
 */
int pia_ip_getv4hdr_icmp (uint8_t *buf, size_t max) {
    pia_ipv4hdr_t *iphdr;
    
    if ( (NULL == buf) ||
         (sizeof(pia_ethhdr_t) + (sizeof(pia_ipv4hdr_t)) > max) ) {
        return PIA_NG;
    }
    
    if(PIA_OK != pia_ip_getv4hdr(buf, max)) {
        return PIA_NG;
    }

    iphdr = (pia_ipv4hdr_t *) (buf + sizeof(pia_ethhdr_t) + sizeof(pia_ipv4hdr_t));
    iphdr->prot = PIA_IP_ICMP;
    
    return PIA_OK;
}
/* end of file */
