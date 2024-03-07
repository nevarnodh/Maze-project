// File: src/main.c

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 8
#define MAP_HEIGHT 8

// Define colors
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF

// Map representing walls (1) and empty spaces (0)
int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int color) {
    SDL_SetRenderDrawColor(renderer, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, 0xFF);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawMap(SDL_Renderer *renderer) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            if (worldMap[x][y] == 1) {
                // Draw walls
                drawLine(renderer, x * (SCREEN_WIDTH / MAP_WIDTH), y * (SCREEN_HEIGHT / MAP_HEIGHT),
                         (x + 1) * (SCREEN_WIDTH / MAP_WIDTH), y * (SCREEN_HEIGHT / MAP_HEIGHT), RED);
                drawLine(renderer, (x + 1) * (SCREEN_WIDTH / MAP_WIDTH), y * (SCREEN_HEIGHT / MAP_HEIGHT),
                         (x + 1) * (SCREEN_WIDTH / MAP_WIDTH), (y + 1) * (SCREEN_HEIGHT / MAP_HEIGHT), RED);
                drawLine(renderer, (x + 1) * (SCREEN_WIDTH / MAP_WIDTH), (y + 1) * (SCREEN_HEIGHT / MAP_HEIGHT),
                         x * (SCREEN_WIDTH / MAP_WIDTH), (y + 1) * (SCREEN_HEIGHT / MAP_HEIGHT), RED);
                drawLine(renderer, x * (SCREEN_WIDTH / MAP_WIDTH), (y + 1) * (SCREEN_HEIGHT / MAP_HEIGHT),
                         x * (SCREEN_WIDTH / MAP_WIDTH), y * (SCREEN_HEIGHT / MAP_HEIGHT), RED);
            } else {
                // Draw empty spaces
                SDL_SetRenderDrawColor(renderer, (BLACK >> 16) & 0xFF, (BLACK >> 8) & 0xFF, BLACK & 0xFF, 0xFF);
                SDL_Rect rect = {x * (SCREEN_WIDTH / MAP_WIDTH), y * (SCREEN_HEIGHT / MAP_HEIGHT),
                                 SCREEN_WIDTH / MAP_WIDTH, SCREEN_HEIGHT / MAP_HEIGHT};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

int main() {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Quit();
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, (BLACK >> 16) & 0xFF, (BLACK >> 8) & 0xFF, BLACK & 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Draw map
        drawMap(renderer);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

