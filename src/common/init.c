/**
 * @file common/init.c
 * @author simpart
 */
#include "pia/com.h"
#include "pia/eth.h"
#include "pia/ip.h"
#include "pia/arp.h"
#include "pia/icmp.h"

int pia_init(void) {
    
    pia_err_init();
    piaeth_init();
    piaip_init();
    piaarp_init();
    piaicm_init();
    
    return PIA_OK;
}
/* end of file */
