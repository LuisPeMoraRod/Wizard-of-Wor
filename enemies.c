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

/**
 * Add enemy to the end of linked list
 * @param struct enemy **enemy_pp
 */ 
void add_enemy(struct enemy **enemy_pp){
    struct enemy *new_enemy = *enemy_pp;
    if (first_enemy == NULL && last_enemy == NULL){
        first_enemy = new_enemy;
        last_enemy = new_enemy;
    }else{
        last_enemy->next_enemy = new_enemy;
        last_enemy = new_enemy;
    }
}

void free_enemies(){
    struct enemy *enemy_tmp = first_enemy;
    struct enemy *enemy_tmp2;
    while(enemy_tmp != NULL){
        enemy_tmp2 = enemy_tmp;
        enemy_tmp = enemy_tmp->next_enemy;
        SDL_DestroyTexture(enemy_tmp2->current_txtr);
        SDL_DestroyTexture(enemy_tmp2->right0);
        SDL_DestroyTexture(enemy_tmp2->right1);
        SDL_DestroyTexture(enemy_tmp2->right2);
        SDL_DestroyTexture(enemy_tmp2->right3);
        SDL_DestroyTexture(enemy_tmp2->left0);
        SDL_DestroyTexture(enemy_tmp2->left1);
        SDL_DestroyTexture(enemy_tmp2->left2);
        SDL_DestroyTexture(enemy_tmp2->left3);
        SDL_DestroyTexture(enemy_tmp2->up0);
        SDL_DestroyTexture(enemy_tmp2->up1);
        SDL_DestroyTexture(enemy_tmp2->up2);
        SDL_DestroyTexture(enemy_tmp2->up3);
        SDL_DestroyTexture(enemy_tmp2->down0);
        SDL_DestroyTexture(enemy_tmp2->down1);
        SDL_DestroyTexture(enemy_tmp2->down2);
        SDL_DestroyTexture(enemy_tmp2->down3);
        free(enemy_tmp2);
    }
}


