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

uint32_t pia_tcp_getseq (pia_tcphdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }

    return pia_byteodr32(tcp_hdr->seq);
}

uint32_t pia_tcp_getchkack (pia_tcphdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }

    return pia_byteodr32(tcp_hdr->chkack);
}
/* end of file */
