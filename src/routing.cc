#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <message.hh>
#include <routing.hh>
#include <point.hh>
#include <bitmap.hh>
#include <text.hh>

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
    routers_[0]->interfaces[0]->str_address = "192.168.10.1";
    routers_[0]->interfaces[0]->str_netmask = "255.255.255.0";
    inet_aton(routers_[0]->interfaces[0]->str_address.c_str(),
              &routers_[0]->interfaces[0]->in_addr_address);
    inet_aton(routers_[0]->interfaces[0]->str_netmask.c_str(),
              &routers_[0]->interfaces[0]->in_addr_netmask);

    routers_[0]->interfaces[1]->index       = 1;
    routers_[0]->interfaces[1]->name        = "eth1";
    routers_[0]->interfaces[1]->str_address = "192.168.20.1";
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
    routers_[1]->interfaces[0]->str_address = "192.168.10.2";
    routers_[1]->interfaces[0]->str_netmask = "255.255.255.0";
    inet_aton(routers_[1]->interfaces[0]->str_address.c_str(),
              &routers_[1]->interfaces[0]->in_addr_address);
    inet_aton(routers_[1]->interfaces[0]->str_netmask.c_str(),
              &routers_[1]->interfaces[0]->in_addr_netmask);

    routers_[1]->interfaces[1]->index       = 1;
    routers_[1]->interfaces[1]->name        = "eth1";
    routers_[1]->interfaces[1]->str_address = "192.168.30.1";
    routers_[1]->interfaces[1]->str_netmask = "255.255.255.0";
    inet_aton(routers_[1]->interfaces[1]->str_address.c_str(),
              &routers_[1]->interfaces[1]->in_addr_address);
    inet_aton(routers_[1]->interfaces[1]->str_netmask.c_str(),
              &routers_[1]->interfaces[1]->in_addr_netmask);

    routers_[1]->interfaces[2]->index       = 2;
    routers_[1]->interfaces[2]->name        = "eth1";
    routers_[1]->interfaces[2]->str_address = "192.168.0.1";
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
    routers_[2]->interfaces[0]->str_address = "192.168.20.2";
    routers_[2]->interfaces[0]->str_netmask = "255.255.255.0";
    inet_aton(routers_[2]->interfaces[0]->str_address.c_str(),
              &routers_[2]->interfaces[0]->in_addr_address);
    inet_aton(routers_[2]->interfaces[0]->str_netmask.c_str(),
              &routers_[2]->interfaces[0]->in_addr_netmask);

    routers_[2]->interfaces[1]->index       = 1;
    routers_[2]->interfaces[1]->name        = "eth1";
    routers_[2]->interfaces[1]->str_address = "192.168.30.2";
    routers_[2]->interfaces[1]->str_netmask = "255.255.255.0";
    inet_aton(routers_[2]->interfaces[1]->str_address.c_str(),
              &routers_[2]->interfaces[1]->in_addr_address);
    inet_aton(routers_[2]->interfaces[1]->str_netmask.c_str(),
              &routers_[2]->interfaces[1]->in_addr_netmask);

    routers_[2]->interfaces[2]->index       = 2;
    routers_[2]->interfaces[2]->name        = "eth2";
    routers_[2]->interfaces[2]->str_address = "192.168.1.1";
    routers_[2]->interfaces[2]->str_netmask = "255.255.255.0";
    inet_aton(routers_[2]->interfaces[2]->str_address.c_str(),
              &routers_[2]->interfaces[2]->in_addr_address);
    inet_aton(routers_[2]->interfaces[2]->str_netmask.c_str(),
              &routers_[2]->interfaces[2]->in_addr_netmask);

    // server interfaces
    servers_[0]->interfaces.push_back(new interface_t);

    servers_[0]->interfaces[0]->index       = 0;
    servers_[0]->interfaces[0]->name        = "eth0";
    servers_[0]->interfaces[0]->str_address = "192.168.0.2";
    servers_[0]->interfaces[0]->str_netmask = "255.255.255.0";
    inet_aton(servers_[0]->interfaces[0]->str_address.c_str(),
              &servers_[0]->interfaces[0]->in_addr_address);
    inet_aton(servers_[0]->interfaces[0]->str_netmask.c_str(),
              &servers_[0]->interfaces[0]->in_addr_netmask);

    servers_[1]->interfaces.push_back(new interface_t);

    servers_[1]->interfaces[0]->index       = 0;
    servers_[1]->interfaces[0]->name        = "eth0";
    servers_[1]->interfaces[0]->str_address = "192.168.1.2";
    servers_[1]->interfaces[0]->str_netmask = "255.255.255.0";
    inet_aton(servers_[1]->interfaces[0]->str_address.c_str(),
              &servers_[1]->interfaces[0]->in_addr_address);
    inet_aton(servers_[1]->interfaces[0]->str_netmask.c_str(),
              &servers_[1]->interfaces[0]->in_addr_netmask);

    // {router_id, router_id}
    template_router_link_.push_back({0, 1});
    template_router_link_.push_back({0, 2});
    template_router_link_.push_back({1, 2});

    dprintf("template_router_link size = %lu", template_router_link_.size());
    dprintf("template_server_link size = %lu", template_server_link_.size());

    // {server_id, router_id}
    template_server_link_.push_back({0, 1});
    template_server_link_.push_back({1, 2});

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
        }
    }

    for (auto x : servers_) {
        for (auto y : x->interfaces) {
            x->routing_table.push_back(new table_t);
            x->routing_table[x->routing_table.size() - 1]->net.s_addr =
                y->in_addr_address.s_addr & y->in_addr_netmask.s_addr;
            x->routing_table[x->routing_table.size() - 1]->mask.s_addr =
                y->in_addr_netmask.s_addr;
            x->routing_table[x->routing_table.size() - 1]->interface_i =
                y->index;

            // default gateway
            x->routing_table.push_back(new table_t);
            x->routing_table[x->routing_table.size() - 1]->net.s_addr  = 0;
            x->routing_table[x->routing_table.size() - 1]->mask.s_addr = 0;
            x->routing_table[x->routing_table.size() - 1]->interface_i =
                y->index;
        }
    }

    servers_[0]->routing_table[1]->gateway =
        routers_[1]->interfaces[2]->in_addr_address;
    servers_[1]->routing_table[1]->gateway =
        routers_[2]->interfaces[2]->in_addr_address;

    for (auto x : routers_) {
        for (auto y : x->routing_table) {
            char net[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &y->net, net, INET_ADDRSTRLEN);
            dprintf("%s: %s %s %s",
                    x->name.c_str(),
                    x->interfaces[y->interface_i]->name.c_str(),
                    net,
                    inet_ntoa(y->mask));
        }
    }
    for (auto x : servers_) {
        for (auto y : x->routing_table) {
            char net[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &y->net, net, INET_ADDRSTRLEN);
            dprintf("%s: %s %s %s",
                    x->name.c_str(),
                    x->interfaces[y->interface_i]->name.c_str(),
                    net,
                    inet_ntoa(y->mask));
        }
        char net[INET_ADDRSTRLEN];
        char gateway[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &x->routing_table[1]->net, net, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &x->routing_table[1]->gateway, gateway, INET_ADDRSTRLEN);
        dprintf("%s: %s %s %s %s",
                x->name.c_str(),
                x->interfaces[x->routing_table[1]->interface_i]->name.c_str(),
                net,
                inet_ntoa(x->routing_table[1]->mask),
                gateway);
    }
}

void routing::init_image(const std::string *resource_path,
                         int display_width,
                         int display_height) {
    int base_x, base_y, base_w, base_h;
    int router_w, router_h;
    int server_w, server_h;
    int packet_w, packet_h;

    base_x = display_width / 15;
    base_y = display_height / 10;
    base_w = display_width / 5;
    base_h = base_w * sin(60 * M_PI / 180.0);

    router_w = display_width / 15;
    router_h = router_w;

    server_w = router_w;
    server_h = server_w;

    packet_w = display_width / 10;
    packet_h = packet_w / 7;

    std::vector<point *> template_router_point;

    template_router_point.push_back(
        new point(base_x + (base_w / 2.0), base_y));

    template_router_point.push_back(new point(base_x, base_y + base_h));

    template_router_point.push_back(
        new point(base_x + base_w, base_y + base_h));

    std::string path = *resource_path + "/router.png";
    dprintf("%s", path.c_str());

    for (auto x : routers_) {
        x->bmp = new bitmap();
        x->bmp->load(&path);
        x->bmp->resize(router_w, router_h);
        x->bmp->move(*template_router_point[x->index]);
    }

    std::vector<point *> template_server_point;

    template_server_point.push_back(
        new point(template_router_point[template_server_link_[0][1]]->x(),
                  template_router_point[template_server_link_[0][1]]->y() +
                      base_h * 0.8));

    template_server_point.push_back(
        new point(template_router_point[template_server_link_[1][1]]->x(),
                  template_router_point[template_server_link_[1][1]]->y() +
                      base_h * 0.8));

    path = *resource_path + "/server.png";
    dprintf("%s", path.c_str());

    for (auto x : servers_) {
        x->bmp = new bitmap();
        x->bmp->load(&path);
        x->bmp->resize(server_w, server_h);
        x->bmp->move(*template_server_point[x->index]);
    }

    path = *resource_path + "/packet.png";
    dprintf("%s", path.c_str());

    packet_.bmp = new bitmap();
    packet_.bmp->load(&path);
    packet_.bmp->resize(packet_w, packet_h);
}

void routing::init_text(const std::string *resource_path) {

    std::string fpath = *resource_path + "/Ricty-Regular.ttf";

    text_.font_size = 24;
    text_.font      = al_load_ttf_font(
        fpath.c_str(), text_.font_size, ALLEGRO_TTF_NO_KERNING);
    if (text_.font == nullptr) throw "Failed to load ttf font";

    text_.ustr = al_ustr_new("");

    text_.font_height = al_get_font_line_height(text_.font);
    text_.font_width  = al_get_text_width(text_.font, "A");
}

void routing::draw_topology() {
    draw_path();
    draw_node();
    draw_name();
}

void routing::draw_path() {
    for (auto x : router_link_) {
        al_draw_line(routers_[x[0]]->bmp->object_destination().x(),
                     routers_[x[0]]->bmp->object_destination().y(),
                     routers_[x[1]]->bmp->object_destination().x(),
                     routers_[x[1]]->bmp->object_destination().y(),
                     al_map_rgb(0xb3, 0xda, 0xff),
                     20);
    }

    // for (int i = 0; i < server_link_.size(); i++) {

    for (auto x : server_link_) {
        al_draw_line(servers_[x[0]]->bmp->object_destination().x(),
                     servers_[x[0]]->bmp->object_destination().y(),
                     routers_[x[1]]->bmp->object_destination().x(),
                     routers_[x[1]]->bmp->object_destination().y(),
                     al_map_rgb(0xb3, 0xda, 0xff),
                     20);
    }
}

void routing::draw_node() {
    for (auto *x : routers_) {
        x->bmp->draw();
    }
    for (auto *x : servers_) {
        x->bmp->draw();
    }
}

void routing::draw_name() {
    ALLEGRO_USTR *name;
    ALLEGRO_USTR *address;
    ALLEGRO_USTR *netmask;

    for (auto x : routers_) {
        name = al_ustr_new(x->name.c_str());
        al_draw_ustr(text_.font,
                     al_map_rgb(80, 80, 80),
                     x->bmp->upper_right_point().x(),
                     x->bmp->upper_right_point().y(),
                     0,
                     name);

        address = al_ustr_new(x->interfaces[0]->str_address.c_str());
        al_draw_ustr(text_.font,
                     al_map_rgb(80, 80, 80),
                     x->bmp->upper_right_point().x(),
                     x->bmp->upper_right_point().y() + text_.font_height,
                     0,
                     address);

        address = al_ustr_new(x->interfaces[1]->str_address.c_str());
        al_draw_ustr(text_.font,
                     al_map_rgb(80, 80, 80),
                     x->bmp->upper_right_point().x(),
                     x->bmp->upper_right_point().y() + text_.font_height * 2,
                     0,
                     address);
    }
    for (auto x : servers_) {
        name = al_ustr_new(x->name.c_str());
        al_draw_ustr(text_.font,
                     al_map_rgb(80, 80, 80),
                     x->bmp->upper_right_point().x(),
                     x->bmp->upper_right_point().y(),
                     0,
                     name);
    }
}

void routing::move_packet() {
}
