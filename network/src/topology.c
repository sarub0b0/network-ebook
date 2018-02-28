#include <string.h>

#include <global.h>
#include <message.h>
#include <graphics.h>

#include <route.h>
#include <topology.h>

void get_path_number();
void create_path();
void print_topology();

int router_number;
int link_number;
int path_number;

topology_t topology;

void init_topology() {

    link_number   = router_number * (router_number - 1) * 2;

    topology.router_number = router_number;

    topology.link_list = (int *) malloc(sizeof(int) * link_number);

    dprintf("link_number %d\n", link_number);
    memset(topology.link_list, -1, sizeof(int) * link_number);

    create_path();

    dprintf("link_number %d\n", link_number);
}

void create_path() {
    int i = 0;
    for (int s = 0; s < router_number; s++) {
        for (int d = 0; d < router_number; d++) {
            if (s != d) {
                topology.link_list[i++] = s;
                topology.link_list[i++] = d;
            }
        }
    }

    print_topology(&topology);

    int *l;
    int *temp_list;
    int temp_list_number;
    temp_list_number = link_number / 2;
    temp_list        = (int *) malloc(sizeof(int) * temp_list_number);
    memset(temp_list, -1, sizeof(int) * temp_list_number);

    l = topology.link_list;

    int flag;
    int s1, s2, d1, d2;
    int temp_i;
    int temp_number;

    flag        = 0;
    temp_number = 2;
    temp_i      = 2;

    temp_list[0] = l[0];
    temp_list[1] = l[1];

    for (int i = 2; i < link_number; i += 2) {
        s1 = l[i];
        d1 = l[i + 1];
        for (int j = 0; j < temp_number; j += 2) {
            s2 = temp_list[j];
            d2 = temp_list[j + 1];

            printf("list %d --- %d  tmp %d --- %d\n", s1, d1, s2, d2);
            if ((s1 == s2 && d1 == d2) || (s1 == d2 && d1 == s2)) {
                flag = 0;
                break;
            } else
                flag = 1;
        }

        if (flag) {
            temp_list[temp_i]     = s1;
            // temp_list[temp_i + 1] = d1;
            temp_i += 2;
            temp_number += 2;
        }
    }

    path_number = temp_number / 2;
    // for (int i = 0; i < temp_number; i += 2) {
    //     printf("path %d --- %d\n", temp_list[i], temp_list[i + 1]);
    // }
    topology.path_list = (int *) malloc(sizeof(int) * path_number);
}

void print_topology(topology_t *t) {
    for (int i = 0; i < link_number; i += 2) {
        printf("link src:%d   dst:%d\n", t->link_list[i], t->link_list[i + 1]);
    }
}
