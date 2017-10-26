/**
 * @file ip/dump.c
 * @author simpart
 */
#include <string.h>
#include "pia/ip.h"

/*** function ***/
/**
 * 
 * 
 */
uint8_t pia_ip_getipv4 (uint8_t *pkt, uint8_t *sip, uint8_t *dip) {
    pia_ipv4hdr_t *ip_hdr = NULL;
    
    if ((NULL == pkt) || (NULL == sip) || (NULL == dip)) {
        return PIA_NG;
    }
    
    ip_hdr = (pia_ipv4hdr_t *) pkt;
    
    memcpy(sip, ip_hdr->sip, sizeof(uint8_t));
    memcpy(dip, ip_hdr->dip, sizeof(uint8_t));
    
    return PIA_OK;
}
/* end of file */
