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
    SDL_Texture *left0;
    SDL_Texture *left1;
    SDL_Texture *left2;
    SDL_Texture *up0;
    SDL_Texture *up1;
    SDL_Texture *up2;
    SDL_Texture *down0;
    SDL_Texture *down1;
    SDL_Texture *down2;
    enum WOR_Sprites current_sprite;

    bool right;
    bool up;

    int lives;
};

struct warrior * create_warrior(SDL_Renderer **renderer_pp);
#endif //WARRIOR_H