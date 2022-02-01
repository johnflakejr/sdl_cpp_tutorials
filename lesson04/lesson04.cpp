#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

SDL_Window * g_window = NULL;
SDL_Surface * g_screen_surface = NULL;

enum key_press_values {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Surface * g_surfaces[KEY_PRESS_SURFACE_TOTAL];

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

SDL_Surface * load_surface(std::string file_name) {

    SDL_Surface * surface = SDL_LoadBMP(file_name.c_str());

    if (NULL == surface) {
        cout << "ERROR: unable to load surface: " << SDL_GetError() << endl;
        return NULL;
    }

    return surface;
}

bool load_media() {
    bool success = true;

    string file_names[] = {"press.bmp", 
                           "up.bmp", 
                           "down.bmp", 
                           "left.bmp", 
                           "right.bmp"};

    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        g_surfaces[i] = load_surface("assets/" + file_names[i]);

        if (NULL == g_surfaces[i]) {
            success = false;
        }
    }

    return true;
}

void sdl_cleanup() {
    //TODO clean and free surfaces
	SDL_DestroyWindow(g_window);
    g_window = NULL;

	SDL_Quit();
}

void run() {

    bool quit = false;
    SDL_Event e;
    SDL_Surface * current_surface = g_surfaces[KEY_PRESS_SURFACE_DEFAULT];

    while (!quit) {
        int event = 0;

        do {
            event = SDL_PollEvent(&e);
            if (SDL_QUIT == e.type) {
                quit = true;
            } else if (SDL_KEYDOWN == e.type) {

                switch (e.key.keysym.sym) {
                    case SDLK_UP: 
                        current_surface = g_surfaces[KEY_PRESS_SURFACE_UP];
                        break;
                    case SDLK_DOWN: 
                        current_surface = g_surfaces[KEY_PRESS_SURFACE_DOWN];
                        break;
                    case SDLK_LEFT: 
                        current_surface = g_surfaces[KEY_PRESS_SURFACE_LEFT];
                        break;
                    case SDLK_RIGHT: 
                        current_surface = g_surfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;
                    default: 
                        current_surface = g_surfaces[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                }
            }
        } while (event != 0);

        SDL_BlitSurface(current_surface, NULL, g_screen_surface, NULL);
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
