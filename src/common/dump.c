/**
 * @file dump.c
 * @brief common dump function
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include "pia/com.h"

/*** function ***/
/**
 * dump option area
 *
 * @param[in] ptgt : pointer of target
 * @param[in] size : dump size
 * @param[in] off  : offset
 */
int pia_dump_opt (uint8_t *ptgt, size_t size, int off) {
    int loop  = 0;
    int oloop = 0;
    
    if (NULL == ptgt) {
        return PIA_NG;
    }
    
    for (loop=0;loop < (int)size;loop++) {
         if ( (0 != loop) && (0 == (loop%4)) ) {
             for (oloop=0;oloop < off;oloop++) {
                 printf(" ");
             }
         }
         printf("%02x ", (uint8_t) *(ptgt+loop));
         if ( (0 != loop) && (0 == ((loop+1) % 4)) ) {
             printf("\n");
         }
    }
    
    return PIA_OK;
}
/* end of file */
