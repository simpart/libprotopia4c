/**
 * @file icmp/init.c
 * @author simpart
 */
#include <sys/types.h> 
#include <unistd.h>
#include <string.h>
#include "pia/icmp.h"

/*** global ***/
piaicm_hdr_t  g_piaicm_hdr;
piaicm_echo_t g_piaicm_echo;
piaicm_dat_t  g_piaicm_dat;
piaicm_dat_t  g_piaicm_rcvdat;

int piaicm_init(void) {
    int loop = 0;
    
    memset(&g_piaicm_hdr   , 0x00, sizeof(piaicm_hdr_t));
    memset(&g_piaicm_dat   , 0x00, sizeof(piaicm_dat_t));
    memset(&g_piaicm_rcvdat, 0x00, sizeof(piaicm_dat_t));
    
    /* set default message type */
    piaicm_setdef_type(PIAICM_TYPE_ECHOREQ);
    
    /* init echo data */
    g_piaicm_echo.id  = PIA_M_BYTORD16((uint16_t) getpid());
    g_piaicm_echo.seq = PIA_M_BYTORD16(1);
    
    /* set default data area */
    g_piaicm_dat.size = PIAICM_DATDEFSIZ;
    for (loop=0;loop < g_piaicm_dat.size;loop++) {
        g_piaicm_dat.data[loop] = loop;
    }
    
    return PIA_OK;
}
/* end of file */
