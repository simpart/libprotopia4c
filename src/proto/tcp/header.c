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
uint16_t piatcp_getport (piatcp_hdr_t * tcp_hdr, int type) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    
    if (PIATCP_PORT_SRC == type) {
        return PIA_M_BYTORD16(tcp_hdr->sport);
    } else if (PIATCP_PORT_DST == type) {
        return PIA_M_BYTORD16(tcp_hdr->dport);
    }
    return PIA_NG;
}

uint32_t piatcp_getseq (piatcp_hdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }

    return PIA_M_BYTORD32(tcp_hdr->seq);
}

uint32_t piatcp_getchkack (piatcp_hdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }

    return PIA_M_BYTORD32(tcp_hdr->chkack);
}

uint8_t piatcp_getoffset (piatcp_hdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    return tcp_hdr->offset * 4;
}

uint16_t piatcp_getwinsiz (piatcp_hdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    return PIA_M_BYTORD16(tcp_hdr->winsiz);
}

uint16_t piatcp_geturgptr (piatcp_hdr_t * tcp_hdr) {
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    return PIA_M_BYTORD16(tcp_hdr->urgptr);
}

int piatcp_getopt (piatcp_hdr_t * tcp_hdr, piatcp_opt_t *opt , int idx) {
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
    opt_siz = piatcp_getoffset(tcp_hdr) - PIATCP_NOPTSIZ;
    
    do {
        /* init option */
        memset(opt, 0x00, sizeof(piatcp_opt_t));
        
        /* check over run */
        if ( opt_siz <= (p_opt - p_fst) ) {
            return PIATCP_RET_OPTOVR;
        }
        
        /* get option type */
        opt->type = (uint8_t) *p_opt;
        p_opt += sizeof(uint8_t);
        
        /* get option length */
        if ( (PIATCP_OPT_END == opt->type) ||
             (PIATCP_OPT_NO  == opt->type) ||
             (PIA_TRUE != piatcp_isvalidopt(opt)) ) {
            /* skip length */
            loop++;
            continue;
        }
        opt->len = (uint8_t) *p_opt;
        p_opt += sizeof(uint8_t);
        
        /* get option value */
        if (PIATCP_OPT_SAPM == opt->type) {
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
