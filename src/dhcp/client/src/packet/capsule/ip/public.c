/**
 * @file public.c
 */
#include <packet/capsule/ip.h>

u_char * ip_capsuling(
             iphdr_t *ip_hdr ,
             u_char * pld,
             u_int32_t pld_size
         ) {
    u_char   * ip_pkt  = NULL;
    u_char   * shift   = NULL;
    iphdr_t  * set_sum = NULL;
    
    if ((NULL == ip_hdr) || (NULL == pld)) {
        return NULL;
    }
    ip_hdr->version  = 0x04;
    ip_hdr->ihl      = sizeof(iphdr_t) / 4;

/*** for debug ***/
//printf("ip header size %lu\n",  sizeof(iphdr_t));    
//printf("payload size %u\n", pld_size);
//printf("set tot_len -> %lu\n", sizeof(iphdr_t) + pld_size);
    
    ip_hdr->tot_len  = htons(sizeof(iphdr_t) + pld_size);
    ip_hdr->id       = htons(1000);
    ip_hdr->frag_off = htons(IP_DF);
    ip_hdr->ttl      = 10;
    
    /* create ip packet */
    ip_pkt = (u_char *) malloc(sizeof(iphdr_t) + pld_size);
    if (NULL == ip_pkt) {
        return NULL;
    }
    /* init ip packet */
    memset(ip_pkt, 0x00, sizeof(iphdr_t) + pld_size);
    /* copy ip packet contents */
    memcpy(ip_pkt, ip_hdr, sizeof(iphdr_t));
    shift = ip_pkt;
    shift += sizeof(iphdr_t);
    memcpy(shift, pld, pld_size);
    /* get check sum */
    set_sum        = (iphdr_t *) ip_pkt;
    set_sum->check = ip_chksum((iphdr_t *) ip_pkt);
    
    return ip_pkt;
}

int ip_chksum( iphdr_t *ip_hdr ) {
  int           hdr_len = 0;
  unsigned long sum     = 0;
  u_int16_t *   buf     = (u_int16_t *)ip_hdr;

  ip_hdr->check = 0;
  hdr_len       = ip_hdr->ihl * 4;

  // 加算開始
  while( hdr_len > 0 ){
    sum += *buf++;

    if( sum & 0x80000000 ){
      // sumが桁あふれしてしまったらエラー
      exit(-1);
    }
    // 16bit(2byte)ずつ加算してるから-2だよね。
    hdr_len -= 2;
  }

  // 桁溢れ分も加算する。
  sum = (sum & 0xffff) + (sum >> 16);
  // ↑の加算で桁溢れする場合もあり得るから念の為もう一回
  sum = (sum & 0xffff) + (sum >> 16);
  // 1の補数
  return ~sum;
}

/* end of file */
