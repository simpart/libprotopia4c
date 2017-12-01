/**
 * @file tcp/header.c
 * @brief header function for ip header
 * @author simpart
 */
/*** include ***/
#include "pia/com.h"
#include "pia/tcp.h"

/*** function ***/
uint16_t pia_tcp_getport (pia_tcphdr_t * tcp_hdr, int type) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    
    if (PIA_TCP_SPORT == type) {
        return pia_ntohs(tcp_hdr->sport);
    } else if (PIA_TCP_DPORT == type) {
        return pia_ntohs(tcp_hdr->dport);
    }
    return PIA_NG;
}

/* end of file */
