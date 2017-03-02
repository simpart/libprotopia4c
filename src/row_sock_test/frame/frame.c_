#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/if.h>

/*** define ***/
#define DCOM_OK 0
#define DCOM_NG -1
#define DNWI_IFNAME "eth0"

/*** prototype ***/
u_int16_t checksum(unsigned short * , int );
char * get_icmp_frame( void );
int    send_icmp( void );

/*** function ***/
int main( void ) {
    return send_icmp();
}

int send_icmp( void ) {
    int    sock = 0;
    char * icmp = NULL;            
    struct sockaddr_ll sll;
    
    memset( &sll, 0x00, sizeof( struct sockaddr_ll ) );
    sock = socket(
               AF_INET,
               SOCK_RAW,
               IPPROTO_ICMP
           );
    if( DCOM_NG == sock ) {
        return DCOM_NG;
    }
    
    sll.sll_family  = AF_PACKET;
    sll.sll_halen   = ETH_ALEN;
    sll.sll_ifindex = if_nametoindex( DNWI_IFNAME );
    if( 0 == sll.sll_ifindex ) {
        close( sock );
        return DCOM_NG;
    }
    
    icmp = get_icmp_frame();
    if ( NULL == icmp ) {
        return DCOM_NG;
    }
    
//    sendto(
//        sock,
//        test_frame,
//        thd_prm->fsize,
//        0,
//        (struct sockaddr *)&sll,
//        sizeof(sll)
//    );
    
    close( sock );
    
    return 0;
}

char * get_icmp_frame( void ) {
    char *                frame      = NULL;
    struct ether_header * eth_hdr    = NULL;

    frame = (char *) malloc( fsize );
    if( NULL == frame ) {
        return NULL;
    }
    memset( frame, 0x00, fsize );

    eth_hdr = (struct ether_header *) frame;
    /* destination mac */
    eth_hdr->ether_dhost[0] = 1;
    eth_hdr->ether_dhost[1] = 1;
    eth_hdr->ether_dhost[2] = 1;
    eth_hdr->ether_dhost[3] = 1;
    eth_hdr->ether_dhost[4] = 1;
    eth_hdr->ether_dhost[5] = 1;
    /* source mac */
    eth_hdr->ether_shost[0] = 2;
    eth_hdr->ether_shost[1] = 2;
    eth_hdr->ether_shost[2] = 2;
    eth_hdr->ether_shost[3] = 2;
    eth_hdr->ether_shost[4] = 2;
    eth_hdr->ether_shost[5] = 2;

    eth_hdr->ether_type = htons( sizeof(struct ether_header) );
    
    return frame;
}

u_int16_t checksum(unsigned short *buf, int size) {
    unsigned long sum = 0;
    /* チェックデータを16bitずつ加算する */
    while( size > 1 ) {
        sum += *buf;
        buf++;
        size -= 2;   /* 16bitずつ加算してるから2byte分減らす */
    }
    if( size == 1 )
        sum += *(unsigned char *)buf;
    
    /* 加算結果で16bit以上桁あふれした分を再度加算すると
       1 の補数和を得る事が出来る */
    sum = (sum & 0xffff) + (sum >> 16);
    /* 上の処理で再度桁あふれする場合を考慮してもう一回 */
    sum = (sum & 0xffff) + (sum >> 16);
    
    return ~sum; /* 1の補数和の1の補数がチェックサムの値になる */
}

