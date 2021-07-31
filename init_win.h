#ifndef INIT_WIN_H
#define INIT_WIN_H

#include <time.h>
#include "graphics.h"

void start_window();
void win_loop(SDL_Window ** main_window_ptr, SDL_Renderer **renderer_ptr, SDL_Texture **bg_txtr_ptr);

#endif //INIT_WIN_H