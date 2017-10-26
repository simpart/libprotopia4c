/**
 * @file ether/dump.c
 * @author simpart
 */
#include <string.h>
#include "pia/com.h"
#include "pia/eth.h"

int pia_eth_issrc (uint8_t *rcv, uint8_t *mac) {
    pia_ethhdr_t *eth_hdr = NULL;
    
    if ( (NULL == rcv) || (NULL == mac)) {
        return PIA_NG;
    }
    
    eth_hdr = (pia_ethhdr_t *) rcv;
    if (0 == memcmp(&(eth_hdr->smac[0]), mac, PIA_ETH_MACSIZE) ) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}


int pia_eth_isdst (uint8_t *rcv, uint8_t *mac) {
    pia_ethhdr_t *eth_hdr = NULL;
    
    if ( (NULL == rcv) || (NULL == mac)) {
        return PIA_NG;
    }
    
    eth_hdr = (pia_ethhdr_t *) rcv;
    if (0 == memcmp(&(eth_hdr->dmac[0]), mac, PIA_ETH_MACSIZE) ) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

int pia_eth_isprot (uint8_t *rcv, uint16_t prot) {
    pia_ethhdr_t *eth_hdr = NULL;

    if (NULL == rcv) {
        return PIA_NG;
    }

    eth_hdr = (pia_ethhdr_t *) rcv;
    if (prot == pia_ntohs(eth_hdr->type)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/* end of file */
