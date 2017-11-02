/**
 * @file ether/dump.c
 * @brief dump fuction for ether header
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include "pia/com.h"
#include "pia/eth.h"
/*** functoin ***/
/**
 * dump ether frame by a line
 * 
 * @param[in] eth_hdr : head pointer to frame
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_eth_dump (pia_ethhdr_t * eth_hdr) {
    
    if (NULL == eth_hdr) {
        return PIA_NG;
    }
    printf("ether ");
    printf("%02x-%02x-%02x-%02x-%02x-%02x",
              eth_hdr->smac[0],
              eth_hdr->smac[1],
              eth_hdr->smac[2],
              eth_hdr->smac[3],
              eth_hdr->smac[4],
              eth_hdr->smac[5]
    );
    printf(" >> ");
    printf("%02x-%02x-%02x-%02x-%02x-%02x",
              eth_hdr->dmac[0],
              eth_hdr->dmac[1],
              eth_hdr->dmac[2],
              eth_hdr->dmac[3],
              eth_hdr->dmac[4],
              eth_hdr->dmac[5]
    );
    
    printf("\n");
    return PIA_OK;
}

/**
 * detail dump ether frame
 * 
 * @param[in] eth_hdr : head pointer to frame
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_eth_dump_detail (pia_ethhdr_t *eth_hdr) {
    uint16_t     type = 0;
    
    if (NULL == eth_hdr) {
        return PIA_NG;
    }
    
    printf("Ether Header\n");
    printf("==============================\n");
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
    
    memcpy(&type, &(eth_hdr->type), sizeof(uint16_t));
    type = pia_ntohs(type);
    printf("ether type : %u(0x%x)\n", type, type);
    printf("\n");
    
    return PIA_OK;
}
/* end of file */
