/**
 * @file  recv/rcv_ether.c
 * @brief receive ethernet frame
 */
#include <recv/ethernet.h>

ppa_sock_t Geth_sock_lst[DPPA_SOCKMAX_CNT];


u_int32_t rcv_init(char * ifname) {
    int sock = 0;
    
    if (NULL == ifname) {
        return DPPA_NG;
    }
    
    if ((sock = socket(PF_PACKET, SOCK_RAW, htons(0x03))) < 0) {
        return DPPA_NG;
    }
    
    return DPPA_OK;
}


/**
 * receive frame
 *
 * @param ifname : receive interface name
 */
u_char * rcv_frame(u_int32_t s_idx) {
//    struct ifreq       ifr;
//    struct packet_mreq mreq;
//    struct sockaddr_in rsin;
//    int    rsin_size = 0;
    u_char rcv_buf[DPCA_ETHRCV_MAXLEN];
    
    if ((0 > s_idx) || ((DPPA_SOCKMAX_CNT-1) < s_idx) ) {
        return NULL;
    }
    
//    memset(&ifr,  0x00, sizeof(struct ifreq));
//    memset(&mreq, 0x00, sizeof(struct packet_mreq));
//    memset(&rsin, 0x00, sizeof(struct sockaddr_in));
    memset(&rcv_buf[0], 0x00, sizeof(rcv_buf));
    
/*    
    strncpy(&(ifr.ifr_name[0]), DPCH_TGT_IFNAME, sizeof(ifr.ifr_name)-1);

    if(ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
        return NULL;
    }

    mreq.mr_type    = PACKET_MR_PROMISC;
    mreq.mr_ifindex = ifr.ifr_ifindex;

    if ((setsockopt(
             sock                  ,
             SOL_PACKET            ,
             PACKET_ADD_MEMBERSHIP ,
             (void *)&mreq         ,
             sizeof(mreq)
         )) < 0) {
        return NULL;
    }

    if (recvfrom(
            sock,
            (void *)&buf,
            sizeof(buf),
            0,
            (struct sockaddr *)&rsin,
            (socklen_t *) &rsin_size
        ) < 0) {
        return NULL;
    }
*/    
    return NULL;

}

u_char * rcv_jumbo_frame(char * ifname) {
    return NULL;
}
/* end of file */
