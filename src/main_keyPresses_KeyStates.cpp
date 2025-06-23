#include "utils/include/texture.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>

constexpr int kScreenWidth{1200};
constexpr int kScreenHeight{768};

SDL_Window *gWindow{nullptr};
SDL_Renderer *gRenderer{nullptr};
LTexture gUpTexture{nullptr}, gDownTexture{nullptr},
         gLeftTexture{nullptr},gRightTexture{nullptr};

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

      LTexture* currentTexture = &gUpTexture;
      SDL_Color bgColor{0xFF, 0xFF, 0xFF, 0xFF};

      while (quit == false) {
        while (SDL_PollEvent(&e) == true) {
          if (e.type == SDL_EVENT_QUIT) {
            quit = true;
          } else if(e.type == SDL_EVENT_KEY_DOWN) {
            if (e.key.key == SDLK_ESCAPE) {
              quit = true;
            }
            if (e.key.key == SDLK_W) {
              currentTexture = &gUpTexture;
            } if (e.key.key == SDLK_S) {
              currentTexture = &gDownTexture;
            } if (e.key.key == SDLK_D) {
              currentTexture = &gRightTexture;
            } if (e.key.key == SDLK_A) {
              currentTexture = &gLeftTexture;
            }
          }
        }

        bgColor.r = 0xFF;
        bgColor.g = 0xFF;
        bgColor.b = 0xFF;

        const bool* keyStates = SDL_GetKeyboardState( nullptr );
        if( keyStates[ SDL_SCANCODE_W ] == true )
        {
            bgColor.r = 0xFF;
            bgColor.g = 0x00;
            bgColor.b = 0x00;
        }
        else if( keyStates[ SDL_SCANCODE_S ] == true )
        {
            bgColor.r = 0x00;
            bgColor.g = 0xFF;
            bgColor.b = 0x00;
        }
        else if( keyStates[ SDL_SCANCODE_A ] == true )
        {
            bgColor.r = 0xFF;
            bgColor.g = 0xFF;
            bgColor.b = 0x00;
        }
        else if( keyStates[ SDL_SCANCODE_D ] == true )
        {
            bgColor.r = 0x00;
            bgColor.g = 0x00;
            bgColor.b = 0xFF;
        }

        SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, 0xFF);
        SDL_RenderClear(gRenderer);

        currentTexture->render((kScreenWidth - currentTexture->getWidth()) * 0.5f,
                               (kScreenHeight - currentTexture->getHeight()) * 0.5f);

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

  gUpTexture = LTexture{gRenderer};
  gDownTexture = LTexture{gRenderer};
  gLeftTexture = LTexture{gRenderer};
  gRightTexture = LTexture{gRenderer};

  return success;
}

bool loadMedia() {
  bool success{true};

  if (gUpTexture.loadFromFile("src/assets/up.png") == false) {
    SDL_Log("Unable to load up png image!\n");
    success = false;
  }

  if (gDownTexture.loadFromFile("src/assets/down.png") == false) {
    SDL_Log("Unable to load down png image!\n");
    success = false;
  }

  if (gLeftTexture.loadFromFile("src/assets/left.png") == false) {
    SDL_Log("Unable to load left png image!\n");
    success = false;
  }

  if (gRightTexture.loadFromFile("src/assets/right.png") == false) {
    SDL_Log("Unable to load right png image!\n");
    success = false;
  }

  return success;
}

void close() {
  gUpTexture.destroy();
  gDownTexture.destroy();
  gLeftTexture.destroy();
  gRightTexture.destroy();

  SDL_DestroyRenderer(gRenderer);
  gRenderer = nullptr;
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  SDL_Quit();
}

