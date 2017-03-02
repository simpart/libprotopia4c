/**
 * @file   discover.c
 * @brief  discover function
 */
/*** include ***/
#include <client.h>

/*** function ***/
int clt_discover (void) {
    int ret               = 0;
    dhcpmsg_t * discv     = NULL;
    u_char *    udp_discv = NULL;
    u_char *    ip_discv  = NULL;
    u_char *    eth_discv = NULL;
    iphdr_t *   get_size  = NULL;
    
    DDBG_PRINT("send discover");
    
    /* get dhcp discover message */
    discv = cdh_get_discover();
    if (NULL == discv) {
        DDBG_PRINT("failed discover");
        return DCOM_NG;
    }
    
    /* get udp packet */
    udp_discv = clt_get_udpdiscv((u_char *) discv);
    if (NULL == udp_discv) {
        free(discv);
        DDBG_PRINT("failed discover");
        return DCOM_NG;
    }
    free(discv);
    
    /* get ip packet */
    ip_discv = clt_get_ipdiscv((u_char *) udp_discv);
    if (NULL == ip_discv) {
        free(udp_discv);
        DDBG_PRINT("failed discover");
        return DCOM_NG;
    }
    free(udp_discv);
    
    /* get ether frame */
    eth_discv = clt_get_etherdiscv((u_char *) ip_discv );
    if (NULL == eth_discv) {
        free(ip_discv);
        DDBG_PRINT("failed discover");
        return DCOM_NG;
    }
    
/* for debug */
dbg_printdhcp((ethhdr_t *) eth_discv);
    
    get_size = (iphdr_t *) ip_discv;
    free(ip_discv);
    
    ret = psd_sendpkt(eth_discv, sizeof(ethhdr_t) + ntohs( get_size->tot_len ));
    if (DCOM_OK != ret) {
        free(eth_discv);
        DDBG_PRINT("failed discover");
        return DCOM_NG;
    }
    
    free(eth_discv);
    
    return DCOM_OK;
}

u_char * clt_get_udpdiscv(u_char * discv) {
    int            ret     = 0;
    u_char *       ret_udp = NULL;
    udphdr_t       udp_hdr;
    dummy_udphdr_t dmy_udp;
    
    if (NULL == discv) {
        return NULL;
    }
    
    memset(&udp_hdr, 0x00, sizeof(udphdr_t));
    memset(&dmy_udp, 0x00, sizeof(dummy_udphdr_t));
    
    /* set udp header */
    memset(&udp_hdr, 0x00, sizeof(udphdr_t));
    udp_hdr.source = htons(0x44);
    udp_hdr.dest   = htons(0x43);
    udp_hdr.len    = htons(sizeof(udphdr_t) + sizeof(dhcpmsg_t));
    
    /* set udp dummy header */
    ret = inet_pton(AF_INET, "255.255.255.255", &(dmy_udp.daddr));
    if (1 != ret) {
        return NULL;
    }
    dmy_udp.prot = 17;
    dmy_udp.len  = htons(sizeof(udphdr_t) + sizeof(dhcpmsg_t));
    
    // cupsuling
    ret_udp = udp_capsuling(&dmy_udp, &udp_hdr, discv);
    if (NULL == discv) {
        return NULL;
    }
    
    return ret_udp;
}


u_char * clt_get_ipdiscv(u_char * udp_discv) {
    int              ret     = 0;
    iphdr_t          ip_hdr;
    u_char *         ret_ip  = NULL;
    udphdr_t *       get_len = NULL;
    
    /* init ip header */
    memset(&ip_hdr, 0x00, sizeof(iphdr_t));
    
    ip_hdr.protocol = 17; /* next protocol is UDP */
    
    /* set dest ip addr */
    ret = inet_pton(AF_INET, "255.255.255.255", (struct in_addr *) &ip_hdr.daddr);
    if (1 != ret) {
        return NULL;
    }
    
    /* get ip packet */
    get_len = (udphdr_t *) udp_discv;
    ret_ip = ip_capsuling(
                 &ip_hdr   ,
                 udp_discv ,
                 ntohs(get_len->len)
             );
    
    return ret_ip;
} 

u_char * clt_get_etherdiscv(u_char * ip_discv ) {
    ethhdr_t   eth_hdr;
    u_char *   ret_frm  = NULL;
    iphdr_t *  get_size = NULL;
    
    if (NULL == ip_discv) {
        DDBG_PRINT("failed ether discover");
        return NULL;
    }
    
    /* init ether header */
    memset(&eth_hdr, 0x00, sizeof(ethhdr_t));
    
    /* set dest mac address */
    eth_hdr.h_dest[0] = 0xFF;
    eth_hdr.h_dest[1] = 0xFF;
    eth_hdr.h_dest[2] = 0xFF;
    eth_hdr.h_dest[3] = 0xFF;
    eth_hdr.h_dest[4] = 0xFF;
    eth_hdr.h_dest[5] = 0xFF;
    
    /* set source mac address */
    eth_hdr.h_source[0] = DCEH_MYMAC_1;
    eth_hdr.h_source[1] = DCEH_MYMAC_2;
    eth_hdr.h_source[2] = DCEH_MYMAC_3;
    eth_hdr.h_source[3] = DCEH_MYMAC_4;
    eth_hdr.h_source[4] = DCEH_MYMAC_5;
    eth_hdr.h_source[5] = DCEH_MYMAC_6;
    
    /* set ether type */
    eth_hdr.h_proto     = htons(0x0800);
    
    /* get ether frame */
    get_size = (iphdr_t *) ip_discv;
    ret_frm  = ether_capsuling(&eth_hdr, ip_discv, ntohs( get_size->tot_len ) );
    if (NULL == ret_frm) {
        DDBG_PRINT("failed ether discover");
    }
    
    return ret_frm;
}
/* end of file */
