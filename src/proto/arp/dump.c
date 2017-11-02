/**
 * @file arp/dump.c
 * @brief dump function for arp
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include "pia/com.h"
#include "pia/arp.h"

/*** function ***/
/**
 * dump arp header by a line
 * 
 * @param[in] arp_hdr : head pointer to arp header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 * @note not supported
 */
int pia_arp_dump (pia_arphdr_t * arp_hdr) {
   arp_hdr = arp_hdr;
   return 0;
}
/**
 * dump arp header detail
 * 
 * @param[in] arp_hdr : head pointer to arp header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_arp_dump_detail (pia_arphdr_t * arp_hdr) {
    /* check parameter */
    if (NULL == arp_hdr) {
        return PIA_NG;
    }
    printf("ARP Header\n");
    printf("===========================\n");
    pia_arp_dump_htype(arp_hdr);
    pia_arp_dump_ptype(arp_hdr);
    
    printf("hardware address length : %02dbyte\n", arp_hdr->hlen);
    printf("protocol address length : %02dbyte\n", arp_hdr->plen);
    printf("operation code : ");
    if (PIA_TRUE == pia_arp_isrequest(arp_hdr)) {
        printf("Request\n");
    } else if (PIA_TRUE == pia_arp_isreply(arp_hdr)) {
        printf("Reply\n");
    } else {
        printf("Unknown\n");
    }
    
    /* source hardware address */
    printf(
        "src hw addr : %02x-%02x-%02x-%02x-%02x-%02x\n",
        arp_hdr->shaddr[0],
        arp_hdr->shaddr[1],
        arp_hdr->shaddr[2],
        arp_hdr->shaddr[3],
        arp_hdr->shaddr[4],
        arp_hdr->shaddr[5]
    );
    
    /* source protocol address */
    printf(
        "src prot addr : %d.%d.%d.%d\n",
        arp_hdr->spaddr[0],
        arp_hdr->spaddr[1],
        arp_hdr->spaddr[2],
        arp_hdr->spaddr[3]
    );
    
    /* destination hardware address */
    printf(
        "dest hw addr : %02x-%02x-%02x-%02x-%02x-%02x\n",
        arp_hdr->dhaddr[0],
        arp_hdr->dhaddr[1],
        arp_hdr->dhaddr[2],
        arp_hdr->dhaddr[3],
        arp_hdr->dhaddr[4],
        arp_hdr->dhaddr[5]
    );
    
    /* destination protocol address */
    printf(
        "dest prot addr : %d.%d.%d.%d\n",
        arp_hdr->dpaddr[0],
        arp_hdr->dpaddr[1],
        arp_hdr->dpaddr[2],
        arp_hdr->dpaddr[3]
    );
    
    return PIA_OK;
}
/**
 * dump hardware type
 * 
 * @param[in] arp_hdr : head pointer to arp header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_arp_dump_htype(pia_arphdr_t *arp_hdr) {
    char * type_lst[] = {
                  "Reserved"                  ,
                  "Ethernet"                  ,
                  "Experimental Ethernet"     ,
                  "Amateur Radio AX.25"       ,
                  "Proteon ProNET Token Ring" ,
                  "Chaos"                     ,
                  "IEEE 802 Networks"         ,
                  "ARCNET"                    ,
                  "Hyperchannel"              ,
                  "Lanstar"                   ,
                  "Autonet Short Address"     ,
                  "LocalTalk"                 ,
                  "LocalNet"                  ,
                  "Ultra link"                ,
                  "SMDS"                      ,
                  "Frame Relay"               ,
                  "Asynchronous Transmission Mode" ,
                  "HDLC"                      ,
                  "Fibre Channel"             ,
                  "Asynchronous Transmission Mode" ,
                  "Serial Line"               ,
                  "Asynchronous Transmission Mode" ,
                  "MIL-STD-188-220"           ,
                  "Metricom"                  ,
                  "IEEE 1394.1995"            ,
                  "MAPOS"                     ,
                  "Twinaxial"                 ,
                  "EUI-64"                    ,
                  "HIPARP"                    ,
                  "IP and ARP over ISO 7816-3",
                  "ARPSec"                    ,
                  "IPsec tunnel"              ,
                  "InfiniBand"                ,
                  "TIA-102 Project 25 Common Air Interface" ,
                  "Wiegand Interface"         ,
                  "Pure IP"                   ,
                  "HW_EXP1"                   ,
                  "HFI"
              };
    uint16_t type = 0;
    
    if (NULL == arp_hdr) {
        return PIA_NG;
    }
    type = pia_htons(arp_hdr->htype);
    printf("hardware type : ");
    
    if ((0 < type) && (38 > type)) {
        printf("%s", type_lst[type]);
    } else if ((37 < type) && (256 > type)) {
        printf("Unassigned");
    } else if (256 == type) {
        printf("HW_EXP2");
    } else if (257 == type) {
        printf("AEthernet");
    } else if ((257 < type) && (65535 > type)) {
        printf("Unassigned");
    } else if (65535 == type) {
        printf("Reserved");
    } else {
        printf("Unknown");
    }
    
    printf(" (0x0%x)", type);
    printf("\n");
    
    return PIA_OK;
}
/**
 * dump protocol type
 * 
 * @param[in] arp_hdr : head pointer to arp header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_arp_dump_ptype(pia_arphdr_t *arp_hdr) {
    if (NULL == arp_hdr) {
        return PIA_NG;
    }
    printf("protocol type : ");
    printf(" (0x04%x)\n", pia_htons(arp_hdr->htype));
    return PIA_OK;
}
/* end of file */
