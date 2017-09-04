/**
 * @file init.c
 * @author simpart
 */
#include "pia/com.h"
#include "pia/eth.h"
#include "pia/ip.h"

int pia_init(void) {
    pia_eth_init();
    pia_ip_init();
    return PIA_OK;
}
/* end of file */
