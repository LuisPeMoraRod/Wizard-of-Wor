#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"

struct image{
    int pos_x, pos_y, width, height;
    char *img_path;
    SDL_Rect pos_rect;
    SDL_Texture *texture;
};

SDL_Window *init_window();
SDL_Renderer *init_renderer(SDL_Window ** window_ptr);
SDL_Texture *load_texture(SDL_Renderer **renderer_ptr, const char path[MAX_PATH]);
TTF_Font *load_font();
void render_text(char *buff, TTF_Font **font_pp, int x, int y, SDL_Renderer **renderer_pp);
void close_window(SDL_Window **window_ptr, SDL_Renderer **renderer_ptr, SDL_Texture **bg_txtr_ptr);

#endif //GRAPHICS_H