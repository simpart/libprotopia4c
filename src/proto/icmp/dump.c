/**
 * @file icmp/dump.c
 * @brief dump function for icmp
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include "pia/com.h"
#include "pia/ip.h"
#include "pia/icmp.h"

/*** function ***/
uint8_t pia_icmp_dump (pia_icmphdr_t * msg) {
    char * str_buf = NULL;
    pia_icmpecho_t * chk_echo = NULL;
    
    /* check parameter */
    if (NULL == msg) {
        PIA_ERROR("paramter is NULL");
        return PIA_NG;
    }
    
    /* dump type */
    str_buf = pia_icmp_gettype_str(msg);
    printf("icmp %s ", str_buf);
    
    /* check type */
    if (PIA_TRUE == pia_icmp_isecho(msg)) {
        /* this is echo message */
        chk_echo = (pia_icmpecho_t *) pia_icmp_seekecho(msg);
        if (NULL == chk_echo) {
            PIA_ERROR("return is NULL");
            return PIA_NG;
        }
        printf("id=%u seq=%u", pia_icmp_getid(chk_echo), pia_icmp_getseq(chk_echo));
    } else {
        /* dumo code */
        str_buf = pia_icmp_getcode_str(msg);
        if (NULL == str_buf) {
            PIA_ERROR("return is NULL");
            return PIA_NG;
        }
        printf("code='%s' (0x%x)", str_buf, msg->code);
    }
    printf("\n");
    
    return PIA_OK;
}

uint8_t pia_icmp_dump_detail (pia_ipv4hdr_t * ip_hdr) {
    char *   str_buf = NULL;
    int      msg_siz = 0;
    pia_icmphdr_t * msg = NULL;
    
    if (NULL == ip_hdr) {
        PIA_ERROR("paramter is NULL");
        return PIA_NG;
    }
    msg = (pia_icmphdr_t *) pia_ip_seekpld(ip_hdr);
    
    printf("ICMP message\n");
    printf("==========================\n");
    pia_icmp_dump_type(msg);
    
    if (PIA_TRUE == pia_icmp_isecho(msg)) {
        /* this is echo message */
        printf("code     : 0x%02x\n", msg->code);
        printf("checksum : 0x%04x\n", msg->chksum);
        pia_icmp_dump_id(msg);
        pia_icmp_dump_seq(msg);
        
        msg_siz = pia_ip_getpldsize(ip_hdr);
        if (PIA_NG == msg_siz) {
            return PIA_NG;
        }
        pia_icmp_dump_dat(
            msg,
            msg_siz - (sizeof(pia_icmphdr_t) + sizeof(pia_icmpecho_t))
        );
    } else {
        /* dumo code */
        str_buf = pia_icmp_getcode_str(msg);
        if (NULL == str_buf) {
            PIA_ERROR("return is NULL");
            return PIA_NG;
        }
        printf("code     : '%s' (0x%x)", str_buf, msg->code);
        printf("checksum : 0x%04x\n", msg->chksum);
    }
    
    return PIA_OK;
}


char * pia_icmp_gettype_str (pia_icmphdr_t * msg) {
    char * tp_lst[] = {
        "echo reply"   ,             // 0x00
        "unknown"      ,             // 0x01
        "unknown"      ,             // 0x02
        "destination unreachable",   // 0x03
        "unknown"      ,             // 0x04
        "redirect"     ,             // 0x05
        "unknown"      ,             // 0x06
        "unknown"      ,             // 0x07
        "echo request" ,             // 0x08
        "unknown"      ,             // 0x09
        "unknown"      ,             // 0x0a
        "time exceeded"              // 0x0b
    };
    if (NULL == msg) {
        PIA_ERROR("paramter is NULL");
        return NULL;
    }
    if (PIA_ICMP_TMEXCD  >= msg->type) {
        return tp_lst[msg->type];
    }
    return NULL;
}

char * pia_icmp_getcode_str (pia_icmphdr_t * msg) {
    uint8_t code     = 0;
    char *  unrch_lst[] = {
        "net unreachable"                ,
        "host unreachable"               ,
        "protocol unreachable"           ,
        "port unreachable"               ,
        "fragment needed and df was set" ,
        "source route failed"            ,
        "destination network unknown"    ,
        "destination host unknown"       ,
        "source host isolated"           ,
        "communication with destination network is administratively prohibited" ,
        "communication with destinaltion host is administratively prohibited"   ,
        "destination network unreachable for tos"  ,
        "destination host unreachable for tos"     ,
        "communication administratively prohibited",
        "host precedence violation"                ,
        "precedence cutoff in effect"
    };
    char * rdct_lst[] = {
        "redirect datagram for the network"         ,
        "redirect datagram for the host"            ,
        "redirect datagram for the tos and network" ,
        "redirect datagram for the tos and host"
    };
    char * tmex_lst[] = {
        "time to live exceeded in transit",
        "fragment reassembly time exceeded"
    };
    
    if (NULL == msg) {
        return NULL;
    }
    
    if (PIA_TRUE == pia_icmp_isecho(msg)) {
        return NULL;
    }
    
    code = msg->code;
    switch (code) {
        case PIA_ICMP_DSTUNRCH:
            if (PIA_ICMP_DUNR_PRCDCF >= code) {
                return unrch_lst[code];
            }
            break;
        case PIA_ICMP_REDIRECT:
            if (PIA_ICMP_RDCT_DGTH >= code) {
                return rdct_lst[code];
            }
            break;
        case PIA_ICMP_TMEXCD:
            if ( (PIA_ICMP_TMEX_TTL == code) || (PIA_ICMP_TMEX_FGR == code) ) {
                return tmex_lst[code];
            }
            break;
    }
    return NULL;
}

uint8_t pia_icmp_dump_type (pia_icmphdr_t * msg) {
    char * type_str = pia_icmp_gettype_str(msg);
    if (NULL == type_str) {
        return PIA_NG;
    }
    printf("type     : %s\n", type_str);
    
    return PIA_OK;
}

uint8_t pia_icmp_dump_id(pia_icmphdr_t * msg) {
    uint8_t * seek = NULL;
    
    seek = pia_icmp_seekecho(msg);
    if (NULL == seek) {
        PIA_ERROR("return is NULL");
        return PIA_NG;
    }
    printf("id       : %u\n", pia_icmp_getid((pia_icmpecho_t *)seek));
    return PIA_OK;
}

uint8_t pia_icmp_dump_seq(pia_icmphdr_t * msg) {
    uint8_t * seek = NULL;

    seek = pia_icmp_seekecho(msg);
    if (NULL == seek) {
        PIA_ERROR("return is NULL");
        return PIA_NG;
    }
    printf("sequence : %u\n", pia_icmp_getseq((pia_icmpecho_t *)seek));
    return PIA_OK;
}

uint8_t pia_icmp_dump_dat(pia_icmphdr_t * msg, size_t siz) {
    uint8_t * seek = NULL;
    int       loop = 0;
    
    seek = pia_icmp_seekecho(msg);
    if (NULL == seek) {
        PIA_ERROR("return is NULL");
        return PIA_NG;
    }
    seek = pia_icmp_seekecho_dat((pia_icmpecho_t *) seek);
    if (NULL == seek) {
        PIA_ERROR("return is NULL");
        return PIA_NG;
    }
    printf("data     : (%u byte)\n", (int)siz);
    for (loop=1; loop <= (int)siz ;loop++) {
        if (0 == ((loop-1)%8)) {
            printf("           ");
        }
        printf("%02x", *(seek+(loop-1)));
        if (1 != loop) {
            if ((0 == (loop%2)) && (0 != (loop%8))) {
                printf(" ");
            } else if (0 == (loop%8)) {
                printf("\n");
            }
        }
    }
    return PIA_OK;
}
/* end of file */
