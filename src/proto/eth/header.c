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
extern pia_ethhdr_t g_ethhdr;
extern pia_ethhdr_t g_ethhdr_ip;
extern pia_ethhdr_t g_ethhdr_arp;

/*** function ***/

int pia_eth_setmac (uint8_t *dmac, uint8_t *smac) {
    if (NULL != dmac) {
        memcpy(&(g_ethhdr.dmac[0]),     dmac, sizeof(g_ethhdr.dmac));
        memcpy(&(g_ethhdr_ip.dmac[0]),  dmac, sizeof(g_ethhdr_ip.dmac));
        memcpy(&(g_ethhdr_arp.dmac[0]), dmac, sizeof(g_ethhdr_arp.dmac));
    }
    if (NULL != smac) {
        memcpy(&(g_ethhdr.smac[0]),     smac, sizeof(g_ethhdr.smac));
        memcpy(&(g_ethhdr_ip.smac[0]),  smac, sizeof(g_ethhdr_ip.smac));
        memcpy(&(g_ethhdr_arp.smac[0]), smac, sizeof(g_ethhdr_arp.smac));
    }
    return PIA_OK;
}

int pia_eth_settype (uint16_t type) {
    g_ethhdr.type = pia_ntohs(type);
    return PIA_OK;
}

int pia_eth_gethdr (uint8_t *buf, size_t max) {
    if ( (NULL == buf) || (max < sizeof(pia_ethhdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_ethhdr, sizeof(pia_ethhdr_t));
    return PIA_OK;
}

int pia_eth_gethdr_ip (uint8_t *buf, size_t max) {
    if ( (NULL == buf) || (max < sizeof(pia_ethhdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_ethhdr_ip, sizeof(pia_ethhdr_t));
    return PIA_OK;
}

int pia_eth_gethdr_arp (uint8_t *buf, size_t max) {
    if ( (NULL == buf) || (max < sizeof(pia_ethhdr_t)) ) {
        return PIA_NG;
    }
    memcpy(buf, &g_ethhdr_arp, sizeof(pia_ethhdr_t));
    return PIA_OK;
}

uint8_t * pia_eth_getconts (uint8_t *frm) {
    if (NULL == frm) {
        return NULL;
    }
    return frm + sizeof(pia_ethhdr_t);
}
/* end of file */
