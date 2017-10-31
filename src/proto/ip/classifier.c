/**
 * @file ip/classifier.c
 * @author simpart
 */
#include <stdio.h>
#include <string.h>
#include "pia/eth.h"
#include "pia/ip.h"

int pia_ip_isv4 (pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }

    if (0x04 == ip_hdr->ver) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

int pia_ip_isv6 (pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }

    if (0x06 == ip_hdr->ver) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

int pia_ip_istos (pia_ipv4hdr_t *ip_hdr, uint8_t tos_val) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    tos_val = tos_val;
    return PIA_OK;
}

int pis_ip_issetopt (pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    if (5 < ip_hdr->hlen) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

int pia_ip_isfragment (pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    return PIA_OK;
}

int pia_ip_isalived (pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    if (0 != ip_hdr->ttl) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

int pia_ip_isicmp (pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    return pia_ip_isprot(ip_hdr, PIA_IP_ICMP);
}

int pia_ip_istcp (pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    return pia_ip_isprot(ip_hdr, PIA_IP_TCP);
}

int pia_ip_isudp (pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    return pia_ip_isprot(ip_hdr, PIA_IP_UDP);
}

int pia_ip_isprot (pia_ipv4hdr_t *ip_hdr, uint8_t prot_val) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    if (prot_val == ip_hdr->prot) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

int pia_ip_issrc (pia_ipv4hdr_t *ip_hdr, uint8_t *sip) {
    if ((NULL == ip_hdr) || (NULL == sip)) {
        return PIA_NG;
    }
    if(0 == memcmp(&(ip_hdr->sip[0]), sip, PIA_IP_IPSIZE)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

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
