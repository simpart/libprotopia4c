/**
 * @file   ctrl.c
 * @brief  dhcp-client controller function
 */
/*** include ***/
#include <client.h>

/*** function ***/
int clt_start (void) {
    DDBG_PRINT("start client");
    
    /* send discover packet */
    clt_discover();
    
    return DCOM_OK;
}
/* end of file */
