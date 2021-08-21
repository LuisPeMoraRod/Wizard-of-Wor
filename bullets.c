#include "bullets.h"

/**
 * Creates new bullet struct
 * @param int x
 * @param int y
 * @return struct bullet *new_bullet
 */
struct bullet *new_bullet(int x, int y, int dir, int width, int height){
    struct bullet *new_bullet = malloc(sizeof(struct bullet));
    new_bullet->pos_x = x;
    new_bullet->pos_y = y;
    SDL_Rect rect = {new_bullet->pos_x, new_bullet->pos_y, width, height};
    new_bullet->rect = rect;
    new_bullet->dir = dir;
    new_bullet->next_bullet = NULL;
    return new_bullet;
}

/**
 * Add bullet at the end of the linked list
 */ 
void add_bullet(struct bullet **new_bullet_pp){
    struct bullet *new_bullet = *new_bullet_pp;
    if (first_bullet == NULL && last_bullet == NULL){
        first_bullet = new_bullet;
        last_bullet = new_bullet;
    }
    else{
        last_bullet->next_bullet = new_bullet;
        last_bullet = new_bullet;
    }
}

/**
 * Creates new bullet
 */
void shoot(){
    int x_bllt; int y_bllt; int dir_bllt; int width; int height;
    switch(player->dir)
    {
        case UP:
            dir_bllt = UP;
            x_bllt = player->pos.x + WOR_WIDTH/2 - BLLT_HEIGHT;
            y_bllt = player->pos.y - BLLT_WIDTH ;
            width = BLLT_HEIGHT;
            height = BLLT_WIDTH;
            break;

        case DOWN:
            dir_bllt = DOWN;
            x_bllt = player->pos.x + WOR_WIDTH/2 - BLLT_HEIGHT;
            y_bllt = player->pos.y + WOR_HEIGHT;
            width = BLLT_HEIGHT;
            height = BLLT_WIDTH;
            break;

        case RIGHT:
            dir_bllt = RIGHT;
            x_bllt = player->pos.x + WOR_WIDTH;
            y_bllt = player->pos.y + WOR_HEIGHT/2 - BLLT_HEIGHT;
            width = BLLT_WIDTH;
            height = BLLT_HEIGHT;
            break;

        case LEFT:
            dir_bllt = LEFT;
            x_bllt = player->pos.x - BLLT_WIDTH;
            y_bllt = player->pos.y + WOR_HEIGHT/2 - BLLT_HEIGHT;
            width = BLLT_WIDTH;
            height = BLLT_HEIGHT;
            break;

        default:
            break;
    }
    struct bullet *bullet = new_bullet(x_bllt, y_bllt, dir_bllt, width, height);
    add_bullet(&bullet);
}

/**
 * Controls movement of bullets
 */
void update_bullets(){
    struct bullet *tmp_bllt = first_bullet;
    while(tmp_bllt != NULL){
        move_bullet(&tmp_bllt);
        tmp_bllt = tmp_bllt->next_bullet;
    }
}

/**
 * Move single bullet
 */
void move_bullet(struct bullet **bullet_pp){
    struct bullet *bullet_ptr = *bullet_pp;
    switch (bullet_ptr->dir)
    {
    case UP:
        bullet_ptr->rect.y -= MV_BLLT;
        break;
    
    case DOWN:
        bullet_ptr->rect.y += MV_BLLT;
        break;
    
    case RIGHT:
        bullet_ptr->rect.x += MV_BLLT;
        break;
    
    case LEFT:
        bullet_ptr->rect.x -= MV_BLLT;
        break;
    
    default:
        break;
    }
}

/**
 * Renders every bullet in linked list
 * @param SDL_Renderer **renderer_pp
 */
void render_bullets(SDL_Renderer **renderer_pp){
    struct bullet *tmp_bullet = first_bullet;
    SDL_SetRenderDrawColor(*renderer_pp, 0xFF, 0xFF, 0x00, 0x00); //yellow color
    while (tmp_bullet != NULL)
    {
        SDL_RenderFillRect(*renderer_pp, &tmp_bullet->rect);
        tmp_bullet = tmp_bullet->next_bullet;
    }
}
/**
 * Free resources from bullets linked list
 */
void free_bullets(){
    struct bullet *tmp_ptr = first_bullet;
    struct bullet *tmp_ptr2;
    while(tmp_ptr != NULL){
        tmp_ptr2 = tmp_ptr;
        tmp_ptr = tmp_ptr->next_bullet;
        free(tmp_ptr2);
    }
}

