#ifndef ROUTING_H_
#define ROUTING_H_

#include <string>
#include <vector>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <text.hh>

class bitmap;

typedef std::vector<std::vector<int>> link_t;

typedef struct interface {
    std::string name;
    int index;
    std::string str_address;
    std::string str_netmask;
    struct in_addr in_addr_address;
    struct in_addr in_addr_netmask;
} interface_t;

typedef struct table {
    struct in_addr gateway;
    struct in_addr net;
    struct in_addr mask;
    int interface_i;
} table_t;

typedef struct router {
    bitmap *bmp;
    std::string name;
    int index;
    std::vector<interface_t *> interfaces;
    std::vector<table_t *> routing_table;
} router_t;

typedef struct packet {
    bitmap *bmp;
    struct in_addr src, dst;
    int port;
} packet_t;

typedef router_t server_t;

class routing {
   private:
    int router_number_;
    int server_number_;
    int packet_number_;

    link_t template_router_link_;
    link_t template_server_link_;

    link_t router_link_;
    link_t server_link_;

    std::vector<router_t *> routers_;
    std::vector<server_t *> servers_;
    // std::vector<packet_t *> packets_;
    packet_t packet_;

    text text_;

    void init_image(const std::string *resource_path,
                    int display_width,
                    int display_height);

    void init_text(const std::string *resource_path);

    void init_topology();

    void init_router();

    void init_table();

    void draw_path();
    void draw_node();
    void draw_name();

   public:
    routing();
    ~routing();

    void init(const std::string *resource_path,
              int display_width,
              int display_height);
    void load_topology();
    void create_topology();
    void create_path();

    void draw_topology();

    void move_packet();
};
#endif
