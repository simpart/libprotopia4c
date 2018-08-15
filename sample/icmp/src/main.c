/**
 * @file main.c
 * @brief packet receive sample
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "tetraring.h"
#include "protopia.h"

/*** define ***/
#define IFACE_NAME "ens8"
#define SRC_MAC 0x52,0x54,0x00,0x94,0x29,0x29
#define DST_MAC 0x52,0x54,0x00,0xe8,0xc9,0x6c
#define SRC_IP 192,168,10,225
#define DST_IP 192,168,10,52

/*** global ***/
uint8_t g_rcvbuf[sizeof(pia_ethhdr_t)+sizeof(pia_ipv4hdr_t)] = {0};

/*** prototype ***/
int init_network (void);

/*** function ***/
int main (void) {
    int       ret      = 0;
    int       sock     = 0;
    uint8_t   buf[128] = {0};
    int       cnt      = 0;
//    uint8_t * seek     = NULL;
    
    sock = init_network();
    
    for (cnt=0;cnt < 1;cnt++) {
        
        memset(&buf[0], 0x00, sizeof(buf));
        
        /* get frame */
        ret = piaicm_getfrm(&buf[0], sizeof(buf));
        if (PIA_NG == ret) {
            printf("get frame is failed\n");
            return -1;
        }
        
        /* send frame */
        if (-1 == send(sock, &buf[0], sizeof(buf), 0) ) {
            printf("sending failed\n");
            return -1;
        }
        sleep(1);
    }
    
    close(sock);
    return 0;
}

int init_network (void) {
    int     sock   = 0;
    uint8_t dmac[] = {DST_MAC};
    uint8_t smac[] = {SRC_MAC};
    uint8_t dip[]  = {DST_IP};
    uint8_t sip[]  = {SRC_IP};
    
    /* init interface */
    sock = ttr_nw_init(IFACE_NAME, g_rcvbuf, sizeof(g_rcvbuf));
    if (TTR_NG == sock) {
        printf("initializing failed\n");
        return -1;
    }
    
    pia_init();
    
    /* init ether member */
    piaeth_setdefmac(&dmac[0], &smac[0]);
    piaeth_setdeftype(PIAETH_TYPE_IP);
    
    /* init ip member */
    piaip_setdefipv4(&sip[0], &dip[0]);
    
    /* init icmp member */
    piaicm_setdef_type(PIAICM_TYPE_ECHOREQ);
    
    return sock;
}
/* end of file */
