/**
 * @file arp/init.c
 * @author simpart
 */
#include <string.h>
#include "pia/arp.h"

/*** global ***/
pia_arphdr_t g_arphdr;

/*** function ***/
int pia_arp_init (void) {
    
    /* initialize global value */
    memset(&g_arphdr, 0x00, sizeof(pia_arphdr_t));
    
    /* set default value */
#if __PIA_ARP_STYLE__ == MAC_IPV4
    g_arphdr.htype = PIA_ARP_HTYPE_ETH;
    g_arphdr.ptype = PIA_ETH_IP;
    g_arphdr.hlen  = PIA_ETH_MACSIZE;
    g_arphdr.plen  = PIA_IP_IPSIZE;
#endif
    
    memset(&g_arphdr.dhaddr[0], 0xFF, PIA_ETH_MACSIZE);
    
    return PIA_OK;
}
/* end of file */
