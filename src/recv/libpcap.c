/**
 * @file libpcap.c
 * @brief receive packet by libpcap
 * @author simpart
 */
#include <pcap.h>
#include <string.h>
#include "pia/common.h"
#include "pia/receive.h"

piast_rcvconf_t  g_recv_conf;
pcap_t   *g_pcapd = NULL;

/**
 * initialize receive config
 *
 * @param[in] conf (piast_rcvconf_t) receive config 
 * @return (uchar) PIA_OK/PIA_NG
 */
int pia_init_recv (piast_rcvconf_t conf) {
    char ebuf[PCAP_ERRBUF_SIZE];
    
    memset(&g_recv_conf, 0x00, sizeof(piast_rcvconf_t));
    memset(&ebuf[0], 0x00, sizeof(ebuf));
    
    /* check interface name */
    if ('\0' == conf.ifname[0]) {
        return PIA_NG;
    }
    
    /* set default max size */
    if (0 == conf.max_size) {
        conf.max_size = 1522;
    }
    
    /* set default timeout (1000ms) */
    if (0 == conf.timeout) {
        conf.timeout = 1000;
    }
    
    if( (g_pcapd = pcap_open_live(
                       &conf.ifname[0] ,
                        conf.max_size  ,
                        conf.promis    ,
                        conf.timeout   ,
                        ebuf )) == NULL ) {
        return PIA_NG;
    }
    
    memcpy(&g_recv_conf, &conf, sizeof(piast_rcvconf_t));
    return PIA_OK;
}

/**
 * start packet receive
 */
int pia_start_recv (void) {

    if( pcap_loop(
            g_pcapd ,
            -1      ,
            (pcap_handler) pia_cbwrap,
            NULL) < 0 ) {
        return PIA_NG;
    }
    
    pcap_close(g_pcapd);
    return PIA_OK;
}

void pia_cbwrap (u_char *user, const struct pcap_pkthdr *h , const u_char *p ) {
    user = user;
    g_recv_conf.cb_func((pkt) p, (void *) h, g_recv_conf.cb_prm);
}
/* end of file */
