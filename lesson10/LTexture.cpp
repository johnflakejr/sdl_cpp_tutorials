#include "LTexture.hpp"
#include <SDL2/SDL_image.h>

LTexture::LTexture() {
  texture = NULL;
  width = 0;
  height = 0;
}

LTexture::~LTexture() {
  free();
}

void LTexture::free() {
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
    texture = NULL;
    width = 0;
    height = 0;
  }
}

bool LTexture::loadFromFile(SDL_Renderer * rend, std::string path) {
  free();

  SDL_Surface * loaded_surface = IMG_Load(path.c_str());

  if (NULL == loaded_surface) {
    std::cout << "couldn't load surface from " << path << std::endl;
    std::cout << "error: " << IMG_GetError() << std::endl;
    return false;
  }

  SDL_SetColorKey(loaded_surface, 
                  SDL_TRUE, 
                  SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
  texture = SDL_CreateTextureFromSurface(rend, loaded_surface);

  if (NULL == texture) {

    std::cout << "couldn't load texture from " << path << std::endl;
    std::cout << "error: " << SDL_GetError() << std::endl;
    return false;
  }

  width = loaded_surface->w;
  height = loaded_surface->h;
  SDL_FreeSurface(loaded_surface);

  return true;
}

void LTexture::render(SDL_Renderer * rend, int x, int y) {
  SDL_Rect render_rect = {x, y, width, height };
  SDL_RenderCopy(rend, texture, NULL, &render_rect);
}

int LTexture::getWidth() {
  return width;
}

int LTexture::getHeight() {
  return height;
}

