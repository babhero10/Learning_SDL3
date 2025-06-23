#include "../include/texture.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

LTexture::LTexture(SDL_Renderer* renderer):
  mRenderer(renderer),
  mTexture{ nullptr },
  mWidth{ 0 },
  mHeight{ 0 }
{

}

LTexture::~LTexture() {
  destroy();
}

bool LTexture::loadFromFile(std::string path) {
  destroy();

  if (SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr) {
    SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
  } else {
    if (mTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface); mTexture == nullptr) {
      SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
    } else {
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }

    SDL_DestroySurface(loadedSurface);
  }

  return mTexture != nullptr;
}

void LTexture::destroy() {
  SDL_DestroyTexture(mTexture);
  mTexture = nullptr;

  mWidth = 0;
  mHeight = 0;
}

void LTexture::render(float x, float y) {
  SDL_FRect dstRect{x, y, static_cast<float>(mWidth), static_cast<float>(mHeight)};
  SDL_RenderTexture(mRenderer, mTexture, nullptr, &dstRect);
}

int LTexture::getWidth() {
  return mWidth;
}

int LTexture::getHeight() {
  return mHeight;
}

bool LTexture::isLoaded() {
  return mTexture != nullptr;
}
