/**
 * @file arp/header.c
 * @brief header function for arp
 * @author simpart
 */
/*** include ***/
#include <string.h>
#include "pia/eth.h"
#include "pia/com.h"
#include "pia/arp.h"

/*** global ***/
extern pia_arphdr_t g_arphdr;

/*** function ***/
/**
 * set default request address,set to global area
 * 
 * @param[in] uint8_t rip : head pointer to request ipv4 address
 * @return PIA_OK : proccessing success
 * @return PIA_NG : proccessing failed
 * @note not supported yet
 */
int pia_arp_setreq (uint8_t * rip) {
    rip = rip;
    return 0;
}

/**
 * get ether frame with arp header
 *
 * @param[in] buf : frame buffer
 * @param[in] max : buffer size
 * @param[in] type : arp type (PIA_ARP_OP_REQ/PIA_ARP_OP_REP)
 * @return PIA_OK : proccessing success
 * @return PIA_NG : proccessing failed
 * @note not supported yet
 */
int pia_arp_getfrm (uint8_t *buf, size_t max, uint8_t type) {
    int ret = 0;
    pia_ethhdr_t * eth_hdr = NULL;
    
    if (NULL == buf) {
        return PIA_NG;
    }
    
    /* get ether header */
    ret = pia_eth_gethdr_arp((pia_ethhdr_t *)buf, max);
    if (PIA_NG == ret) {
        return ret;
    }
    if (PIA_ARP_OP_REQ == type) {
        /* this is request */
        eth_hdr = (pia_ethhdr_t *) buf;
        memset(&(eth_hdr->dmac[0]), 0xFF, PIA_ETH_MACSIZE);
    }
    
    /* get arp header */
    buf += sizeof(pia_ethhdr_t);  // seek to head of arp header
    pia_arp_gethdr(
        (pia_arphdr_t *) buf,
        max - sizeof(pia_ethhdr_t),
        type
    );
    
    return PIA_OK;
}

/**
 * get arp header
 * 
 * @param[out] buf : header buffer
 * @param[in] max : buffer size
 * @param[in] type : arp type (PIA_ARP_OP_REQ/PIA_ARP_OP_REP)
 * @return PIA_OK : proccessing success
 * @return PIA_NG : proccessing failed
 * @note not supported yet
 */
int pia_arp_gethdr (pia_arphdr_t *buf, size_t max, uint8_t type) {
//    if ((NULL == buf) || (sizeof(pia_arphdr_t) > max)) {
///        return PIA_NG;
 //   }
//    
//    memcpy(buf, &g_arphdr, sizeof(pia_arphdr_t));
//    
//    
//    
    buf = buf;
    max = max;
    type = type;
    return PIA_OK;
}
/* end of file */
