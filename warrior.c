#include "warrior.h"

/**
 * Sets struct for new warrior
 * @param SDL_Renderer ** renderer_pp
 * @return struct warrior *new_warrior
 */
struct warrior *create_warrior(SDL_Renderer **renderer_pp)
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

    int x0 = WOR_X0;
    int y0 = WOR_Y0; //initial warrior position
    SDL_Rect pos_rect = {x0, y0, WOR_WIDTH, WOR_HEIGHT};
    new_warrior->pos = pos_rect;

    //initial sprite
    new_warrior->current_sprite = RIGHT_0;
    new_warrior->current_txtr = new_warrior->right0;
}

/**
 * Moves warrior to the right if it doesn't collide with another element
 * @param struct warrior ** warrior_pp
 */
void move_right(struct warrior **warrior_pp)
{
    struct warrior *warrior_ptr = *warrior_pp;
    int x = warrior_ptr->pos.x + MOVE;
    int y = warrior_ptr->pos.y;
    if (!collision_wall(x, y, &first_block))
    {
        warrior_ptr->pos.x = x;
    }
}

/**
 * Moves warrior to the left if it doesn't collide with another element
 * @param struct warrior ** warrior_pp
 */
void move_left(struct warrior **warrior_pp)
{
    struct warrior *warrior_ptr = *warrior_pp;
    int x = warrior_ptr->pos.x - MOVE;
    int y = warrior_ptr->pos.y;
    if (!collision_wall(x, y, &first_block))
    {
        warrior_ptr->pos.x = x;
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
    int y = warrior_ptr->pos.y - MOVE;
    if (!collision_wall(x, y, &first_block))
    {
        warrior_ptr->pos.y = y;
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
    int y = warrior_ptr->pos.y + MOVE;
    if (!collision_wall(x, y, &first_block))
    {
        warrior_ptr->pos.y = y;
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
    if (block_tmp->next_block == NULL) //stop recursion
        return false;
    else
    {
        if (wor_collision_r(x, block_tmp->pos_x) || wor_collision_l(x, block_tmp->pos_x))
        {                                                                                     //collision in x
            if (wor_collision_u(y, block_tmp->pos_y) || wor_collision_d(y, block_tmp->pos_y)) //collision in y
                return true;
        }
        return collision_wall(x, y, &block_tmp->next_block); //recursive call to compare next block in linked list
    }
}

/**
 *Checks if right side of wor collides with block
 *@param int x_wor
 *@param int x_block
 */
bool wor_collision_r(int x_wor, int x_block)
{
    int x = x_wor + WOR_WIDTH;
    return ((x_block <= x) && ((x_block + B_WIDTH) >= x));
}

/**
 *Checks if left side of wor collides with block
 *@param int x_wor
 *@param int x_block
 */
bool wor_collision_l(int x_wor, int x_block)
{
    return ((x_block <= x_wor) && ((x_block + B_WIDTH) >= x_wor));
}

/**
 *Checks if top side of wor collides with block
 *@param int y_wor
 *@param int y_block
 */
bool wor_collision_u(int y_wor, int y_block)
{
    return ((y_block <= y_wor) && ((y_block + B_HEIGHT) >= y_wor));
}

/**
 *Checks if top side of wor collides with block
 *@param int y_wor
 *@param int y_block
 */
bool wor_collision_d(int y_wor, int y_block)
{
    int y = y_wor + WOR_HEIGHT;
    return ((y_block <= y) && ((y_block + B_HEIGHT) >= y));
}


/**
 *Checks if right side of block collides with wor
 *@param int x_wor
 *@param int x_block
 */
bool blk_collision_r(int x_wor, int x_block)
{
    int x = x_block + B_WIDTH;
    return (x >= x_wor) && (x <= (x_wor + WOR_WIDTH));
}
