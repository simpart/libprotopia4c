/**
 * @file ip/classifier.c
 * @author simpart
 */
#include <stdio.h>
#include "pia/eth.h"
#include "pia/ip.h"

int pia_ip_isip (uint8_t *pkt) {
    pia_ethhdr_t *eth_hdr = NULL;
    
    if (NULL == pkt) {
        return PIA_NG;
    }
    eth_hdr = (pia_ethhdr_t *) pkt;
    if (PIA_ETH_IP == pia_ntohs(eth_hdr->type)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/* end of file */
