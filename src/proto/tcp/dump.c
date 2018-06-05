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
//    uint8_t *dbg_opt = (uint8_t *) (&(tcp_hdr->urgptr) + sizeof(tcp_hdr->urgptr));
    int ret = 0;
    int idx = 0;
    char *tp_str[] = {
        "end of option list"   , //! 0x00
        "no operation"         , //! 0x01
        "maximum segment size" , //! 0x02
        "window scale"         , //! 0x03
        "sack permitted"       , //! 0x04
        "sack"                 , //! 0x05
        "(unknown type)"       ,
        "(unknown type)"       ,
        "time stamp"             //! 0x08
    };
    pia_tcpopt_t opt = {0};
    

    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    memset(&opt, 0x00, sizeof(pia_tcpopt_t));
    printf("option      : ");
    
    while (1) {
        /* get option element */
        ret = pia_tcp_getopt(tcp_hdr, &opt, idx);
        idx++;
        if (PIA_NG == ret) {
            return PIA_NG;
        } else if (PIA_TCP_OPTOVR == ret) {
            break;
        }
        /*** dump option element ***/
        if (1 != idx) {
            printf("              ");
        }
        /* type */
        if (PIA_TRUE != pia_tcp_isvalidopt(&opt)) { 
            printf("(unknown type)\n");
            continue;
        } else {
            printf("%s(0x%02x)", tp_str[opt.type], opt.type);
        }
        /* length */
        if (0 == opt.len) {
            printf("\n");
            continue;
        }
        printf(",%u byte,", opt.len);
        /* value */
        if (PIA_TCP_OPTTMSP == opt.type) {
            pia_tcp_dump_opttmsp(&opt);
        }
        
        printf("\n");
    }
    
    printf("\n");
    
//    printf("dbg option  : ");
//    pia_dump_opt(
//        dbg_opt,
//        pia_tcp_getoffset(tcp_hdr) - PIA_TCP_NOPTSIZ,
//        14
//    );
    
    return PIA_OK;
}

int pia_tcp_dump_opttmsp(pia_tcpopt_t * tcp_opt) {
    uint32_t ts  = 0;
    uint32_t rep = 0;
    
    if (NULL == tcp_opt) {
        return PIA_NG;
    }
    
    memcpy(&ts,  tcp_opt->val, sizeof(uint32_t));
    memcpy(&rep, (tcp_opt->val+sizeof(uint32_t)), sizeof(uint32_t));
    
    printf("ts(%u),",      PIA_M_BYTORD32(ts));
    printf("echo rep(%u)", PIA_M_BYTORD32(rep));
    
    return PIA_OK;
}
/* end of file */
