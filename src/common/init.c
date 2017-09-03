/**
 * @file init.c
 * @author simpart
 */
#include "pia/com.h"

int pia_init(void) {
    pia_eth_init();
    pia_ip_init();
}
/* end of file */
