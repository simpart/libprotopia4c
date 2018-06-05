/**
 * @file tcp/header.c
 * @brief header function for tcp header
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include "pia/com.h"
#include "pia/tcp.h"

/*** function ***/
uint16_t pia_tcp_getport (pia_tcphdr_t * tcp_hdr, int type) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    
    if (PIA_TCP_SPORT == type) {
        return PIA_M_BYTORD16(tcp_hdr->sport);
    } else if (PIA_TCP_DPORT == type) {
        return PIA_M_BYTORD16(tcp_hdr->dport);
    }
    return PIA_NG;
}

uint32_t pia_tcp_getseq (pia_tcphdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }

    return PIA_M_BYTORD32(tcp_hdr->seq);
}

uint32_t pia_tcp_getchkack (pia_tcphdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }

    return PIA_M_BYTORD32(tcp_hdr->chkack);
}

uint8_t pia_tcp_getoffset (pia_tcphdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    return tcp_hdr->offset * 4;
}

uint16_t pia_tcp_getwinsiz (pia_tcphdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    return PIA_M_BYTORD16(tcp_hdr->winsiz);
}

uint16_t pia_tcp_geturgptr (pia_tcphdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    return PIA_M_BYTORD16(tcp_hdr->urgptr);
}

int pia_tcp_getopt (pia_tcphdr_t * tcp_hdr, pia_tcpopt_t *opt , int idx) {
    int loop    = 0;
    int vloop   = 0;
    int opt_siz = 0;
    uint8_t *p_fst = (uint8_t *) (&(tcp_hdr->urgptr) + sizeof(tcp_hdr->urgptr));
    uint8_t *p_opt = (uint8_t *) (&(tcp_hdr->urgptr) + sizeof(tcp_hdr->urgptr));
    
    /* check parameter */
    if ( (NULL == tcp_hdr) || (NULL == opt) || (idx < 0) ) {
        return PIA_NG;
    }
    
    /* get option size */
    opt_siz = pia_tcp_getoffset(tcp_hdr) - PIA_TCP_NOPTSIZ;
    
    do {
        /* init option */
        memset(opt, 0x00, sizeof(pia_tcpopt_t));
        
        /* check over run */
        if ( opt_siz <= (p_opt - p_fst) ) {
            return PIA_TCP_OPTOVR;
        }
        
        /* get option type */
        opt->type = (uint8_t) *p_opt;
        p_opt += sizeof(uint8_t);
        
        /* get option length */
        if ( (PIA_TCP_OPTEND == opt->type) ||
             (PIA_TCP_OPTNOO == opt->type) ||
             (PIA_TRUE != pia_tcp_isvalidopt(opt)) ) {
            /* skip length */
            loop++;
            continue;
        }
        opt->len = (uint8_t) *p_opt;
        p_opt += sizeof(uint8_t);
        
        /* get option value */
        if (PIA_TCP_OPTSAPM == opt->type) {
            /* this is no value */
            loop++;
            continue;
        }
        opt->val = p_opt;
        for (vloop=0;vloop < (opt->len-2);vloop++) {
            p_opt += sizeof(uint8_t);
        }
        
        loop++;
    } while (loop <= idx);
    
    return PIA_OK;
}
/* end of file */
