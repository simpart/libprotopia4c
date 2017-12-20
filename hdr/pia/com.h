/**
 * @file pia/com.h
 * @brief protopia common defined
 * @author simpart
 */
/*** include ***/
#include <stddef.h>
#include <stdint.h>

#ifndef __PIA_COM_H__
#define __PIA_COM_H__

/*** define ***/
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

#define PIA_RANDOM_8   0xFF
#define PIA_RANDOM_16  0xFFFF

#define PIA_BYOR_LITED  0x100
#define PIA_BYOR_BIGED  0x101
#define __PIA_BYTEORDER__ PIA_BYOR_LITED

/*** struct ***/
typedef struct pia_errinf {
    char file[32];
    int  line;
    char detail[128];
} pia_errinf_t;

/*** prototype ***/
int pia_init(void);
int pia_err_init(void);
void pia_error(const char *, int, const char *);
void pia_dump_err (void);
uint16_t pia_htons (uint16_t);
uint16_t pia_ntohs (uint16_t);
uint16_t pia_byteodr16 (uint16_t);
uint32_t pia_byteodr32 (uint32_t);
uint16_t pia_checksum (uint16_t *, size_t);
uint32_t pia_random (uint32_t);
int pia_dump_opt (uint8_t *, size_t, int);
/*** macro ***/
#define PIA_ERROR(d) pia_error(__FILE__, __LINE__, d);

#endif
/* end of file */
