#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "maps.h"
#include "warrior.h"
#include "enemies.h"
#include "bullets.h"

//global variables to handle data structures
struct block *first_block;
struct block *last_block;
struct enemy *first_enemy;
struct enemy *last_enemy;
struct bullet *first_bullet;
struct bullet *last_bullet;
struct warrior *player;

time_t strt_rand_en;
time_t fnsh_rand_en;
int rand_time;

int enemies_cnt;

void game_win();
void new_game(SDL_Window ** main_window_pp, SDL_Renderer **renderer_pp, SDL_Texture **bg_txtr_pp);
void game_loop(int map, SDL_Window ** main_window_pp, SDL_Renderer **renderer_pp, SDL_Texture **bg_txtr_pp);
void get_ready(SDL_Renderer **renderer_pp);
void game_over(SDL_Renderer **renderer_pp);
void you_win(SDL_Window ** main_window_pp, SDL_Renderer ** renderer_pp);
#endif //GAME_H