/**
 * @file ether/header.c
 * @brief header function for ether header
 * @author simpart
 */
/*** include ***/
#include <stddef.h>
#include <string.h>
#include "pia/com.h"
#include "pia/eth.h"
/*** global ***/
extern pia_ethhdr_t g_pia_ethhdr;
extern pia_ethhdr_t g_pia_ethhdr_ip;
extern pia_ethhdr_t g_pia_ethhdr_arp;
extern int g_pia_eth_setaddr;
/*** function ***/
/**
 * set default mac address,set to global area
 * 
 * @param[in] dmac : head pointer to dest mac address
 * @param[in] smac : head pointer to src mac address
 * @return PIA_OK : proccessing success
 */
int pia_eth_setdefmac (uint8_t *dmac, uint8_t *smac) {
    uint8_t chk_mac[PIA_ETH_MACSIZE] = {0}; 
    if (NULL != dmac) {
        memcpy(&(g_pia_ethhdr.dmac[0]),     dmac, PIA_ETH_MACSIZE);
        memcpy(&(g_pia_ethhdr_ip.dmac[0]),  dmac, PIA_ETH_MACSIZE);
        memcpy(&(g_pia_ethhdr_arp.dmac[0]), dmac, PIA_ETH_MACSIZE);
    }
    if (NULL != smac) {
        memcpy(&(g_pia_ethhdr.smac[0]),     smac, PIA_ETH_MACSIZE);
        memcpy(&(g_pia_ethhdr_ip.smac[0]),  smac, PIA_ETH_MACSIZE);
        memcpy(&(g_pia_ethhdr_arp.smac[0]), smac, PIA_ETH_MACSIZE);
    }
    /* update init flag */
    if ((NULL != dmac) || (NULL != smac)) {
        g_pia_eth_setaddr = PIA_TRUE;
    } else if ( (0 != memcmp(&(g_pia_ethhdr.dmac[0]), &chk_mac[0], PIA_ETH_MACSIZE)) &&
                (0 != memcmp(&(g_pia_ethhdr.smac[0]), &chk_mac[0], PIA_ETH_MACSIZE))) {
        g_pia_eth_setaddr = PIA_TRUE;
    }
    return PIA_OK;
}

/**
 * set mac address,set to parameter header
 * 
 * @param[in] eth_hdr : head pointer to ether frame
 * @param[in] dmac : head pointer to dest mac address
 * @param[in] smac : head pointer to src mac address
 * @return PIA_NG : proccessing failed
 * @return PIA_OK : proccessing success
 */
int pia_eth_setmac (pia_ethhdr_t *eth_hdr, uint8_t *dmac, uint8_t *smac) {
    /* check paramter */
    if (NULL == eth_hdr) {
        return PIA_NG;
    }
    /* set mac address to header if paramter is set */
    if (NULL != dmac) {
        memcpy(&(eth_hdr->dmac[0]), dmac, PIA_ETH_MACSIZE);
    }
    if (NULL != smac) {
        memcpy(&(eth_hdr->smac[0]), smac, PIA_ETH_MACSIZE);
    }
    return PIA_OK;
}

/**
 * set default ether type,set to global area
 * 
 * @param[in] type : ether type value
 * @return PIA_OK : proccessing success
 */
int pia_eth_setdeftype (uint16_t type) {
    g_pia_ethhdr.type = pia_ntohs(type);
    return PIA_OK;
}

/**
 * set ether type,set to parameter header
 * 
 * @param[in] eth_hdr : head pointer to ether frame
 * @return PIA_NG : proccessing failed
 * @return PIA_OK : proccessing success
 */
int pia_eth_settype (pia_ethhdr_t *eth_hdr, uint16_t type) {
    /* check paramter */
    if (NULL ==eth_hdr) {
        return PIA_NG;
    }
    /* set ether type */
    eth_hdr->type = pia_ntohs(type);
    return PIA_OK;
}

/**
 * get default header,copy from global area
 * 
 * @param[out] buf : frame buffer
 * @param[in] max : buffer max size
 * @return PIA_NG : proccessing failed
 * @return PIA_OK : proccessing success
 */
int pia_eth_gethdr (pia_ethhdr_t *buf, size_t max) {
    /* check parameter */
    if ((NULL == buf) || (max < sizeof(pia_ethhdr_t))) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ethhdr, sizeof(pia_ethhdr_t));
    return PIA_OK;
}

/**
 * get default header,copy from global area
 * 
 * @param[out] buf : frame buffer
 * @param[in] max : buffer max size
 * @return PIA_NG : proccessing failed
 * @return PIA_OK : proccessing success
 * @note ether type is set PIA_ETH_IP(0x800)
 */
int pia_eth_gethdr_ip (pia_ethhdr_t *buf, size_t max) {
    if ( (NULL == buf) || (max < sizeof(pia_ethhdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ethhdr_ip, sizeof(pia_ethhdr_t));
    return PIA_OK;
}

/**
 * get default header,copy from global area
 * 
 * @param[out] buf : frame buffer
 * @param[in] max : buffer max size
 * @return PIA_NG : proccessing failed
 * @return PIA_OK : proccessing success
 * @note ether type is set PIA_ETH_ARP(0x806)
 */
int pia_eth_gethdr_arp (pia_ethhdr_t *buf, size_t max) {
    if ( (NULL == buf) || (max < sizeof(pia_ethhdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ethhdr_arp, sizeof(pia_ethhdr_t));
    return PIA_OK;
}

/**
 * seek to payload
 *
 * @param[in] eth_hdr : head pointer to ether frame
 * @return pointer to payload
 * @return NULL : get payload is failed
 */
uint8_t * pia_eth_seekpld (pia_ethhdr_t *eth_hdr) {
    uint8_t * seek = NULL;
    if (NULL == eth_hdr) {
        return NULL;
    }
    seek = (uint8_t *) eth_hdr;
    return seek + sizeof(pia_ethhdr_t);
}
/* end of file */
