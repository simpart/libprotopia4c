/**
 * @file init.c
 * @author simpart
 */
#include "pia/icmp.h"

/*** global ***/
uint8_t  g_icmp_data[32];
uint32_t g_seq;

int pia_icmp_init(void) {
    int loop = 0;
    
    for (loop=0;loop < 32;loop++) {
        g_icmp_data[loop] = loop;
    }
    
    g_seq = 0;
    
    return PIA_OK;
}
/* end of file */
