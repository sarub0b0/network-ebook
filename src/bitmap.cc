#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <message.hh>
#include <point.hh>
#include <bitmap.hh>

bitmap::bitmap()
    : bitmap_(nullptr),
      name_(""),
      id_(-1),
      object_center_(point()),
      object_dst_(point()),
      actual_dst_(point()),
      angle_(0.0),
      width_(0),
      height_(0),
      scale_x_(0),
      scale_y_(0),
      flags_(0) {
}

bitmap::~bitmap() {
}

void bitmap::init() {
    angle_   = 0.0;
    scale_x_ = 0;
    scale_y_ = 0;
    flags_   = 0;
}

void bitmap::changed_name(std::string name) {
    name_ = name;
}

void bitmap::changed_id(int id) {
    id_ = id;
}

void bitmap::load(const std::string *resource_path) {
    if ((bitmap_ = al_load_bitmap(resource_path->c_str())) == NULL)
        throw "Failed to load image";

    width_  = al_get_bitmap_width(bitmap_);
    height_ = al_get_bitmap_height(bitmap_);
    point c(width_ / 2.0f, height_ / 2.0f);
    object_center_ = c;
    actual_dst_    = object_dst_ - object_center_;
}

void bitmap::move(point dst) {
    object_dst_ = dst;
    actual_dst_ = object_dst_ - object_center_;
}

void bitmap::resize(int dst_w, int dst_h) {
    ALLEGRO_BITMAP *temp;
    if ((temp = scaled_bitmap(bitmap_, dst_w, dst_h)) == nullptr)
        throw "Failed to scaled bitmap";
    bitmap_ = temp;

    width_  = al_get_bitmap_width(bitmap_);
    height_ = al_get_bitmap_height(bitmap_);

    point c(width_ / 2.0f, height_ / 2.0f);
    object_center_ = c;
    object_dst_    = object_dst_ - object_center_;
}

void bitmap::rotate(float angle) {
    ALLEGRO_BITMAP *temp;
    if ((temp = rotated_bitmap()) == nullptr) throw "Failed to scaled bitmap";
    bitmap_ = temp;
}

ALLEGRO_BITMAP *bitmap::rotated_bitmap() {
    return nullptr;
    // ALLEGRO_BITMAP *rotated_bmp, *prev_target;

    // // 1. create atemporary bitmap of size we want
    // int w, h;

    // w = al_get_bitmap_width(original_bmp);
    // h = al_get_bitmap_height(original_bmp);

    // double rad;
    // double s, c;

    // if (angle < 0) {
    //     angle += 360;
    // }

    // rad = angle * M_PI / 180.0;

    // s = fabs(sin(rad));
    // c = fabs(cos(rad));

    // int r_w, r_h;
    // r_w = ceil((w * c) + (h * s));
    // r_h = ceil((w * s) + (h * c));

    // // dprintf("rotated_bmp w:%d h:%d\n", r_w, r_h);

    // rotated_bmp = al_create_bitmap(r_w, r_h);
    // // rotated_bmp = al_create_bitmap(600, 400);
    // if (!rotated_bmp) return ERROR;

    // // 2. load the bitmap at the original size
    // // if (!original_bmp) abort_game("Failed to load path.png");

    // float dx, dy;
    // dx = h * s / 2;
    // dy = h * c / 2;

    // if (90 < angle && angle <= 180) {
    //     dx += w * c;
    // } else if (180 < angle && angle <= 270) {
    //     dx += w * c;
    //     dy += w * s;
    // } else if (270 < angle && angle < 360) {
    //     dy += w * s;
    // }

    // // dprintf("rotated_bmp w:%d h:%d\n",
    // //         al_get_bitmap_width(rotated_bmp),
    // //         al_get_bitmap_height(rotated_bmp));

    // // 3. set the target bitmap top the rotated bitmap
    // prev_target = al_get_target_bitmap();
    // al_set_target_bitmap(rotated_bmp);
    // al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    // // al_clear_to_color(al_map_rgba(255, 255, 255, 0));
    // // al_draw_bitmap(rotated_bmp, 300, 0, 0);

    // // dprintf("rotated_bmp dx:%f dy:%f\n", dx, dy);

    // // 4. copy the loaded bitmap to the rotated bitmap

    // // al_draw_rotated_bitmap(original_bmp, c.x, c.y, c.x, c.y, angle, 0);
    // al_draw_rotated_bitmap(original_bmp, 0, h / 2, dx, dy, rad, 0);

    // // al_draw_rotated_bitmap(original_bmp,
    // //                        (SCREEN_W / 2.0),
    // //                        (SCREEN_H / 2.0),
    // //                        dx,
    // //                        dy,
    // //                        (angle * M_PI / 180.0),
    // //                        0);

    // // 5. restore the previous target and clean up
    // al_set_target_bitmap(prev_target);

    // opt->bmp   = rotated_bmp;
    // opt->dst.x = dx;
    // opt->dst.y = dy;
    // opt->w     = r_w;
    // opt->h     = r_h;

    // return SUCCESS;
}

ALLEGRO_BITMAP *bitmap::scaled_bitmap(ALLEGRO_BITMAP *original_bmp,
                                      int w,
                                      int h) {
    ALLEGRO_BITMAP *scaled_bmp, *prev_target;

    // 1. create atemporary bitmap of size we want
    scaled_bmp = al_create_bitmap(w, h);
    if (!scaled_bmp) return nullptr;

    // 2. load the bitmap at the original size

    // 3. set the target bitmap top the scaled bitmap
    prev_target = al_get_target_bitmap();
    al_set_target_bitmap(scaled_bmp);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));

    // 4. copy the loaded bitmap to the scaled bitmap
    al_draw_scaled_bitmap(original_bmp,
                          0,
                          0,
                          al_get_bitmap_width(original_bmp),
                          al_get_bitmap_height(original_bmp),
                          0,
                          0,
                          w,
                          h,
                          flags_);

    // 5. restore the previous target and clean up
    al_set_target_bitmap(prev_target);

    width_  = w;
    height_ = h;

    return scaled_bmp;
}

void bitmap::draw() {
    al_draw_bitmap(bitmap_, actual_dst_.x(), actual_dst_.y(), flags_);
}

void bitmap::print() {
    printf("id=%d name=%s width=%d height=%d x=%.2f y=%.2f\n",
           id_,
           name_.c_str(),
           width_,
           height_,
           actual_dst_.x(),
           actual_dst_.y());
}

point bitmap::object_destination() {
    return object_dst_;
}

int bitmap::id() {
    return id_;
}

point bitmap::upper_right_point() {
    return actual_dst_ + point(width_, 0);
}
