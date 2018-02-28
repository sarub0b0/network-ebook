#ifndef _TOPOLOGY_H
#define _TOPOLOGY_H


typedef struct topology{
    int router_number;
    int *link_list;
    int *path_list;
}topology_t;


extern topology_t topology;
extern int link_number;
extern int path_number;

void init_topology();
#endif
