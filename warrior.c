#include "warrior.h"

/**
 * Sets struct for new warrior
 * @param SDL_Renderer ** renderer_pp
 * @return struct warrior *new_warrior
 */
struct warrior * create_warrior(SDL_Renderer **renderer_pp){

    struct warrior *new_warrior = malloc(sizeof(struct warrior)); //allocation in memory of player
    
    //temporay path and texture
    const char *warrior_path = NULL;
    SDL_Texture *warrior_txtr = NULL;

    //set all textures (one for every sprite)
    warrior_path = WARRIOR_R0;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->right0 = warrior_txtr;

    warrior_path = WARRIOR_R1;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->right1 = warrior_txtr;

    warrior_path = WARRIOR_R2;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->right2 = warrior_txtr;

    warrior_path = WARRIOR_L0;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->left0 = warrior_txtr;

    warrior_path = WARRIOR_L1;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->left1 = warrior_txtr;

    warrior_path = WARRIOR_L2;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->left2 = warrior_txtr;

    warrior_path = WARRIOR_U0;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->up0 = warrior_txtr;

    warrior_path = WARRIOR_U1;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->up1 = warrior_txtr;

    warrior_path = WARRIOR_U2;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->up2 = warrior_txtr;

    warrior_path = WARRIOR_D0;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->down0 = warrior_txtr;

    warrior_path = WARRIOR_D1;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->down1 = warrior_txtr;

    warrior_path = WARRIOR_D2;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->down2 = warrior_txtr;

    int x0 = WOR_X0; int y0 = WOR_Y0; //initial warrior position
    SDL_Rect pos_rect = {x0, y0, WOR_WIDTH, WOR_HEIGHT}; 
    new_warrior->pos = pos_rect;

    //initial sprite
    new_warrior->current_sprite = RIGHT_0;
    new_warrior->current_txtr = new_warrior->right0;

}
