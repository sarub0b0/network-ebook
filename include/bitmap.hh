#ifndef BITMAP_H_
#define BITMAP_H_

#include <string>

#include <point.hh>

typedef struct ALLEGRO_BITMAP ALLEGRO_BITMAP;

class bitmap {
   private:
    ALLEGRO_BITMAP *bitmap_;
    ALLEGRO_BITMAP *original_bitmap_;
    std::string name_;
    int id_;
    point object_center_;
    point object_dst_;
    point actual_dst_;
    float angle_;
    int width_, height_;
    int original_width_, original_height_;
    int scale_x_, scale_y_;
    int flags_;

    ALLEGRO_BITMAP *rotated_bitmap(ALLEGRO_BITMAP *original_bmp, float angle);
    ALLEGRO_BITMAP *scaled_bitmap(ALLEGRO_BITMAP *original_bmp, int w, int h);

   public:
    bitmap();
    ~bitmap();

    void init();
    void changed_name(std::string name);
    void changed_id(int id);
    void load(const std::string *resource_path);
    void move(point dst);
    void resize(int dst_w, int dst_h);
    void rotate(float angle);
    point object_destination();
    point actual_destination();
    point object_center();
    point upper_right_point();
    int id();
    void draw();
    void print();

    void destroy();
};

#endif
