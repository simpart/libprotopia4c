/**
 * @file ether.c
 */
/*** include ***/
#include <packet/dump/ether.h>

/*** functoin ***/
void dmp_ethhdr(ethhdr_t * eth_hdr) {
    
    if (NULL == eth_hdr) {
        printf("ether header is null\n");
        return;
    }

    printf("Ether Header\n");
    printf("----------------------------------\n");
    printf("dest mac   : %02x-%02x-%02x-%02x-%02x-%02x\n",
              eth_hdr->h_dest[0],
              eth_hdr->h_dest[1],
              eth_hdr->h_dest[2],
              eth_hdr->h_dest[3],
              eth_hdr->h_dest[4],
              eth_hdr->h_dest[5]
          );
    printf("src mac    : %02x-%02x-%02x-%02x-%02x-%02x\n",
              eth_hdr->h_source[0],
              eth_hdr->h_source[1],
              eth_hdr->h_source[2],
              eth_hdr->h_source[3],
              eth_hdr->h_source[4],
              eth_hdr->h_source[5]
          );
    printf("ether type : %u(0x%x)\n", ntohs(eth_hdr->h_proto), ntohs(eth_hdr->h_proto));
    printf("\n");
}

/* end of file */
