/**
 * @file arp/classifier.c
 * @author simpart
 */
#include <stdio.h>
#include "pia/arp.h"

/*** function ***/

int pia_arp_isrequest (uint8_t *pkt) {
    pia_arphdr_t * arp_hdr;
    if (NULL == pkt) {
        return PIA_FALSE;
    }
    
    arp_hdr = (pia_arphdr_t *) pkt;
    
    if (PIA_ARP_OP_REQ == pia_htons(arp_hdr->op)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

int pia_arp_isreply (uint8_t *pkt) {
    pia_arphdr_t * arp_hdr;
    if (NULL == pkt) {
        return PIA_FALSE;
    }

    arp_hdr = (pia_arphdr_t *) pkt;

    if (PIA_ARP_OP_REP == pia_htons(arp_hdr->op)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/* end of file */
