/**
 * @file icmp/header.c
 * @author simpart
 */
#include "pia/com.h"
#include "pia/eth.h"
#include "pia/ip.h"
#include "pia/icmp.h"

int pia_icmp_getfrm (uint8_t *buf, size_t max, int type) {
    buf = buf;
    max = max;
    type = type;
//    int ret = 0;
//    /* check parameter */
//    if (NULL == buf) {
//        return PIA_NG;
//    }
    
    //pia_eth_gethdr
    //ret = pia_ip_getpkt(buf, max, PIA_IP_ICMP);
    //if (PIA_OK != ret) {
    //    return ret;
    //}
    
    return PIA_OK;
}

int pia_icmp_getpkt (uint8_t *buf, size_t max, int type) {
    buf = buf;
    max = max;
    type = type;
    return PIA_OK;
}
/* end of file */

