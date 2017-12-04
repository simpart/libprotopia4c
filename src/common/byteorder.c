/* link : https://chromium.googlesource.com/native_client/src/native_client/+/togit/src/untrusted/nacl/htons.c */
/*
 * Copyright 2014 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#include <stdio.h>
#include <stdint.h>
#include "pia/com.h"

uint16_t pia_htons(uint16_t hostshort) {
#if __PIA_BYTEORDER__ == PIA_BYOR_LITED
    return ((hostshort & 0xFF) << 8) | (hostshort >> 8);
#else
    return hostshort;
#endif
}

uint16_t pia_ntohs(uint16_t netshort) {
#if __PIA_BYTEORDER__ == PIA_BYOR_LITED
    return ((netshort & 0xFF) << 8) | (netshort >> 8);
#else
    return netshort;
#endif

}


uint16_t pia_byteodr16 (uint16_t val) {
#if __PIA_BYTEORDER__ == PIA_BYOR_LITED
    return ((val & 0xFF) << 8) | (val >> 8);
#else
    return val;
#endif
}

uint16_t pia_byteodr32 (uint32_t val) {
#if __PIA_BYTEORDER__ == PIA_BYOR_LITED
    
    //printf("[dbg] %u\n", );
    
    return ( (pia_byteodr16((val & 0xFFFF0000) >> 16)) | ((pia_byteodr16(val & 0x0000FFFF) << 16)) );
#else
    return val;
#endif
}

uint16_t pia_htons_32(uint16_t hostlong) {
#if __PIA_BYTEORDER__ == PIA_BYOR_LITED
    return (pia_htons((hostlong & 0xFFFF0000) >> 16) & (pia_htons(hostlong  & 0x0000FFFF) << 16));
#else
    return hostlong;
#endif
}

uint16_t pia_ntohs_32(uint16_t netlong) {
#if __PIA_BYTEORDER__ == PIA_BYOR_LITED
    return (pia_htons((netlong & 0xFFFF0000) >> 16) & (pia_htons(netlong  & 0x0000FFFF) << 16));
#else
    return netlong;
#endif
}
/* end of file */
