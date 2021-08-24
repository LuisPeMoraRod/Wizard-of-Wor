#include "warrior.h"

/**
 * Inits struct for new warrior
 * @param SDL_Renderer ** renderer_pp
 * @return struct warrior *new_warrior
 */
struct warrior *init_warrior(SDL_Renderer **renderer_pp)
{

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

    warrior_path = WARRIOR_R3;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->right3 = warrior_txtr;

    warrior_path = WARRIOR_L0;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->left0 = warrior_txtr;

    warrior_path = WARRIOR_L1;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->left1 = warrior_txtr;

    warrior_path = WARRIOR_L2;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->left2 = warrior_txtr;

    warrior_path = WARRIOR_L3;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->left3 = warrior_txtr;

    warrior_path = WARRIOR_U0;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->up0 = warrior_txtr;

    warrior_path = WARRIOR_U1;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->up1 = warrior_txtr;

    warrior_path = WARRIOR_U2;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->up2 = warrior_txtr;

    warrior_path = WARRIOR_U3;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->up3 = warrior_txtr;

    warrior_path = WARRIOR_D0;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->down0 = warrior_txtr;

    warrior_path = WARRIOR_D1;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->down1 = warrior_txtr;

    warrior_path = WARRIOR_D2;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->down2 = warrior_txtr;

    warrior_path = WARRIOR_D3;
    warrior_txtr = load_texture(renderer_pp, warrior_path);
    new_warrior->down3 = warrior_txtr;

    //initial warrior position
    SDL_Rect pos_rect = {WOR_X0, WOR_Y0, WOR_WIDTH, WOR_HEIGHT};
    new_warrior->pos = pos_rect;
    new_warrior->pos_rdr = map_radar(new_warrior->pos);

    //initial sprite
    new_warrior->current_sprite = RIGHT_0;
    new_warrior->current_txtr = new_warrior->right0;
    new_warrior->dir = RIGHT;

    new_warrior->lives = LIVES;
    new_warrior->kills = 0;
    new_warrior->death = false;
}

/**
 * Free resources for warrior (including graphics)
 */
void free_warrior(struct warrior **warrior_pp)
{
    struct warrior *warrior_ptr = *warrior_pp;
    SDL_DestroyTexture(warrior_ptr->current_txtr);
    SDL_DestroyTexture(warrior_ptr->right0);
    SDL_DestroyTexture(warrior_ptr->right1);
    SDL_DestroyTexture(warrior_ptr->right2);
    SDL_DestroyTexture(warrior_ptr->right3);
    SDL_DestroyTexture(warrior_ptr->left0);
    SDL_DestroyTexture(warrior_ptr->left1);
    SDL_DestroyTexture(warrior_ptr->left2);
    SDL_DestroyTexture(warrior_ptr->left3);
    SDL_DestroyTexture(warrior_ptr->up0);
    SDL_DestroyTexture(warrior_ptr->up1);
    SDL_DestroyTexture(warrior_ptr->up2);
    SDL_DestroyTexture(warrior_ptr->up1);
    SDL_DestroyTexture(warrior_ptr->down0);
    SDL_DestroyTexture(warrior_ptr->down1);
    SDL_DestroyTexture(warrior_ptr->down2);
    SDL_DestroyTexture(warrior_ptr->down3);
    free(warrior_ptr);
}
/**
 * Moves warrior to the right if it doesn't collide with another element
 * @param struct warrior ** warrior_pp
 */
void move_right(struct warrior **warrior_pp)
{
    struct warrior *warrior_ptr = *warrior_pp;
    int x = warrior_ptr->pos.x + MOVE; //move to right
    int y = warrior_ptr->pos.y;
    if (!collision_wall(x, y, &first_block))
    {
        // Update position
        if (warrior_ptr->pos.x >= R_DOOR)
            warrior_ptr->pos.x = L_DOOR;
        else 
            warrior_ptr->pos.x = x;
        warrior_ptr->dir = RIGHT; //set direction

        int sprite = warrior_ptr->current_sprite;
        switch (sprite) //change sprite for visual movement effect
        {
        case RIGHT_0:
            warrior_ptr->current_sprite = RIGHT_1;
            warrior_ptr->current_txtr = warrior_ptr->right1;
            break;

        case RIGHT_1:
            warrior_ptr->current_sprite = RIGHT_2;
            warrior_ptr->current_txtr = warrior_ptr->right2;
            break;

        case RIGHT_2:
            warrior_ptr->current_sprite = RIGHT_3;
            warrior_ptr->current_txtr = warrior_ptr->right3;
            break;

        case RIGHT_3:
            warrior_ptr->current_sprite = RIGHT_0;
            warrior_ptr->current_txtr = warrior_ptr->right0;
            break;

        default:
            warrior_ptr->current_sprite = RIGHT_0;
            warrior_ptr->current_txtr = warrior_ptr->right0;
            break;
        }
        warrior_ptr->pos_rdr = map_radar(warrior_ptr->pos);
    }
}

/**
 * Moves warrior to the left if it doesn't collide with another element
 * @param struct warrior ** warrior_pp
 */
void move_left(struct warrior **warrior_pp)
{
    struct warrior *warrior_ptr = *warrior_pp;
    int x = warrior_ptr->pos.x - MOVE; //move to left
    int y = warrior_ptr->pos.y;
    if (!collision_wall(x, y, &first_block))
    {
        // Update position
        if (warrior_ptr->pos.x <= L_DOOR)
            warrior_ptr->pos.x = R_DOOR;
        else 
            warrior_ptr->pos.x = x;
        warrior_ptr->dir = LEFT; //set direction

        int sprite = warrior_ptr->current_sprite;
        switch (sprite) //change sprite for visual movement effect
        {
        case LEFT_0:
            warrior_ptr->current_sprite = LEFT_1;
            warrior_ptr->current_txtr = warrior_ptr->left1;
            break;

        case LEFT_1:
            warrior_ptr->current_sprite = LEFT_2;
            warrior_ptr->current_txtr = warrior_ptr->left2;
            break;

        case LEFT_2:
            warrior_ptr->current_sprite = LEFT_3;
            warrior_ptr->current_txtr = warrior_ptr->left3;
            break;

        case LEFT_3:
            warrior_ptr->current_sprite = LEFT_0;
            warrior_ptr->current_txtr = warrior_ptr->left0;
            break;

        default:
            warrior_ptr->current_sprite = LEFT_0;
            warrior_ptr->current_txtr = warrior_ptr->left0;
            break;
        }
        warrior_ptr->pos_rdr = map_radar(warrior_ptr->pos);
    }
}

/**
 * Moves warrior up if it doesn't collide with another element
 * @param struct warrior ** warrior_pp
 */
void move_up(struct warrior **warrior_pp)
{
    struct warrior *warrior_ptr = *warrior_pp;
    int x = warrior_ptr->pos.x;
    int y = warrior_ptr->pos.y - MOVE; //move up
    if (!collision_wall(x, y, &first_block))
    {
        warrior_ptr->pos.y = y; //update position
        warrior_ptr->dir = UP;  //set direction

        int sprite = warrior_ptr->current_sprite;
        switch (sprite) //change sprite for visual movement effect
        {
        case UP_0:
            warrior_ptr->current_sprite = UP_1;
            warrior_ptr->current_txtr = warrior_ptr->up1;
            break;

        case UP_1:
            warrior_ptr->current_sprite = UP_2;
            warrior_ptr->current_txtr = warrior_ptr->up2;
            break;

        case UP_2:
            warrior_ptr->current_sprite = UP_3;
            warrior_ptr->current_txtr = warrior_ptr->up3;
            break;

        case UP_3:
            warrior_ptr->current_sprite = UP_0;
            warrior_ptr->current_txtr = warrior_ptr->up0;
            break;

        default:
            warrior_ptr->current_sprite = UP_0;
            warrior_ptr->current_txtr = warrior_ptr->up0;
            break;
        }
        warrior_ptr->pos_rdr = map_radar(warrior_ptr->pos);
    }
}

/**
 * Moves warrior down if it doesn't collide with another element
 * @param struct warrior ** warrior_pp
 */
void move_down(struct warrior **warrior_pp)
{
    struct warrior *warrior_ptr = *warrior_pp;
    int x = warrior_ptr->pos.x;
    int y = warrior_ptr->pos.y + MOVE; //move down
    if (!collision_wall(x, y, &first_block))
    {
        warrior_ptr->pos.y = y;  //update position
        warrior_ptr->dir = DOWN; //set direction

        int sprite = warrior_ptr->current_sprite;
        switch (sprite) //change sprite for visual movement effect
        {
        case DOWN_0:
            warrior_ptr->current_sprite = DOWN_1;
            warrior_ptr->current_txtr = warrior_ptr->down1;
            break;

        case DOWN_1:
            warrior_ptr->current_sprite = DOWN_2;
            warrior_ptr->current_txtr = warrior_ptr->down2;
            break;

        case DOWN_2:
            warrior_ptr->current_sprite = DOWN_3;
            warrior_ptr->current_txtr = warrior_ptr->down3;
            break;

        case DOWN_3:
            warrior_ptr->current_sprite = DOWN_0;
            warrior_ptr->current_txtr = warrior_ptr->down0;
            break;

        default:
            warrior_ptr->current_sprite = DOWN_0;
            warrior_ptr->current_txtr = warrior_ptr->down0;
            break;
        }
        warrior_ptr->pos_rdr = map_radar(warrior_ptr->pos);
    }
}

/**
 * Loops (recursively) through blocks linked list to determine if warrior has collided with a wall
 * @param int x : warrior position in x axis
 * @param int y : warrior position in y axis
 * @param struct block **block_pp
 * @return bool
 */
bool collision_wall(int x, int y, struct block **block_pp)
{
    struct block *block_tmp = *block_pp;
    if (block_tmp == NULL) //stop recursion
        return false;
    else
    {
        if (wor_collision_r(x, block_tmp->pos_x, B_WIDTH) || wor_collision_l(x, block_tmp->pos_x, B_WIDTH))       //collision in x
            if (wor_collision_u(y, block_tmp->pos_y, B_HEIGHT) || wor_collision_d(y, block_tmp->pos_y, B_HEIGHT)) //collision in y
                return true;

        if (blk_collision_r(x, block_tmp->pos_x) || blk_collision_l(x, block_tmp->pos_x))     //collision in x with single block row
            if (blk_collision_u(y, block_tmp->pos_y) || blk_collision_d(y, block_tmp->pos_y)) //collision in y with single block column
                return true;

        return collision_wall(x, y, &block_tmp->next_block); //recursive call to compare next block in linked list
    }
}

/**
 * Checks if right side of wor collides with block or enemy
 * @param int x_wor
 * @param int x_obj
 * @param int obj_width : block or enemy width
 */
bool wor_collision_r(int x_wor, int x_obj, int obj_width)
{
    int x = x_wor + WOR_WIDTH;
    return ((x_obj <= x) && ((x_obj + obj_width) >= x));
}

/**
 * Checks if left side of wor collides with block
 * @param int x_wor
 * @param int x_obj
 * @param int obj_width : block or enemy width
 */
bool wor_collision_l(int x_wor, int x_obj, int obj_width)
{
    return ((x_obj <= x_wor) && ((x_obj + obj_width) >= x_wor));
}

/**
 * Checks if top side of wor collides with block
 * @param int y_wor
 * @param int y_obj
 * @param int obj_width : block or enemy height
 */
bool wor_collision_u(int y_wor, int y_obj, int obj_height)
{
    return ((y_obj <= y_wor) && ((y_obj + obj_height) >= y_wor));
}

/**
 * Checks if top side of wor collides with block
 * @param int y_wor
 * @param int y_obj
 * @param int obj_width : block or enemy height
 */
bool wor_collision_d(int y_wor, int y_obj, int obj_height)
{
    int y = y_wor + WOR_HEIGHT;
    return ((y_obj <= y) && ((y_obj + obj_height) >= y));
}

/**
 * Checks if right side of block collides with wor
 * @param int x_wor
 * @param int x_block
 */
bool blk_collision_r(int x_wor, int x_block)
{
    int x = x_block + B_WIDTH;
    return (x >= x_wor) && (x <= (x_wor + WOR_WIDTH));
}

/**
 * Checks if left side of block collides with wor
 * @param int x_wor
 * @param int x_block
 */
bool blk_collision_l(int x_wor, int x_block)
{
    return (x_block >= x_wor) && (x_block <= (x_wor + WOR_WIDTH));
}

/**
 * Checks if top side of block collides with wor
 * @param int y_wor
 * @param int y_block
 */
bool blk_collision_u(int y_wor, int y_block)
{
    return (y_block >= y_wor) && (y_block <= (y_wor + WOR_HEIGHT));
}

/**
 * Checks if bottom side of block collides with wor
 * @param int y_wor
 * @param int y_block
 */
bool blk_collision_d(int y_wor, int y_block)
{
    int y = y_block + B_HEIGHT;
    return (y >= y_wor) && (y_block <= (y_wor + WOR_HEIGHT));
}

/**
 * Renders worrior's sprite
 * @param SDL_Renderer **renderer_pp
 */
void render_wor(SDL_Renderer **renderer_pp){
    SDL_RenderCopy(*renderer_pp, player->current_txtr, NULL, &player->pos);
    SDL_SetRenderDrawColor(*renderer_pp, 0xFF, 0xFF, 0x00, 0x00); //yellow color
    SDL_RenderFillRect(*renderer_pp, &player->pos_rdr);
}

/**
 * Renders extra worriors
 */ 
void render_extra_wors(SDL_Renderer **renderer_pp){
    if (player->lives > 1){
        SDL_Rect pos = {W_LIVE0_X, W_LIVE0_Y, WOR_WIDTH, WOR_HEIGHT};
        SDL_RenderCopy(*renderer_pp, player->right0, NULL, &pos);
        for (int i = 0; i < player->lives - 2; i++){
            pos.x = 0;
            pos.y -= WOR_HEIGHT * i; 
            SDL_RenderCopy(*renderer_pp, player->right0, NULL, &pos);
        }
    }
}

/**
 * Checks if worrior collided with an enemy
 */
void check_death(){
    if(player->death){ //binking routine
        time(&player->finish);
        if (difftime(player->finish, player->start) > WOR_BLINK){
            player->blinks += 1;
            time(&player->start);
            player->visible = !player->visible;
            if (player->visible){
                player->pos.x = WOR_X0;
                player->pos.y = WOR_Y0;
            }else{
                player->pos.x = INVSBL;
                player->pos.y = INVSBL;
            }
        }
        if(player->blinks == 5){
            player->death = false;
            player->pos.x = WOR_X0;
            player->pos.y = WOR_Y0;
        }
    }
    else if (collision_enemies(player->pos.x, player->pos.y, &first_enemy)){ //checks colision
        player->death = true;
        player->lives -= 1;
        player->pos.x = WOR_X0;
        player->pos.y = WOR_Y0;
        player->dir = RIGHT;
        player->current_sprite = RIGHT_0;
        player->current_txtr = player->right0;
        player->blinks = 0;
        player->visible = false;
        time(&player->start);
    }
}

/**
 * Loops (recursively) through enemies linked list to determine if warrior has collided with an enemy
 * @param int x : warrior position in x axis
 * @param int y : warrior position in y axis
 * @param struct enemy **enemy_pp
 */
bool collision_enemies(int x, int y, struct enemy **enemy_pp)
{
    struct enemy *enemy_ptr = *enemy_pp;
    if (enemy_ptr == NULL)
        return false;
    else if (collision_enemy(x, y, &enemy_ptr))
        return true;
    return collision_enemies(x, y, &enemy_ptr->next_enemy);
}

/**
 * Checks if warrior collided with a given enemy
 * @param int x : warrior position in x axis
 * @param int y : warrior position in y axis
 * @param struct enemy **enemy_pp
 */
bool collision_enemy(int x, int y, struct enemy **enemy_pp)
{
    struct enemy *enemy_ptr = *enemy_pp;
    if (wor_collision_r(x, enemy_ptr->pos.x, WOR_WIDTH) || wor_collision_l(x, enemy_ptr->pos.x, WOR_WIDTH))       //collision in x
        if (wor_collision_u(y, enemy_ptr->pos.y, WOR_HEIGHT) || wor_collision_d(y, enemy_ptr->pos.y, WOR_HEIGHT)) //collision in y
            return true;
}