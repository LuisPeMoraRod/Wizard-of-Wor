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
    SDL_Rect pos_rect = set_pos();
    new_enemy->pos = pos_rect;

    //initial sprite
    new_enemy->dir = set_dir();
    set_sprite(new_enemy->dir, &new_enemy);

    new_enemy->next_enemy = NULL;
}

/**
 * Creates linked list of enemies
 * @param SDL_Renderer **renderer_pp
 */
void create_enemies(SDL_Renderer **renderer_pp){
    struct enemy *new_enemy;
    srand(time(0));
    for (int i = 0; i < 6; i++){
        new_enemy = init_enemy(renderer_pp);
        add_enemy(&new_enemy);
    }
}

/**
 * Sets enemy's random position. Checks that position doesn't collide with a wall, worrior or other enemy
 */
SDL_Rect set_pos(){
    bool valid_pos = false;
    int x; int y;
    while(!valid_pos){
        x = random_range(X_MIN, X_MAX);
        y = random_range(Y_MIN, Y_MAX);
        if (!collision_wall(x, y, &first_block))
            if (!collision_enemies(x, y, &first_enemy))
                if (!collision_wor(x, y))
                    valid_pos = true;
    }
    SDL_Rect pos = {x, y, WOR_WIDTH, WOR_HEIGHT};
    return pos;
}

/**
 * Sets initial enemy direction randomly 
 */ 
int set_dir(){
    int dir = random_range(0, 3);
    return dir;
}

/**
 * Set enemy's initial sprite
 */ 
void set_sprite(int dir, struct enemy **enemy_pp){
    struct enemy  *enemy_ptr = *enemy_pp;
    switch (dir)
    {
    case UP:
        enemy_ptr->current_sprite = UP_0;
        enemy_ptr->current_txtr = enemy_ptr->up0;
        break;

    case DOWN:
        enemy_ptr->current_sprite = DOWN_0;
        enemy_ptr->current_txtr = enemy_ptr->down0;
    
    case RIGHT:
        enemy_ptr->current_sprite = RIGHT_0;
        enemy_ptr->current_txtr = enemy_ptr->right0;

    case LEFT:
        enemy_ptr->current_sprite = LEFT_0;
        enemy_ptr->current_txtr = enemy_ptr->left0;

    default:
        break;
    }
}

/**
 * Random number in a given range
 * @param int min
 * @param int max
 * @return int : random number
 */
int random_range(int min, int max){
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

/**
 * Checks if enemy's positions collides with worrior's
 */ 
bool collision_wor(int x_enemy, int y_enemy){
    int x_wor = player->pos.x;
    int y_wor = player->pos.y;
    if (wor_collision_r(x_wor, x_enemy, WOR_WIDTH) || wor_collision_l(x_wor, x_enemy, WOR_WIDTH))
        if (wor_collision_u(y_wor, y_enemy, WOR_HEIGHT) || wor_collision_d(y_wor, y_enemy, WOR_HEIGHT))
            return true;
    return false;
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
        enemies_cnt += 1;
    }else{
        last_enemy->next_enemy = new_enemy;
        last_enemy = new_enemy;
        enemies_cnt += 1;
    }
}

/**
 * Delete enemy from linked list
 * @param struct enemy **enemy_pp
 */
void delete_enemy(struct enemy **enemy_pp){
    struct enemy *enemy_ptr = *enemy_pp;
    struct enemy *tmp = first_enemy;
    struct enemy *tmp2;
    bool found_enemy = false;
    while(!found_enemy || tmp == NULL){ //loop through linked list to find to-be-deleted enemy
        if (enemy_ptr == first_enemy){ //if it's first in list
            first_enemy = first_enemy->next_enemy;
            free_enemy(&enemy_ptr);
            found_enemy = true;
            enemies_cnt -= 1;
        }
        else if (tmp->next_enemy == enemy_ptr){
            if (enemy_ptr == last_enemy)
                last_enemy = tmp;
            tmp2 = tmp->next_enemy;
            tmp->next_enemy = tmp2->next_enemy;
            free_enemy(&tmp2);
            found_enemy = true;
            enemies_cnt -= 1;
        }
        else tmp = tmp->next_enemy;
    }
}

/**
 * Renders every enemy in linked list
 * @param SDL_Renderer **renderer_pp
 */
void render_enemies(SDL_Renderer **renderer_pp){
    struct enemy *tmp = first_enemy;
    SDL_Rect *pos = NULL;
    while(tmp != NULL){
        pos = &tmp->pos;
        SDL_RenderCopy(*renderer_pp, tmp->current_txtr, NULL, pos);
        tmp = tmp->next_enemy;
    }
}


/**
 * Free resources from enemies linked list
 */
void free_enemies(){
    struct enemy *enemy_tmp = first_enemy;
    struct enemy *enemy_tmp2;
    while(enemy_tmp != NULL){
        enemy_tmp2 = enemy_tmp;
        enemy_tmp = enemy_tmp->next_enemy;
        free_enemy(&enemy_tmp2);
    }
}

/**
 * Free resources from a single enemy struct
 */
void free_enemy(struct enemy **enemy_pp){
    struct enemy *enemy_ptr = *enemy_pp;
    SDL_DestroyTexture(enemy_ptr->current_txtr);
    SDL_DestroyTexture(enemy_ptr->right0);
    SDL_DestroyTexture(enemy_ptr->right1);
    SDL_DestroyTexture(enemy_ptr->right2);
    SDL_DestroyTexture(enemy_ptr->right3);
    SDL_DestroyTexture(enemy_ptr->left0);
    SDL_DestroyTexture(enemy_ptr->left1);
    SDL_DestroyTexture(enemy_ptr->left2);
    SDL_DestroyTexture(enemy_ptr->left3);
    SDL_DestroyTexture(enemy_ptr->up0);
    SDL_DestroyTexture(enemy_ptr->up1);
    SDL_DestroyTexture(enemy_ptr->up2);
    SDL_DestroyTexture(enemy_ptr->up3);
    SDL_DestroyTexture(enemy_ptr->down0);
    SDL_DestroyTexture(enemy_ptr->down1);
    SDL_DestroyTexture(enemy_ptr->down2);
    SDL_DestroyTexture(enemy_ptr->down3);
    free(enemy_ptr);
}
