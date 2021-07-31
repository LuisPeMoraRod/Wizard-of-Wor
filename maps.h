#ifndef MAPS_H
#define MAPS_H

#include "graphics.h"

struct block{
    int pos_x, pos_y;
    SDL_Rect rect;
    struct block *next_block;
};

#endif //MAPS_H