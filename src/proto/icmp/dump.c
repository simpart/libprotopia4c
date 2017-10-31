/**
 * @file icmp/dump.c
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include "pia/com.h"
#include "pia/icmp.h"

uint8_t pia_icmp_dump (pia_icmpmsg_com_t * msg) {
    if (NULL == msg) {
        return PIA_NG;
    }
    printf("ICMP message\n");
    printf("==========================\n");
    pia_icmp_dump_type(msg);
    //pia_icmp_isrequest
    
    return PIA_OK;
}

void pia_icmp_dump_type (pia_icmpmsg_com_t * msg) {
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
