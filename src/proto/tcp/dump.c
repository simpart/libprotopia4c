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
int piatcp_dump (piatcp_hdr_t * tcp_hdr) {
    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    printf("tcp ");
    printf(
        "port:%u >> port:%u",
        piatcp_getport(tcp_hdr, PIATCP_PORT_SRC),
        piatcp_getport(tcp_hdr, PIATCP_PORT_DST)
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
int piatcp_dumpdtl (piatcp_hdr_t * tcp_hdr) {
    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    /* check version */
    printf("TCP Header\n");
    printf("=========================\n");
    piatcp_dump_port(tcp_hdr);
    printf("sequence    : %u\n",      piatcp_getseq(tcp_hdr));
    printf("check ack   : %u\n",      piatcp_getchkack(tcp_hdr));
    printf("offset      : %u byte\n", piatcp_getoffset(tcp_hdr));
    piatcp_dump_cflag(tcp_hdr);
    printf("window size : %u\n",      piatcp_getwinsiz(tcp_hdr));
    printf("check sum   : 0x%x\n",    tcp_hdr->chksum);
    if (PIA_TRUE == piatcp_isurg(tcp_hdr)) {
        printf("urg pointer : %u\n",  piatcp_geturgptr(tcp_hdr));
    }
    if (PIA_TRUE == piatcp_existsopt(tcp_hdr)) {
        piatcp_dump_opt(tcp_hdr);
    }
    
    return PIA_OK;
}


int piatcp_dump_port (piatcp_hdr_t * tcp_hdr) {
    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    printf("src  port   : %u\n", piatcp_getport(tcp_hdr, PIATCP_PORT_SRC));
    printf("dest port   : %u\n", piatcp_getport(tcp_hdr, PIATCP_PORT_DST));
    return PIA_OK;
}

int piatcp_dump_cflag (piatcp_hdr_t * tcp_hdr) {
    uint32_t loop = 0;
    int      flg  = PIA_FALSE;
    uint8_t  flglst[] = { PIATCP_CFLG_FIN,
                          PIATCP_CFLG_SYN,
                          PIATCP_CFLG_RST,
                          PIATCP_CFLG_PSH,
                          PIATCP_CFLG_ACK,
                          PIATCP_CFLG_URG };
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

int piatcp_dump_opt(piatcp_hdr_t * tcp_hdr) {
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
    piatcp_opt_t opt = {0};
    

    /* check parameter */
    if (NULL == tcp_hdr) {
        return PIA_NG;
    }
    memset(&opt, 0x00, sizeof(piatcp_opt_t));
    printf("option      : ");
    
    while (1) {
        /* get option element */
        ret = piatcp_getopt(tcp_hdr, &opt, idx);
        idx++;
        if (PIA_NG == ret) {
            return PIA_NG;
        } else if (PIATCP_RET_OPTOVR == ret) {
            break;
        }
        /*** dump option element ***/
        if (1 != idx) {
            printf("              ");
        }
        /* type */
        if (PIA_TRUE != piatcp_isvalidopt(&opt)) { 
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
        if (PIATCP_OPT_TMSP == opt.type) {
            piatcp_dump_opttmsp(&opt);
        }
        
        printf("\n");
    }
    
    printf("\n");
    
    return PIA_OK;
}

int piatcp_dump_opttmsp(piatcp_opt_t * tcp_opt) {
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
