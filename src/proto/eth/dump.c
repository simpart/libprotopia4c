/**
 * @file ether/dump.c
 * @author simpart
 */
#include <stdio.h>
#include <string.h>
#include "pia/com.h"
#include "pia/eth.h"

/*** functoin ***/
void pia_eth_dump(uint8_t *rcv) {
    uint16_t     type = 0;
    pia_ethhdr_t *eth_hdr;
    
    if (NULL == rcv) {
        //printf("parameter is null\n");
        return;
    }
    eth_hdr = (pia_ethhdr_t *) rcv;
    
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
