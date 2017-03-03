/**
 * @file   main.c
 * @brief  dhcp-client main function
 */
/*** include ***/
#include <common.h>
#include <client.h>

/*** function ***/
int main (int argc, char *argv[]) {
    int ret = 0;
    
    /* start dhcp client */
    ret = clt_start();
    if (DCOM_OK != ret) {
        DDBG_PRINT("failed dhcp client");
    }
    
    DDBG_PRINT("finished dhcp client");
    return DCOM_OK;
}
/* end of file */
