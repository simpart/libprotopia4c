/**
 * @file ip/dump.c
 * @brief dump function for ip header
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include "pia/ip.h"
/*** function ***/
/**
 * dump ip header by a line
 *
 * @param[in] ip_hdr : head pointer to ip header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 * @note not supported
 */
int pia_ip_dump (pia_ipv4hdr_t * ip_hdr) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    
    printf("ip ");
    
    printf(
        "%u.%u.%u.%u",
        ip_hdr->sip[0],
        ip_hdr->sip[1],
        ip_hdr->sip[2],
        ip_hdr->sip[3]
    );
     
    printf(" >> ");
    
    printf(
        "%u.%u.%u.%u",
        ip_hdr->dip[0],
        ip_hdr->dip[1],
        ip_hdr->dip[2],
        ip_hdr->dip[3]
    );
    
    printf("\n");
    
    return 0;
}
/**
 * dump ip header detail
 *
 * @param[in] ip_hdr : head pointer to ip header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_ip_dump_detail (pia_ipv4hdr_t * ip_hdr) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    /* check version */
    printf("IP Header");
    if (PIA_TRUE == pia_ip_isv4(ip_hdr)) {
        printf("(v4)\n");
        printf("===========================\n");
        pia_ip_dumpv4(ip_hdr);
    } else if (PIA_TRUE == pia_ip_isv6(ip_hdr)) {
        printf("(v6)\n");
        printf("===========================\n");
        pia_ip_dumpv6(ip_hdr);
    } else {
        printf("(unknown version)\n");
        printf("===========================\n");
        pia_ip_dumpv4(ip_hdr);
    }
    return PIA_OK;
}
/**
 * dump ip header detail (version4)
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_ip_dumpv4(pia_ipv4hdr_t *ip_hdr) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    /* version */
    pia_ip_dump_ver(ip_hdr);
    /* header length */
    pia_ip_dump_hlen(ip_hdr);
    /* type of service */
    pia_ip_dump_tos(ip_hdr, PIA_IP_TOSDMP);
    /* total length */
    printf("total length  : %u byte\n", pia_ntohs(ip_hdr->total));
    /* identification */
    printf("id            : %u\n", pia_ntohs(ip_hdr->id));
    /* flag offset */
    pia_ip_dump_fragoff(ip_hdr);
    /* time to live */
    printf("time to live  : %u\n" , ip_hdr->ttl );
    /* protocol */
    pia_ip_dump_prot(ip_hdr);
    /* check sum */
    printf("check sum     : 0x%x\n", ip_hdr->chksum);
    /* ip address */
    pia_ip_dump_ipv4(ip_hdr);
    return PIA_OK;
}
/**
 * dump ip header detail (version6)
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 * @note not supported
 */
int pia_ip_dumpv6(pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    printf("not supported\n");
    
    return PIA_OK;
}
/**
 * dump version
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_ip_dump_ver (pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    printf("version       : %d\n", ip_hdr->ver);
    return PIA_OK;
}
/**
 * dump header length
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_ip_dump_hlen (pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    printf("header length : %u byte\n" , ip_hdr->hlen*4);
    return PIA_OK;
}
/**
 * dump type of servie
 *
 * @param[in] ip_hdr : head pointer to ip header
 * @param[in] dmp_tp : dump type (PIA_IP_PREC/PIA_IP_DSCP)
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_ip_dump_tos (pia_ipv4hdr_t *ip_hdr, int dmp_tp) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    if (PIA_IP_PREC == dmp_tp) {
        pia_ip_dump_tosprec(ip_hdr);
    } else if (PIA_IP_DSCP == dmp_tp) {
        pia_ip_dump_tosdscp(ip_hdr);
    } else {
        printf("not supported\n");
    }
    return PIA_OK;
}
/**
 * dump type of servie by ip precedence
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_ip_dump_tosprec (pia_ipv4hdr_t *ip_hdr) {
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
//    printf( "ip precedence : " );
//    if( 0 == (ip_hdr->tos & (0xFF & ~IPTOS_CLASS_MASK)) ) {
//        switch(IPTOS_PREC( ip_hdr->tos )) {
//            case IPTOS_PREC_ROUTINE:
//                printf("routine\n");
//                break;
//            case IPTOS_PREC_PRIORITY:
//                printf("priority\n");
//                break;
//            case IPTOS_PREC_IMMEDIATE:
//                printf("immediate\n");
//                break;
//            case IPTOS_PREC_FLASH:
//                printf("flash\n");
//                break;
//            case IPTOS_PREC_FLASHOVERRIDE:
//                printf("flash-override\n");
//                break;
//            case IPTOS_PREC_CRITIC_ECP:
//                printf("critical\n");
//                break;
//            case IPTOS_PREC_INTERNETCONTROL:
//                printf("internet\n");
//                break;
//            case IPTOS_PREC_NETCONTROL:
//                printf("network\n");
//                break;
//        }
//    } else {
//        printf("not deteced\n");
//    }
    return PIA_OK;
}
/**
 * dump type of servie by dscp
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_ip_dump_tosdscp (pia_ipv4hdr_t *ip_hdr) {
ip_hdr = ip_hdr;
//    int dscp = IPTOS_DSCP(ip_hdr->tos);
//    /* check parameter */
//    if (NULL == ip_hdr) {
//        return PIA_NG;
//    }
//    /* dump dscp value */
//    if(0 == dscp) {
//        printf("not detected\n");
//    } else if(IPTOS_DSCP_EF == dscp) {
//        printf("expedited forwarding\n");
//    } else {
//        printf("assured forwarding");
//        switch(dscp) {
//            case IPTOS_DSCP_AF11:
//                printf("(af11)\n");
//                break;
//            case IPTOS_DSCP_AF12:
//                printf("(af12)\n");
//                break;
//            case IPTOS_DSCP_AF13:
//                printf("(af13)\n");
//                break;
//            case IPTOS_DSCP_AF21:
//                printf("(af21)\n");
//                break;
//            case IPTOS_DSCP_AF22:
//                printf("(af22)\n");
//                break;
//            case IPTOS_DSCP_AF23:
//                printf("(af23)\n");
//                break;
//            case IPTOS_DSCP_AF31:
//                printf("(af31)\n");
//                break;
//            case IPTOS_DSCP_AF32:
//                printf("(af32)\n");
//                break;
//            case IPTOS_DSCP_AF33:
//                printf("(af33)\n");
//                break;
//            case IPTOS_DSCP_AF41:
//                printf("(af41)\n");
//                break;
//            case IPTOS_DSCP_AF42:
//                printf("(af42)\n");
//                break;
//            case IPTOS_DSCP_AF43:
//                printf("(af43)\n");
//                break;
//            default:
//                printf("(unknown)\n");
//                break;
//        }
//    }
    return PIA_OK;
}
/**
 * dump fragment offset
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_ip_dump_fragoff (pia_ipv4hdr_t *ip_hdr) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    printf("fragment      : ");
//    if(IP_DF == ip_hdr->frag_off) {
//        printf("don't fragment\n");
//    } else if(IP_MF == ip_hdr->frag_off) {
//        printf("more fragment(offset : %u byte)\n", (IP_OFFMASK & (pia_ntohs(ip_hdr->frag_off)))*8);
//          printf("more fragment");
//    } else {
//        printf("finish fragment\n");
//    }
    return PIA_OK;
}
/**
 * dump protocol
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @return protocol string
 * @return NULL : getting string is failed
 */
char * pia_ip_dump_protstr (pia_ipv4hdr_t *ip_hdr) {
    char * prt_str[] = {
        "hopopt"       ,  // 0
        "icmp"         ,  // 1
	"igmp"         ,  // 2
        "ggp"          ,  // 3
        "ip(ip-in-ip)" ,  // 4
        "stream"       ,  // 5
        "tcp"          ,  // 6
        "cbt"          ,  // 7
        "egp"          ,  // 8
        "igp"          ,  // 9
        "bbn-rcc-mon"  ,  // 10
        "nvp-2"        ,  // 11
        "pup"          ,  // 12
        "argus"        ,  // 13
        "emcon"        ,  // 14
        "xnet"         ,  // 15
        "chaos"        ,  // 16
        "udp"          ,  // 17
        "mux"          ,  // 18
        "dcn-meas"     ,  // 19
        "hmp"          ,  // 20	HMP	Host Monitoring
        "prm"          ,  // 21	PRM	Packet Radio Measurement
        "xns-idp"      ,  // 22	XNS-IDP	XEROX NS IDP
        "trunk-1"      ,  // 23	TRUNK-1	Trunk-1
        "trunk-2"      ,  // 24	TRUNK-2	Trunk-2
        "leaf-1"       ,  // 25	LEAF-1	Leaf-1
        "leaf-2"       ,  // 26	LEAF-2	Leaf-2
        "rdp"          ,  // 27	RDP	Reliable Data Protocol
        "irtp"         ,  // 28	IRTP	Internet Reliable Transaction
        "iso-tp4"      ,  // 29	ISO-TP4	ISO Transport Protocol Class 4
        "netblt"       ,  // 30	NETBLT	Bulk Data Transfer Protocol
        "mfe-nsp"      ,  // 31	MFE-NSP	MFE Network Services Protocol
        "merit-inp"    ,  // 32	MERIT-INP	MERIT Internodal Protocol
        "dccp"         ,  // 33	DCCP	Datagram Congestion Control Protocol
        "3pc"          ,  // 34	3PC	Third Party Connect Protocol
        "idpr"         ,  // 35	IDPR	Inter-Domain Policy Routing Protocol
        "xtp"          ,  // 36	XTP	XTP
        "ddp"          ,  // 37	DDP	Datagram Delivery Protocol
        "idpr-cmtp"    ,  // 38	IDPR-CMTP	IDPR Control Message Transport Protol
        "tp++"         ,  // 39	TP++	TP++ Transport Protocol
        "il"           ,  // 40	IL	IL Transport Protocol
        "ipv6"         ,  // 41	IPv6	Ipv6
        "sdrp"         ,  // 42	SDRP	Source Demand Routing Protocol
        "ipv6-route"   ,  // 43	IPv6-Route	Routing Header for IPv6
        "ipv6-frag"    ,  // 44	IPv6-Frag	Fragment Header for IPv6
        "idrp"         ,  // 45	IDRP	Inter-Domain Routing Protocol
        "rsvp"         ,  // 46	RSVP	Reservation Protocol
        "gre"          ,  // 47	GRE	General Routing Encapsulation
        "mhrp"         ,  // 48	MHRP	Mobile Host Routing Protocol
        "bna"          ,  // 49	BNA	BNA
        "esp"          ,  // 50	ESP	Encap Security Payload
        "ah"           ,  // 51	AH	Authentication Header
        "i-nlsp"       ,  // 52	I-NLSP	Integrated Net Layer Security
        "swipe"        ,  // 53	SWIPE	IP with Encryption
        "narp"         ,  // 54	NARP	NBMA Address Resolution Protocol
        "mobile"       ,  // 55	MOBILE	IP Mobility
        "tlsp"         ,  // 56	TLSP	Transport Layer Security Protocol
        "skip"         ,  // 57	SKIP	SKIP
        "ipv6-icmp"    ,  // 58	IPv6-ICMP	ICMP for IPv6
        "ipv6-nonxt"   ,  // 59	IPv6-NoNxt	No Next Header for IPv6
        "ipv6-opts"    ,  // 60	IPv6-Opts	Destination Options for IPv6
        "any host internal protocol", //61	-	any host internal protocol
        "cftp"         ,  // 62	CFTP	CFTP
        "any local network", //63	-	any local network
        "sat-expak"    ,  // 64	SAT-EXPAK	SATNET and Backroom EXPAK
        "kryptolan"    ,  // 65	KRYPTOLAN	Kryptolan
        "rvd"          ,  // 66	RVD	MIT Remote Virtual Disk Protocol
        "ippc"         ,  // 67	IPPC	Internet Pluribus Packet Core
        "any distributed file system", //68	-	any distributed file system
        "sat-mon"      ,  // 69	SAT-MON	SATNET Monitoring
        "visa"         ,  // 70	VISA	VISA Protocol
        "ipcv"         ,  // 71	IPCV	Internet Packet Core Utility
        "cpnx"         ,  // 72	CPNX	Computer Protocol Network Executive
        "cphb"         ,  // 73	CPHB	Computer Protocol Heart Beat
        "wsn"          ,  // 74	WSN	Wang Span Network
        "pvp"          ,  // 75	PVP	Packet Video Protocol
        "br-sat-mon"   ,  // 76	BR-SAT-MON	Backroom SATNET Monitoring
        "sun-nd"       ,  // 77	SUN-ND	SUN ND PROTOCOL-Temporary
        "wb-mon"       ,  // 78	WB-MON	WIDEBAND Monitoring
        "wb-expak"     ,  // 79	WB-EXPAK	WIDEBAND EXPAK
        "iso-ip"       ,  // 80	ISO-IP	ISO Internet Protocol
        "vmtp"         ,  // 81	VMTP	VMTP
        "secure-vmtp"  ,  // 82	SECURE-VMTP	SECURE-VMTP
        "vines"        ,  // 83	VINES	VINES
        "ttp"          ,  // 84	TTP	TTP
        "nsfnet-igp"   ,  // 85	NSFNET-IGP	NSFNET-IGP
        "dgp"          ,  // 86	DGP	Dissimilar Gateway Protocol
        "tcf"          ,  // 87	TCF	TCF
        "eigrp"        ,  // 88	EIGRP	EIGRP
        "ospfigp"      ,  // 89	OSPFIGP	OSPFIGP
        "sprite-rpc"   ,  // 90	Sprite-RPC	Sprite RPC Protocol
        "larp"         ,  // 91	LARP	Locus Address Resolution Protocol
        "mtp"          ,  // 92	MTP	Multicast Transport Protocol
        "ax.25"        ,  // 93	AX.25	AX.25 Frames
        "ipip"         ,  // 94	IPIP	IP-within-IP Encapsulation Protocol
        "micp"         ,  // 95	MICP	Mobile Internetworking Control Protcol
        "scc-sp"       ,  // 96	SCC-SP	Semaphore Communications Sec. Pro.
        "etherip"      ,  // 97	ETHERIP	Ethernet-within-IP Encapsulation
        "encap"        ,  // 98	ENCAP	Encapsulation Header
        "any private encryption scheme", //99	-	any private encryption scheme
        "gmtp"         ,  // 100	GMTP	GMTP
        "ifmp"         ,  // 101	IFMP	Ipsilon Flow Management Protocol
        "pnni"         ,  // 102	PNNI	PNNI over IP
        "pim"          ,  // 103	PIM	Protocol Independent Multicast
        "aris"         ,  // 104	ARIS	ARIS
        "scps"         ,  // 105	SCPS	SCPS
        "qnx"          ,  // 106	QNX	QNX
        "a/n"          ,  // 107	A/N	Active Networks
        "ipcomp"       ,  // 108	IPComp	IP Payload Compression Protocol
        "snp"          ,  // 109	SNP	Sitara Networks Protocol
        "compaq-peer"  ,  // 110	Compaq-Peer	Compaq Peer Protocol
        "ipx-in-ip"    ,  // 111	IPX-in-IP	IPX in IP
        "vrrp"         ,  // 112	VRRP	Virtual Router Redundancy Protocol
        "pgm"          ,  // 113	PGM	PGM Reliable Transport Protocol
        "any 0-hop protocol" , // 114	-	any 0-hop protocol
        "l2tp"         ,  // 115	L2TP	Layer Two Tunneling Protocol
        "ddx"          ,  // 116	DDX	D-II Data Exchange (DDX)
        "iatp"         ,  // 117	IATP	Interactive Agent Transfer Protocol
        "stp"          ,  // 118	STP	Schedule Transfer Protocol
        "srp"          ,  //119	SRP	SpectraLink Radio Protocol
        "uti"          ,  // 120	UTI	UTI
        "smp"          ,  // 121	SMP	Simple Message Protocol
        "sm"           ,  // 122	SM	SM
        "ptp"          ,  // 123	PTP	Performance Transparency Protocol
        "isis"         ,  // 124	ISIS over IPv4	-
        "fire"         ,  // 125	FIRE	-
        "crtp"         ,  // 126	CRTP	Combat Radio Transport Protocol
        "crudp"        ,  // 127	CRUDP	Combat Radio User Datagram
        "sscopmce"     ,  // 128	SSCOPMCE	-
        "iplt"         ,  // 129	IPLT	-
        "sps"          ,  // 130	SPS	Secure Packet Shield
        "pipe"         ,  // 131	PIPE	Private IP Encapsulation within IP
        "sctp"         ,  // 132	SCTP	Stream Control Transmission Protocol
        "fc"           ,  // 133	FC	Fibre Channel
        "rsvp-e2e-ignore",// 134	RSVP-E2E-IGNORE
    };
    /* check parameter */
    if (NULL == ip_hdr) {
        return NULL;
    }
    /* check protocol */
    if (134 >= ip_hdr->prot) {
        return prt_str[ip_hdr->prot];
    } else if ((138 <= ip_hdr->prot) && (252 >= ip_hdr->prot)) {
        return "unassigned";
    } else if ((253 == ip_hdr->prot) || (254 == ip_hdr->prot)) {
        return "experimentation/testing";
    } else if (255 == ip_hdr->prot) {
        return "reserved";
    } else {
        return "unknown";
    }
}


int pia_ip_dump_prot (pia_ipv4hdr_t *ip_hdr) {
    char *prt_str = NULL;
    
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    
    prt_str = pia_ip_dump_protstr(ip_hdr);
    printf("protocol      : %s", prt_str);
    printf(" (0x%x)\n", ip_hdr->prot);
    
    return PIA_OK;
}
/**
 * dump ipv4 address
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_ip_dump_ipv4 (pia_ipv4hdr_t *ip_hdr) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    
    printf(
        "src ip        : %u.%u.%u.%u\n",
        ip_hdr->sip[0],
        ip_hdr->sip[1],
        ip_hdr->sip[2],
        ip_hdr->sip[3]
    );
    printf(
        "dest ip       : %u.%u.%u.%u\n", 
        ip_hdr->dip[0],
        ip_hdr->dip[1],
        ip_hdr->dip[2],
        ip_hdr->dip[3]
    );
    
    return PIA_OK;
}
/* end of file */
