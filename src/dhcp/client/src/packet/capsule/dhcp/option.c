/**
 * @file   option.c
 * @brief  util function for dhcp option
 */
#include <packet/capsule/dhcp.h>

void cdh_setopt_msgtype (dhcpmsg_t ** msg, u_int16_t type, u_int16_t offset) {
    dhcpmsg_t * set = NULL;
    if ((NULL == msg) || (NULL == *msg)) {
        return;
    }
    set = *msg;
    set->dp_options[offset]   = 53;
    set->dp_options[offset+1] = 1;
    set->dp_options[offset+2] = type;
}

void cdh_setopt_reqaddr (dhcpmsg_t ** msg, u_char * addr, u_int16_t offset) {
    dhcpmsg_t * set = NULL;
    if ((NULL == msg) || (NULL == *msg) || (NULL == addr)) {
        return;
    }
    set = *msg;
    set->dp_options[offset]   = 50;
    set->dp_options[offset+1] = 4;
    set->dp_options[offset+2] = addr[0];
    set->dp_options[offset+3] = addr[1];
    set->dp_options[offset+4] = addr[2];
    set->dp_options[offset+5] = addr[3];
}

void cdh_setopt_reqconts(dhcpmsg_t ** msg, u_char * req, u_int16_t size, u_int16_t offset) {
    int loop        = 0;
    dhcpmsg_t * set = NULL;
    if ((NULL == msg) || (NULL == *msg) || (NULL == req)) {
        return;
    }
    
    set = *msg;
    set->dp_options[offset]   = 55;
    set->dp_options[offset+1] = size;
    
    for(loop=0; loop < size ;loop++) {
        set->dp_options[offset+2+loop] = req[loop];
    }
}
/* end of file */
