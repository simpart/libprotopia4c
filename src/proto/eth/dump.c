/**
 * @file ether/dump.c
 * @author simpart
 */
#include <stdio.h>
#include <string.h>
#include "pia/com.h"
#include "pia/eth.h"

/*** functoin ***/
int pia_eth_dump (pia_ethhdr_t * frm) {
    
    if (NULL == frm) {
        return PIA_NG;
    }
    printf("ether ");
    printf("%02x-%02x-%02x-%02x-%02x-%02x",
              frm->smac[0],
              frm->smac[1],
              frm->smac[2],
              frm->smac[3],
              frm->smac[4],
              frm->smac[5]
    );
    printf(" >> ");
    printf("%02x-%02x-%02x-%02x-%02x-%02x",
              frm->dmac[0],
              frm->dmac[1],
              frm->dmac[2],
              frm->dmac[3],
              frm->dmac[4],
              frm->dmac[5]
    );
    
    printf("\n");
    return PIA_OK;
}

int pia_eth_dump_detail (pia_ethhdr_t *frm) {
    uint16_t     type = 0;
    
    if (NULL == frm) {
        return PIA_NG;
    }
    
    printf("Ether Header\n");
    printf("----------------------------------\n");
    printf("dest mac   : %02x-%02x-%02x-%02x-%02x-%02x\n",
              frm->dmac[0],
              frm->dmac[1],
              frm->dmac[2],
              frm->dmac[3],
              frm->dmac[4],
              frm->dmac[5]
          );
    printf("src mac    : %02x-%02x-%02x-%02x-%02x-%02x\n",
              frm->smac[0],
              frm->smac[1],
              frm->smac[2],
              frm->smac[3],
              frm->smac[4],
              frm->smac[5]
          );
    
    memcpy(&type, &(frm->type), sizeof(uint16_t));
    type = pia_ntohs(type);
    printf("ether type : %u(0x%x)\n", type, type);
    printf("\n");
    
    return PIA_OK;
}
/* end of file */
