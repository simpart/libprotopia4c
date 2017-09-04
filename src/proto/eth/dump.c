/**
 * @file ether/dump.c
 * @author simpart
 */
#include <stdio.h>
#include <string.h>
#include "pia/com.h"
#include "pia/eth.h"

/*** functoin ***/
void pia_dmp_ether(pia_ethhdr_t * eth_hdr) {
    uint16_t type = 0;
    
    if (NULL == eth_hdr) {
        printf("ether header is null\n");
        return;
    }
    
    printf("Ether Header\n");
    printf("----------------------------------\n");
    printf("dest mac   : %02x-%02x-%02x-%02x-%02x-%02x\n",
              eth_hdr->dmac[0],
              eth_hdr->dmac[1],
              eth_hdr->dmac[2],
              eth_hdr->dmac[3],
              eth_hdr->dmac[4],
              eth_hdr->dmac[5]
          );
    printf("src mac    : %02x-%02x-%02x-%02x-%02x-%02x\n",
              eth_hdr->smac[0],
              eth_hdr->smac[1],
              eth_hdr->smac[2],
              eth_hdr->smac[3],
              eth_hdr->smac[4],
              eth_hdr->smac[5]
          );
    
    memcpy(&type, &eth_hdr->type, sizeof(uint16_t));
    type = pia_ntohs(type);
    printf("ether type : %u(0x%x)\n", type, type);
    printf("\n");
}

/* end of file */
