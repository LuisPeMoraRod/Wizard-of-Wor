#ifndef MAPS_H
#define MAPS_H

#include "graphics.h"
#include "game.h"

struct block{
    int pos_x, pos_y;
    SDL_Rect rect;
    struct block *next_block;
};

void map0();
void map1();
void map2();
void set_map(int map_num);
struct block * new_block(int x, int y);
void add_block(struct block **new_block_pp);
void render_blocks(SDL_Renderer **renderer_pp);
void wall_left(int *x, int y, struct block ** block_pp, int blocks);
void wall_right(int *x, int y, struct block ** block_pp, int blocks);
void wall_up(int x, int *y, struct block ** block_pp, int blocks);
void wall_down(int x, int *y, struct block ** block_pp, int blocks);


#endif //MAPS_H