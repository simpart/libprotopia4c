/**
 * @file dump.c
 * @brief common dump function
 * @author simpart
 */
#include <stdio.h>
#include "pia/com.h"

int pia_dump_opt (uint8_t *buf, size_t size, int off) {
    int loop  = 0;
    int oloop = 0;
    
    if (NULL == buf) {
        return PIA_NG;
    }
    
    for (loop=0;loop < (int)size;loop++) {
         if ( (0 != loop) && (0 == (loop%4)) ) {
             for (oloop=0;oloop < off;oloop++) {
                 printf(" ");
             }
         }
         printf("%02x ", (uint8_t) *(buf+loop));
         if ( (0 != loop) && (0 == ((loop+1) % 4)) ) {
             printf("\n");
         }
    }
    
    return PIA_OK;
}

