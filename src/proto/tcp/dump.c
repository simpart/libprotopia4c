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
    uint8_t * dbg = NULL;

    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    /* check version */
    printf("TCP Header\n");
    printf("=========================\n");
    pia_tcp_dump_port(tcp_hdr);
    pia_tcp_dump_seq(tcp_hdr);
    pia_tcp_dump_chkack(tcp_hdr);
    
    


    printf("%u\n", tcp_hdr->ctlflg);
    
    return PIA_OK;
}


int pia_tcp_dump_port (pia_tcphdr_t * tcp_hdr) {
    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    printf("src  port : %u\n", pia_tcp_getport(tcp_hdr, PIA_TCP_SPORT));
    printf("dest port : %u\n", pia_tcp_getport(tcp_hdr, PIA_TCP_DPORT));
    return PIA_OK;
}

int pia_tcp_dump_seq (pia_tcphdr_t * tcp_hdr) {
    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    printf("sequence  : %u\n", pia_tcp_getseq(tcp_hdr));
    return PIA_OK;
}

int pia_tcp_dump_chkack (pia_tcphdr_t * tcp_hdr) {
    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    printf("check ack : %u\n", pia_tcp_getchkack(tcp_hdr));
    return PIA_OK;
}
/* end of file */
