/**
 * @file byteorder.c
 * @brief byte order functions
 * @author simpart
 */
/*** include ***/
#include <stdio.h>
#include <stdint.h>
#include "pia/com.h"

/*** function ***/
/**
 * convert byteorder for 16bit
 * 
 * @param[in] val : convert target value
 */
uint16_t pia_bytord16(uint16_t val) {
    return ((val & 0xFF) << 8) | (val >> 8);
}

/**
 * convert byteorder for 32bit
 *
 * @param[in] val : convert target value
 */
uint32_t pia_bytodr32 (uint32_t val) {
    return ( (pia_bytodr16((val & 0xFFFF0000) >> 16)) | ((pia_bytord16(val & 0x0000FFFF) << 16)) );
}
/* end of file */
