#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

SDL_Window * g_window = NULL;
SDL_Surface * g_screen_surface = NULL;
SDL_Surface * g_stretched = NULL;
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

bool initialize_sdl() {

    int res = SDL_Init(SDL_INIT_VIDEO);

	if (res < 0) {
		cout << "SDL could not initialize! SDL_Error: ";
        cout << SDL_GetError() << endl;
        return false;
    }

    const char * title = "SDL Tutorial";

    int width = 640;
    int height = 480;
    int x_pos = SDL_WINDOWPOS_CENTERED;
    int y_pos = SDL_WINDOWPOS_CENTERED;

    int flags = SDL_WINDOW_SHOWN;

    g_window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);

    if (NULL == g_window) {
        cout << "Window could not be created! SDL_Error: ";
        cout << SDL_GetError() << endl;
        return false;
    }


    flags = IMG_INIT_PNG;

    res = IMG_Init(flags) & flags;

    if (!res) {
        cout << "Window could not be created! SDL_Error: ";
        cout << IMG_GetError() << endl;
        return false;
    }

    g_screen_surface = SDL_GetWindowSurface(g_window);

    return true;
}

SDL_Surface * load_surface(std::string file_name) {

    SDL_Surface * optimized = NULL;
    //SDL_Surface * surface = SDL_LoadBMP(file_name.c_str());
    SDL_Surface * surface = IMG_Load(file_name.c_str());

    if (NULL == surface) {
        cout << "ERROR: unable to load surface: " << SDL_GetError() << endl;
        return NULL;
    }

    optimized = SDL_ConvertSurface(surface, g_screen_surface->format, 0);

    if (NULL == optimized) {
        cout << "ERROR: unable to optimize surface: " << SDL_GetError() << endl;
    }

    SDL_FreeSurface(surface);

    return optimized;
}

bool load_media() {
    bool success = true;

    g_stretched = load_surface("assets/loaded.png");

    return true;
}

void sdl_cleanup() {
    SDL_FreeSurface(g_screen_surface);
    g_screen_surface = NULL;

    SDL_FreeSurface(g_stretched);
    g_stretched = NULL;

	SDL_DestroyWindow(g_window);
    g_window = NULL;

	SDL_Quit();
}

void run() {

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        int event = 0;

        do {
            event = SDL_PollEvent(&e);
            if (SDL_QUIT == e.type) {
                quit = true;
            } 
        } while (event != 0);


        //Scale the image: 

        SDL_Rect stretch_rect;
        stretch_rect.x = 0;
        stretch_rect.y = 0;
        stretch_rect.w = SCREEN_WIDTH;
        stretch_rect.h = SCREEN_HEIGHT;


        SDL_BlitScaled(g_stretched, NULL, g_screen_surface, &stretch_rect);
        SDL_UpdateWindowSurface(g_window);
    }
}

int main(int argc, char * args[]) {

    if (!initialize_sdl()){
        return 1;
    }

    if (!load_media()) {
        return 1;
    }

    run();

    sdl_cleanup();

    return 0;
}
