/**
 * @file ip/init.c
 * @brief initialize fuction for ip header
 * @author simpart
 */
/*** include ***/
#include <sys/time.h>
#include <string.h>
#include "pia/com.h"
#include "pia/ip.h"
#include "pia/icmp.h"

/*** global ***/
pia_ipv4hdr_t g_pia_ipv4hdr = {0};
pia_ipv4hdr_t g_pia_ipv4hdr_tcp = {0};
pia_ipv4hdr_t g_pia_ipv4hdr_udp = {0};
pia_ipv4hdr_t g_pia_ipv4hdr_icmp = {0};
int g_pia_ip_setaddr = PIA_FALSE;
/*** function ***/
/**
 * initialize ip function
 *
 * @return PIA_OK : proccessing success
 */
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
    g_pia_ipv4hdr.id       = pia_random(0xFFFF);
    g_pia_ipv4hdr.frag_off = 0;
    g_pia_ipv4hdr.ttl      = 64;
    
    memcpy(&g_pia_ipv4hdr_tcp, &g_pia_ipv4hdr, sizeof(pia_ipv4hdr_t));
    g_pia_ipv4hdr_tcp.id   = pia_random(0xFFFF);
    g_pia_ipv4hdr_tcp.prot = PIA_IP_TCP;
    
    memcpy(&g_pia_ipv4hdr_udp, &g_pia_ipv4hdr, sizeof(pia_ipv4hdr_t));
    g_pia_ipv4hdr_udp.id   = pia_random(0xFFFF);
    g_pia_ipv4hdr_udp.prot = PIA_IP_UDP;
    
    memcpy(&g_pia_ipv4hdr_icmp, &g_pia_ipv4hdr, sizeof(pia_ipv4hdr_t));
    g_pia_ipv4hdr_icmp.id    = pia_random(0xFFFF);
    g_pia_ipv4hdr_icmp.prot  = PIA_IP_ICMP;
    
    return PIA_OK;
}
/* end of file */
