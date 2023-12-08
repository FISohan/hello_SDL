#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

// Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
// The window we will render
SDL_Window *window = NULL;
// The screen surface contain the window
SDL_Surface *screen_surface = NULL;
SDL_Surface *image_surface = NULL;

SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface *gCurrentSurface = NULL;

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

SDL_Surface *loadSurface(std::string path)
{
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Failed to load %s", path);
    }
    return loadedSurface;
}

bool load_media()
{
    bool success = true;
    // Load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("./press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        printf("Failed to load default image!\n");
        success = false;
    }

    // Load up surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("./up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        printf("Failed to load up image!\n");
        success = false;
    }

    // Load down surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("./down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        printf("Failed to load down image!\n");
        success = false;
    }

    // Load left surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("./left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        printf("Failed to load left image!\n");
        success = false;
    }

    // Load right surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("./right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        printf("Failed to load right image!\n");
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
            SDL_Event e;
            bool quit = false;
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            // display update loop
            while (quit == false)
            {

                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        quit = true;
                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;
                        case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;

                        case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;

                        case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;

                        default:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                    SDL_BlitSurface(gCurrentSurface, NULL, screen_surface, NULL);
                    SDL_UpdateWindowSurface(window);
                }
            }
        }
    }
    close();
    return 0;
}
