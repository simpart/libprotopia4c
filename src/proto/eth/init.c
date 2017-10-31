/**
 * @file init.c
 * @author simpart
 */
#include <string.h>
#include "pia/eth.h"

/*** global ***/
pia_ethhdr_t g_ethhdr;
pia_ethhdr_t g_ethhdr_ip;
pia_ethhdr_t g_ethhdr_arp;

/*** function ***/
int pia_eth_init (void) {
    
    /* initialize global value */
    memset(&g_ethhdr,     0x00, sizeof(pia_ethhdr_t));
    memset(&g_ethhdr_ip,  0x00, sizeof(pia_ethhdr_t));
    memset(&g_ethhdr_arp, 0x00, sizeof(pia_ethhdr_t));
    
    g_ethhdr.type     = PIA_ETH_IP;
    g_ethhdr_ip.type  = PIA_ETH_IP;
    g_ethhdr_arp.type = PIA_ETH_ARP;
    
    return PIA_OK;
}
/* end of file */
