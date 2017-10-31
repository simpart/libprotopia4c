/**
 * @file icmp/header.c
 * @author simpart
 */
#include "pia/com.h"
#include "pia/eth.h"
#include "pia/ip.h"
#include "pia/icmp.h"

int pia_icmp_getmsg_frame (uint8_t *frm) {
//    int ret = 0;
 //   pia_iphdr_t *ip_hdr = NULL;
 //   
//    /* check parameter */
//    if (NULL == frm) {
//        return PIA_NG;
//    }
///    /* check ether protocol */
 //   if (PIA_FALSE == pia_eth_isip(frm)) {
 //       return PIA_NG;
 //   }
 //   /* get ip header */
 //   ip_hdr = pia_eth_getconts(frm);
 //   if (NULL == ip_hdr) {
 //       return PIA_NG;
 //   }
    /* check ip protocol */
    
    
    /* get icmp message */
    //pia_ip_getconts
    return PIA_OK;
}
//int pia_icmp_getfrm (uint8_t *buf, size_t max, uint8_t type) {
//    
//}
//
//int pia_icmp_getpkt (uint8_t *buf, size_t max, uint8_t type) {
//    
//}
//
//
//int pia_icmp_gethdr (uint8_t *buf, size_t max, uint8_t type) {
//    
//}
/* end of file */

