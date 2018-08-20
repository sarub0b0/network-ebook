#include <cmath>
#include <cfloat>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <global.hh>
#include <message.hh>
#include <routing.hh>
#include <point.hh>
#include <bitmap.hh>
#include <text.hh>

#define PI 3.1415

int _netmask_len();
void _print_inaddr(struct in_addr *addr);

void _print_inaddr(struct in_addr *addr) {

    for (int i = 0; i < 32; i += 8) {
        printf("%02x ", (addr->s_addr >> i) % 256);
    }

    printf("\n");
}
int _netmask_len(struct in_addr mask) {
    int i = 0;
    while (0 < mask.s_addr) {
        mask.s_addr = mask.s_addr >> 1;
        i++;
    }
    return i;
}

routing::routing() {
}
routing::~routing() {
}

void routing::init(const std::string *resource_path,
                   int display_width,
                   int display_height) {

    if (!al_init_font_addon()) throw "Failed to initialize font addon";

    router_number_ = 3;
    server_number_ = 2;

    for (int i = 0; i < router_number_; i++) {
        routers_.push_back(new router_t);
        routers_[routers_.size() - 1]->index = i;
        routers_[routers_.size() - 1]->name  = "R" + std::to_string(i);
    }

    for (int i = 0; i < server_number_; i++) {
        servers_.push_back(new server_t);
        servers_[servers_.size() - 1]->index = i;
        servers_[servers_.size() - 1]->name  = "H" + std::to_string(i);
    }

    init_topology();
    init_table();

    init_image(resource_path, display_width, display_height);
    init_text(resource_path);

    is_packets = 0;
}
void load_topology() {
}
void routing::create_topology() {
}

void routing::create_path() {
}

void routing::init_topology() {

    routers_[0]->interfaces.push_back(new interface_t);
    routers_[0]->interfaces.push_back(new interface_t);

    routers_[0]->interfaces[0]->index       = 0;
    routers_[0]->interfaces[0]->name        = "eth0";
    routers_[0]->interfaces[0]->str_address = "10.0.0.1";
    routers_[0]->interfaces[0]->str_netmask = "255.255.255.0";
    inet_aton(routers_[0]->interfaces[0]->str_address.c_str(),
              &routers_[0]->interfaces[0]->in_addr_address);
    inet_aton(routers_[0]->interfaces[0]->str_netmask.c_str(),
              &routers_[0]->interfaces[0]->in_addr_netmask);

    routers_[0]->interfaces[1]->index       = 1;
    routers_[0]->interfaces[1]->name        = "eth1";
    routers_[0]->interfaces[1]->str_address = "10.0.2.2";
    routers_[0]->interfaces[1]->str_netmask = "255.255.255.0";
    inet_aton(routers_[0]->interfaces[1]->str_address.c_str(),
              &routers_[0]->interfaces[1]->in_addr_address);
    inet_aton(routers_[0]->interfaces[1]->str_netmask.c_str(),
              &routers_[0]->interfaces[1]->in_addr_netmask);

    routers_[1]->interfaces.push_back(new interface_t);
    routers_[1]->interfaces.push_back(new interface_t);
    routers_[1]->interfaces.push_back(new interface_t);

    routers_[1]->interfaces[0]->index       = 0;
    routers_[1]->interfaces[0]->name        = "eth0";
    routers_[1]->interfaces[0]->str_address = "10.0.0.2";
    routers_[1]->interfaces[0]->str_netmask = "255.255.255.0";
    inet_aton(routers_[1]->interfaces[0]->str_address.c_str(),
              &routers_[1]->interfaces[0]->in_addr_address);
    inet_aton(routers_[1]->interfaces[0]->str_netmask.c_str(),
              &routers_[1]->interfaces[0]->in_addr_netmask);

    routers_[1]->interfaces[1]->index       = 1;
    routers_[1]->interfaces[1]->name        = "eth1";
    routers_[1]->interfaces[1]->str_address = "10.0.1.1";
    routers_[1]->interfaces[1]->str_netmask = "255.255.255.0";
    inet_aton(routers_[1]->interfaces[1]->str_address.c_str(),
              &routers_[1]->interfaces[1]->in_addr_address);
    inet_aton(routers_[1]->interfaces[1]->str_netmask.c_str(),
              &routers_[1]->interfaces[1]->in_addr_netmask);

    routers_[1]->interfaces[2]->index       = 2;
    routers_[1]->interfaces[2]->name        = "eth2";
    routers_[1]->interfaces[2]->str_address = "192.168.1.254";
    routers_[1]->interfaces[2]->str_netmask = "255.255.255.0";
    inet_aton(routers_[1]->interfaces[2]->str_address.c_str(),
              &routers_[1]->interfaces[2]->in_addr_address);
    inet_aton(routers_[1]->interfaces[2]->str_netmask.c_str(),
              &routers_[1]->interfaces[2]->in_addr_netmask);

    routers_[2]->interfaces.push_back(new interface_t);
    routers_[2]->interfaces.push_back(new interface_t);
    routers_[2]->interfaces.push_back(new interface_t);

    routers_[2]->interfaces[0]->index       = 0;
    routers_[2]->interfaces[0]->name        = "eth0";
    routers_[2]->interfaces[0]->str_address = "10.0.1.2";
    routers_[2]->interfaces[0]->str_netmask = "255.255.255.0";
    inet_aton(routers_[2]->interfaces[0]->str_address.c_str(),
              &routers_[2]->interfaces[0]->in_addr_address);
    inet_aton(routers_[2]->interfaces[0]->str_netmask.c_str(),
              &routers_[2]->interfaces[0]->in_addr_netmask);

    routers_[2]->interfaces[1]->index       = 1;
    routers_[2]->interfaces[1]->name        = "eth1";
    routers_[2]->interfaces[1]->str_address = "10.0.2.1";
    routers_[2]->interfaces[1]->str_netmask = "255.255.255.0";
    inet_aton(routers_[2]->interfaces[1]->str_address.c_str(),
              &routers_[2]->interfaces[1]->in_addr_address);
    inet_aton(routers_[2]->interfaces[1]->str_netmask.c_str(),
              &routers_[2]->interfaces[1]->in_addr_netmask);

    routers_[2]->interfaces[2]->index       = 2;
    routers_[2]->interfaces[2]->name        = "eth2";
    routers_[2]->interfaces[2]->str_address = "192.168.2.254";
    routers_[2]->interfaces[2]->str_netmask = "255.255.255.0";
    inet_aton(routers_[2]->interfaces[2]->str_address.c_str(),
              &routers_[2]->interfaces[2]->in_addr_address);
    inet_aton(routers_[2]->interfaces[2]->str_netmask.c_str(),
              &routers_[2]->interfaces[2]->in_addr_netmask);

    // server interfaces
    servers_[0]->interfaces.push_back(new interface_t);

    servers_[0]->interfaces[0]->index       = 0;
    servers_[0]->interfaces[0]->name        = "eth0";
    servers_[0]->interfaces[0]->str_address = "192.168.1.1";
    servers_[0]->interfaces[0]->str_netmask = "255.255.255.0";
    inet_aton(servers_[0]->interfaces[0]->str_address.c_str(),
              &servers_[0]->interfaces[0]->in_addr_address);
    inet_aton(servers_[0]->interfaces[0]->str_netmask.c_str(),
              &servers_[0]->interfaces[0]->in_addr_netmask);

    servers_[1]->interfaces.push_back(new interface_t);

    servers_[1]->interfaces[0]->index       = 0;
    servers_[1]->interfaces[0]->name        = "eth0";
    servers_[1]->interfaces[0]->str_address = "192.168.2.1";
    servers_[1]->interfaces[0]->str_netmask = "255.255.255.0";
    inet_aton(servers_[1]->interfaces[0]->str_address.c_str(),
              &servers_[1]->interfaces[0]->in_addr_address);
    inet_aton(servers_[1]->interfaces[0]->str_netmask.c_str(),
              &servers_[1]->interfaces[0]->in_addr_netmask);

    // {router_id, interface_id}, {router_id, interface_id}
    // id_link.push_back({0, 0});
    // id_link.push_back({1, 0});
    template_router_link_.push_back({{"router0", 0},
                                     {"router0_iface", 0},
                                     {"router1", 1},
                                     {"router1_iface", 0}});

    template_router_link_.push_back({{"router0", 0},
                                     {"router0_iface", 1},
                                     {"router1", 2},
                                     {"router1_iface", 0}});

    template_router_link_.push_back({{"router0", 2},
                                     {"router0_iface", 1},
                                     {"router1", 1},
                                     {"router1_iface", 1}});

    // {server_id, interface_id}, {router_id, interface_id}
    template_server_link_.push_back({{"server", 0},
                                     {"server_iface", 0},
                                     {"router", 1},
                                     {"router_iface", 2}});

    template_server_link_.push_back({{"server", 1},
                                     {"server_iface", 0},
                                     {"router", 2},
                                     {"router_iface", 2}});

    dprintf("template_router_link size = %lu", template_router_link_.size());
    dprintf("template_server_link size = %lu", template_server_link_.size());

    router_link_ = template_router_link_;
    server_link_ = template_server_link_;
}

void routing::init_table() {
    for (auto x : routers_) {
        for (auto y : x->interfaces) {
            x->routing_table.push_back(new table_t);
            x->routing_table[x->routing_table.size() - 1]->net.s_addr =
                y->in_addr_address.s_addr & y->in_addr_netmask.s_addr;
            x->routing_table[x->routing_table.size() - 1]->mask.s_addr =
                y->in_addr_netmask.s_addr;
            x->routing_table[x->routing_table.size() - 1]->interface_i =
                y->index;
            x->routing_table[x->routing_table.size() - 1]->src.s_addr =
                y->in_addr_address.s_addr;
        }
    }

    table_t *table    = new table_t();
    table->net.s_addr = servers_[1]->interfaces[0]->in_addr_address.s_addr &
                        servers_[1]->interfaces[0]->in_addr_netmask.s_addr;
    table->mask        = servers_[0]->interfaces[0]->in_addr_netmask;
    table->src         = servers_[0]->interfaces[0]->in_addr_address;
    table->interface_i = 1;
    table->is_gateway  = 0;

    routers_[1]->routing_table.push_back(table);

    table             = new table_t();
    table->net.s_addr = servers_[0]->interfaces[0]->in_addr_address.s_addr &
                        servers_[0]->interfaces[0]->in_addr_netmask.s_addr;
    table->mask        = servers_[1]->interfaces[0]->in_addr_netmask;
    table->src         = servers_[1]->interfaces[0]->in_addr_address;
    table->interface_i = 2;
    table->is_gateway  = 0;

    routers_[1]->routing_table.push_back(table);

    //
    table             = new table_t();
    table->net.s_addr = servers_[0]->interfaces[0]->in_addr_address.s_addr &
                        servers_[0]->interfaces[0]->in_addr_netmask.s_addr;
    table->mask        = servers_[1]->interfaces[0]->in_addr_netmask;
    table->src         = servers_[1]->interfaces[0]->in_addr_address;
    table->interface_i = 1;
    table->is_gateway  = 0;

    routers_[2]->routing_table.push_back(table);

    table             = new table_t();
    table->net.s_addr = servers_[1]->interfaces[0]->in_addr_address.s_addr &
                        servers_[1]->interfaces[0]->in_addr_netmask.s_addr;
    table->mask        = servers_[0]->interfaces[0]->in_addr_netmask;
    table->src         = servers_[0]->interfaces[0]->in_addr_address;
    table->interface_i = 2;
    table->is_gateway  = 0;

    routers_[2]->routing_table.push_back(table);

    for (auto x : servers_) {
        for (auto y : x->interfaces) {
            // default gateway
            x->routing_table.push_back(new table_t);
            x->routing_table[x->routing_table.size() - 1]->is_gateway  = 1;
            x->routing_table[x->routing_table.size() - 1]->net.s_addr  = 0;
            x->routing_table[x->routing_table.size() - 1]->mask.s_addr = 0;
            x->routing_table[x->routing_table.size() - 1]->interface_i =
                y->index;

            //
            x->routing_table.push_back(new table_t);
            x->routing_table[x->routing_table.size() - 1]->net.s_addr =
                y->in_addr_address.s_addr & y->in_addr_netmask.s_addr;
            x->routing_table[x->routing_table.size() - 1]->mask.s_addr =
                y->in_addr_netmask.s_addr;
            x->routing_table[x->routing_table.size() - 1]->interface_i =
                y->index;
            x->routing_table[x->routing_table.size() - 1]->src.s_addr =
                y->in_addr_address.s_addr;
            x->routing_table[x->routing_table.size() - 1]->is_gateway = 0;
        }
    }

    servers_[0]->routing_table[0]->gateway =
        routers_[1]->interfaces[2]->in_addr_address;
    servers_[1]->routing_table[0]->gateway =
        routers_[2]->interfaces[2]->in_addr_address;

    for (auto x : routers_) {
        for (auto y : x->routing_table) {
            char net[INET_ADDRSTRLEN];
            char src[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &y->net, net, INET_ADDRSTRLEN);
            inet_ntop(AF_INET, &y->src, src, INET_ADDRSTRLEN);
            dprintf("%s: %s/%d dev %s src %s",
                    x->name.c_str(),
                    net,
                    _netmask_len(y->mask),
                    x->interfaces[INDEX(y->interface_i)]->name.c_str(),
                    src);
        }
    }
    for (auto x : servers_) {
        for (auto y : x->routing_table) {
            char net[INET_ADDRSTRLEN];
            char src[INET_ADDRSTRLEN];
            char gateway[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &y->net, net, INET_ADDRSTRLEN);
            inet_ntop(AF_INET, &y->src, src, INET_ADDRSTRLEN);
            if (!y->is_gateway) {
                dprintf("%s: %s/%d dev %s src %s",
                        x->name.c_str(),
                        net,
                        _netmask_len(y->mask),
                        x->interfaces[INDEX(y->interface_i)]->name.c_str(),
                        src);
            } else {
                inet_ntop(AF_INET, &y->gateway, gateway, INET_ADDRSTRLEN);
                dprintf("%s: default via %s dev %s",
                        x->name.c_str(),
                        gateway,
                        x->interfaces[INDEX(y->interface_i)]->name.c_str());
            }
        }
        // char net[INET_ADDRSTRLEN];
        // char gateway[INET_ADDRSTRLEN];
        // inet_ntop(AF_INET, &x->routing_table[0]->net, net,
        // INET_ADDRSTRLEN); inet_ntop(
        //     AF_INET, &x->routing_table[0]->gateway, gateway,
        //     INET_ADDRSTRLEN);
        // dprintf("%s: %s %s %s %s",
        //         x->name.c_str(),
        //         x->interfaces[INDEX(x->routing_table[0]->interface_i)]
        //             ->name.c_str(),
        //         net,
        //         inet_ntoa(x->routing_table[0]->mask),
        //         gateway);
    }
}

void routing::init_image(const std::string *resource_path,
                         int display_width,
                         int display_height) {
    int base_x, base_y, base_w, base_h;
    int router_w, router_h;
    int server_w, server_h;
    int packet_w, packet_h;

    base_x = display_width / 14;
    base_y = display_height / 9;
    base_w = display_width / 4;
    base_h = INT(base_w * FLOAT(sin(60 * M_PI / 180.0)));

    router_w = display_width / 15;
    router_h = router_w;

    server_w = router_w;
    server_h = server_w;

    packet_w = display_width / 30;
    packet_h = display_height / 40;

    packet_w_ = packet_w;
    packet_h_ = packet_h;

    std::vector<point *> template_router_point;

    template_router_point.push_back(
        new point(FLOAT(base_x + (base_w / 2.0)), base_y));

    template_router_point.push_back(new point(base_x, base_y + base_h));

    template_router_point.push_back(
        new point(base_x + base_w, base_y + base_h));

    std::string path = *resource_path + "/router.png";
    dprintf("%s", path.c_str());

    for (auto x : routers_) {
        x->bmp = new bitmap();
        x->bmp->load(&path);
        x->bmp->resize(router_w, router_h);
        x->bmp->move(*template_router_point[INDEX(x->index)]);
    }

    std::vector<point *> template_server_point;

    template_server_point.push_back(new point(
        template_router_point[INDEX(template_server_link_[0]["router"])]->x(),
        template_router_point[INDEX(template_server_link_[0]["router"])]
                ->y() +
            FLOAT(base_h * 0.8)));

    template_server_point.push_back(new point(
        template_router_point[INDEX(template_server_link_[1]["router"])]->x(),
        template_router_point[INDEX(template_server_link_[1]["router"])]
                ->y() +
            FLOAT(base_h * 0.8)));

    path = *resource_path + "/server.png";
    // dprintf("%s", path.c_str());

    for (auto x : servers_) {
        x->bmp = new bitmap();
        x->bmp->load(&path);
        x->bmp->resize(server_w, server_h);
        x->bmp->move(*template_server_point[INDEX(x->index)]);
    }

    path = *resource_path + "/packet.png";

    packet_resource_path_ = path;

    // dprintf("%s", path.c_str());
}

void routing::init_text(const std::string *resource_path) {

    if (!al_init_font_addon()) throw "Failed to initialize font addon";
    if (!al_init_ttf_addon()) throw "Failed to initialize ttf addon";

    std::string fpath = *resource_path + "/Ricty-Regular.ttf";

    text_.font_size = 16;
    text_.font      = al_load_ttf_font(
        fpath.c_str(), text_.font_size, ALLEGRO_TTF_NO_KERNING);
    if (text_.font == nullptr) throw "Failed to load ttf font";

    text_.ustr     = al_ustr_new("");
    text_.ustr_pos = 0;

    text_.font_height = al_get_font_line_height(text_.font);
    text_.font_width  = al_get_text_width(text_.font, "A");
}

void routing::draw_topology() {
    draw_path();
    draw_node();
    draw_name();
    draw_packet();
}

void routing::draw_path() {
    point src, dst;
    std::string line;
    point draw_point;

    for (auto x : router_link_) {
        src = routers_[INDEX(x["router0"])]->bmp->object_destination();
        dst = routers_[INDEX(x["router1"])]->bmp->object_destination();
        al_draw_line(src.x(),
                     src.y(),
                     dst.x(),
                     dst.y(),
                     al_map_rgb(0xb3, 0xda, 0xff),
                     20);

        line = routers_[INDEX(x["router0"])]
                   ->interfaces[INDEX(x["router0_iface"])]
                   ->name;

        draw_point = dst - src;
        text_.ustr = al_ustr_new(line.c_str());

        al_draw_ustr(text_.font,
                     al_map_rgb(80, 80, 80),
                     src.x() + draw_point.x() / 5,
                     src.y() + draw_point.y() / 5,
                     ALLEGRO_ALIGN_CENTER,
                     text_.ustr);

        line = routers_[INDEX(x["router1"])]
                   ->interfaces[INDEX(x["router1_iface"])]
                   ->name;

        draw_point = src - dst;
        text_.ustr = al_ustr_new(line.c_str());

        al_draw_ustr(text_.font,
                     al_map_rgb(80, 80, 80),
                     dst.x() + draw_point.x() / 5,
                     dst.y() + draw_point.y() / 5,
                     ALLEGRO_ALIGN_CENTER,
                     text_.ustr);
    }

    for (auto x : server_link_) {
        src = servers_[INDEX(x["server"])]->bmp->object_destination();
        dst = routers_[INDEX(x["router"])]->bmp->object_destination();

        al_draw_line(src.x(),
                     src.y(),
                     dst.x(),
                     dst.y(),
                     al_map_rgb(0xb3, 0xda, 0xff),
                     20);

        line = servers_[INDEX(x["server"])]
                   ->interfaces[INDEX(x["server_iface"])]
                   ->name;

        draw_point = dst - src;
        text_.ustr = al_ustr_new(line.c_str());

        al_draw_ustr(text_.font,
                     al_map_rgb(80, 80, 80),
                     src.x() + draw_point.x() / 4,
                     src.y() + draw_point.y() / 4,
                     ALLEGRO_ALIGN_CENTER,
                     text_.ustr);

        line = routers_[INDEX(x["router"])]
                   ->interfaces[INDEX(x["router_iface"])]
                   ->name;

        draw_point = src - dst;
        text_.ustr = al_ustr_new(line.c_str());

        al_draw_ustr(text_.font,
                     al_map_rgb(80, 80, 80),
                     dst.x() + draw_point.x() / 4,
                     dst.y() + draw_point.y() / 4,
                     ALLEGRO_ALIGN_CENTER,
                     text_.ustr);
    }
}

void routing::draw_node() {
    for (auto *x : routers_) {
        // x->bmp->rotate(60);
        x->bmp->draw();
    }
    for (auto *x : servers_) {
        // x->bmp->rotate(60);
        x->bmp->draw();
    }
}

void routing::draw_name() {

    std::string line;
    int width_margin  = 10;
    int height_margin = 10;
    int height_offset = 1;

    char net[INET_ADDRSTRLEN];
    char src[INET_ADDRSTRLEN];
    char gateway[INET_ADDRSTRLEN];

    for (auto x : routers_) {
        line = x->name + "\n";
        for (auto y : x->routing_table) {
            inet_ntop(AF_INET, &y->net, net, INET_ADDRSTRLEN);
            inet_ntop(AF_INET, &y->src, src, INET_ADDRSTRLEN);

            line += std::string(net) + "/" +
                    std::to_string(_netmask_len(y->mask)) + " dev " +
                    x->interfaces[INDEX(y->interface_i)]->name + " src " +
                    std::string(src) + "\n";
        }

        text_.ustr = al_ustr_new(line.c_str());
        al_draw_multiline_ustr(
            text_.font,
            al_map_rgb(40, 40, 40),
            x->bmp->upper_right_point().x() + width_margin,
            x->bmp->object_destination().y() + height_margin,
            al_get_text_width(text_.font, "A") * 50,
            0,
            0,
            text_.ustr);
        height_offset++;
    }

    height_offset = 1;
    for (auto x : servers_) {
        line = x->name + "\n";
        for (auto y : x->routing_table) {
            inet_ntop(AF_INET, &y->net, net, INET_ADDRSTRLEN);
            inet_ntop(AF_INET, &y->src, src, INET_ADDRSTRLEN);
            if (!y->is_gateway) {
                line += std::string(net) + "/" +
                        std::to_string(_netmask_len(y->mask)) + " dev " +
                        x->interfaces[INDEX(y->interface_i)]->name + " src " +
                        std::string(src) + "\n";
            } else {
                inet_ntop(AF_INET, &y->gateway, gateway, INET_ADDRSTRLEN);
                line += "default via " + std::string(gateway) + " dev " +
                        x->interfaces[INDEX(y->interface_i)]->name + "\n";
            }
        }

        text_.ustr = al_ustr_new(line.c_str());
        al_draw_multiline_ustr(
            text_.font,
            al_map_rgb(40, 40, 40),
            x->bmp->upper_right_point().x() + width_margin,
            x->bmp->object_destination().y() + height_margin,
            al_get_text_width(text_.font, "A") * 50,
            0,
            0,

            text_.ustr);
        height_offset++;
    }
}

void routing::draw_packet() {
    for (auto &&x : packets_) {
        x->bmp->draw();
    }
}

int routing::move_packet(float speed) {
    if (!is_packets) {
        return ERROR;
    }
    flow_t flow;
    point vec, normal;

    std::vector<int> delete_list;
    int idx = 0;
    for (auto &&p : packets_) {
        flow = route(p);

        if (flow.is_moved) {
            p->is_moving = 1;

            normal = point(flow.vector.x() / flow.vector.magnitude(),
                           flow.vector.y() / flow.vector.magnitude());

            vec = servers_[p->server_id]->bmp->object_destination() -
                  point(normal.x() * speed, normal.y() * speed);

            vec.print();
            p->bmp->move(vec);
        }

        if (flow.is_delete) {
            p->bmp->destroy();
            delete_list.push_back(idx);
        }

        idx++;
    }

    for (auto &&i : delete_list) {
        packets_.erase(packets_.begin() + i);
    }

    return SUCCESS;
}

int routing::add_packet() {
    is_packets = 1;

    packet_t *p = new packet();

    p->bmp = new bitmap();
    p->bmp->load(&packet_resource_path_);
    p->bmp->resize(packet_w_, packet_h_);
    p->bmp->move(point());

    int src_id, dst_id;

    src_id = rand() % 2;
    dst_id = (src_id + 1) % 2;

    src_id = 0;
    dst_id = 1;

    p->data.src = servers_[src_id]->interfaces[0]->in_addr_address;
    p->data.dst = servers_[dst_id]->interfaces[0]->in_addr_address;

    p->server_id  = src_id;
    p->is_arrived = 1;
    p->is_moving  = 0;

    packets_.push_back(p);

    dprintf("src_id=%d", src_id);

    return SUCCESS;
}

flow_t routing::route(packet_t *packet) {
    flow_t ret;

    if (packet->is_arrived) {

        /// TODO routing program

        // struct in_addr src = packet->data.src;
        // struct in_addr dst = packet->data.dst;

        // for (auto &&table : servers_[packet->server_id]->routing_table) {
        // }
        routers_[1]->bmp->print();
        servers_[packet->server_id]->bmp->print();

        ret.vector = routers_[1]->bmp->object_destination() -
                     servers_[packet->server_id]->bmp->object_destination();

        float angle;
        if (FLT_EPSILON < fabs(ret.vector.x()) ||
            FLT_EPSILON < fabs(ret.vector.y())) {
            angle = acos(ret.vector.x() / ret.vector.magnitude());
            angle = angle * 180.0 / PI;
            if (ret.vector.y() < 0) {
                angle = 360.0 - angle;
            }
        } else {
            angle = 0.0;
        }

        packet->bmp->rotate(angle);

        dprintf("x=%.2f y=%.2f angle=%.2f",
                ret.vector.x(),
                ret.vector.y(),
                angle);

        packet->is_arrived = 0;
        ret.is_moved       = 1;
        ret.is_delete      = 0;
    }
    return ret;
}
