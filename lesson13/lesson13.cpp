#include <SDL.h>
#include "LTexture.hpp"
#include <SDL_image.h>
#include <iostream>

using namespace std;

SDL_Window * g_window = NULL;
SDL_Renderer * g_renderer = NULL;
SDL_Rect g_sprite_clips[4];
LTexture g_texture;
LTexture g_background;

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

    int width = SCREEN_WIDTH;
    int height = SCREEN_HEIGHT;
    int x_pos = SDL_WINDOWPOS_CENTERED;
    int y_pos = SDL_WINDOWPOS_CENTERED;

    int flags = SDL_WINDOW_SHOWN;

    g_window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);

    if (NULL == g_window) {
        cout << "Window could not be created! SDL_Error: ";
        cout << SDL_GetError() << endl;
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    if (NULL == g_renderer){
        cout << "Renderer could not be created. ";
        cout << SDL_GetError() << endl;
        return false;
    }

    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    flags = IMG_INIT_PNG;

    res = IMG_Init(flags) & flags;

    if (!res) {
        cout << "Window could not be created! SDL_Error: ";
        cout << IMG_GetError() << endl;
        return false;
    }

    return true;
}

SDL_Texture * loadTexture(string path) {
    SDL_Surface * newSurface = IMG_Load(path.c_str());

    if (NULL == newSurface) {
        cout << "Can't load surface for texture ";
        cout << SDL_GetError() << endl;
        return NULL;
    }

    SDL_Texture * newTex = SDL_CreateTextureFromSurface(g_renderer, newSurface);

    if (NULL == newTex) {
        cout << "Error getting texture from surface: ";
        cout << SDL_GetError() << endl;
    }

    SDL_FreeSurface(newSurface);

    return newTex;
}

bool load_media() {
    bool success = true;

    success = g_background.loadFromFile(g_renderer, "assets/fadeout.png");

    if (!success) {
        cout << "Error loading media. " << endl;
        return success;
    }

    g_background.setBlendMode(SDL_BLENDMODE_BLEND);

    success = g_texture.loadFromFile(g_renderer, "assets/fadein.png");

    if (!success) {
        cout << "Error loading media. " << endl;
        return success;
    }

    return success;
}

void sdl_cleanup() {

    g_texture.free();
    g_background.free();

    SDL_DestroyRenderer(g_renderer);
    g_renderer = NULL;

	SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
	SDL_Quit();
}

void run() {

    bool quit = false;
    SDL_Event e;

    uint8_t a = 255;

    while (!quit) {
        int event = 0;

        do {
            event = SDL_PollEvent(&e);
            if (SDL_QUIT == e.type) {
                quit = true;
            } else if (SDL_KEYDOWN == e.type) {
                switch(e.key.keysym.sym) {
                    case SDLK_w:
                        a += 32;
                        if (a < 32) {
                            a = 255;
                        }
                        break;
                    case SDLK_s:
                        a -= 32;
                        if (a > 223) {
                            a = 0;
                        }
                        break;
                }

            }
        } while (event != 0);

        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_renderer);
        g_texture.render(g_renderer, 0,0);
        g_background.setAlpha(a);
        g_background.render(g_renderer, 0,0);
        SDL_RenderPresent(g_renderer);
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
