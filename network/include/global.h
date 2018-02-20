#ifndef __GLOBAL_H
#define __GLOBAL_H

#define MAX_STRLEN 255

#include <allegro5/allegro.h>

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;

extern ALLEGRO_BITMAP *router_bmp_ori;
extern ALLEGRO_BITMAP *path_bmp_ori;
extern ALLEGRO_BITMAP *packet_bmp_ori;

extern ALLEGRO_BITMAP **router_bmp;
extern ALLEGRO_BITMAP **path_bmp;
extern ALLEGRO_BITMAP **packet_bmp;

// extern float FPS;
// extern int SCREEN_W;
// extern int SCREEN_H;

// extern float SPEED;

#endif
