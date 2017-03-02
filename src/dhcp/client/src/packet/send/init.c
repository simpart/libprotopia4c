/**
 * @file   init.c
 * @brief  packet sender initialize function
 */
/*** include ***/
#include <packet/send.h>

/*** extern ***/
extern int Gpsd_sock;
extern struct sockaddr_ll sll;

/*** function ***/
int psd_init (void) {
    int          ret  = 0;
    int          sock = 0;
    struct ifreq ifr;
    
    DDBG_PRINT("initialize packet sender");
    
    memset(&ifr, 0x00, sizeof(struct ifreq));
    memset(&sll, 0x00, sizeof(struct sockaddr_ll));
    
    Gpsd_sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (0 > sock) {
        return DCOM_NG;
    }
    
    strncpy(ifr.ifr_name, DPSD_IFNAME, strnlen(DPSD_IFNAME,16));
    ret = ioctl(Gpsd_sock, SIOCGIFINDEX, &ifr);
    if (DCOM_NG == ret) {
        printf("invalid ifname\n");
        return DCOM_NG;
    }
    sll.sll_ifindex = ifr.ifr_ifindex;
    
    return DCOM_OK;
}
/* end of file */
