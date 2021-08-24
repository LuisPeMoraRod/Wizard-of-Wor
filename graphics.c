#include "graphics.h"

/**
 * Initialices a window
 * @return SDL_Window
 */
SDL_Window *init_window(){

    SDL_Window *window = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Set background_texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear background_texture filtering not enabled!" );
        }
        //Create window
        window = SDL_CreateWindow("Wizard of Wor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN );
    }
    return window;

}

/**
 * Creates graphic renderer
 * @param window_ptr: SDL_Window **
 * @return SDL_Renderer *
 */
SDL_Renderer *init_renderer(SDL_Window ** window_ptr){
    SDL_Window *window = *window_ptr;
    SDL_Renderer *renderer = NULL;

    //Create renderer for window
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    if( renderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Initialize renderer color
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        }
    }
    return renderer;
}


/**
 * Loads png image to be rendered
 * @param renderer_ptr: SDL_Renderer **
 * @param path : char
 * @return SDL_Texture *
 */
SDL_Texture *load_texture(SDL_Renderer **renderer_ptr, const char path[MAX_PATH]){
    SDL_Renderer *renderer = *renderer_ptr;
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Create new texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

TTF_Font *load_font(){
    TTF_Font* font;
    if ( TTF_Init() < 0 ) 
	    printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
    font = TTF_OpenFont("resources/pixelletters.ttf", FONT_SIZE);
    if ( !font ) 
	    printf("Failed to load font: %s\n", TTF_GetError());
    
}

/**
 * Attemps to create text texture to be rendered
 * @param char * text
 * @param TTF_Font **font_pp
 * @param int x
 * @param int y
 * @param SDL_Renderer **renderer_pp
 */
void render_text(char *buff, TTF_Font **font_pp, SDL_Color color, int x, int y, SDL_Renderer **renderer_pp){
    SDL_Surface* text;
    SDL_Texture* text_texture;

    text = TTF_RenderText_Solid(*font_pp, buff, color );

    if (!text)
	    printf("Failed to load font: %s\n", TTF_GetError());
    
    text_texture = SDL_CreateTextureFromSurface( *renderer_pp, text );

    SDL_Rect pos = { x, y, text->w, text->h };

    SDL_RenderCopy(*renderer_pp, text_texture, NULL, &pos);
    SDL_DestroyTexture( text_texture );
    SDL_FreeSurface( text );
}


/**
 * Free SDL graphic resources
 */
void close_window(SDL_Window **window_ptr, SDL_Renderer **renderer_ptr, SDL_Texture **bg_txtr_ptr)
{
    SDL_Window *window = *window_ptr;
    SDL_Renderer *renderer = *renderer_ptr;
    SDL_Texture *background_texture = *bg_txtr_ptr;
    //Free loaded image
    SDL_DestroyTexture(background_texture);
    background_texture = NULL;

    //Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
