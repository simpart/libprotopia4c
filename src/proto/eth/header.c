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
extern pia_ethhdr_t g_pia_ethhdr;
extern pia_ethhdr_t g_pia_ethhdr_ip;
extern pia_ethhdr_t g_pia_ethhdr_arp;
extern int g_pia_eth_setaddr;
/*** function ***/

int pia_eth_setdefmac (uint8_t *dmac, uint8_t *smac) {
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
    } else if ( (0 != memcmp(&(g_pia_ethhdr.dmac[0]), 0x00, PIA_ETH_MACSIZE)) &&
                (0 != memcmp(&(g_pia_ethhdr.smac[0]), 0x00, PIA_ETH_MACSIZE))) {
        g_pia_eth_setaddr = PIA_TRUE;
    }
    return PIA_OK;
}

int pia_eth_setmac (pia_ethhdr_t *hdr, uint8_t *dmac, uint8_t *smac) {
    if (NULL == hdr) {
        return PIA_NG;
    }
    if (NULL != dmac) {
        memcpy(&(hdr->dmac[0]), dmac, PIA_ETH_MACSIZE);
    }
    if (NULL != smac) {
        memcpy(&(hdr->smac[0]), smac, PIA_ETH_MACSIZE);
    }
    return PIA_OK;
}

int pia_eth_setdeftype (uint16_t type) {
    g_pia_ethhdr.type = pia_ntohs(type);
    return PIA_OK;
}

int pia_eth_settype (pia_ethhdr_t *hdr, uint16_t type) {
    if (NULL ==hdr) {
        return PIA_NG;
    }
    hdr->type = pia_ntohs(type);
    return PIA_OK;
}

int pia_eth_gethdr (uint8_t *buf, size_t max) {
    if ( (NULL == buf) || (max < sizeof(pia_ethhdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ethhdr, sizeof(pia_ethhdr_t));
    return PIA_OK;
}

int pia_eth_gethdr_ip (uint8_t *buf, size_t max) {
    if ( (NULL == buf) || (max < sizeof(pia_ethhdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ethhdr_ip, sizeof(pia_ethhdr_t));
    return PIA_OK;
}

int pia_eth_gethdr_arp (uint8_t *buf, size_t max) {
    if ( (NULL == buf) || (max < sizeof(pia_ethhdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_pia_ethhdr_arp, sizeof(pia_ethhdr_t));
    return PIA_OK;
}

uint8_t * pia_eth_getconts (uint8_t *frm) {
    if (NULL == frm) {
        return NULL;
    }
    return frm + sizeof(pia_ethhdr_t);
}
/* end of file */
