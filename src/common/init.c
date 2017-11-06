/**
 * @file init.c
 * @author simpart
 */
#include "pia/com.h"
#include "pia/eth.h"
#include "pia/ip.h"
#include "pia/arp.h"
#include "pia/icmp.h"

int pia_init(void) {
    
    pia_err_init();
    pia_eth_init();
    pia_ip_init();
    pia_arp_init();
    pia_icmp_init();
    
    return PIA_OK;
}
/* end of file */
