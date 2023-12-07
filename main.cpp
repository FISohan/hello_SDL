#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char const *argv[])
{
    // The window we will render
    SDL_Window *window = NULL;
    // The screen surface contain the window
    SDL_Surface *screen_surface = NULL;
    printf("Hello SDL \n");
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create window
        printf("Create window");
        window = SDL_CreateWindow("HELLO SDL",
                                  0,
                                  0,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created err:%s", SDL_GetError());
        }
        screen_surface = SDL_GetWindowSurface(window);
        SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
        SDL_Event e;
        bool quit = false;
        while (quit == false)
        {
            printf("update");
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                    quit = true;
            }
        }
    }

    return 0;
}
