#include <SDL3/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    printf("SDL initialized successfully\n");

    // Add SDL_WINDOW_RESIZABLE flag
    SDL_Window* window = SDL_CreateWindow("SDL3 Window (C Example)",
                                          640, 480,
                                          SDL_WINDOW_RESIZABLE); // <--- ADD THIS FLAG
    if (!window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    printf("Window created successfully\n");

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    printf("Renderer created successfully\n");
    
    // You might not need SDL_ShowWindow/RaiseWindow explicitly,
    // as tiling WMs often handle visibility.
    // SDL_ShowWindow(window);
    // SDL_RaiseWindow(window);

    // Main loop
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
            // Handle window resizing events
            else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                // In a tiling WM, the window's size will be managed by the WM.
                // You usually don't need to manually resize the renderer here,
                // but if you have a complex rendering setup, you might need to
                // update your viewport or re-create textures/render targets.
                // For this simple example, SDL_RenderPresent handles it.
            }
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
        SDL_RenderClear(renderer);

        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        int rectSize = 100; // Size of the square
        SDL_FRect fillRect = {
            (float)(windowWidth / 2) - (rectSize / 2),  // x
            (float)(windowHeight / 2) - (rectSize / 2), // y
            (float)rectSize,                            // width
            (float)rectSize                             // height
        };

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
        SDL_RenderFillRect(renderer, &fillRect);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
