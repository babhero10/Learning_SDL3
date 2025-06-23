#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL3/SDL.h>
#include <string>

class LTexture {
public:
  LTexture(SDL_Renderer* renderer);

  ~LTexture();

  bool loadFromFile(std::string path);

  void destroy();

  void render(float x, float y);

  int getWidth();
  int getHeight();
  bool isLoaded();

private:
  SDL_Texture* mTexture;

  int mWidth;
  int mHeight;

  SDL_Renderer* mRenderer;
};

#endif
