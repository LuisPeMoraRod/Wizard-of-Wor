#include "game.h"

/**
 * Creates game window
 */
void game_win(){
    //Window to be rendering
    SDL_Window *start_wdw = NULL;

    //Window renderer
    SDL_Renderer *renderer = NULL;

    //Current displayed background texture
    SDL_Texture *bg_texture = NULL;

    start_wdw = init_window();

    if (start_wdw == NULL){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }else{
        renderer = init_renderer(&start_wdw);
        if(renderer != NULL){
            const char *background_path = GAME_BG_PATH;
            bg_texture = load_texture(&renderer, background_path);
            if (bg_texture != NULL) {
                new_game(&start_wdw, &renderer, &bg_texture);
            } else {
                printf("Failed to load media!\n");
            }
        }
    }
}

/**
 * Loop that handles game logic.
 */
void new_game(SDL_Window ** main_window_pp, SDL_Renderer **renderer_pp, SDL_Texture **bg_txtr_pp){
    //First map
    int map = 0;

    //Init player struct
    player = init_warrior(renderer_pp);

    game_loop(map, main_window_pp, renderer_pp, bg_txtr_pp);

    free_warrior(&player);
}

void game_loop(int map, SDL_Window ** main_window_pp, SDL_Renderer **renderer_pp, SDL_Texture **bg_txtr_pp){
    SDL_Renderer *renderer = *renderer_pp;
    SDL_Texture *background_texture = *bg_txtr_pp;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_texture, NULL, NULL );

    //Font for text rendering
    TTF_Font *font = load_font(); 

    //Main loop flag
    bool win = false;
    bool quit = false;

    //Event handler
    SDL_Event event;

    //initialize global variables
    first_block = NULL;
    last_block = NULL;
    first_enemy = NULL;
    last_enemy = NULL;
    first_bullet = NULL;
    last_bullet = NULL;

    //set map
    switch (map)
    {
    case MAP0:
        map0();
        break;

    case MAP1:
        map1();
        break;

    case MAP2:
        map2();
        break;
    
    default:
        win = true;
        break;
    }

    SDL_Rect *player_pos = NULL;
    if (!win){
        //Init enemies
        enemies_cnt = 0;
        create_enemies(renderer_pp);

        //Render map
        render_blocks(renderer_pp);

        //Render warrior
        player->pos.x = WOR_X0;
        player->pos.y = WOR_Y0;
        player->dir = RIGHT;
        player->current_sprite = RIGHT_0;
        player->current_txtr = player->right0;
        render_wor(renderer_pp);

        //Render extra worriors
        render_extra_wors(renderer_pp);

        //Render enemies
        render_enemies(renderer_pp);

        //GET READY message
        get_ready(renderer_pp);

        SDL_RenderPresent(*renderer_pp);
        SDL_Delay(DELAY_GR);
    } else you_win(main_window_pp ,renderer_pp);

    //While application is running
    while( !quit && !win && player->lives > 0 && enemies_cnt > 0)
    {
        //Handle events on queue
        while(SDL_PollEvent( &event ) != 0 )
        {
            if (event.type == SDL_WINDOWEVENT
                && event.window.event == SDL_WINDOWEVENT_CLOSE)
            {

                if (SDL_GetWindowID(*main_window_pp) == event.window.windowID)
                {
                    quit = true;
                }
            }
            if( event.type == SDL_KEYDOWN && !player->death) 
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_d:
                    move_right(&player);
                    break;

                case SDLK_a:
                    move_left(&player);
                    break;

                case SDLK_w:
                    move_up(&player);
                    break;
                    
                case SDLK_s:
                    move_down(&player);
                    break;
                
                case SDLK_SPACE:
                    shoot();
                    break;
                
                default:
                    break;
                }
            }
        }
        
        //Clear screen
        SDL_RenderClear(renderer);

        //Render background_texture to screen
        SDL_RenderCopy(renderer, background_texture, NULL, NULL );
        
        //Render map
        render_blocks(renderer_pp);

        if (!player->death){
            //Update enemies
            update_enemies();

            //Update bullets
            update_bullets();
        }

        //Render enemies
        render_enemies(renderer_pp);

        //Render bullets
        render_bullets(renderer_pp);

        //Checks if worrior collided with enemy
        check_death();

        //Render warrior
        render_wor(renderer_pp);

        //Render extra worriors
        render_extra_wors(renderer_pp);

        //Render text for enemies counter
        char kills_txt[20];
        snprintf(kills_txt, 20, "Kills: %d, Lives: %d", player->kills, player->lives);
        // Set color to red
        SDL_Color color = { 255, 0, 0 };
        render_text(kills_txt, &font, color, CONT_X, CONT_Y, renderer_pp);

        //Render text for radar
        char *radar_txt = "RADAR";
        render_text(radar_txt, &font, color, RDR_X, RDR_Y, renderer_pp);
        
        //Update screen
        SDL_RenderPresent(renderer);

        //Game update delay
        SDL_Delay( DELAY ); 

    }

    if (player->lives > 0 && !win && !quit){
        free_map();
        free_enemies();
        free_bullets();
        map += 1;
        game_loop(map, main_window_pp, renderer_pp, bg_txtr_pp);
    } else if (player->lives == 0 && !win && !quit){
        free_map();
        free_enemies();
        free_bullets();

        game_over(renderer_pp);
        close_window(main_window_pp, &renderer, bg_txtr_pp);
        main();

    } else if(quit){
        free_map();
        free_enemies();
        free_bullets();
        close_window(main_window_pp, &renderer, bg_txtr_pp);
    }
}

/**
 * Render "GET READY" message
 * @param SDL_Renderer **renderer_pp
 */
void get_ready(SDL_Renderer **renderer_pp){
    const char *gr_path = GETREADY;
    SDL_Texture *txtr = load_texture(renderer_pp, gr_path);
    SDL_Rect pos = {GR_X, GR_Y, GR_W, GR_H};

    SDL_RenderCopy(*renderer_pp, txtr, NULL, &pos);
    
}

/**
 * Render "GAME OVER" message
 * @param SDL_Renderer **renderer_pp
 */
void game_over(SDL_Renderer **renderer_pp){
    const char *gr_path = GAMEOVER;
    SDL_Texture *txtr = load_texture(renderer_pp, gr_path);
    SDL_Rect pos = {GR_X, GR_Y, GR_W, GR_H};

    SDL_RenderCopy(*renderer_pp, txtr, NULL, &pos);
    SDL_RenderPresent(*renderer_pp);
    SDL_Delay(DELAY_GR);
}

/**
 * Render "YOU WIN" message
 * @param SDL_Renderer **renderer_pp
 */
void you_win(SDL_Window ** main_window_pp, SDL_Renderer **renderer_pp){
    const char *yw_path = YOUWIN;
    SDL_Texture *win_txtr = load_texture(renderer_pp, yw_path);
    SDL_RenderCopy(*renderer_pp, win_txtr, NULL, NULL);

    const char *wor_path = WOR_IMG;
    SDL_Rect pos = {WOR_IMG_X, WOR_IMG_Y, WOR_IMG_W, WOR_IMG_H};
    SDL_Texture *wor_txtr = load_texture(renderer_pp, wor_path);
    SDL_RenderCopy(*renderer_pp, wor_txtr, NULL, &pos);

    TTF_Font *font = load_font(); 
    char *text_c = "YOU WIN!!!";
    SDL_Color color = { 255, 216, 61}; //yellow
    render_text(text_c, &font, color, WOR_IMG_X + WOR_IMG_W * 3/2, WOR_IMG_Y + WOR_IMG_H/2, renderer_pp);



    SDL_RenderPresent(*renderer_pp);
    SDL_Delay(DELAY_GR);
    close_window(main_window_pp, renderer_pp, &win_txtr);
    main();
}