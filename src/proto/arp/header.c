/**
 * @file arp/header.c
 * @author simpart
 */
#include <string.h>
#include "pia/eth.h"
#include "pia/com.h"
#include "pia/arp.h"

/*** global ***/
extern pia_arphdr_t g_arphdr;

/*** function ***/
//int pia_arp_setreq (uint8_t * dip) {
//    
//}


int pia_arp_getfrm (uint8_t *buf, size_t max, uint8_t type) {
    int ret = 0;
    pia_ethhdr_t * eth_hdr = NULL;
    
    if (NULL == buf) {
        return PIA_NG;
    }
    
    /* get ether header */
    ret = pia_eth_gethdr_arp(buf, max);
    if (PIA_NG == ret) {
        return ret;
    }
    if (PIA_ARP_OP_REQ == type) {
        /* this is request */
        eth_hdr = (pia_ethhdr_t *) buf;
        memset(&(eth_hdr->dmac[0]), 0xFF, PIA_ETH_MACSIZE);
    }
    
    /* get arp header */
    pia_arp_gethdr(
        buf + sizeof(pia_ethhdr_t),
        max - sizeof(pia_ethhdr_t),
        type
    );
    
    return PIA_OK;
}


int pia_arp_gethdr (uint8_t *buf, size_t max, uint8_t type) {
//    if ((NULL == buf) || (sizeof(pia_arphdr_t) > max)) {
///        return PIA_NG;
 //   }
//    
//    memcpy(buf, &g_arphdr, sizeof(pia_arphdr_t));
//    
//    
//    
    buf = buf;
    max = max;
    type = type;
    return PIA_OK;
}
/* end of file */
