/**
 * @file tcp/classifier.c
 * @brief classifier function for tcp header
 * @author simpart
 */
/*** include ***/
#include "pia/com.h"
#include "pia/tcp.h"

/*** function ***/
int pia_tcp_issyn (pia_tcphdr_t * tcp_hdr) {
    return pia_tcp_isctlflg(
               tcp_hdr,
               PIA_TCP_SYNFLG
           );
}

int pia_tcp_isack (pia_tcphdr_t * tcp_hdr) {
    return pia_tcp_isctlflg(
               tcp_hdr,
               PIA_TCP_ACKFLG
           );
}

int pia_tcp_issynack (pia_tcphdr_t * tcp_hdr) {
    return pia_tcp_isctlflg(
               tcp_hdr,
               PIA_TCP_SYNFLG | PIA_TCP_ACKFLG
           );
}

int pia_tcp_isfinack (pia_tcphdr_t * tcp_hdr) {
    return pia_tcp_isctlflg(
               tcp_hdr,
               PIA_TCP_FINFLG | PIA_TCP_ACKFLG
           );
}

int pia_tcp_isrst (pia_tcphdr_t *tcp_hdr) {
    return pia_tcp_isctlflg(
               tcp_hdr,
               PIA_TCP_RSTFLG
           );
}

int pia_tcp_isurg (pia_tcphdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    if (0 != (PIA_TCP_URGFLG & tcp_hdr->urgptr)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

int pia_tcp_isctlflg (pia_tcphdr_t * tcp_hdr, uint8_t flg) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    
    if (flg == tcp_hdr->ctlflg) {
        return PIA_TRUE;
    }
    
    return PIA_FALSE;
}

int pia_tcp_existsopt(pia_tcphdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    if (PIA_TCP_NOPTSIZ < pia_tcp_getoffset(tcp_hdr)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

int pia_tcp_isvalidopt (pia_tcpopt_t *opt) {
    if (NULL == opt) {
        return PIA_NG;
    }
    if (PIA_TCP_OPTTMSP < opt->type) {
        return PIA_FALSE;
    } else if ((0x06 == opt->type) || (opt->type == 0x07)) {
        return PIA_FALSE;
    }
    return PIA_TRUE;
}
/* end of file */
