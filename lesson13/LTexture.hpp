#ifndef __LTEXTURE_H__
#define __LTEXTURE_H__
#include <SDL.h>
#include <iostream>

class LTexture {
    public: 
        LTexture();
        ~LTexture();
        bool loadFromFile(SDL_Renderer * rend, std::string path);
        void free();
        void set_color(uint8_t red, uint8_t blue, uint8_t green);
        void render(SDL_Renderer * rend, int x, int y, SDL_Rect * clip = NULL);
        int getWidth();
        int getHeight(); 

        void setAlpha(uint8_t alpha);
        void setBlendMode(SDL_BlendMode blending);

    private: 

        SDL_Texture * texture;
        int width;
        int height;
};

#endif