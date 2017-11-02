/**
 * @file icmp/header.c
 * @brief header function for icmp
 * @author simpart
 */
/*** include ***/
#include <string.h>
#include "pia/com.h"
#include "pia/eth.h"
#include "pia/ip.h"
#include "pia/icmp.h"

/*** global ***/
extern pia_icmphdr_t  g_pia_icmphdr;
extern pia_icmpecho_t g_pia_icmpecho;
extern pia_icmpdat_t  g_pia_icmpdat;
extern pia_icmpdat_t  g_pia_icmp_rcvdat;

/*** function ***/
int pia_icmp_setdef_type (uint8_t type) {
    
    g_pia_icmphdr.type = type;
    switch (type) {
        case PIA_ICMP_ECHOREP:
        case PIA_ICMP_ECHOREQ:
            g_pia_icmphdr.code = 0;
            break;
        case PIA_ICMP_DSTUNRCH:
        case PIA_ICMP_REDIRECT:
        case PIA_ICMP_TMEXCD:
            break;
    }
    
    return PIA_OK;
}

int pia_icmp_setdef_code (uint8_t code) {
    g_pia_icmphdr.code = code;
    return PIA_OK;
}

int pia_icmp_getfrm (uint8_t *buf, size_t max) {
    int ret = 0;
    /* check parameter */
    if ( (NULL == buf) ||
         ( sizeof(pia_ethhdr_t)   + \
           sizeof(pia_ipv4hdr_t)  + \
           sizeof(pia_icmphdr_t)  > max) ) {
        return PIA_NG;
    }
    
    /* get ip packet that include ether header */
    ret = pia_ip_getfrm(buf, max, PIA_IP_ICMP);
    if (PIA_OK != ret) {
        return ret;
    }
    
    /* get icmp message */
    buf += sizeof(pia_ethhdr_t);
    ret = pia_icmp_getmsg((pia_icmphdr_t *)buf, max - sizeof(pia_ethhdr_t));
    if (PIA_OK != ret) {
        return ret;
    }
    
    return PIA_OK;
}

int pia_icmp_getpkt (uint8_t *buf, size_t max) {
    int ret = 0;
    
    /* check parameter */
    if (NULL == buf) {
        return PIA_NG;
    }
    
    /* get ip header */
    ret = pia_ip_getv4hdr_icmp((pia_ipv4hdr_t *)buf, max);
    if (PIA_OK != ret) {
        return ret;
    }

    /* get icmp message */
    buf += sizeof(pia_ipv4hdr_t);
    ret = pia_icmp_getmsg((pia_icmphdr_t *)buf, max - sizeof(pia_ipv4hdr_t));
    if (PIA_OK != ret) {
        return ret;
    }
    
    return PIA_OK;
}

int pia_icmp_getmsg (pia_icmphdr_t * buf, size_t max) {
    uint8_t * seek = NULL;
    
    /* check parameter */
    if ((NULL == buf) || (sizeof(pia_icmphdr_t) > max)) {
        return PIA_NG;
    }
    
    memcpy(buf, &g_pia_icmphdr, sizeof(pia_icmphdr_t));
    
    /* check icmp type */
    if (PIA_ICMP_ECHOREQ == buf->type) {
        /* this is echo request */
        seek = (uint8_t *) buf;
        seek += sizeof(pia_icmphdr_t);
        memcpy(seek, &g_pia_icmpecho, sizeof(pia_icmpecho_t));
        g_pia_icmpecho.seq++; // increment sequence
        seek += sizeof(pia_icmpecho_t);
        memcpy(seek, &(g_pia_icmpdat.data[0]), g_pia_icmpdat.size);
    }
    
    return PIA_OK;
}
/* end of file */
