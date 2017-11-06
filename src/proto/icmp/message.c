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

void pia_icmp_incdef_seq (void) {
    uint16_t seq = pia_icmp_getseq(&g_pia_icmpecho);
    seq++;
    g_pia_icmpecho.seq = pia_htons(seq);
}

int pia_icmp_getfrm (uint8_t *buf, size_t max) {
    int       ret  = 0;
    uint8_t * seek = NULL;
    uint8_t * p_ip = NULL;
    
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
    
    /* seek to top of icmp header */
    seek = pia_eth_seekpld((pia_ethhdr_t *) buf);
    if (NULL == seek) {
        return PIA_NG;
    }
    p_ip = seek;
    seek = pia_ip_seekpld((pia_ipv4hdr_t *) seek);
    if (NULL == seek) {
        return PIA_NG;
    }
    
    /* get icmp message */
    ret = pia_icmp_getmsg(
              (pia_icmphdr_t *) seek,
              max - (sizeof(pia_ethhdr_t) + sizeof(pia_ipv4hdr_t))
          );
    if (PIA_NG == ret) {
        return ret;
    }
    
    /* update ip payload size */
    ret = pia_ip_pldsize((pia_ipv4hdr_t *) p_ip, PIA_ICMP_ECHREQ_DEFSIZE);
    if (PIA_NG == ret) {
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
    
    /* update ip payload size */
    
    return PIA_OK;
}

int pia_icmp_getmsg (pia_icmphdr_t * buf, size_t max) {
    uint8_t * seek = NULL;
    
    /* check parameter */
    if ((NULL == buf) || (sizeof(pia_icmphdr_t) > max)) {
        return PIA_NG;
    }
    
    /* copy icmp default common header */
    memcpy(buf, &g_pia_icmphdr, sizeof(pia_icmphdr_t));
    
    /* check icmp type */
    if (PIA_ICMP_ECHOREQ == buf->type) {
        /* this is echo request */
        /* copy echo default header */
        seek = pia_icmp_seekecho(buf);
        if (NULL == seek) {
            return PIA_NG;
        }
        memcpy(seek, &g_pia_icmpecho, sizeof(pia_icmpecho_t));
        pia_icmp_incdef_seq();
        
        /* copy echo default data */
        seek = pia_icmp_seekecho_dat((pia_icmpecho_t *) seek);
        memcpy(seek, &(g_pia_icmpdat.data[0]), g_pia_icmpdat.size);
        
        /* set check sum */
        buf->chksum = pia_checksum(
                          (uint16_t *)buf,
                          sizeof(pia_icmphdr_t) + sizeof(pia_icmpecho_t) + g_pia_icmpdat.size
                      );
    } else {
        buf->chksum = pia_checksum((uint16_t *)buf, sizeof(pia_icmphdr_t));
    }
    
    return PIA_OK;
}

uint16_t pia_icmp_getseq (pia_icmpecho_t * ech) {
    if (NULL == ech) {
        return PIA_NG;
    }
    return pia_ntohs(ech->seq);
}

uint16_t pia_icmp_getid (pia_icmpecho_t * ech) {
    if (NULL == ech) {
        return PIA_NG;
    }
    return pia_ntohs(ech->id);
}


uint8_t * pia_icmp_seekecho (pia_icmphdr_t * msg) {
    if (NULL == msg) {
        return NULL;
    }
    
    if (PIA_TRUE == pia_icmp_isecho(msg)) {
        return ((uint8_t *) msg) + sizeof(pia_icmphdr_t);
    }
    return NULL;
}

uint8_t * pia_icmp_seekecho_dat (pia_icmpecho_t * ech) {
    if (NULL == ech) {
        return NULL;
    }
    return ((uint8_t *) ech) + sizeof(pia_icmpecho_t);
}
/* end of file */
