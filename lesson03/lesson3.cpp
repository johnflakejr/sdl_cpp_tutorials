#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

SDL_Window * g_window = NULL;
SDL_Surface * g_screen_surface = NULL;
SDL_Surface * g_x_out_surface = NULL;

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

    g_screen_surface = SDL_GetWindowSurface(g_window);

    return true;
}

bool load_media() {

    g_x_out_surface = SDL_LoadBMP("x.bmp");

    if (NULL == g_x_out_surface) {
        return false;
    }

    SDL_BlitSurface(g_x_out_surface, NULL, g_screen_surface, NULL);
    SDL_UpdateWindowSurface(g_window);

    return true;
}

void sdl_cleanup() {
    SDL_FreeSurface(g_x_out_surface);
    g_x_out_surface = NULL;

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
