/**
 * @file icmp/init.c
 * @author simpart
 */
#include <sys/types.h> 
#include <unistd.h>
#include <string.h>
#include "pia/icmp.h"

/*** global ***/
pia_icmphdr_t  g_pia_icmphdr;
pia_icmpecho_t g_pia_icmpecho;
pia_icmpdat_t  g_pia_icmpdat;
pia_icmpdat_t  g_pia_icmp_rcvdat;

int pia_icmp_init(void) {
    int loop = 0;
    
    memset(&g_pia_icmphdr,     0x00, sizeof(pia_icmphdr_t));
    memset(&g_pia_icmpdat,     0x00, sizeof(pia_icmpdat_t));
    memset(&g_pia_icmp_rcvdat, 0x00, sizeof(pia_icmpdat_t));
    
    /* set default message type */
    pia_icmp_setdef_type(PIA_ICMP_ECHOREQ);
    
    /* init echo data */
    g_pia_icmpecho.id  = pia_htons((uint16_t) getpid());
    g_pia_icmpecho.seq = pia_htons(1);
    
    /* set default data area */
    g_pia_icmpdat.size = PIA_ICMP_DATDEFSIZ;
    for (loop=0;loop < g_pia_icmpdat.size;loop++) {
        g_pia_icmpdat.data[loop] = loop;
    }
    
    return PIA_OK;
}
/* end of file */
