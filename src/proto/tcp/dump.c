/**
 * @file tcp/dump.c
 * @brief dump function for tcp header
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include "pia/com.h"
#include "pia/tcp.h"
/*** function ***/
/**
 * dump tcp header by a line
 *
 * @param[in] tcp_hdr : head pointer to tcp header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 * @note not supported
 */
int pia_tcp_dump (pia_tcphdr_t * tcp_hdr) {
    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    printf("tcp ");
    printf(
        "port:%u >> port:%u",
        pia_tcp_getport(tcp_hdr, PIA_TCP_SPORT),
        pia_tcp_getport(tcp_hdr, PIA_TCP_DPORT)
    );
    printf("\n");
    return PIA_OK;
}
/**
 * dump tcp header detail
 *
 * @param[in] tcp_hdr : head pointer to tcp header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_tcp_dump_detail (pia_tcphdr_t * tcp_hdr) {
    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    /* check version */
    printf("TCP Header\n");
    printf("=========================\n");
    pia_tcp_dump_port(tcp_hdr);
    printf("sequence    : %u\n",      pia_tcp_getseq(tcp_hdr));
    printf("check ack   : %u\n",      pia_tcp_getchkack(tcp_hdr));
    printf("offset      : %u byte\n", pia_tcp_getoffset(tcp_hdr));
    pia_tcp_dump_cflag(tcp_hdr);
    printf("window size : %u\n",      pia_tcp_getwinsiz(tcp_hdr));
    printf("check sum   : 0x%x\n",    tcp_hdr->chksum);
    if (PIA_TRUE == pia_tcp_isurg(tcp_hdr)) {
        printf("urg pointer : %u\n",  pia_tcp_geturgptr(tcp_hdr));
    }
    if (PIA_TRUE == pia_tcp_existsopt(tcp_hdr)) {
        pia_tcp_dump_opt(tcp_hdr);
    }
    
    return PIA_OK;
}


int pia_tcp_dump_port (pia_tcphdr_t * tcp_hdr) {
    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    printf("src  port   : %u\n", pia_tcp_getport(tcp_hdr, PIA_TCP_SPORT));
    printf("dest port   : %u\n", pia_tcp_getport(tcp_hdr, PIA_TCP_DPORT));
    return PIA_OK;
}

int pia_tcp_dump_cflag (pia_tcphdr_t * tcp_hdr) {
    uint32_t loop = 0;
    int      flg  = PIA_FALSE;
    uint8_t  flglst[] = { PIA_TCP_FINFLG,
                          PIA_TCP_SYNFLG,
                          PIA_TCP_RSTFLG,
                          PIA_TCP_PSHFLG,
                          PIA_TCP_ACKFLG,
                          PIA_TCP_URGFLG };
    char * flgnm[]   = { "FIN","SYN","RST","PSH","ACK","URG" };
    
    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }

    printf("ctrl flag   : ");
    for (loop=0;loop < sizeof(flglst) ;loop++) {
        if (0 != (flglst[loop] & tcp_hdr->ctlflg)) {
            if (PIA_TRUE == flg) {
                printf(",");
            }
            printf("%s", flgnm[loop]);
            flg = PIA_TRUE;
        }
    }
    if (PIA_FALSE == flg) {
        printf("(no flag)");
    }
    
    printf("\n");
    
    return PIA_OK;
}

int pia_tcp_dump_opt(pia_tcphdr_t * tcp_hdr) {
    uint8_t *tcp_opt = NULL;
    int     opt_siz  = 0;
    char    *opt_idx = "option      : ";
    
    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    
    tcp_opt  = (uint8_t *) &(tcp_hdr->urgptr);
    tcp_opt += sizeof(tcp_hdr->urgptr);
    
    opt_siz = pia_tcp_getoffset(tcp_hdr) - PIA_TCP_NOPTSIZ;
    if (0 > opt_siz) {
        return PIA_NG;
    }
    
    printf("%s", opt_idx);
    pia_dump_opt(tcp_opt, opt_siz , strnlen(opt_idx, 14));
    
    printf("\n");
    return PIA_OK;
}
/* end of file */
