/**
 * @file discover.c
 */
#include <packet/dump/dhcp.h>

void dmp_discover(dhcpmsg_t * msg) {
    int loop = 0;
    
    if (NULL == msg) {
        return;
    }
    printf(">>>>> DHCP DISCOVER\n");
    
    printf("      from : ");
    printf(
        "%02x-%02x-%02x-%02x-%02x-%02x\n",
        msg->dp_chaddr[0],
        msg->dp_chaddr[1],
        msg->dp_chaddr[2],
        msg->dp_chaddr[3],
        msg->dp_chaddr[4],
        msg->dp_chaddr[5]
    );

    printf("       tid : ");
    printf("%d\n",msg->dp_xid);
    
//    printf(
//        "   request : %d.%d.%d.%d\n",
//        msg->dp_options[9],
//        msg->dp_options[10],
//        msg->dp_options[11],
//        msg->dp_options[12]
//    );
    printf("    option : ");
    for(loop=0; loop < 50 ;) {
        if (0 != loop) {
            printf("             ");
        }
        printf(
            "%d %d %d %d %d\n",
            msg->dp_options[loop],
            msg->dp_options[loop+1],
            msg->dp_options[loop+2],
            msg->dp_options[loop+3],
            msg->dp_options[loop+4]
        );
        loop = loop + 5;
    }
    printf("\n");
}


/* end of file */
