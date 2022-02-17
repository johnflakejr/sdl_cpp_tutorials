#ifndef __LTEXTURE_H__
#define __LTEXTURE_H__
#include <SDL2/SDL.h>
#include <iostream>

class LTexture {
    public: 
        LTexture();
        ~LTexture();
        bool loadFromFile(SDL_Renderer * rend, std::string path);
        void free();
        void render(SDL_Renderer * rend, int x, int y, SDL_Rect * clip = NULL);
        int getWidth();
        int getHeight(); 

    private: 

        SDL_Texture * texture;
        int width;
        int height;
};

#endif