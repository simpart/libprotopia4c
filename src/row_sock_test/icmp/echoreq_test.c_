#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>

#define DQIT_ECHO_TGT "172.17.42.1"
#define DQIT_SEND_CNT 5

u_int16_t checksum(unsigned short * , int );

int main( void ) {
  int ret           = 0;
  unsigned long sum = 0;
  int size          = 0;
  struct sockaddr_in addr;
  struct in_addr     insaddr;
  struct icmphdr icmp;
  struct icmphdr *recv_icmp = NULL;
  struct iphdr *recv_iphdr  = NULL;
  int sock          = 0;
  char buf[1500];
  int loop          = 0;
  
  memset(&addr, 0x00, sizeof(struct sockaddr_in));
  memset(&icmp, 0x00, sizeof(struct icmphdr));
  memset(&buf,  0x00, sizeof(&buf[0]));
  
  addr.sin_family      = AF_INET;
  addr.sin_addr.s_addr = inet_addr(DQIT_ECHO_TGT);
  
  sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if( -1 == sock ) {
    return -1;
  }
  
  for(loop=0; loop < DQIT_SEND_CNT ; loop++) {
    memset(&icmp, 0x00, sizeof(struct icmphdr)); /* icmp内容初期化 */
    
    icmp.type     = ICMP_ECHO;    /* エコー要求 */
    icmp.checksum = checksum((unsigned short *)&icmp,
                             sizeof(struct icmphdr));
    icmp.un.echo.sequence = loop+10;
    
    /* ICMPパケット送信 */
    ret = sendto( sock,
                  (char *)&icmp,
                  sizeof(icmp),
                  0,
                  (struct sockaddr *)&addr,
                  sizeof(addr));
    if( 1 > ret ) {
      printf("error\n");
      return -1;
    }
  
    ret = recv(sock, buf, sizeof(buf), 0);
    if( 1 > ret ) {
      printf("error");
      return -1;
    }
  
    recv_iphdr = (struct iphdr *)buf;
    /* IPヘッダからヘッダ長を求め、icmpヘッダの開始位置を調べる */
    recv_icmp  = (struct icmphdr *)(buf + (recv_iphdr->ihl << 2));
    //  insaddr.s_addr = recv_iphdr->saddr;
    //  /* 送信先と受信したパケットの送信源が一致するかと受信したパケットがICMP ECHO REPLYか確認  */
    if( recv_icmp->type == ICMP_ECHOREPLY ) {
      printf("icmp echo reply id=%d seq=%d\n", 
             recv_icmp->un.echo.id,
             recv_icmp->un.echo.sequence );
    }
  }
  close(sock);
  
  return 0;
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

