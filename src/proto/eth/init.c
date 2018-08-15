/**
 * @file eth/init.c
 * @brief initialize function for ether header
 * @author simpart
 */
/*** include ***/
#include <string.h>
#include "pia/com.h"
#include "pia/eth.h"

/*** global ***/
piaeth_hdr_t g_piaeth_hdr;
piaeth_hdr_t g_piaeth_hdrip;
piaeth_hdr_t g_piaeth_hdrarp;
int g_piaeth_setaddr = PIA_FALSE;
/*** function ***/
/**
 * initialize ether function
 * 
 * @return PIA_OK : proccessing success
 */
int piaeth_init (void) {
    
    /* initialize global value */
    memset(&g_piaeth_hdr,    0x00, sizeof(piaeth_hdr_t));
    memset(&g_piaeth_hdrip,  0x00, sizeof(piaeth_hdr_t));
    memset(&g_piaeth_hdrarp, 0x00, sizeof(piaeth_hdr_t));
    
    g_piaeth_hdr.type    = PIA_M_BYTORD16(PIAETH_TYPE_IP);
    g_piaeth_hdrip.type  = PIA_M_BYTORD16(PIAETH_TYPE_IP);
    g_piaeth_hdrarp.type = PIA_M_BYTORD16(PIAETH_TYPE_ARP);
    
    return PIA_OK;
}
/* end of file */
