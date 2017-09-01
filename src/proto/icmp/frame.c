/**
 * @file frame.c
 * @author simpart
 */
#include "pia/common.h"
#include "pia/icmp.h"
#include "pia/ether.h"
#include <string.h>

size_t pia_icmp_getecho (uint8_t * buf, size_t max, int type) {
    pia_eth_hdr_t ethhdr;
    
    if (NULL == buf) {
        return PIA_NG;
    }
    /* set ether */
    ethhdr = pia_eth_gethdr(PIA_ETH_IP);
    memcpy(buf, ethhdr, max);
    
    /* set ip */
    
    
    /* set icmp */
    memcpy(buf, , );
    
}
/* end of file */
