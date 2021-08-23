#ifndef ENEMIES_H
#define ENEMIES_H

#include "graphics.h"
#include "game.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct enemy{
    SDL_Rect pos;
    SDL_Rect pos_rdr;
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

    int x_obj;
    int y_obj;

    bool search_wor;

    struct enemy *next_enemy;
};

struct enemy* init_enemy(SDL_Renderer **renderer_pp);
void create_enemies(SDL_Renderer **renderer_pp);
SDL_Rect set_pos();
int set_dir();
void set_sprite(int dir, struct enemy **enemy_pp);
int random_range(int min, int max);
void update_enemies();
void move_enemy(struct enemy **enemy_pp);
SDL_Rect map_radar(SDL_Rect pos);
int map_x(float x);
int map_y(float y);
void move_r(struct enemy **enemy_pp);
void move_l(struct enemy **enemy_pp);
void move_u(struct enemy **enemy_pp);
void move_d(struct enemy **enemy_pp);
int mnhttn_dist(int x1, int y1, int x2, int y2);
bool collision_wor(int x_enemy, int y_enemy);
void add_enemy(struct enemy **enemy_pp);
void delete_enemy(struct enemy **enemy_pp);
bool collision_pos(int x1, int y1, int x2, int y2);
void render_enemies(SDL_Renderer **renderer_pp);
void free_enemies();
void free_enemy(struct enemy **enemy_pp);

#endif //ENEMIES_H