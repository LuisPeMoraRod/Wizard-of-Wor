#ifndef WARRIOR_H
#define WARRIOR_H

#include "graphics.h"
#include "game.h"

struct warrior{
    SDL_Rect pos;
    SDL_Texture *current_txtr;

    SDL_Texture *right0;
    SDL_Texture *right1;
    SDL_Texture *right2;
    SDL_Texture *right3;
    SDL_Texture *left0;
    SDL_Texture *left1;
    SDL_Texture *left2;
    SDL_Texture *left3;
    SDL_Texture *up0;
    SDL_Texture *up1;
    SDL_Texture *up2;
    SDL_Texture *up3;
    SDL_Texture *down0;
    SDL_Texture *down1;
    SDL_Texture *down2;
    SDL_Texture *down3;
    enum WOR_Sprites current_sprite;

    enum direction dir;

    int lives;
};

struct warrior * create_warrior(SDL_Renderer **renderer_pp);
void move_right(struct warrior ** warrior_pp);
void move_left(struct warrior ** warrior_pp);
void move_up(struct warrior ** warrior_pp);
void move_down(struct warrior ** warrior_pp);
bool collision_wall(int x, int y, struct block **block_pp);
bool wor_collision_r(int x_wor, int x_block);
bool wor_collision_l(int x_wor, int x_block);
bool wor_collision_u(int y_wor, int y_block);
bool wor_collision_d(int y_wor, int y_block);
bool blk_collision_r(int x_wor, int x_block);
bool blk_collision_l(int x_wor, int x_block);
bool blk_collision_u(int y_wor, int y_block);
bool blk_collision_d(int y_wor, int y_block);

#endif //WARRIOR_H