#ifndef _ROUTE_H
#define _ROUTE_H

#include  <global.h>

#define TABLE_SIZE 20

typedef struct packet {
    int id;
    int dst_router;
    // point_t dst;
    // point_t src;

    // TODO packet header
    // tmp packet header
    int ip;
} packet_t;

typedef struct router {
    int id;
    // TODO routing table
    // temp routing table ip - dst table

    int table[TABLE_SIZE * 2];

    // TODO interface
} router_t;

typedef struct iface {
    char name[MAX_STRLEN];
    int id;
    int dst_router;
    int dst_iface; // destination router interface id
} iface_t;

extern packet_t *packet;
extern router_t *router;

extern int router_number;
extern int packet_number;

void init_packet();
void init_route();


#endif
