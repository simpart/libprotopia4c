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
/*** function ***/
/**
 * check parameter header whether it is version 4 header
 *
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : parameter is version 4
 * @return PIA_FALSE : parameter is not version 4
 */
int pia_ip_isv4 (pia_ipv4hdr_t *ip_hdr) {
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
int pia_ip_isv6 (pia_ipv4hdr_t *ip_hdr) {
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
 * @param[in] tos_val : value of type of servie
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : tos is same
 * @return PIA_FALSE : tos is different
 */
int pia_ip_istos (pia_ipv4hdr_t *ip_hdr, uint8_t tos) {
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
int pis_ip_issetopt (pia_ipv4hdr_t *ip_hdr) {
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
int pia_ip_isfragment (pia_ipv4hdr_t *ip_hdr) {
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
int pia_ip_isalived (pia_ipv4hdr_t *ip_hdr) {
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
int pia_ip_isicmp (pia_ipv4hdr_t *ip_hdr) {
    return pia_ip_isprot(ip_hdr, PIA_IP_ICMP);
}
/**
 * check parameter header whether next protocol is tcp
 * 
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : next protocol is tcp
 * @return PIA_FALSE : next protocol is not tcp
 */
int pia_ip_istcp (pia_ipv4hdr_t *ip_hdr) {
    return pia_ip_isprot(ip_hdr, PIA_IP_TCP);
}
/**
 * check parameter header whether next protocol is udp
 * 
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : next protocol is udp
 * @return PIA_FALSE : next protocol is not udp
 */
int pia_ip_isudp (pia_ipv4hdr_t *ip_hdr) {
    return pia_ip_isprot(ip_hdr, PIA_IP_UDP);
}
/**
 * check parameter header whether prot is same
 * 
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : prot is same
 * @return PIA_FALSE : prot is defferent
 */
int pia_ip_isprot (pia_ipv4hdr_t *ip_hdr, uint8_t prot) {
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
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : sip is same
 * @return PIA_FALSE : sip is defferent
 */
int pia_ip_issrc (pia_ipv4hdr_t *ip_hdr, uint8_t *sip) {
    if ((NULL == ip_hdr) || (NULL == sip)) {
        return PIA_NG;
    }
    if(0 == memcmp(&(ip_hdr->sip[0]), sip, PIA_IP_IPSIZE)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/**
 * check parameter header whether dip is same
 * 
 * @param [in] ip_hdr : head pointer to ip header
 * @return PIA_NG : proccessing failed
 * @return PIA_TRUE : dip is same
 * @return PIA_FALSE : dip is defferent
 */
int pia_ip_isdst (pia_ipv4hdr_t *ip_hdr, uint8_t *dip) {
    if ((NULL == ip_hdr) || (NULL == dip)) {
        return PIA_NG;
    }
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    if(0 == memcmp(&(ip_hdr->dip[0]), dip, PIA_IP_IPSIZE)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/* end of file */
