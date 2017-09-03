/**
 * @file init.c
 * @author simpart
 */
#include "pia/eth.h"

/*** global ***/
extern pia_ethhdr_t g_ethhdr;
extern pia_ethhdr_t g_ethhdr_ip;

/*** function ***/
int pia_eth_init () {
    g_ethhdr.type    = PIA_ETH_IP;
    g_ethhdr_ip.type = PIA_ETH_IP;
    return PIA_OK;
}
/* end of file */
