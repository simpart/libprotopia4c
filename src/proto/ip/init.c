/**
 * @file init.c
 * @author simpart
 */
#include <sys/time.h>
#include "pia/ip.h"

/*** global ***/
pia_ipv4hdr_t g_pia_ipv4hdr;
pia_ipv4hdr_t g_pia_ipv4hdr_tcp;
pia_ipv4hdr_t g_pia_ipv4hdr_icmp;

/*** function ***/
int pia_ip_init (void) {
    g_pia_ipv4hdr.ver      = 4;
//    g_pia_ipv4hdr.hlen     = 5;
    g_pia_ipv4hdr.tos      = 0;
    //g_ipv4hdr.total = 0;
    g_pia_ipv4hdr.id       = pia_ip_getid();
    g_pia_ipv4hdr.frag_off = 0;
    g_pia_ipv4hdr.ttl      = 0;
    
    return PIA_OK;
}
/* end of file */
