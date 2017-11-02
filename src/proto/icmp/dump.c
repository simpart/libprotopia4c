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
        "Echo Reply"   ,             // 0x00
        "Unknown"      ,             // 0x01
        "Unknown"      ,             // 0x02
        "Destination Unreachable",   // 0x03
        "Unknown"      ,             // 0x04
        "Redirect"     ,             // 0x05
        "Unknown"      ,             // 0x06
        "Unknown"      ,             // 0x07
        "Echo Request" ,             // 0x08
        "Unknown"      ,             // 0x09
        "Unknown"      ,             // 0x0a
        "Time Exceeded"              // 0x0b
    };
    
    if (0x0b < msg->type) {
        printf("type : Unknown(0x%x)\n",msg->type);
    } else {
        printf("type : %s(0x%x)\n",tp_lst[msg->type], msg->type);
    }
}

/* end of file */
