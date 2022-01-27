#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

SDL_Window * g_window = NULL;
SDL_Surface * g_screen_surface = NULL;
SDL_Surface * g_hello_surface = NULL;

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

    g_hello_surface = SDL_LoadBMP("hello_world.bmp");

    if (NULL == g_hello_surface) {
        return false;
    }

    SDL_BlitSurface(g_hello_surface, NULL, g_screen_surface, NULL);
    SDL_UpdateWindowSurface(g_window);

    uint32_t ms = 5000;
    SDL_Delay(ms);
}

void sdl_cleanup() {
    SDL_FreeSurface(g_hello_surface);
    g_hello_surface = NULL;

	SDL_DestroyWindow(g_window);
    g_window = NULL;

	SDL_Quit();
}

int main(int argc, char * args[]) {

    if (!initialize_sdl()){
        return 1;
    }

    if (!load_media()) {
        return 1;
    }

    sdl_cleanup();

    return 0;
}
