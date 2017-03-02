/**
 * @file debug.c
 * @brief debug printer
 */

/*** include ***/
#include <debug.h>

/*** function ***/
void dbg_print(char * fname, int code, char * msg) {
    time_t tm;
    time(&tm);

    printf("[%d] ", (int)tm);
    printf("%s->%d : ", fname, code);
    printf("%s\n", msg);
}


void dbg_printdhcp(ethhdr_t * eth_hdr) {
    u_char * shift = NULL;;
    
    if (NULL == eth_hdr) {
        return;
    }
    
    dmp_ethhdr(eth_hdr);
    shift  = (u_char *) eth_hdr;
    shift += sizeof(ethhdr_t);
    
    dmp_iphdr((iphdr_t *) shift );
    shift += sizeof(iphdr_t);
    
    dmp_udphdr((udphdr_t *) shift );
    shift += sizeof(udphdr_t);
    
    dmp_discover((dhcpmsg_t *)shift);
    
    
}
/* end of file */
