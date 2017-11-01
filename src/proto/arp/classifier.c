/**
 * @file arp/classifier.c
 * @brief classifier function for arp
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include "pia/arp.h"

/*** function ***/
/**
 * check arp header whether it is request
 * 
 * @param[in] arp_hdr : head pointer to arp header
 * @return PIA_TRUE : this is arp request
 * @return PIA_FALSE : this is not arp request
 * @return PIA_NG : proccessing failed
 */
int pia_arp_isrequest (pia_arphdr_t * arp_hdr) {
    /* check parameter */
    if (NULL == arp_hdr) {
        return PIA_NG;
    }
    if (PIA_ARP_OP_REQ == pia_htons(arp_hdr->op)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/**
 * check arp header whether it is reply
 * 
 * @param[in] arp_hdr : head pointer to arp header
 * @return PIA_TRUE : this is arp reply
 * @return PIA_FALSE : this is not arp reply
 * @return PIA_NG : proccessing failed
 */
int pia_arp_isreply (pia_arphdr_t * arp_hdr) {
    /* check parameter */
    if (NULL == arp_hdr) {
        return PIA_NG;
    }
    if (PIA_ARP_OP_REP == pia_htons(arp_hdr->op)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/* end of file */
