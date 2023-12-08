#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
// The window we will render
SDL_Window *window = NULL;
// The screen surface contain the window
SDL_Surface *screen_surface = NULL;
SDL_Surface *image_surface = NULL;
bool init()
{
    bool success = true;
    printf("Hello SDL \n");
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window
        window = SDL_CreateWindow("HELLO SDL",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created err:%s", SDL_GetError());
            success = false;
        }
        screen_surface = SDL_GetWindowSurface(window);
        // SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0x00, 0xFF));
    }
    return success;
}

bool load_media()
{
    bool success = true;
    image_surface = SDL_LoadBMP("./hello_world.bmp");
    if (image_surface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError());
        success = false;
    }
    return success;
}

void close()
{
    // deallocate window and surface
    SDL_FreeSurface(image_surface);
    image_surface = NULL;
    SDL_FreeSurface(screen_surface);
    screen_surface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

int main(int argc, char const *argv[])
{

    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!load_media())
        {
            printf("Failed to load media \n");
        }
        else
        {
            // apply the image
            SDL_BlitSurface(image_surface, NULL, screen_surface, NULL);
            SDL_UpdateWindowSurface(window);
            SDL_Event e;
            bool quit = false;

            // display update loop
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        quit = true;
                }
            }
        }
    }
    close();
    return 0;
}
