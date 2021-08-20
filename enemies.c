#include "enemies.h"

/**
 * Inits struct for new warrior
 * @param SDL_Renderer ** renderer_pp
 * @return struct warrior *new_warrior
 */
struct enemy* init_enemy(SDL_Renderer **renderer_pp){
    struct enemy *new_enemy = malloc(sizeof(struct enemy)); //allocation in memory of player

    //temporay path and texture
    const char *enemy_path = NULL;
    SDL_Texture *enemy_txtr = NULL;

    //set all textures (one for every sprite)
    enemy_path = ENEMY_R0;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->right0 = enemy_txtr;

    enemy_path = ENEMY_R1;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->right1 = enemy_txtr;

    enemy_path = ENEMY_R2;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->right2 = enemy_txtr;

    enemy_path = ENEMY_R3;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->right3 = enemy_txtr;

    enemy_path = ENEMY_L0;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->left0 = enemy_txtr;

    enemy_path = ENEMY_L1;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->left1 = enemy_txtr;

    enemy_path = ENEMY_L2;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->left2 = enemy_txtr;

    enemy_path = ENEMY_L3;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->left3 = enemy_txtr;

    enemy_path = ENEMY_U0;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->up0 = enemy_txtr;

    enemy_path = ENEMY_U1;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->up1 = enemy_txtr;

    enemy_path = ENEMY_U2;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->up2 = enemy_txtr;

    enemy_path = ENEMY_U3;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->up3 = enemy_txtr;

    enemy_path = ENEMY_D0;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->down0 = enemy_txtr;

    enemy_path = ENEMY_D1;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->down1 = enemy_txtr;

    enemy_path = ENEMY_D2;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->down2 = enemy_txtr;

    enemy_path = ENEMY_D3;
    enemy_txtr = load_texture(renderer_pp, enemy_path);
    new_enemy->down3 = enemy_txtr;

    //SDL_Rect pos_rect = set_pos();
    //new_enemy->pos = pos_rect;

    //initial warrior position
    SDL_Rect pos_rect = {EN_X0, EN_Y0, WOR_WIDTH, WOR_HEIGHT};
    new_enemy->pos = pos_rect;

    //initial sprite
    new_enemy->current_sprite = RIGHT_0;
    new_enemy->current_txtr = new_enemy->right0;
    new_enemy->dir = RIGHT;

}

/**
 * Sets enemy's random position. Checks that position doesn't collide with a wall or worrior
 */
void set_pos(){
    //TODO
    return;
}

/**
 * Random number in a given range
 * @param int min
 * @param int max
 * @return int : random number
 */
int random_range(int min, int max){
    srand(time(0));
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}


