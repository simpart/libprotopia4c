/**
 * @file piacom.h
 * @brief protopia common defined
 * @author simpart
 */
#include <stddef.h>
#include <stdint.h>

#ifndef __COMMON_H__
#define __COMMON_H__
/**
 * @brief value of function return
 */
#define PIA_OK  0  //! function is successful
#define PIA_NG -1  //! function is failed
/**
 * @brief error value
 */
#define PIA_ERR_NMCH  -10 //! not match
/**
 * @brief common flag
 */
#define PIA_TRUE  1  //! value of true
#define PIA_FALSE 0  //! value of false

#define PIA_RANDOM_8   0x0F
#define PIA_RANDOM_16  0xFF

/**
 * @brief util data type for protopia
 */
typedef unsigned char * pkt;
typedef unsigned int    uint;
typedef unsigned char   uchar;

/*** prototype ***/
uint16_t pia_htons (uint16_t);
uint16_t pia_ntohs (uint16_t);
uint16_t pia_checksum (uint16_t *, size_t);
uint32_t pia_random (uint32_t);
#endif
/* end of file */
