/**
 * @file header.c
 * @author simpart
 */

/*** include ***/
#include <stddef.h>
#include <string.h>
#include "pia/com.h"
#include "pia/eth.h"

/*** global ***/
pia_ethhdr_t g_ethhdr;
pia_ethhdr_t g_ethhdr_ip;
/*** function ***/

int pia_eth_setmac (uint8_t *dmac, uint8_t *smac) {
    if (NULL != dmac) {
        memcpy(&g_ethhdr.dmac, dmac, sizeof(g_ethhdr.dmac));
        memcpy(&g_ethhdr_ip.dmac, dmac, sizeof(g_ethhdr_ip.dmac));
    }
    if (NULL != smac) {
        memcpy(&g_ethhdr.smac, smac, sizeof(g_ethhdr.smac));
        memcpy(&g_ethhdr_ip.smac, smac, sizeof(g_ethhdr_ip.smac));
    }
    return PIA_OK;
}

int pia_eth_settype (uint16_t type) {
    g_ethhdr.type = ntohs(type);
    return PIA_OK;
}

int pia_eth_gethdr (uint8_t *buf, size_t max) {
    if ( (NULL == buf) || (max > sizeof(pia_ethhdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_ethhdr, sizeof(pia_ethhdr_t));
    return PIA_OK;
}

int pia_eth_gethdr_ip (uint8_t *buf, size_t max) {
    if ( (NULL == buf) || (max > sizeof(pia_ethhdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_ethhdr_ip, sizeof(pia_ethhdr_t));
    return PIA_OK;
}
/* end of file */
