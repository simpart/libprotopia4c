/**
 * @file icmp/classifier.c
 * @author simpart
 */
#include "pia/com.h"
#include "pia/icmp.h"

uint8_t piaicm_isecho (piaicm_hdr_t *msg) {
    if ( (PIA_TRUE == piaicm_isrequest(msg)) ||
         (PIA_TRUE == piaicm_isreply(msg)) ) {
        return PIA_TRUE;
    } else {
        return PIA_FALSE;
    }
}

uint8_t piaicm_isrequest (piaicm_hdr_t *msg) {
    return piaicm_istype(msg, PIAICM_TYPE_ECHOREQ);
}

uint8_t piaicm_isreply (piaicm_hdr_t *msg) {
    return piaicm_istype(msg, PIAICM_TYPE_ECHOREP);
}

uint8_t piaicm_istype (piaicm_hdr_t *msg, uint8_t tp) {
    if (NULL == msg) {
        return PIA_NG;
    }
    if (tp == msg->type) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

/* end of file */
