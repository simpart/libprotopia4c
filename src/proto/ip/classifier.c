/**
 * @file ip/classifier.c
 * @author simpart
 */
#include <stdio.h>
#include "pia/ether.h"
#include "pia/ip.h"

int pia_isip (pkt frm) {
    //piast_ether_t *eth = NULL;
    
    if (NULL == frm) {
        return PIA_FALSE;
    }
    
    pia_dmp_ether((piast_ether_hdr_t *) frm);
    
    return PIA_TRUE;
}
/* end of file */
