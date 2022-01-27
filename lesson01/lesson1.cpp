#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main(int argc, char * args[]) {

    int res = SDL_Init(SDL_INIT_VIDEO);

	if (res < 0) {
		cout << "SDL could not initialize! SDL_Error: ";
        cout << SDL_GetError() << endl;
        return 1;
    }

    const char * title = "SDL Tutorial";
    int width = 500;
    int height = 400;

    SDL_Window * window = SDL_CreateWindow(title, 
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED, 
                                           width,
                                           height,
                                           SDL_WINDOW_SHOWN);

    if (NULL == window) {
        cout << "Window could not be created! SDL_Error: ";
        cout << SDL_GetError() << endl;

    } else {
        SDL_Surface * screenSurface = SDL_GetWindowSurface(window);

        uint32_t rgb = SDL_MapRGB(screenSurface->format,0,0,0xFF);
        SDL_FillRect(screenSurface,NULL,rgb);

        SDL_UpdateWindowSurface(window);

        uint32_t ms = 5000;
        SDL_Delay(ms);
    }

	SDL_DestroyWindow(window);
	SDL_Quit();

    return 0;
}
