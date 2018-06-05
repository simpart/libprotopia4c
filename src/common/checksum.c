/**
 * @file checksum.c
 * @brief checksum function
 * @author simpart
 */
/*** include ***/
#include "pia/com.h"

/*** function ***/
/**
 * generate checksum value
 *
 * @param[in] ptgt : pointer of target
 * @param[in] size : target length
 */
uint16_t pia_checksum(uint16_t *ptgt, size_t size) {
    unsigned long sum = 0;
    
    while(size > 1) {
        sum += *ptgt;
        ptgt++;
        size -= 2;
    }
    if(size == 1) {
        sum += *(uint16_t *) ptgt;
    }
    
    sum = (sum & 0xffff) + (sum >> 16);
    sum = (sum & 0xffff) + (sum >> 16);
    
    return ~sum;
}
/* end of file */
