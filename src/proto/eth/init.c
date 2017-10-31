/**
 * @file init.c
 * @author simpart
 */
#include <string.h>
#include "pia/eth.h"

/*** global ***/
pia_ethhdr_t g_pia_ethhdr;
pia_ethhdr_t g_pia_ethhdr_ip;
pia_ethhdr_t g_pia_ethhdr_arp;
int g_pia_eth_setaddr = PIA_FALSE;

/*** function ***/
int pia_eth_init (void) {
    
    /* initialize global value */
    memset(&g_pia_ethhdr,     0x00, sizeof(pia_ethhdr_t));
    memset(&g_pia_ethhdr_ip,  0x00, sizeof(pia_ethhdr_t));
    memset(&g_pia_ethhdr_arp, 0x00, sizeof(pia_ethhdr_t));
    
    g_pia_ethhdr.type     = PIA_ETH_IP;
    g_pia_ethhdr_ip.type  = PIA_ETH_IP;
    g_pia_ethhdr_arp.type = PIA_ETH_ARP;
    
    return PIA_OK;
}
/* end of file */
