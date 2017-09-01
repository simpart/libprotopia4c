/**
 * @file header.c
 * @author simpart
 */

/*** include ***/
#include <stddef.h>
#include "pia/common.h"
#include "pia/ether.h"

/*** global ***/
pia_eth_hdr_t g_ethhdr;

/*** function ***/

int pia_eth_setmac (uint8_t *dmac, uint8_t *smac) {
    if (NULL != dmac) {
        
    }
    if (NULL != smac) {
        
    }
    
    return PIA_OK;
}

pia_eth_hdr_t pia_eth_gethdr (uint16_t type) {
    g_ethhdr.type = ntohs(type);
    return g_ethhdr;
}

/* end of file */
