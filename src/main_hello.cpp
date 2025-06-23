#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <string>

constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 400 };

SDL_Window* gWindow{ nullptr };

SDL_Surface* gScreenSurface{ nullptr };

SDL_Surface* gHelloWorld{ nullptr };

bool init();

bool loadMedia();

void close();

int main(int argc, char* args[]) {
  int exitCode{ 0 };

  if (init() == false) {
    SDL_Log("Unable to initialize program!\n");
    exitCode = 1;
  } else {
    if (loadMedia() == false) {
      SDL_Log("Unable to load meida!\n");
    } else {
      bool quite{ false };

      SDL_Event e;
      SDL_zero(e);

      while (quite == false) {
        while (SDL_PollEvent(&e) == true) {
          if (e.type == SDL_EVENT_QUIT) {
            quite = true;
          }
        }

        SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));
        SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }

  close();

  return exitCode;
}

bool init() {
  bool success{ true };

  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    success = false;
  } else {
      if(gWindow = SDL_CreateWindow( "SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0); gWindow == nullptr) {
          SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
          success = false;
      } else {
          gScreenSurface = SDL_GetWindowSurface(gWindow);
      }
  }

  return success;
}

bool loadMedia() {
    //File loading flag
    bool success{ true };

    //Load splash image
    std::string imagePath{ "src/assets/sample_640×426.bmp"};
    if( gHelloWorld = SDL_LoadBMP( imagePath.c_str() ); gHelloWorld == nullptr ) {
        SDL_Log("Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError());
        success = false;
    }

    return success;
}

void close() {
    //Clean up surface
    SDL_DestroySurface(gHelloWorld);
    gHelloWorld = nullptr;
    
    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gScreenSurface = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}
