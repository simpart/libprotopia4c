/**
 * @file util.c
 * @author simpart
 */
/*** include ***/
#include <sys/time.h>
#include "pia/com.h"
/*** function ***/
/**
 * get random value 
 *
 * @param[in] rng : mask value(specify bit range)
 * @return random value
 */
uint32_t pia_random (uint32_t rng) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return rng & (tv.tv_usec << 2);
}
/* end of file */
