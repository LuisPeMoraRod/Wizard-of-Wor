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
        check_collisions(&tmp_bllt);
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
 * Checks if bullet has collided with a wall or enemy
 * @struct bullet **bullet_pp
 */
void check_collisions(struct bullet **bullet_pp){
    struct bullet *bllt_ptr = *bullet_pp;
    if (coll_bllt_wall(&bllt_ptr, &first_block))
        delete_bullet(&bllt_ptr);

}

/**
 * Loops recursively through blocks linked list to check if bullet has collided with a wall
 * @param struct bullet **bullet_pp
 * @param struct block **block_pp
 * @return bool
 */
bool coll_bllt_wall(struct bullet **bullet_pp, struct block **block_pp){
    struct block *blck_ptr = *block_pp;
    struct bullet *bllt_ptr = *bullet_pp;
    if (blck_ptr == NULL) //stop recursion
        return false;
    else if (coll_bllt_r(bllt_ptr->rect.x, BLLT_WIDTH, blck_ptr->pos_x, B_WIDTH) || coll_bllt_l(bllt_ptr->rect.x, BLLT_WIDTH, blck_ptr->pos_x, B_WIDTH)) //check horizontal collision
        if (coll_bllt_u(bllt_ptr->rect.y, BLLT_HEIGHT, blck_ptr->pos_y, B_HEIGHT) || coll_bllt_d(bllt_ptr->rect.y, BLLT_HEIGHT, blck_ptr->pos_y, B_HEIGHT)) //check vertical collsions
            return true;
    return coll_bllt_wall(bullet_pp, &blck_ptr->next_block);
}

bool coll_bllt_enemies(struct bullet **bullet_pp, struct enemy **enemy_pp){
    //TODO  
}

/**
 * Checks if bullet has collided to its right with an object
 * @param int x_bllt
 * @param int w_bllt
 * @param int x_obj
 * @param int w_obj
 * @return bool
 */ 
bool coll_bllt_r(int x_bllt, int w_bllt, int x_obj, int w_obj){
    int x = x_bllt + w_bllt;
    return ((x_obj <= x) && ((x_obj + w_obj) >= x));
}

/**
 * Checks if bullet has collided to its right with an object
 * @param int x_bllt
 * @param int w_bllt
 * @param int x_obj
 * @param int w_obj
 * @return bool
 */ 
bool coll_bllt_l(int x_bllt, int w_bllt, int x_obj, int w_obj){
    return ((x_obj <= x_bllt) && ((x_obj + w_obj) >= x_bllt));
}

/**
 * Checks if bullet has collided to its right with an object
 * @param int y_bllt
 * @param int h_bllt
 * @param int y_obj
 * @param int h_obj
 * @return bool
 */ 
bool coll_bllt_u(int y_bllt, int h_bllt, int y_obj, int h_obj){
    return ((y_obj <= y_bllt) && ((y_obj + h_obj) >= y_bllt));
}

/**
 * Checks if bullet has collided to its right with an object
 * @param int y_bllt
 * @param int h_bllt
 * @param int y_obj
 * @param int h_obj
 * @return bool
 */ 
bool coll_bllt_d(int y_bllt, int h_bllt, int y_obj, int h_obj){
    int y = y_bllt + h_bllt;
    return ((y_obj <= y) && ((y_obj + h_obj) >= y));
}

/**
 * Delete given bullet from linked list
 * @param struct bullet **bullet_pp
 */
void delete_bullet(struct bullet **bullet_pp){
    struct bullet *bllt_ptr = *bullet_pp;
    struct bullet *tmp = first_bullet;
    struct bullet *tmp2;
    bool found_bullet = false;
    while(!found_bullet || tmp == NULL){
        if (bllt_ptr == first_bullet){ //if it's first bullet 
            first_bullet = first_bullet->next_bullet;
            if (bllt_ptr == last_bullet) //if it's the only bullet
                last_bullet = NULL;
            free(bllt_ptr);
            found_bullet = true;
        }
        else if (tmp->next_bullet == bllt_ptr){
            if (bllt_ptr == last_bullet) //if it's last bullet
                last_bullet = tmp;
            tmp2 = tmp->next_bullet;
            tmp->next_bullet = tmp2->next_bullet;
            free(tmp2);
            found_bullet = true;
        }
        else tmp = tmp->next_bullet;
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

