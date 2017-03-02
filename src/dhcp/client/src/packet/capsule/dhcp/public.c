/**
 * @file   ctrl.c
 * @brief  create dhcp massage
 */
#include <packet/capsule/dhcp.h>

/*** function ***/
dhcpmsg_t * cdh_get_discover(void) {
    return cdh_get_discover_pri();
}
/* end of file */
