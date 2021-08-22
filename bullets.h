#ifndef BULLET_H
#define BULLET_H

#include "game.h"
#include "graphics.h"

struct bullet{
    int pos_x, pos_y;
    SDL_Rect rect;
    int dir;
    struct bullet *next_bullet;
};

struct bullet *new_bullet(int x, int y, int dir, int width, int height);
void add_bullet(struct bullet **new_bullet_pp);
void shoot();
void update_bullets();
void move_bullet(struct bullet **bullet_pp);
void check_collisions(struct bullet **bullet_pp);
bool coll_bllt_wall(struct bullet **bullet_pp, struct block **block_pp);
bool coll_bllt_enemies(struct bullet **bullet_pp, struct enemy **enemy_pp);
bool coll_bllt_r(int x_bllt, int w_bllt, int x_obj, int w_obj);
bool coll_bllt_l(int x_bllt, int w_bllt, int x_obj, int w_obj);
bool coll_bllt_u(int y_bllt, int h_bllt, int y_obj, int h_obj);
bool coll_bllt_d(int y_bllt, int h_bllt, int y_obj, int h_obj);
void delete_bullet(struct bullet **bullet_pp);
void render_bullets(SDL_Renderer **renderer_pp);
void free_bullets();
#endif //BULLET