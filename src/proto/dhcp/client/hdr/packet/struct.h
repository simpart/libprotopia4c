/**
 * @file   struct.h
 * @brief  packet common strct defind
 */
#ifndef _PKTSTRCT_H_
#define _PKTSTRCT_H_

/*** struct ***/

typedef struct ethhdr ethhdr_t;


typedef struct iphdr iphdr_t;

typedef struct udphdr udphdr_t;

typedef struct dummy_udphdr {
    u_int32_t  saddr;
    u_int32_t  daddr;
    u_char     dummy;
    u_char     prot;
    u_int16_t  len;
}dummy_udphdr_t;


typedef struct dhcpmsg {
    u_char            dp_op;          /* packet opcode type */
    u_char            dp_htype;       /* hardware addr type */
    u_char            dp_hlen;        /* hardware addr length */
    u_char            dp_hops;        /* gateway hops */
    u_int32_t         dp_xid;         /* transaction ID */
    u_int16_t         dp_secs;        /* seconds since boot began */
    u_int16_t         dp_flags;       /* flags */
    struct in_addr    dp_ciaddr;      /* client IP address */
    struct in_addr    dp_yiaddr;      /* 'your' IP address */
    struct in_addr    dp_siaddr;      /* server IP address */
    struct in_addr    dp_giaddr;      /* gateway IP address */
    u_char            dp_chaddr[16];  /* client hardware address */
    u_char            dp_sname[64];   /* server host name */
    u_char            dp_file[128];   /* boot file name */
    u_char            dp_options[64];  /* variable-length options field */
}dhcpmsg_t;

#endif
/* end of file */
