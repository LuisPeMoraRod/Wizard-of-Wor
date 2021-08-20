#include "maps.h"

/**
 * Generates outer walls for the maps
 */
void map_contour(int x, int y, struct block **block_pp)
{
    struct block *block = *block_pp;
    add_block(&block);

    wall_right(&x, y, &block, 6);

    wall_up(x, &y, &block, 19);
    wall_right(&x, y, &block, 83);
    wall_down(x, &y, &block, 19);
    wall_right(&x, y, &block, 7);

    x = -10;
    y = 260;
    wall_right(&x, y, &block, 7);
    wall_down(x, &y, &block, 25);
    wall_right(&x, y, &block, 6);
    wall_up(x, &y, &block, 5);

    x = -10;y = 510;
    wall_right(&x, y, &block, 6);
    x = 60; y = 450;
    wall_right(&x, y, &block, 83);
    wall_up(x, &y, &block, 19);
    wall_right(&x, y, &block, 7);
}

/**
 * Generates first map
 */
void map0(){
    int x = 0;
    int y = 200;
    struct block *block = new_block(x, y);
    map_contour(x, y, &block);

    x = 60; y = 260;
    wall_right(&x, y, &block, 12);
    wall_up(x, &y, &block, 9);

    x = 120; y = 210;
    wall_up(x, &y, &block, 14);

    x = 180; y = 10;
    wall_down(x, &y, &block, 9);

    x = 390; y = 70;
    wall_left(&x, y, &block, 15);
    wall_down(x, &y, &block, 19);
    wall_right(&x, y, &block, 15);

    x = 120; y = 310;
    wall_down(x, &y, &block, 8);

    x = 180; y = 450;
    wall_up(x, &y, &block, 6);

    x = 170; y = 320;
    wall_right(&x, y, &block, 22);
    
    x = 390; y = 450;
    wall_up(x, &y, &block, 6);

    //simetry
    x = 560, y = 70;
    wall_right(&x, y, &block, 15);
    wall_down(x, &y, &block, 19);
    wall_left(&x, y, &block, 15);

    x = 830; y = 310;
    wall_down(x, &y, &block, 8);

    x = 770; y = 450;
    wall_up(x, &y, &block, 6);

    x = 780; y = 320;
    wall_left(&x, y, &block, 22);

    x = 560; y = 450;
    wall_up(x, &y, &block, 6);

    x = 890; y = 260;
    wall_left(&x, y, &block, 12);
    wall_up(x, &y, &block, 9);

    x = 770; y = 10;
    wall_down(x, &y, &block, 9);

    x = 830; y = 210;
    wall_up(x, &y, &block, 14);
    
    x = 480; y = 250;
    wall_down(x, &y, &block, 13);

}

/**
 * Draws wall of consecutive block to the left
 * @param int *x : current x position
 * @param int y : current y position
 * @param struct block **block_pp
 * @param int block : amount of blocks to draw
 */
void wall_left(int *x, int y, struct block **block_pp, int blocks)
{
    struct block *block = *block_pp;
    for (int i = 0; i < blocks; ++i)
    {
        *x -= B_WIDTH;
        block = new_block(*x, y);
        add_block(&block);
    }
}

/**
 * Draws wall of consecutive block to the right
 * @param int *x : current x position
 * @param int y : current y position
 * @param struct block **block_pp
 * @param int block : amount of blocks to draw
 */
void wall_right(int *x, int y, struct block **block_pp, int blocks)
{
    struct block *block = *block_pp;
    for (int i = 0; i < blocks; ++i)
    {
        *x += B_WIDTH;
        block = new_block(*x, y);
        add_block(&block);
    }
}

/**
 * Draws wall of consecutive block upward
 * @param int x : current x position
 * @param int *y : current y position
 * @param struct block **block_pp
 * @param int block : amount of blocks to draw
 */
void wall_up(int x, int *y, struct block **block_pp, int blocks)
{
    struct block *block = *block_pp;
    for (int j = 0; j < blocks; ++j)
    {
        *y -= B_HEIGHT;
        block = new_block(x, *y);
        add_block(&block);
    }
}

/**
 * Draws wall of consecutive block downward
 * @param int x : current x position
 * @param int *y : current y position
 * @param struct block **block_pp
 * @param int block : amount of blocks to draw
 */
void wall_down(int x, int *y, struct block **block_pp, int blocks)
{
    struct block *block = *block_pp;
    for (int j = 0; j < blocks; ++j)
    {
        *y += B_HEIGHT;
        block = new_block(x, *y);
        add_block(&block);
    }
}

/**
 * Creates new block struct
 * @return struct block *new_block
 */
struct block *new_block(int x, int y)
{
    struct block *new_block = malloc(sizeof(struct block));
    new_block->pos_x = x;
    new_block->pos_y = y;
    SDL_Rect rect = {new_block->pos_x, new_block->pos_y, B_WIDTH, B_HEIGHT};
    new_block->rect = rect;
    new_block->next_block = NULL;
    return new_block;
}

/**
 * Adds block struct to linked list at the last place
 * @param struct block** new_block_pp
 */
void add_block(struct block **new_block_pp)
{
    struct block *new_block = *new_block_pp;
    if (first_block == NULL && last_block == NULL) //add first block to linked list
    { 
        first_block = new_block;
        last_block = new_block;
    }
    else
    {
        last_block->next_block = new_block;
        last_block = new_block;
    }
}

/**
 * Renders every block in linked list
 * @param SDL_Renderer **renderer_pp
 */
void render_blocks(SDL_Renderer **renderer_pp)
{
    struct block *tmp_block = first_block;
    SDL_SetRenderDrawColor(*renderer_pp, 0x00, 0x00, 0xFF, 0x00); //blue color
    while (tmp_block != NULL)
    {
        SDL_RenderFillRect(*renderer_pp, &tmp_block->rect);
        tmp_block = tmp_block->next_block;
    }
}

/**
 * Free resources from block linked list
 */
void free_map(){
    struct block * block_tmp = first_block;
    struct block *block_tmp2;
    while(block_tmp != NULL){
        block_tmp2 = block_tmp;
        block_tmp = block_tmp->next_block;
        free(block_tmp2);
    }
}
