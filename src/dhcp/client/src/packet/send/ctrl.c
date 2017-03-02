/**
 * @file   ctrl.c
 * @brief  packet sender
 */
/*** include ***/
#include <packet/send.h>

/*** global ***/
int Gpsd_sock = 0;
struct sockaddr_ll sll = {0};

/*** function ***/
int psd_sendpkt(u_char * frame, u_int32_t send_size) {
    ssize_t  send_ret = 0;
    
    if (NULL == frame) {
        return DCOM_NG;
    }
    
    /* check init */
    if (0 == Gpsd_sock) {
        psd_init();
        if (DCOM_NG == Gpsd_sock) {
            DDBG_PRINT("failed send packet");
            return DCOM_NG;
        }
    }
    
    send_ret = sendto(
                    Gpsd_sock               ,
                    (char *)frame           ,
                    send_size               ,
                    0                       ,
                    (struct sockaddr *)&sll ,
                    sizeof(struct sockaddr_ll)
                );
    if (0 > send_ret) {
         DDBG_PRINT("failed sendto");
        return DCOM_NG;
    }
    printf("send %d byte\n",(int) send_ret);
    DDBG_PRINT("send packet");
    
    
    
    return DCOM_OK;
}
/* end of file */
