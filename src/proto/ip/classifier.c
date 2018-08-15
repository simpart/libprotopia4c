/**
 * @file ip/classifier.c
 * @brief classifier function for ip header
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include "pia/eth.h"
#include "pia/ip.h"
#include "pia/tcp.h"
/*** function ***/
/**
 * check parameter header whether it is version 4 header
 *
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : parameter is version 4
 * @return PIA_FALSE : parameter is not version 4
 */
int piaip_isv4 (piaip_v4hdr_t *ip_hdr) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    
    if (0x04 == ip_hdr->ver) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

/**
 * check parameter header whether it is version 6 header
 *
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : parameter is version 6
 * @return PIA_FALSE : parameter is not version 6
 */
int piaip_isv6 (piaip_v4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }

    if (0x06 == ip_hdr->ver) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/**
 * check parameter header whether tos is same
 *
 * @param [in] ip_hdr : head pointer to ip header
 * @param[in] tos : value of type of servie
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : tos is same
 * @return PIA_FALSE : tos is different
 */
int piaip_istos (piaip_v4hdr_t *ip_hdr, uint8_t tos) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    if (ip_hdr->tos == tos) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/**
 * not supported
 */
int pisip_issetopt (piaip_v4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    if (5 < ip_hdr->hlen) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/**
 * check parameter header whether it is fragment packet
 *
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : this is fragment packet
 * @return PIA_FALSE : this is not fragment packet
 * @note not supported
 */
int piaip_isfragment (piaip_v4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    return PIA_OK;
}
/**
 * check parameter header whether ttl is over
 *
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : this is alive packet
 * @return PIA_FALSE : this is dead packet
 */
int piaip_isalived (piaip_v4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    if (0 != ip_hdr->ttl) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/**
 * check parameter header whether next protocol is icmp
 *
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : next protocol is icmp
 * @return PIA_FALSE : next protocol is not icmp
 */
int piaip_isicmp (piaip_v4hdr_t *ip_hdr) {
    return piaip_isprot(ip_hdr, PIAIP_TYPE_ICMP);
}
/**
 * check parameter header whether next protocol is tcp
 * 
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : next protocol is tcp
 * @return PIA_FALSE : next protocol is not tcp
 */
int piaip_istcp (piaip_v4hdr_t *ip_hdr) {
    return piaip_isprot(ip_hdr, PIAIP_TYPE_TCP);
}
/**
 * check parameter header whether next protocol is udp
 * 
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : next protocol is udp
 * @return PIA_FALSE : next protocol is not udp
 */
int piaip_isudp (piaip_v4hdr_t *ip_hdr) {
    return piaip_isprot(ip_hdr, PIAIP_TYPE_UDP);
}
/**
 * check parameter header whether prot is same value
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @param[in] prot : protocol value
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : prot is same
 * @return PIA_FALSE : prot is defferent
 */
int piaip_isprot (piaip_v4hdr_t *ip_hdr, uint8_t prot) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    if (prot == ip_hdr->prot) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/**
 * check parameter header whether sip is same
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @param[in] sip : pointer of source ip address
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : sip is same
 * @return PIA_FALSE : sip is defferent
 */
int piaip_issrc (piaip_v4hdr_t *ip_hdr, uint8_t *sip) {
    if ((NULL == ip_hdr) || (NULL == sip)) {
        return PIA_NG;
    }
    if(0 == memcmp(&(ip_hdr->sip[0]), sip, PIAIP_IPSIZ)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/**
 * check parameter header whether dip is same
 * 
 * @param [in] ip_hdr : head pointer to ip header
 * @param[in] dip : destination ip address
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : dip is same
 * @return PIA_FALSE : dip is defferent
 */
int piaip_isdst (piaip_v4hdr_t *ip_hdr, uint8_t *dip) {
    if ((NULL == ip_hdr) || (NULL == dip)) {
        return PIA_NG;
    }
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    if(0 == memcmp(&(ip_hdr->dip[0]), dip, PIAIP_IPSIZ)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}


int piaip_is3way (piaip_v4hdr_t *ip_hdr) {
    uint8_t *seek    = NULL;
    int      tcp_siz = 0;
    
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    /* check protocol */
    if (PIA_TRUE != piaip_istcp(ip_hdr)) {
        return PIA_FALSE;
    }
    /* check payload size */
    seek    = piaip_seekpld(ip_hdr);
    tcp_siz = piatcp_getoffset((piatcp_hdr_t *) seek);
    if (0 != (piaip_getpldsize(ip_hdr) - tcp_siz)) {
        return PIA_FALSE;
    }
    /* check cflag */
    if ( (PIA_TRUE == piatcp_issyn((piatcp_hdr_t *)    seek)) ||
         (PIA_TRUE == piatcp_isack((piatcp_hdr_t *)    seek)) ||
         (PIA_TRUE == piatcp_issynack((piatcp_hdr_t *) seek))  ) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/* end of file */
