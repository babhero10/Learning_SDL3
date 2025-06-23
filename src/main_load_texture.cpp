#include "utils/include/texture.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>

constexpr int kScreenWidth{640};
constexpr int kScreenHeight{400};

SDL_Window *gWindow{nullptr};
SDL_Renderer *gRenderer{nullptr};
LTexture gPngTexture{nullptr};

bool init();
bool loadMedia();
void close();

int main() {
  int exitCode{0};

  if (init() == false) {
    SDL_Log("Unable to initialize program!\n");
    exitCode = 1;
  } else {
    if (loadMedia() == false) {
      SDL_Log("Unable to load media!\n");
      exitCode = 2;
    } else {
      bool quit{false};

      SDL_Event e;
      SDL_zero(e);

      while (quit == false) {
        while (SDL_PollEvent(&e) == true) {
          if (e.type == SDL_EVENT_QUIT) {
            quit = true;
          }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        gPngTexture.render(0.0f, 0.0f);

        SDL_RenderPresent(gRenderer);
      }
    }
  }

  close();

  return exitCode;
}

bool init() {
  // Initialization flag
  bool success{true};

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window with renderer
    if (SDL_CreateWindowAndRenderer(
            "SDL3 Tutorial: Textures and Extension Libraries", kScreenWidth,
            kScreenHeight, 0, &gWindow, &gRenderer) == false) {
      SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
      success = false;
    }
  }

  gPngTexture = LTexture(gRenderer);
  return success;
}

bool loadMedia() {
  bool success{true};

  if (gPngTexture.loadFromFile("src/assets/loaded.png") == false) {
    SDL_Log("Unable to load png image!\n");
    success = false;
  }

  return success;
}

void close() {
  gPngTexture.destroy();

  SDL_DestroyRenderer(gRenderer);
  gRenderer = nullptr;
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  SDL_Quit();
}
