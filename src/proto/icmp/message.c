/**
 * @file icmp/message.c
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
extern piaicm_hdr_t  g_piaicm_hdr;
extern piaicm_echo_t g_piaicm_echo;
extern piaicm_dat_t  g_piaicm_dat;
extern piaicm_dat_t  g_piaicmp_rcvdat;

/*** function ***/
int piaicm_setdef_type (uint8_t type) {
    
    g_piaicm_hdr.type = type;
    switch (type) {
        case PIAICM_TYPE_ECHOREP:
        case PIAICM_TYPE_ECHOREQ:
            g_piaicm_hdr.code = 0;
            break;
        case PIAICM_TYPE_DSTUNRCH:
        case PIAICM_TYPE_REDIRECT:
        case PIAICM_TYPE_TMEXCD:
            break;
    }
    
    return PIA_OK;
}

int piaicm_setdef_code (uint8_t code) {
    g_piaicm_hdr.code = code;
    return PIA_OK;
}

void piaicm_incdef_seq (void) {
    uint16_t seq = piaicm_getseq(&g_piaicm_echo);
    seq++;
    g_piaicm_echo.seq = PIA_M_BYTORD16(seq);
}

int piaicm_getfrm (uint8_t *buf, size_t max) {
    int       ret  = 0;
    uint8_t * seek = NULL;
    uint8_t * p_ip = NULL;
    
    /* check parameter */
    if ( (NULL == buf) ||
         ( sizeof(piaeth_hdr_t)   + \
           sizeof(piaip_v4hdr_t)  + \
           sizeof(piaicm_hdr_t)  > max) ) {
        return PIA_NG;
    }
    
    /* get ip packet that include ether header */
    ret = piaip_getfrm(buf, max, PIAIP_TYPE_ICMP);
    if (PIA_OK != ret) {
        return ret;
    }
    
    /* seek to top of icmp header */
    seek = piaeth_seekpld((piaeth_hdr_t *) buf);
    if (NULL == seek) {
        return PIA_NG;
    }
    p_ip = seek;
    seek = piaip_seekpld((piaip_v4hdr_t *) seek);
    if (NULL == seek) {
        return PIA_NG;
    }
    
    /* get icmp message */
    ret = piaicm_getmsg(
              (piaicm_hdr_t *) seek,
              max - (sizeof(piaeth_hdr_t) + sizeof(piaip_v4hdr_t))
          );
    if (PIA_NG == ret) {
        return ret;
    }
    
    /* update ip payload size */
    ret = piaip_setpldsize((piaip_v4hdr_t *) p_ip, PIAICM_ECHREQ_DEFSIZ);
    if (PIA_NG == ret) {
        return ret;
    }
    
    return PIA_OK;
}

int piaicm_getpkt (uint8_t *buf, size_t max) {
    int ret = 0;
    
    /* check parameter */
    if (NULL == buf) {
        return PIA_NG;
    }
    
    /* get ip header */
    ret = piaip_getv4hdr_icmp((piaip_v4hdr_t *)buf, max);
    if (PIA_OK != ret) {
        return ret;
    }

    /* get icmp message */
    buf += sizeof(piaip_v4hdr_t);
    ret = piaicm_getmsg((piaicm_hdr_t *)buf, max - sizeof(piaip_v4hdr_t));
    if (PIA_OK != ret) {
        return ret;
    }
    
    /* update ip payload size */
    
    return PIA_OK;
}

int piaicm_getmsg (piaicm_hdr_t * buf, size_t max) {
    uint8_t * seek = NULL;
    
    /* check parameter */
    if ((NULL == buf) || (sizeof(piaicm_hdr_t) > max)) {
        return PIA_NG;
    }
    
    /* copy icmp default common header */
    memcpy(buf, &g_piaicm_hdr, sizeof(piaicm_hdr_t));
    
    /* check icmp type */
    if (PIAICM_TYPE_ECHOREQ == buf->type) {
        /* this is echo request */
        /* copy echo default header */
        seek = piaicm_seekecho(buf);
        if (NULL == seek) {
            return PIA_NG;
        }
        memcpy(seek, &g_piaicm_echo, sizeof(piaicm_echo_t));
        piaicm_incdef_seq();
        
        /* copy echo default data */
        seek = piaicm_seekecho_dat((piaicm_echo_t *) seek);
        memcpy(seek, &(g_piaicm_dat.data[0]), g_piaicm_dat.size);
        
        /* set check sum */
        buf->chksum = pia_checksum(
                          (uint16_t *)buf,
                          sizeof(piaicm_hdr_t) + sizeof(piaicm_echo_t) + g_piaicm_dat.size
                      );
    } else {
        buf->chksum = pia_checksum((uint16_t *)buf, sizeof(piaicm_hdr_t));
    }
    
    return PIA_OK;
}

uint16_t piaicm_getseq (piaicm_echo_t * ech) {
    if (NULL == ech) {
        return PIA_NG;
    }
    return PIA_M_BYTORD16(ech->seq);
}

uint16_t piaicm_getid (piaicm_echo_t * ech) {
    if (NULL == ech) {
        return PIA_NG;
    }
    return PIA_M_BYTORD16(ech->id);
}


uint8_t * piaicm_seekecho (piaicm_hdr_t * msg) {
    if (NULL == msg) {
        return NULL;
    }
    
    if (PIA_TRUE == piaicm_isecho(msg)) {
        return ((uint8_t *) msg) + sizeof(piaicm_hdr_t);
    }
    return NULL;
}

uint8_t * piaicm_seekecho_dat (piaicm_echo_t * ech) {
    if (NULL == ech) {
        return NULL;
    }
    return ((uint8_t *) ech) + sizeof(piaicm_echo_t);
}
/* end of file */
