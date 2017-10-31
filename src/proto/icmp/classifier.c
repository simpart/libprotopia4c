/**
 * @file icmp/classifier.c
 * @author simpart
 */
#include "pia/com.h"
#include "pia/icmp.h"

uint8_t pia_icmp_isrequest (pia_icmpmsg_com_t *msg) {
    return pia_icmp_istype(msg, PIA_ICMP_ECHOREQ);
}

uint8_t pia_icmp_isreply (pia_icmpmsg_com_t *msg) {
    return pia_icmp_istype(msg, PIA_ICMP_ECHOREP);
}

uint8_t pia_icmp_istype (pia_icmpmsg_com_t *msg, uint8_t tp) {
    if (NULL == msg) {
        return PIA_NG;
    }
    if (tp == msg->type) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

/* end of file */
