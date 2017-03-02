/**
 * @file public.c
 */
#include <packet/capsule/ether.h>


u_char * ether_capsuling(ethhdr_t * eth_hdr, u_char * pld, u_int32_t pld_size) {
    u_char * eth_frm = NULL;
    u_char * shift   = NULL;
    
    if ((NULL == eth_hdr) || (NULL == pld) ) {
        return NULL;
    }
    
    /* create ether frame */
    eth_frm = (u_char *) malloc(sizeof(ethhdr_t) + pld_size);
    if (NULL == eth_frm) {
        return NULL;
    }
    /* copy contents */
    memcpy(eth_frm, eth_hdr, sizeof(ethhdr_t));
    shift  = eth_frm;
    shift += sizeof(ethhdr_t);
    memcpy(shift, pld, pld_size);
    
    
    return eth_frm;
}
/* end of file */
