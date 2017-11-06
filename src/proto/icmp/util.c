/**
 * @file util.c
 * @author simpart
 */
#include <string.h>
#include "pia/icmp.h"

/*** global ***/
uint8_t  g_icmp_data[32];
uint32_t g_seq;


int pia_icmp_getdata (uint8_t *buf, size_t siz) {
    int cpy_cnt = siz / 32;
    int offset  = 0;
    
    if ( (NULL == buf) || (0 >= siz) ) {
        return PIA_NG;
    }
    
    if (cpy_cnt > 0) {
        while (cpy_cnt) {
            memcpy((buf + offset), &g_icmp_data[0], sizeof(g_icmp_data));
            offset += sizeof(g_icmp_data);
            cpy_cnt--;
        }
    }
    memcpy((buf+offset), &g_icmp_data[0], siz);
    return PIA_OK;
}

int pia_icmp_getdefseq (void) {
    return g_seq++;
}
/* end of file */
