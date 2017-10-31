/**
 * @file init.c
 * @author simpart
 */
#include <sys/time.h>
#include <string.h>
#include "pia/ip.h"

/*** global ***/
pia_ipv4hdr_t g_pia_ipv4hdr = {0};
pia_ipv4hdr_t g_pia_ipv4hdr_tcp = {0};
pia_ipv4hdr_t g_pia_ipv4hdr_udp = {0};
pia_ipv4hdr_t g_pia_ipv4hdr_icmp = {0};
int g_pia_ip_setaddr = PIA_FALSE;
/*** function ***/
int pia_ip_init (void) {
    
    /* init global */
    memset(&g_pia_ipv4hdr,      0x00, sizeof(pia_ipv4hdr_t));
    memset(&g_pia_ipv4hdr_tcp,  0x00, sizeof(pia_ipv4hdr_t));
    memset(&g_pia_ipv4hdr_udp,  0x00, sizeof(pia_ipv4hdr_t));
    memset(&g_pia_ipv4hdr_icmp, 0x00, sizeof(pia_ipv4hdr_t));
    
    g_pia_ipv4hdr.ver      = 4;
    g_pia_ipv4hdr.hlen     = 5;
    g_pia_ipv4hdr.tos      = 0;
    g_pia_ipv4hdr.total    = 0;
    g_pia_ipv4hdr.id       = pia_ip_getid();
    g_pia_ipv4hdr.frag_off = 0;
    g_pia_ipv4hdr.ttl      = 64;
    
    memcpy(&g_pia_ipv4hdr_tcp, &g_pia_ipv4hdr, sizeof(pia_ipv4hdr_t));
    g_pia_ipv4hdr_tcp.id   = pia_ip_getid();
    g_pia_ipv4hdr_tcp.prot = PIA_IP_TCP;
    
    memcpy(&g_pia_ipv4hdr_tcp, &g_pia_ipv4hdr, sizeof(pia_ipv4hdr_t));
    g_pia_ipv4hdr_tcp.id   = pia_ip_getid();
    g_pia_ipv4hdr_tcp.prot = PIA_IP_TCP;
    
    memcpy(&g_pia_ipv4hdr_tcp, &g_pia_ipv4hdr, sizeof(pia_ipv4hdr_t));
    g_pia_ipv4hdr_tcp.id   = pia_ip_getid();
    g_pia_ipv4hdr_tcp.prot = PIA_IP_TCP;
    
    return PIA_OK;
}
/* end of file */
