#include "init_win.h"

/**
 * Creates initial window
 */
void start_window(){
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
            const char *background_path = TITTLE_WIN_PATH;
            bg_texture = load_texture(&renderer, background_path);
            if (bg_texture != NULL) {
                win_loop(&start_wdw, &renderer, &bg_texture);
            } else {
                printf("Failed to load media!\n");
            }
        }
    }
}



/**
 * Initial window loop to handle events
 * @param renderer_ptr: SDL_Renderer **
 * @param bg_txtr_ptr: SDL_Texture **
 */
void win_loop(SDL_Window ** main_window_ptr, SDL_Renderer **renderer_ptr, SDL_Texture **bg_txtr_ptr){
    time_t start, finish;
    bool show_mssg = true;

    SDL_Renderer *renderer = *renderer_ptr;
    SDL_Texture *background_texture = *bg_txtr_ptr;

    //Main loop flag
    bool quit = false;
    pthread_t game_t;

    //Event handler
    SDL_Event event;

    SDL_Rect *pos = NULL;

    int x = 0, y = 0;

    time(&start);

    //While application is running
    while( !quit )
    {
        //Clear screen
        SDL_RenderClear(renderer);

        //Render background_texture to screen
        SDL_RenderCopy(renderer, background_texture, NULL, NULL );

        //Render "press any key to start" image
        size_t size = sizeof(struct image);
        struct image *press_key = malloc(size);
        press_key->img_path = PRESS_KEY;
        press_key->pos_x = PK_X;
        press_key->pos_y = PK_Y;
        press_key->width = PK_WIDTH;
        press_key->height = PK_HEIGHT;
        SDL_Rect pos_rect = {press_key->pos_x, press_key->pos_y, press_key->width, press_key->height};
        press_key->pos_rect = pos_rect;
        SDL_Texture *texture = load_texture(renderer_ptr, press_key->img_path);
        press_key->texture = texture;
        time(&finish);
        if (difftime(finish, start) > PK_BLINK){ //blink message
            time(&start);
            show_mssg = !show_mssg;
        }
        if (show_mssg) SDL_RenderCopy(renderer, press_key->texture, NULL, &press_key->pos_rect);

        //Update screen
        SDL_RenderPresent(renderer);

        SDL_Delay( DELAY );

        //Handle events on queue
        while(SDL_PollEvent( &event ) != 0 )
        {
            if (event.type == SDL_WINDOWEVENT
                && event.window.event == SDL_WINDOWEVENT_CLOSE)
            {

                if (SDL_GetWindowID(*main_window_ptr) == event.window.windowID)
                {
                    quit = true;
                }
            }
            if( event.type == SDL_KEYDOWN) 
            {
                printf("Starting game...");
            }
        }

    }
}
