/**
 * @file ip/dump.c
 * @author simpart
 */
#include <stdio.h>
#include "pia/com.h"
#include "pia/arp.h"

/*** function ***/

void pia_arp_dump (uint8_t *pkt) {
    pia_arphdr_t * arp_hdr;
    
    if (NULL == pkt) {
        return;
    }
    
    arp_hdr = (pia_arphdr_t *) pkt;
    
    printf("ARP Header\n");
    printf("===========================\n");
    pia_arp_dump_htype(arp_hdr);
    
    pia_arp_dump_ptype(arp_hdr);
    
    printf("hardware address length : %02dbyte\n", arp_hdr->hlen);
    
    printf("protocol address length : %02dbyte\n", arp_hdr->plen);
    
    printf("operation code : ");
    if (PIA_TRUE == pia_arp_isrequest(pkt)) {
        printf("Request\n");
    } else if (PIA_TRUE == pia_arp_isreply(pkt)) {
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
}

void pia_arp_dump_htype(pia_arphdr_t *arp_hdr) {
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
    uint16_t type = pia_htons(arp_hdr->htype);
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
}

void pia_arp_dump_ptype(pia_arphdr_t *arp_hdr) {
    printf("protocol type : ");
    printf(" (0x04%x)\n", pia_htons(arp_hdr->htype));
}
/* end of file */
