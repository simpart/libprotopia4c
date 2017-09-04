/* link : https://chromium.googlesource.com/native_client/src/native_client/+/togit/src/untrusted/nacl/htons.c */
/*
 * Copyright 2014 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#include <stdint.h>
#include "pia/com.h"

uint16_t pia_htons(uint16_t hostshort) {
    return ((hostshort & 0xff) << 8) | (hostshort >> 8);
}

uint16_t pia_ntohs(uint16_t netshort) {
    return ((netshort & 0xff) << 8) | (netshort >> 8);
}
/* end of file */
