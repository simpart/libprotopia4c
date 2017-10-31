/**
 * @file ip/classifier.c
 * @author simpart
 */
#include <stdio.h>
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
/* end of file */
