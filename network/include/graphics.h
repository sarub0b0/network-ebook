#ifndef __GRAPHICS_H
#define __GRAPHICS_H

typedef struct ALLEGRO_BITMAP ALLEGRO_BITMAP;

typedef struct bitmap bitmap_t;

extern bitmap_t *router_bmps;
extern bitmap_t *path_bmps;
extern bitmap_t *packet_bmps;

extern ALLEGRO_BITMAP *router_al_bmp_ori;
extern ALLEGRO_BITMAP *path_al_bmp_ori;
extern ALLEGRO_BITMAP *packet_al_bmp_ori;

extern ALLEGRO_BITMAP **router_al_bmps;
extern ALLEGRO_BITMAP **path_al_bmps;
extern ALLEGRO_BITMAP **packet_al_bmps;

extern int SCREEN_W;
extern int SCREEN_H;

void init();
void loop();
void shutdown();

#endif
