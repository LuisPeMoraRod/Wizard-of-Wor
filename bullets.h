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
void check_collision();
void delete_bullet(struct bullet **bullet_pp);
void render_bullets(SDL_Renderer **renderer_pp);
void free_bullets();
#endif //BULLET