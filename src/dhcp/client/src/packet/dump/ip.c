/**
 * @file ip.c
 */
/*** include ***/
#include <packet/dump/ip.h>

/*** functoin ***/
void dmp_iphdr(iphdr_t * ip_hdr) {
    int frag = 0;
    
    if (NULL == ip_hdr) {
        return;
    }

    printf("IP Header\n");
    printf("-------------------------\n");
    printf("version        : %u\n"      , ip_hdr->version);
    printf("header length  : %u byte\n" , ip_hdr->ihl*4);
    printf("total length   : %u byte\n" , ntohs( ip_hdr->tot_len ) );
    printf("identification : %u\n"      , ntohs( ip_hdr->id ) );
    
    frag = ntohs(ip_hdr->frag_off);
    printf("flag           : ");
    if ( IP_DF == frag ) {
        printf("don't fragment\n");
    } else if ( IP_MF == frag ) {
        printf("more fragment\n");
    } else {
        printf("finish fragment\n");
    }
    
    printf("time to live   : %u\n" , ip_hdr->ttl );
    
    printf("protocol       : ");
    if( 0x01 == ip_hdr->protocol ) {
        printf("icmp\n");
    } else if ( 0x06 == ip_hdr->protocol ) {
        printf("tcp\n");
    } else if ( 0x17 == ip_hdr->protocol ) {
        printf("udp\n");
    } else {
        printf("0x%x\n" , ip_hdr->protocol );
    }
    
    printf("check sum      : %u\n", ip_hdr->check);
    printf("\n");
}

/* end of file */
