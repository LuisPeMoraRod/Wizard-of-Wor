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
                game_loop(&start_wdw, &renderer, &bg_texture);
            } else {
                printf("Failed to load media!\n");
            }
        }
    }
}

/**
 * Loop that handles game logic.
 */
void game_loop(SDL_Window ** main_window_pp, SDL_Renderer **renderer_pp, SDL_Texture **bg_txtr_pp){
    SDL_Renderer *renderer = *renderer_pp;
    SDL_Texture *background_texture = *bg_txtr_pp;

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    //initialize global variables
    first_block = NULL;
    last_block = NULL;
    map0();

    //create player warrior
    struct warrior *player = create_warrior(renderer_pp);
    SDL_Rect *player_pos = NULL;
    

    //While application is running
    while( !quit )
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
            if( event.type == SDL_KEYDOWN) 
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

        //render warrior
        player_pos = &player->pos;
        SDL_RenderCopy(renderer, player->current_txtr, NULL, player_pos);

        //Update screen
        SDL_RenderPresent(renderer);

        //Game update delay
        SDL_Delay( DELAY ); 

    }
}