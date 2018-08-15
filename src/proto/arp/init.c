/**
 * @file arp/init.c
 * @brief initialize function for arp
 * @author simpart
 */
/*** include ***/
#include <string.h>
#include "pia/arp.h"

/*** global ***/
piaarp_hdr_t g_arphdr;

/*** function ***/
/**
 * initialize arp function
 * 
 * @return PIA_OK : proccessing success
 */
int piaarp_init (void) {
    
    /* initialize global value */
    memset(&g_arphdr, 0x00, sizeof(piaarp_hdr_t));
    
    /* set default value */
#if __PIAARP_STYLE__ == MAC_IPV4
    g_arphdr.htype = PIAARP_HTYPE_ETH;
    g_arphdr.ptype = PIAETH_TYPE_IP;
    g_arphdr.hlen  = PIAETH_MACSIZ;
    g_arphdr.plen  = PIAIP_IPSIZ;
#endif
    
    memset(&g_arphdr.dhaddr[0], 0xFF, PIAETH_MACSIZ);
    
    return PIA_OK;
}
/* end of file */
