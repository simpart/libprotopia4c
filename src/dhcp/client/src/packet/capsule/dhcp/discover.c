/**
 * @file   discover.c
 * @brief  create dhcp discover massage
 */
#include <packet/capsule/dhcp.h>

/*** function ***/
dhcpmsg_t * cdh_get_discover_pri(void) {
    u_char reqaddr[4]  = {0};
    u_char reqconts[13] = {0};
    dhcpmsg_t * discv = NULL;
    struct timeval time; 
    
    memset(&time, 0x00, sizeof(struct timeval));
    
    discv = (dhcpmsg_t *) malloc(sizeof (dhcpmsg_t));
    if (NULL == discv) {
        DDBG_PRINT("failed create discover massage");
        return NULL;
    }
    
    discv->dp_op    = 0x01;
    discv->dp_htype = 0x01;
    discv->dp_hlen  = 0x06;
    
    /* set transaction id */
    gettimeofday(&time, NULL);
    srand((int) time.tv_usec);
    discv->dp_xid   = rand();
    
    /* set my mac */
    discv->dp_chaddr[0] = DCDH_MAC_1;
    discv->dp_chaddr[1] = DCDH_MAC_2;
    discv->dp_chaddr[2] = DCDH_MAC_3;
    discv->dp_chaddr[3] = DCDH_MAC_4;
    discv->dp_chaddr[4] = DCDH_MAC_5;
    discv->dp_chaddr[5] = DCDH_MAC_6;
    
    /* set option */
    // 99 130 83 99
    discv->dp_options[0] = 99;
    discv->dp_options[1] = 130;
    discv->dp_options[2] = 83;
    discv->dp_options[3] = 99;
    
    cdh_setopt_msgtype(&discv, 1, 4);
    // 99 130 83 99    -> 3
    // 53 1 1          -> 6
    reqaddr[0] = DCDH_FIRST_REQADDR1;
    reqaddr[1] = DCDH_FIRST_REQADDR2;
    reqaddr[2] = DCDH_FIRST_REQADDR3;
    reqaddr[3] = DCDH_FIRST_REQADDR4;
    cdh_setopt_reqaddr(&discv, reqaddr, 7);
    // 99 130 83 99        -> 3
    // 53 1 1              -> 6
    // 50 4 192 168 1 104  -> 12
    
    reqconts[0]  = 1;  
    reqconts[1]  = 28; 
    reqconts[2]  = 2;  
    reqconts[3]  = 121; 
    reqconts[4]  = 15;  
    reqconts[5]  = 6;
    reqconts[6]  = 12;
    reqconts[7]  = 40;
    reqconts[8]  = 41;
    reqconts[9]  = 42;
    reqconts[10] = 26;
    reqconts[11] = 119;
    reqconts[12] = 3;
    
    cdh_setopt_reqconts(&discv, reqconts, 13, 13);
     
    discv->dp_options[28] = 255;
    
    ////99 130 83 99 53
    ////1 1 50 4 192
    ////168 1 109 55 13
    ////1 28 2 121 15
    ////6 12 40 41 42
    ////26 119 3 255 0
   
    
    DDBG_PRINT("return discover massage");
    return discv;
}
/* end of file */
