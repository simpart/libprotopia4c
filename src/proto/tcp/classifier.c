/**
 * @file tcp/classifier.c
 * @brief classifier function for tcp header
 * @author simpart
 */
/*** include ***/
#include "pia/com.h"
#include "pia/tcp.h"

/*** function ***/
int piatcp_issyn (piatcp_hdr_t * tcp_hdr) {
    return piatcp_isctlflg(
               tcp_hdr,
               PIATCP_CFLG_SYN
           );
}

int piatcp_isack (piatcp_hdr_t * tcp_hdr) {
    return piatcp_isctlflg(
               tcp_hdr,
               PIATCP_CFLG_ACK
           );
}

int piatcp_issynack (piatcp_hdr_t * tcp_hdr) {
    return piatcp_isctlflg(
               tcp_hdr,
               PIATCP_CFLG_SYN | PIATCP_CFLG_ACK
           );
}

int piatcp_isfinack (piatcp_hdr_t * tcp_hdr) {
    return piatcp_isctlflg(
               tcp_hdr,
               PIATCP_CFLG_FIN | PIATCP_CFLG_ACK
           );
}

int piatcp_isrst (piatcp_hdr_t *tcp_hdr) {
    return piatcp_isctlflg(
               tcp_hdr,
               PIATCP_CFLG_RST
           );
}

int piatcp_isurg (piatcp_hdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    if (0 != (PIATCP_CFLG_URG & tcp_hdr->urgptr)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

int piatcp_isctlflg (piatcp_hdr_t * tcp_hdr, uint8_t flg) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    
    if (flg == tcp_hdr->ctlflg) {
        return PIA_TRUE;
    }
    
    return PIA_FALSE;
}

int piatcp_existsopt(piatcp_hdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    if (PIATCP_NOPTSIZ < piatcp_getoffset(tcp_hdr)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

int piatcp_isvalidopt (piatcp_opt_t *opt) {
    if (NULL == opt) {
        return PIA_NG;
    }
    if (PIATCP_OPT_TMSP < opt->type) {
        return PIA_FALSE;
    } else if ((0x06 == opt->type) || (opt->type == 0x07)) {
        return PIA_FALSE;
    }
    return PIA_TRUE;
}
/* end of file */
