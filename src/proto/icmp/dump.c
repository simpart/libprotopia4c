/**
 * @file icmp/dump.c
 * @brief dump function for icmp
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include "pia/com.h"
#include "pia/icmp.h"

/*** function ***/
uint8_t pia_icmp_dump (pia_icmphdr_t * msg) {
    uint8_t *seek = NULL;
    pia_icmpecho_t * chk_echo = NULL;
    
    /* check parameter */
    if (NULL == msg) {
        return PIA_NG;
    }
    
    
    /* check type */
    if (PIA_TRUE == pia_icmp_isrequest(msg)) {
        printf("icmp request ");
    } else if (PIA_TRUE == pia_icmp_isreply(msg)) {
        printf("icmp reply ");
    }
    
    seek = (uint8_t *) msg;
    seek += sizeof(pia_icmphdr_t);
    chk_echo = (pia_icmpecho_t *) seek;
    
    printf("id=%u seq=%u", chk_echo->id, chk_echo->seq);
    printf("\n");
    return PIA_OK;
}

uint8_t pia_icmp_dump_detail (pia_icmphdr_t * msg) {
    if (NULL == msg) {
        return PIA_NG;
    }
    printf("ICMP message\n");
    printf("==========================\n");
    pia_icmp_dump_type(msg);
    //pia_icmp_isrequest
    
    return PIA_OK;
}

void pia_icmp_dump_type (pia_icmphdr_t * msg) {
    char * tp_lst[] = {
        "echo reply"   ,             // 0x00
        "unknown"      ,             // 0x01
        "unknown"      ,             // 0x02
        "destination unreachable",   // 0x03
        "unknown"      ,             // 0x04
        "redirect"     ,             // 0x05
        "unknown"      ,             // 0x06
        "unknown"      ,             // 0x07
        "echo Request" ,             // 0x08
        "unknown"      ,             // 0x09
        "unknown"      ,             // 0x0a
        "time Exceeded"              // 0x0b
    };
    
    if (0x0b < msg->type) {
        printf("type : unknown(0x%x)\n",msg->type);
    } else {
        printf("type : %s(0x%x)\n",tp_lst[msg->type], msg->type);
    }
}

/* end of file */
