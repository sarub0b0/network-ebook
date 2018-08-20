#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include <float.h>

#include <global.hh>
#include <message.hh>
#include <point.hh>
#include <bitmap.hh>

bitmap::bitmap()
    : bitmap_(nullptr),
      name_(""),
      id_(-1),
      object_center_(point(0, 0)),
      object_dst_(point(0, 0)),
      actual_dst_(point(0, 0)),
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

    if ((original_bitmap_ = al_load_bitmap(resource_path->c_str())) == NULL)
        throw "Failed to load image";

    width_  = al_get_bitmap_width(bitmap_);
    height_ = al_get_bitmap_height(bitmap_);

    original_width_  = width_;
    original_height_ = height_;

    point center(width_ / 2.0f, height_ / 2.0f);
    object_center_ = center;
}

void bitmap::move(point dst) {
    object_dst_ = dst;
    actual_dst_ = object_dst_ - object_center_;
}

void bitmap::resize(int dst_w, int dst_h) {
    ALLEGRO_BITMAP *temp;
    if ((temp = scaled_bitmap(bitmap_, dst_w, dst_h)) == nullptr)
        throw "Failed to scaled bitmap";
    if (bitmap_ != nullptr) {
        al_destroy_bitmap(bitmap_);
    }
    bitmap_ = temp;

    if ((temp = scaled_bitmap(original_bitmap_, dst_w, dst_h)) == nullptr)
        throw "Failed to scaled bitmap";
    if (original_bitmap_ != nullptr) {
        al_destroy_bitmap(original_bitmap_);
    }
    original_bitmap_ = temp;

    width_  = al_get_bitmap_width(bitmap_);
    height_ = al_get_bitmap_height(bitmap_);

    original_width_  = width_;
    original_height_ = height_;

    point center(width_ / 2.0f, height_ / 2.0f);
    object_center_ = center;
}

void bitmap::rotate(float angle) {
    ALLEGRO_BITMAP *temp;
    if ((temp = rotated_bitmap(original_bitmap_, angle)) == nullptr)
        throw "Failed to rotate bitmap";
    if (bitmap_ != nullptr) {
        al_destroy_bitmap(bitmap_);
    }
    bitmap_ = temp;

    width_  = al_get_bitmap_width(bitmap_);
    height_ = al_get_bitmap_height(bitmap_);

    point center(width_ / 2.0f, height_ / 2.0f);
    object_center_ = center;
}

ALLEGRO_BITMAP *bitmap::rotated_bitmap(ALLEGRO_BITMAP *original_bmp,
                                       float angle) {
    ALLEGRO_BITMAP *rotated_bmp, *prev_target;

    // 1. create atemporary bitmap of size we want
    int w, h;

    w = original_width_;
    h = original_height_;

    angle_ += angle;

    if (angle_ < 0) {
        angle_ += 360;
    }

    if (360 < angle_) {
        angle_ -= 360;
    }

    rotated_bmp = al_create_bitmap(original_width_, original_width_);
    if (!rotated_bmp) return nullptr;

    // 2. load the bitmap at the original size
    // 3. set the target bitmap top the rotated bitmap
    float cx, cy, dx, dy;
    prev_target = al_get_target_bitmap();
    al_set_target_bitmap(rotated_bmp);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));

    cx = original_width_ / 2;
    cy = original_height_ / 2;

    dx = original_width_ / 2;
    dy = original_width_ / 2;

    // 4. copy the loaded bitmap to the rotated bitmap
    al_draw_rotated_bitmap(
        original_bmp, cx, cy, dx, dy, FLOAT(angle_ * ALLEGRO_PI / 180.0), 0);

    // 5. restore the previous target and clean up
    al_set_target_bitmap(prev_target);

    width_  = al_get_bitmap_width(bitmap_);
    height_ = al_get_bitmap_height(bitmap_);

    return rotated_bmp;
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

point bitmap::actual_destination() {
    return actual_dst_;
}

point bitmap::object_center() {
    return object_center_;
}
int bitmap::id() {
    return id_;
}

point bitmap::upper_right_point() {
    return actual_dst_ + point(width_, 0);
}

void bitmap::destroy() {
    al_destroy_bitmap(bitmap_);
    al_destroy_bitmap(original_bitmap_);
}
