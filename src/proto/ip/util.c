/**
 * @file util.c
 * @author simpart
 */
#include <sys/time.h>
#include "pia/com.h"

uint16_t pia_ip_getid (void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 0xFFFF & (tv.tv_usec << 2);
}


/* end of file */
