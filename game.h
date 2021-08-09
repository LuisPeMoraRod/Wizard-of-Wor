#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "maps.h"
#include "warrior.h"

//global variables to handle data structures
struct block *first_block;
struct block *last_block;

void game_win();
void game_loop(SDL_Window ** main_window_pp, SDL_Renderer **renderer_pp, SDL_Texture **bg_txtr_pp);

#endif //GAME_H