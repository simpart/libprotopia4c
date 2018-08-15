/**
 * @file eth/header.c
 * @brief header function for ether header
 * @author simpart
 */

/*** include ***/
#include <stddef.h>
#include <string.h>
#include "pia/com.h"
#include "pia/eth.h"

/*** global ***/
extern piaeth_hdr_t g_piaeth_hdr;
extern piaeth_hdr_t g_piaeth_hdrip;
extern piaeth_hdr_t g_piaeth_hdrarp;
extern int g_piaeth_setaddr;

/*** function ***/
/**
 * set default mac address,set to global area
 * 
 * @param[in] dmac : head pointer to dest mac address
 * @param[in] smac : head pointer to src mac address
 * @return PIA_OK : proccessing success
 */
int piaeth_setdefmac (uint8_t *dmac, uint8_t *smac) {
    uint8_t chk_mac[PIAETH_MACSIZ] = {0}; 
    if (NULL != dmac) {
        memcpy(&(g_piaeth_hdr.dmac[0])   , dmac, PIAETH_MACSIZ);
        memcpy(&(g_piaeth_hdrip.dmac[0]) , dmac, PIAETH_MACSIZ);
        memcpy(&(g_piaeth_hdrarp.dmac[0]), dmac, PIAETH_MACSIZ);
    }
    if (NULL != smac) {
        memcpy(&(g_piaeth_hdr.smac[0])   , smac, PIAETH_MACSIZ);
        memcpy(&(g_piaeth_hdrip.smac[0]) , smac, PIAETH_MACSIZ);
        memcpy(&(g_piaeth_hdrarp.smac[0]), smac, PIAETH_MACSIZ);
    }
    /* update init flag */
    if ((NULL != dmac) || (NULL != smac)) {
        g_piaeth_setaddr = PIA_TRUE;
    } else if ( (0 != memcmp(&(g_piaeth_hdr.dmac[0]), &chk_mac[0], PIAETH_MACSIZ)) &&
                (0 != memcmp(&(g_piaeth_hdr.smac[0]), &chk_mac[0], PIAETH_MACSIZ))) {
        g_piaeth_setaddr = PIA_TRUE;
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
int piaeth_setmac (piaeth_hdr_t *eth_hdr, uint8_t *dmac, uint8_t *smac) {
    /* check paramter */
    if (NULL == eth_hdr) {
        return PIA_NG;
    }
    /* set mac address to header if paramter is set */
    if (NULL != dmac) {
        memcpy(&(eth_hdr->dmac[0]), dmac, PIAETH_MACSIZ);
    }
    if (NULL != smac) {
        memcpy(&(eth_hdr->smac[0]), smac, PIAETH_MACSIZ);
    }
    return PIA_OK;
}

/**
 * set default ether type,set to global area
 * 
 * @param[in] type : ether type value
 * @return PIA_OK : proccessing success
 */
int piaeth_setdeftype (uint16_t type) {
    g_piaeth_hdr.type = PIA_M_BYTORD16(type);
    return PIA_OK;
}

/**
 * set ether type,set to parameter header
 * 
 * @param[in] eth_hdr : head pointer to ether frame
 * @param[in] type : ether type value
 * @return PIA_NG : proccessing failed
 * @return PIA_OK : proccessing success
 */
int piaeth_settype (piaeth_hdr_t *eth_hdr, uint16_t type) {
    /* check paramter */
    if (NULL ==eth_hdr) {
        return PIA_NG;
    }
    /* set ether type */
    eth_hdr->type = PIA_M_BYTORD16(type);
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
int piaeth_gethdr (piaeth_hdr_t *buf, size_t max) {
    /* check parameter */
    if ((NULL == buf) || (max < sizeof(piaeth_hdr_t))) {
        return PIA_NG;
    }
    memcpy(buf, &g_piaeth_hdr, sizeof(piaeth_hdr_t));
    return PIA_OK;
}

/**
 * get default header,copy from global area
 * 
 * @param[out] buf : frame buffer
 * @param[in] max : buffer max size
 * @return PIA_NG : proccessing failed
 * @return PIA_OK : proccessing success
 * @note ether type is set PIAETH_TYPE_IP(0x800)
 */
int piaeth_gethdr_ip (piaeth_hdr_t *buf, size_t max) {
    if ( (NULL == buf) || (max < sizeof(piaeth_hdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_piaeth_hdrip, sizeof(piaeth_hdr_t));
    return PIA_OK;
}

/**
 * get default header,copy from global area
 * 
 * @param[out] buf : frame buffer
 * @param[in] max : buffer max size
 * @return PIA_NG : proccessing failed
 * @return PIA_OK : proccessing success
 * @note ether type is set PIAETH_TYPE_ARP(0x806)
 */
int piaeth_gethdr_arp (piaeth_hdr_t *buf, size_t max) {
    if ( (NULL == buf) || (max < sizeof(piaeth_hdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_piaeth_hdrarp, sizeof(piaeth_hdr_t));
    return PIA_OK;
}

/**
 * seek to payload
 *
 * @param[in] eth_hdr : head pointer to ether frame
 * @return pointer to payload
 * @return NULL : get payload is failed
 */
uint8_t * piaeth_seekpld (piaeth_hdr_t *eth_hdr) {
    uint8_t * seek = NULL;
    if (NULL == eth_hdr) {
        return NULL;
    }
    seek = (uint8_t *) eth_hdr;
    return seek + sizeof(piaeth_hdr_t);
}
/* end of file */
