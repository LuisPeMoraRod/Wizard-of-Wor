#ifndef ENEMIES_H
#define ENEMIES_H

#include "graphics.h"
#include "game.h"
#include <time.h>
#include <stdio.h>

struct enemy{
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
    enum sprites_num current_sprite;

    enum direction dir;
    struct enemy *next_enemy;
};

struct enemy* init_enemy(SDL_Renderer **renderer_pp);
void create_enemies(SDL_Renderer **renderer_pp);
SDL_Rect set_pos();
int random_range(int min, int max);
bool collision_wor(int x_enemy, int y_enemy);
void add_enemy(struct enemy **enemy_pp);
void delete_enemy(struct enemy **enemy_pp);
void render_enemies(SDL_Renderer **renderer_pp);
void free_enemies();
void free_enemy(struct enemy **enemy_pp);

#endif //ENEMIES_H