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
extern piaarp_hdr_t g_arphdr;

/*** function ***/
/**
 * set default request address,set to global area
 * 
 * @param[in] rip : head pointer to request ipv4 address
 * @return PIA_OK : proccessing success
 * @return PIA_NG : proccessing failed
 * @note not supported yet
 */
int piaarp_setreq (uint8_t * rip) {
    rip = rip;
    return 0;
}

/**
 * get ether frame with arp header
 *
 * @param[in] buf : frame buffer
 * @param[in] max : buffer size
 * @param[in] type : arp type (PIAARP_OP_REQ/PIAARP_OP_REP)
 * @return PIA_OK : proccessing success
 * @return PIA_NG : proccessing failed
 * @note not supported yet
 */
int piaarp_getfrm (uint8_t *buf, size_t max, uint8_t type) {
    int ret = 0;
    piaeth_hdr_t * eth_hdr = NULL;
    
    if (NULL == buf) {
        return PIA_NG;
    }
    
    /* get ether header */
    ret = piaeth_gethdr_arp((piaeth_hdr_t *)buf, max);
    if (PIA_NG == ret) {
        return ret;
    }
    if (PIAARP_OP_REQ == type) {
        /* this is request */
        eth_hdr = (piaeth_hdr_t *) buf;
        memset(&(eth_hdr->dmac[0]), 0xFF, PIAETH_MACSIZ);
    }
    
    /* get arp header */
    buf += sizeof(piaeth_hdr_t);  // seek to head of arp header
    piaarp_gethdr(
        (piaarp_hdr_t *) buf,
        max - sizeof(piaeth_hdr_t),
        type
    );
    
    return PIA_OK;
}

/**
 * get arp header
 * 
 * @param[out] buf : header buffer
 * @param[in] max : buffer size
 * @param[in] type : arp type (PIAARP_OP_REQ/PIAARP_OP_REP)
 * @return PIA_OK : proccessing success
 * @return PIA_NG : proccessing failed
 * @note not supported yet
 */
int piaarp_gethdr (piaarp_hdr_t *buf, size_t max, uint8_t type) {
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
