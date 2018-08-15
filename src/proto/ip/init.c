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
piaip_v4hdr_t g_piaip_v4hdr      = {0};
piaip_v4hdr_t g_piaip_v4hdr_tcp  = {0};
piaip_v4hdr_t g_piaip_v4hdr_udp  = {0};
piaip_v4hdr_t g_piaip_v4hdr_icmp = {0};
int g_piaip_setaddr = PIA_FALSE;

/*** function ***/
/**
 * initialize ip function
 *
 * @return PIA_OK : proccessing success
 */
int piaip_init (void) {
    
    /* init global */
    memset(&g_piaip_v4hdr     , 0x00, sizeof(piaip_v4hdr_t));
    memset(&g_piaip_v4hdr_tcp , 0x00, sizeof(piaip_v4hdr_t));
    memset(&g_piaip_v4hdr_udp , 0x00, sizeof(piaip_v4hdr_t));
    memset(&g_piaip_v4hdr_icmp, 0x00, sizeof(piaip_v4hdr_t));
    
    g_piaip_v4hdr.ver  = 4;
    g_piaip_v4hdr.hlen = 5;
    piaip_updid(&g_piaip_v4hdr);
    g_piaip_v4hdr.ttl  = 64;
    
    memcpy(&g_piaip_v4hdr_tcp, &g_piaip_v4hdr, sizeof(piaip_v4hdr_t));
    piaip_updid(&g_piaip_v4hdr_tcp);
    g_piaip_v4hdr_tcp.prot = PIAIP_TYPE_TCP;
    
    memcpy(&g_piaip_v4hdr_udp, &g_piaip_v4hdr, sizeof(piaip_v4hdr_t));
    piaip_updid(&g_piaip_v4hdr_udp);
    g_piaip_v4hdr_udp.prot = PIAIP_TYPE_UDP;
    
    memcpy(&g_piaip_v4hdr_icmp, &g_piaip_v4hdr, sizeof(piaip_v4hdr_t));
    piaip_updid(&g_piaip_v4hdr_icmp);
    g_piaip_v4hdr_icmp.prot  = PIAIP_TYPE_ICMP;
    
    return PIA_OK;
}
/* end of file */
