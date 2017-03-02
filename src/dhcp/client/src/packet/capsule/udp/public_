/**
 * @file   public.c
 * @brief  cupsuling udp 
 */
#include <packet/capsule/udp.h>

/*** function ***/
u_char * udp_capsuling(
             dummy_udphdr_t * dmy_hdr,
             udphdr_t * udp_hdr,
             u_char * pld
         ) {
    u_char *   shift       = NULL;
    u_char *   udp_chk_pkt = NULL;
    u_char *   udp_pkt     = NULL;
    int        check_sum   = NULL;
    udphdr_t * set_sum     = NULL;  
    
    if ((NULL == dmy_hdr) || (NULL == udp_hdr) || (NULL == pld)) {
        return NULL;
    }
    
    /* create udp-check-packet */
    udp_chk_pkt  = (u_char *) malloc(sizeof(dummy_udphdr_t) + ntohs(udp_hdr->len));
    if (NULL == udp_chk_pkt) {
        return NULL;
    }
    /* init udp-check-packet */
    memset(udp_chk_pkt, 0x00, sizeof(dummy_udphdr_t) + ntohs(udp_hdr->len));
    
    /** copy contents udp-check-packet **/
    /* udp dummy header */
    memcpy(udp_chk_pkt, dmy_hdr, sizeof(dummy_udphdr_t));
    shift = udp_chk_pkt;
    shift += sizeof(dummy_udphdr_t);
    /* udp header */
    memcpy(shift, udp_hdr, sizeof(udphdr_t));
    shift += sizeof(udphdr_t);
    /* udp payload */
    memcpy(shift, pld, ntohs(udp_hdr->len) - sizeof(udphdr_t));
    
    /* set check sum */
    check_sum = udp_get_chksum(udp_chk_pkt, sizeof(dummy_udphdr_t) + ntohs(udp_hdr->len));
    
    /* release udp-check-packet */
    free(udp_chk_pkt);
    
    /** create udp-packet **/
    udp_pkt  = (u_char *) malloc(ntohs(udp_hdr->len));
    if (NULL == udp_pkt) {
        return NULL;
    }
    /* init udp-check-packet */
    memset(udp_pkt, 0x00, ntohs(udp_hdr->len));
    
    /* copy udp-header */
    memcpy(udp_pkt, udp_hdr, sizeof(udphdr_t));
    shift = udp_pkt;
    shift += sizeof(udphdr_t);
    
    /* copy udp-payload  */
    memcpy(shift, pld, ntohs(udp_hdr->len) - sizeof(udphdr_t));
    
    /* set check sum */
    set_sum = (udphdr_t *) udp_pkt;
    set_sum->check = check_sum;
    
    return udp_pkt;
}

int udp_get_chksum(
        u_char *  chk_pkt,
        int       pkt_size
    ) {
    unsigned long sum = 0;
    u_int16_t *buf    = (u_int16_t *)chk_pkt;
    
    if (NULL == chk_pkt) {
        return DCOM_NG;
    }
    
    // start add
    while( pkt_size > 0 ){
        sum += *buf++;
        
        if( sum & 0x80000000 ){
            // sum is burst
            return DCOM_NG;
        }
        // add every 16bit(2byte)
        pkt_size -= 2;
    }
    
    // for burst
    sum = (sum & 0xffff) + (sum >> 16);
    // for burst
    sum = (sum & 0xffff) + (sum >> 16);
    // complement on one
    return ~sum;
}
/* end of file */
