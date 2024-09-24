#pragma once
#include <SDL_image.h>

class Texture {
 public:
  Texture(SDL_Texture* texture);
  ~Texture();
  void render(SDL_Renderer* renderer, const SDL_Rect* pos);

 private:
  SDL_Texture* texture;

};
