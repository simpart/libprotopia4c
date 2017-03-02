/**
 * @file udp.c
 */

/*** include ***/
#include <packet/dump/udp.h>

/*** function ***/
void dmp_udphdr(udphdr_t * udp_hdr) {
    if (NULL == udp_hdr) {
        return;
    }
    
    printf("UDP Header\n");
    printf("-----------------------\n");
    printf("source port      : %u(0x%x)\n", ntohs(udp_hdr->source), ntohs(udp_hdr->source));
    printf("destination port : %u(0x%x)\n", ntohs(udp_hdr->dest), ntohs(udp_hdr->dest));
    printf("packet size      : %u\n", ntohs(udp_hdr->len));
    printf("check sum        : %u\n", ntohs(udp_hdr->check));
    printf("\n");
}

/* end of file */
