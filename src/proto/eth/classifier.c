/**
 * @file ether/classifier.c
 * @brief classifier function for ip header
 * @author simpart
 */
/*** include ***/
#include <string.h>
#include "pia/com.h"
#include "pia/eth.h"

/*** function ***/
/**
 * checking header src mac address whether it is same to the parameter
 *
 * @param[in] eth_hdr : head pointer to frame
 * @param[in] mac : head pointer to mac
 * @return PIA_NG : checking failed
 * @return PIA_TRUE : mac of paramter is same to src mac of header
 * @return PIA_FALSE : mac of paramter is different to src mac of header
 */
int pia_eth_issrc (pia_ethhdr_t *eth_hdr, uint8_t *mac) {
    /* check parameter */
    if ((NULL == eth_hdr) || (NULL == mac)) {
        return PIA_NG;
    }
    /* compares mac */
    if (0 == memcmp(&(eth_hdr->smac[0]), mac, PIA_ETH_MACSIZE)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

/**
 * checking header dest mac address whether it is same to the parameter
 * 
 * @param[in] eth_hdr : head pointer to frame
 * @param[in] mac : head pointer to mac
 * @return PIA_NG : checking failed
 * @return PIA_TRUE : mac of paramter is same to dest mac of header
 * @return PIA_FALSE : mac of paramter is different to dest mac of header
 */
int pia_eth_isdst (pia_ethhdr_t *eth_hdr, uint8_t *mac) {
    /* check paramter */
    if ( (NULL == eth_hdr) || (NULL == mac)) {
        return PIA_NG;
    }
    /* compares mac */
    if (0 == memcmp(&(eth_hdr->dmac[0]), mac, PIA_ETH_MACSIZE)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

/**
 * checking header ether type whether it is ip packet
 *
 * @param[in] eth_hdr : head pointer to frame
 * @return PIA_NG : checking failed
 * @return PIA_TRUE :  paramter is ip packet
 * @return PIA_FALSE : paramter is not ip packet
 */
int pia_eth_isip (pia_ethhdr_t *eth_hdr) {
    /* check parameter */
    if (NULL == eth_hdr) {
        return PIA_NG;
    }
    /* check ether type */
    if (PIA_ETH_IP == pia_ntohs(eth_hdr->type)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
} 

/**
 * checking header ether type whether it is arp packet
 *
 * @param[in] eth_hdr : head pointer to frame
 * @return PIA_NG : checking failed
 * @return PIA_TRUE : paramter is arp packet
 * @return PIA_FALSE : paramter is not arp packet
 */
int pia_eth_isarp (pia_ethhdr_t *eth_hdr) {
    /* check paramter */
    if (NULL == eth_hdr) {
        return PIA_NG;
    }
    /* check ether type */
    if (PIA_ETH_ARP == pia_ntohs(eth_hdr->type)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}

/**
 * checking header ether type whether it is same to the parameter
 * 
 * @param[in] eth_hdr : head pointer to frame
 * @param[in] prot : protocol type value
 * @return PIA_NG : checking failed
 * @return PIA_TRUE : prot is same to protocol type of header
 * @return PIA_FALSE : prot is different to protocol type of header
 */
int pia_eth_isprot (pia_ethhdr_t *eth_hdr, uint16_t prot) {
    /* check paramter */
    if (NULL == eth_hdr) {
        return PIA_NG;
    }
    /* compares ether type */
    if (prot == pia_ntohs(eth_hdr->type)) {
        return PIA_TRUE;
    }
    return PIA_FALSE;
}
/* end of file */
