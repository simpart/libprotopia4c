/**
 * @file error.c
 * @author simpart
 */

/*** include ***/
#include <stdio.h>
#include <string.h>
#include "pia/com.h"

/*** global ***/
pia_errinf_t g_pia_errinf;

/*** function ***/

int pia_err_init(void) {
    memset(&g_pia_errinf, 0x00, sizeof(pia_errinf_t));
    return PIA_OK;
}

/**
 * set error
 *
 * @param[in] line : line number
 * @param[in] dtl : error detail
 */
void pia_error (char *file, int line, char * dtl) {
    if ((NULL == file) || (NULL == dtl)) {
        return;
    }
    strncpy(&(g_pia_errinf.file[0]), file, sizeof(g_pia_errinf.file));
    g_pia_errinf.line = line;
    strncpy(&(g_pia_errinf.detail[0]), file, sizeof(g_pia_errinf.detail));
}

void pia_dump_err (void) {
    printf("Error Info\n");
    printf("====================\n");
    printf("file   : %s\n", g_pia_errinf.file);
    printf("line   : %u\n", g_pia_errinf.line);
    printf("detail : %s\n", g_pia_errinf.detail);
}
/* end of file */
