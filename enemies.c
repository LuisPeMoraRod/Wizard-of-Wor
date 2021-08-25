#include "enemies.h"

/**
 * Inits struct for new warrior
 * @param SDL_Renderer ** renderer_pp
 * @return struct warrior *new_warrior
 */
struct enemy *init_enemy(SDL_Renderer **renderer_pp)
{
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

    //initial warrior position
    SDL_Rect pos_rect = set_pos();
    new_enemy->pos = pos_rect;

    //radar mapping
    new_enemy->pos_rdr = map_radar(new_enemy->pos);

    //initial sprite
    new_enemy->dir = set_dir();
    set_sprite(new_enemy->dir, &new_enemy);

    //searches for worrior
    new_enemy->search_wor = true;
    new_enemy->x_obj = player->pos.x;
    new_enemy->y_obj = player->pos.y;

    new_enemy->visible = true;
    time(&new_enemy->start_vsbl);
    new_enemy->vsbl_time = random_range(RND_MIN1, RND_MAX1);

    new_enemy->next_enemy = NULL;
}

/**
 * Creates linked list of enemies
 * @param SDL_Renderer **renderer_pp
 */
void create_enemies(SDL_Renderer **renderer_pp)
{
    struct enemy *new_enemy;
    srand(time(0));
    for (int i = 0; i < ENEMIES; i++)
    {
        new_enemy = init_enemy(renderer_pp);
        add_enemy(&new_enemy);
    }
}

/**
 * Sets enemy's random position. Checks that position doesn't collide with a wall, worrior or other enemy
 */
SDL_Rect set_pos()
{
    bool valid_pos = false;
    int x;
    int y;
    while (!valid_pos)
    {
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
int set_dir()
{
    int dir = random_range(0, 3);
    return dir;
}

/**
 * Set enemy's initial sprite
 */
void set_sprite(int dir, struct enemy **enemy_pp)
{
    struct enemy *enemy_ptr = *enemy_pp;
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
int random_range(int min, int max)
{
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

/**
 * Controls enemies' movement
 */
void update_enemies()
{
    struct enemy *enemy_ptr = first_enemy;
    struct step *step_tmp;
    while (enemy_ptr != NULL)
    {
        update_visibility(&enemy_ptr);
        move_enemy(&enemy_ptr);
        enemy_ptr = enemy_ptr->next_enemy;
    }
}

/**
 * Checks if visibility of enemy needs to be changed
 */ 
void update_visibility(struct enemy **enemy_pp){
    struct enemy *enemy_ptr = *enemy_pp;
    time_t start = enemy_ptr->start_vsbl;
    time_t finish = enemy_ptr->finish_vsbl;
    int timelapse = enemy_ptr->vsbl_time;
    time(&finish);
    if (difftime(finish, start) > timelapse && enemy_ptr == first_enemy)
        {
            time(&enemy_ptr->start_vsbl);
            enemy_ptr->visible = !enemy_ptr->visible;
        }
    
}
/**
 * Move enemy depending on heuristic by manhattan distance
 * @param struct enemy **enemy_pp
 */
void move_enemy(struct enemy **enemy_pp){
    struct enemy *enemy_ptr = *enemy_pp;
    int x_enm = enemy_ptr->pos.x;
    int y_enm = enemy_ptr->pos.y;
    int x_wor = enemy_ptr->x_obj;
    int y_wor = enemy_ptr->y_obj;
    int curr_dist = mnhttn_dist(x_enm, y_enm, x_wor, y_wor);
    if (mnhttn_dist(x_enm, y_enm - MOVE_ENM, x_wor, y_wor) < curr_dist && !collision_wall(x_enm, y_enm - MOVE_ENM, &first_block))
        move_u(enemy_pp);
    else if (mnhttn_dist(x_enm, y_enm + MOVE_ENM, x_wor, y_wor) < curr_dist && !collision_wall(x_enm, y_enm + MOVE_ENM, &first_block))
        move_d(enemy_pp);
    else if (mnhttn_dist(x_enm + MOVE_ENM, y_enm, x_wor, y_wor) < curr_dist && !collision_wall(x_enm + MOVE_ENM, y_enm, &first_block))
        move_r(enemy_pp);
    else if (mnhttn_dist(x_enm - MOVE_ENM, y_enm, x_wor, y_wor) < curr_dist && !collision_wall(x_enm - MOVE_ENM, y_enm, &first_block))
        move_l(enemy_pp); 
    else{
        enemy_ptr->search_wor = !enemy_ptr->search_wor;
        if (enemy_ptr->search_wor){
            enemy_ptr->x_obj = player->pos.x;
            enemy_ptr->y_obj = player->pos.y;
        }else{
            enemy_ptr->x_obj = random_range(X_MIN, X_MAX);
            enemy_ptr->y_obj = random_range(Y_MIN, Y_MAX);
        }
    }
    enemy_ptr->pos_rdr = map_radar(enemy_ptr->pos);
}

/**
 * Maps position of enemy in radar
 * @param struct enemy **enemy_pp
 */
SDL_Rect map_radar(SDL_Rect pos){
    int x = map_x(pos.x);
    int y = map_y(pos.y);
    SDL_Rect rdr_pos = {x , y, E_RDR_W, E_RDR_H};
    return rdr_pos;
}

/**
 * Maps x position to radar
 * @param int x
 * @return int : x radar
 */ 
int map_x(float x){
    int x_rdr = x / MAP_W * RDR_W;
    x_rdr += RDR_X0 + B_WIDTH;
    return x_rdr;
}

/**
 * Maps y position to radar
 * @param int y
 * @return int : y radar
 */ 
int map_y(float y){
    int y_rdr = y / MAP_H * RDR_H;
    y_rdr += RDR_Y0 + B_HEIGHT;
    return y_rdr;
}

/**
 * Moves enemy to the right
 * @param struct enemy **enemy_pp
 */
void move_r(struct enemy **enemy_pp){
    struct enemy *enemy_ptr = *enemy_pp;
    enemy_ptr->pos.x += MOVE_ENM;

    if (enemy_ptr->pos.x >= R_DOOR)
        enemy_ptr->pos.x = L_DOOR;
    
    enemy_ptr->dir = RIGHT;

    int sprite = enemy_ptr->current_sprite;
    switch (sprite)
    {
    case RIGHT_0:
        enemy_ptr->current_sprite = RIGHT_1;
        enemy_ptr->current_txtr = enemy_ptr->right1;
        break;

    case RIGHT_1:
        enemy_ptr->current_sprite = RIGHT_2;
        enemy_ptr->current_txtr = enemy_ptr->right2;
        break;

    case RIGHT_2:
        enemy_ptr->current_sprite = RIGHT_3;
        enemy_ptr->current_txtr = enemy_ptr->right3;
        break;

    case RIGHT_3:
        enemy_ptr->current_sprite = RIGHT_0;
        enemy_ptr->current_txtr = enemy_ptr->right0;
        break;
    
    default:
        enemy_ptr->current_sprite = RIGHT_0;
        enemy_ptr->current_txtr = enemy_ptr->right0;
        break;
    }
}

/**
 * Moves enemy to the left
 * @param struct enemy **enemy_pp
 */
void move_l(struct enemy **enemy_pp){
    struct enemy *enemy_ptr = *enemy_pp;
    enemy_ptr->pos.x -= MOVE_ENM;

    if (enemy_ptr->pos.x <= L_DOOR)
        enemy_ptr->pos.x = R_DOOR;
    
    enemy_ptr->dir = LEFT;

    int sprite = enemy_ptr->current_sprite;
    switch (sprite)
    {
    case LEFT_0:
        enemy_ptr->current_sprite = LEFT_1;
        enemy_ptr->current_txtr = enemy_ptr->left1;
        break;

    case LEFT_1:
        enemy_ptr->current_sprite = LEFT_2;
        enemy_ptr->current_txtr = enemy_ptr->left2;
        break;

    case LEFT_2:
        enemy_ptr->current_sprite = LEFT_3;
        enemy_ptr->current_txtr = enemy_ptr->left3;
        break;

    case LEFT_3:
        enemy_ptr->current_sprite = LEFT_0;
        enemy_ptr->current_txtr = enemy_ptr->left0;
        break;

    default:
        enemy_ptr->current_sprite = LEFT_0;
        enemy_ptr->current_txtr = enemy_ptr->left0;
        break;
    }
}

/**
 * Moves enemy up
 * @param struct enemy **enemy_pp
 */
void move_u(struct enemy **enemy_pp){
    struct enemy *enemy_ptr = *enemy_pp;
    enemy_ptr->pos.y -= MOVE_ENM;

    enemy_ptr->dir = UP;

    int sprite = enemy_ptr->current_sprite;
    switch (sprite)
    {
    case UP_0:
        enemy_ptr->current_sprite = UP_1;
        enemy_ptr->current_txtr = enemy_ptr->up1;
        break;

    case UP_1:
        enemy_ptr->current_sprite = UP_2;
        enemy_ptr->current_txtr = enemy_ptr->up2;
        break;
        
    case UP_2:
        enemy_ptr->current_sprite = UP_3;
        enemy_ptr->current_txtr = enemy_ptr->up3;
        break;

    case UP_3:
        enemy_ptr->current_sprite = UP_0;
        enemy_ptr->current_txtr = enemy_ptr->up0;
        break;

    default:
        enemy_ptr->current_sprite = UP_0;
        enemy_ptr->current_txtr = enemy_ptr->up0;
        break;
    }
}

/**
 * Moves enemy down
 * @param struct enemy **enemy_pp
 */
void move_d(struct enemy **enemy_pp){
    struct enemy *enemy_ptr = *enemy_pp;
    enemy_ptr->pos.y += MOVE_ENM;

    enemy_ptr->dir = DOWN;

    int sprite = enemy_ptr->current_sprite;
    switch (sprite)
    {
    case DOWN_0:
        enemy_ptr->current_sprite = DOWN_1;
        enemy_ptr->current_txtr = enemy_ptr->down1;
        break;

    case DOWN_1:
        enemy_ptr->current_sprite = DOWN_2;
        enemy_ptr->current_txtr = enemy_ptr->down2;
        break;
        
    case DOWN_2:
        enemy_ptr->current_sprite = DOWN_3;
        enemy_ptr->current_txtr = enemy_ptr->down3;
        break;

    case DOWN_3:
        enemy_ptr->current_sprite = DOWN_0;
        enemy_ptr->current_txtr = enemy_ptr->down0;
        break;

    default:
        enemy_ptr->current_sprite = DOWN_0;
        enemy_ptr->current_txtr = enemy_ptr->down0;
        break;
    }
}

/**
 * Computes Manhattan distance between two points
 * @param int x1
 * @param int x1
 * @param int x1
 * @param int y2
 * @return distance
 */
int mnhttn_dist(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

/**
 * Checks if enemy's positions collides with worrior's
 */
bool collision_wor(int x_enemy, int y_enemy)
{
    int x_wor = player->pos.x;
    int y_wor = player->pos.y;
    if (wor_collision_r(x_wor, x_enemy, WOR_WIDTH) || wor_collision_l(x_wor, x_enemy, WOR_WIDTH))
        if (wor_collision_u(y_wor, y_enemy, WOR_HEIGHT) || wor_collision_d(y_wor, y_enemy, WOR_HEIGHT))
            return true;
    return false;
}

/**
 * Creates random enemy every certain amount of time
 */
void create_rand_en(SDL_Renderer **renderer_pp){
    time(&fnsh_rand_en);
    if (difftime(fnsh_rand_en, strt_rand_en) > rand_time){
        time(&strt_rand_en);
        struct enemy *new_enemy = init_enemy(renderer_pp);
        add_enemy(&new_enemy);
    }
}


/**
 * Add enemy to the end of linked list
 * @param struct enemy **enemy_pp
 */
void add_enemy(struct enemy **enemy_pp)
{
    struct enemy *new_enemy = *enemy_pp;
    if (first_enemy == NULL && last_enemy == NULL)
    {
        first_enemy = new_enemy;
        last_enemy = new_enemy;
        enemies_cnt += 1;
    }
    else
    {
        last_enemy->next_enemy = new_enemy;
        last_enemy = new_enemy;
        enemies_cnt += 1;
    }
}

/**
 * Delete enemy from linked list
 * @param struct enemy **enemy_pp
 */
void delete_enemy(struct enemy **enemy_pp)
{
    struct enemy *enemy_ptr = *enemy_pp;
    struct enemy *tmp = first_enemy;
    struct enemy *tmp2;
    bool found_enemy = false;
    while (!found_enemy || tmp == NULL)
    { //loop through linked list to find to-be-deleted enemy
        if (enemy_ptr == first_enemy)
        {                                 //if it's first in list
            if (enemy_ptr == last_bullet) //if it's the only enemy
                last_bullet = NULL;
            first_enemy = first_enemy->next_enemy;
            free_enemy(&enemy_ptr);
            found_enemy = true;
            enemies_cnt -= 1;
        }
        else if (tmp->next_enemy == enemy_ptr)
        { //if its in between or last node
            if (enemy_ptr == last_enemy)
                last_enemy = tmp;
            tmp2 = tmp->next_enemy;
            tmp->next_enemy = tmp2->next_enemy;
            free_enemy(&tmp2);
            found_enemy = true;
            enemies_cnt -= 1;
        }
        else
            tmp = tmp->next_enemy;
    }
}

/**
 * Checks if two positions will collide
 * @param int x1
 * @param int y1
 * @param int x2
 * @param int y2
 * @return bool
 */
bool collision_pos(int x1, int y1, int x2, int y2){
    if (wor_collision_r(x1, x2, WOR_WIDTH) || wor_collision_l(x1, x2, WOR_WIDTH))
        if (wor_collision_u(y1, y2, WOR_HEIGHT) || wor_collision_d(y1, y2, WOR_HEIGHT))
            return true;
    return false;
}

/**
 * Renders every enemy in linked list
 * @param SDL_Renderer **renderer_pp
 */
void render_enemies(SDL_Renderer **renderer_pp)
{
    struct enemy *tmp = first_enemy;
    SDL_Rect *pos = NULL;
    SDL_SetRenderDrawColor(*renderer_pp, 0xFF, 0x99, 0x66, 0x00); //red color
    while (tmp != NULL)
    {
        pos = &tmp->pos;
        if (tmp->visible)
            SDL_RenderCopy(*renderer_pp, tmp->current_txtr, NULL, pos);
        pos = &tmp->pos_rdr;
        SDL_RenderFillRect(*renderer_pp, pos);
        tmp = tmp->next_enemy;
    }
}

/**
 * Free resources from enemies linked list
 */
void free_enemies()
{
    struct enemy *enemy_tmp = first_enemy;
    struct enemy *enemy_tmp2;
    while (enemy_tmp != NULL)
    {
        enemy_tmp2 = enemy_tmp;
        enemy_tmp = enemy_tmp->next_enemy;
        free_enemy(&enemy_tmp2);
    }
}

/**
 * Free resources from a single enemy struct
 */
void free_enemy(struct enemy **enemy_pp)
{
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
