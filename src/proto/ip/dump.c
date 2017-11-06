/**
 * @file ip/dump.c
 * @brief dump function for ip header
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <string.h>
#include <netinet/ip.h>
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
    printf( "ip precedence : " );
    if( 0 == (ip_hdr->tos & (0xFF & ~IPTOS_CLASS_MASK)) ) {
        switch(IPTOS_PREC( ip_hdr->tos )) {
            case IPTOS_PREC_ROUTINE:
                printf("routine\n");
                break;
            case IPTOS_PREC_PRIORITY:
                printf("priority\n");
                break;
            case IPTOS_PREC_IMMEDIATE:
                printf("immediate\n");
                break;
            case IPTOS_PREC_FLASH:
                printf("flash\n");
                break;
            case IPTOS_PREC_FLASHOVERRIDE:
                printf("flash-override\n");
                break;
            case IPTOS_PREC_CRITIC_ECP:
                printf("critical\n");
                break;
            case IPTOS_PREC_INTERNETCONTROL:
                printf("internet\n");
                break;
            case IPTOS_PREC_NETCONTROL:
                printf("network\n");
                break;
        }
    } else {
        printf("not deteced\n");
    }
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
    int dscp = IPTOS_DSCP(ip_hdr->tos);
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    /* dump dscp value */
    if(0 == dscp) {
        printf("not detected\n");
    } else if(IPTOS_DSCP_EF == dscp) {
        printf("expedited forwarding\n");
    } else {
        printf("assured forwarding");
        switch(dscp) {
            case IPTOS_DSCP_AF11:
                printf("(af11)\n");
                break;
            case IPTOS_DSCP_AF12:
                printf("(af12)\n");
                break;
            case IPTOS_DSCP_AF13:
                printf("(af13)\n");
                break;
            case IPTOS_DSCP_AF21:
                printf("(af21)\n");
                break;
            case IPTOS_DSCP_AF22:
                printf("(af22)\n");
                break;
            case IPTOS_DSCP_AF23:
                printf("(af23)\n");
                break;
            case IPTOS_DSCP_AF31:
                printf("(af31)\n");
                break;
            case IPTOS_DSCP_AF32:
                printf("(af32)\n");
                break;
            case IPTOS_DSCP_AF33:
                printf("(af33)\n");
                break;
            case IPTOS_DSCP_AF41:
                printf("(af41)\n");
                break;
            case IPTOS_DSCP_AF42:
                printf("(af42)\n");
                break;
            case IPTOS_DSCP_AF43:
                printf("(af43)\n");
                break;
            default:
                printf("(unknown)\n");
                break;
        }
    }
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
    if(IP_DF == ip_hdr->frag_off) {
        printf("don't fragment\n");
    } else if(IP_MF == ip_hdr->frag_off) {
        printf("more fragment(offset : %u byte)\n", (IP_OFFMASK & (pia_ntohs(ip_hdr->frag_off)))*8);
    } else {
        printf("finish fragment\n");
    }
    return PIA_OK;
}
/**
 * dump protocol
 * 
 * @param[in] ip_hdr : head pointer to ip header
 * @return PIA_NG : dumping failed
 * @return PIA_OK : dumping success
 */
int pia_ip_dump_prot (pia_ipv4hdr_t *ip_hdr) {
    /* check parameter */
    if (NULL == ip_hdr) {
        return PIA_NG;
    }
    printf("protocol      : ");
    if(PIA_IP_ICMP == ip_hdr->prot) {
        printf("icmp");
    } else if (PIA_IP_TCP == ip_hdr->prot) {
        printf("tcp");
    } else if (PIA_IP_UDP == ip_hdr->prot) {
        printf("udp");
    } else {
        printf("unknown");
    }
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
