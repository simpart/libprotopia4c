/**
 * @file checksum.c
 * @author simpart
 */
#include "pia/com.h"

uint16_t pia_checksum(uint16_t *buf, size_t size) {
    unsigned long sum = 0;
    
    while(size > 1) {
        sum += *buf;
        buf++;
        size -= 2;
    }
    if(size == 1) {
        sum += *(uint16_t *) buf;
    }
    
    sum = (sum & 0xffff) + (sum >> 16);
    sum = (sum & 0xffff) + (sum >> 16);
    
    return ~sum;
}

