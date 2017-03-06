/**
 * @file receive.h
 * @brief defined common packet reeive
 * @author simpart
 */
#include "pia/common.h"

#ifndef __RECEIVE_H__
#define __RECEIVE_H__

/**
 * @brief packet receive config
 */
typedef struct piast_rcvconf {
    /* receive parameter */
    char   ifname[16];  //! receive interface name
    uint   max_size;    //! receive max size (byte)
    uchar  promis;      //! promiscuous mode flag
    uint   timeout;     //! receive timeout (ms)
    
    /* callback */
    void (* cb_func)(unsigned char *, void *, void *);
    void  *cb_prm;
} piast_rcvconf_t;

/* prototype */
int pia_init_recv (piast_rcvconf_t);
int pia_start_recv (void);

#include <pcap.h>
void pia_cbwrap (u_char *, const struct pcap_pkthdr *, const u_char *);

#endif
/* end of file */
