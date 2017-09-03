/**
 * @file frame.c
 * @author simpart
 */
#include <string.h>
#include <unistd.h>
#include "pia/com.h"
#include "pia/eth.h"
#include "pia/ip.h"
#include "pia/icmp.h"

/*** function ***/


int pia_icmp_getecho_req (uint8_t * buf, size_t max) {
    pia_icmphdr_com_t  com_hdr;
    pia_icmphdr_echo_t echo_hdr;
    uint8_t *msg = NULL;
    
    // no offset
    int offset = sizeof(pia_ethhdr_t) + sizeof(pia_ipv4hdr_t);
    
    if (NULL == buf) {
        return PIA_NG;
    }
    
    /* get header */
    if (PIA_OK != pia_ip_getv4hdr_icmp(buf, max)) {
        return PIA_NG;
    }
    
    /* set icmp common header */
    com_hdr.type = PIA_ICMP_ECHOREQ;
    com_hdr.code = 0;
    memcpy(
        buf + offset,
        &com_hdr,
        sizeof(pia_icmphdr_com_t)
    );
    offset += sizeof(pia_icmphdr_com_t);
    
    /* set icmp echo header */
    echo_hdr.id  = (int) getpid();
    echo_hdr.seq = pia_icmp_getseq();
    memcpy(
        buf + offset,
        &echo_hdr,
        sizeof(pia_icmphdr_echo_t)
    );
    
    /* set icmp echo message */
    offset += sizeof(pia_icmphdr_echo_t);
    if (PIA_OK != pia_icmp_getdata(buf + offset, 32) ) {
        return PIA_NG;
    }
    msg = buf + offset;
    
    /* set icmp checksum */
    echo_hdr.chksum = pia_checksum((uint16_t *)msg, 32);
    offset -= sizeof(pia_icmphdr_echo_t) + sizeof(pia_icmphdr_com_t);
    com_hdr.chksum  = pia_checksum(
                          (uint16_t *)buf + offset,
                          sizeof(pia_icmphdr_echo_t) + 32
                      );
    
    // ip length
    
    /* set ip checksum */
    //pia_ip_chksum(buf + sizeof(pia_ethhdr_t));
    
    return PIA_OK;
}
/* end of file */
