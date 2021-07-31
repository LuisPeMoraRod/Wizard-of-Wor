#ifndef INIT_WIN_H
#define INIT_WIN_H

#include <time.h>
#include "graphics.h"

void start_window();
void win_loop(SDL_Window ** main_window_pp, SDL_Renderer **renderer_pp, SDL_Texture **bg_txtr_pp);

#endif //INIT_WIN_H