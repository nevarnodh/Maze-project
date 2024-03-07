// File: src/main.c

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MOVE_SPEED 0.05
#define ROTATE_SPEED 0.05

// Define colors
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define CYAN 0x00FFFF

// Texture variables
SDL_Texture *wallTexture = NULL;
SDL_Texture *floorTexture = NULL;
SDL_Texture *ceilingTexture = NULL;
SDL_Texture *weaponTexture = NULL;
SDL_Texture *raindropTexture = NULL; // Added raindrop texture
SDL_Renderer *renderer = NULL;

// Raindrop structure
typedef struct {
    double x;
    double y;
    double speed;
} Raindrop;

// Array to store raindrops
Raindrop raindrops[100];

void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int color) {
    SDL_SetRenderDrawColor(renderer, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, 0xFF);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawMap(SDL_Renderer *renderer, char **map, int mapWidth, int mapHeight,
             double posX, double posY, double dirX, double dirY,
             int drawMapEnabled) {
    // Draw the map
    // ...

    // Draw the ground texture
    // ...

    // Draw the ceiling texture
    // ...

    // Draw the weapon texture
    // ...

    // Draw the player's line of sight
    // ...

    // Draw raindrops
    if (drawRain) {
        for (int i = 0; i < 100; ++i) {
            SDL_Rect raindropRect = {(int)raindrops[i].x, (int)raindrops[i].y, 2, 10};
            SDL_RenderCopy(renderer, raindropTexture, NULL, &raindropRect);
        }
    }
}

// Load textures
void loadTextures() {
    // Load wall, floor, ceiling, and weapon textures
    // ...

    // Load raindrop texture
    raindropTexture = loadTexture(renderer, "raindrop_texture.png");
}

// Free textures
void freeTextures() {
    // Free wall, floor, ceiling, and weapon textures
    // ...

    if (raindropTexture != NULL) {
        SDL_DestroyTexture(raindropTexture); // Free raindrop texture
    }
}

// Initialize raindrops
void initRain() {
    for (int i = 0; i < 100; ++i) {
        raindrops[i].x = (double)(rand() % SCREEN_WIDTH);
        raindrops[i].y = (double)(-rand() % SCREEN_HEIGHT);
        raindrops[i].speed = (double)(1 + rand() % 5);
    }
}

// Update raindrops
void updateRain() {
    for (int i = 0; i < 100; ++i) {
        raindrops[i].y += raindrops[i].speed;
        if (raindrops[i].y > SCREEN_HEIGHT) {
            raindrops[i].y = -10;
            raindrops[i].x = (double)(rand() % SCREEN_WIDTH);
        }
    }
}

// Main function
int main(int argc, char *argv[]) {
    // Initialize SDL and create window/renderer
    // ...

    // Load textures
    loadTextures();

    // Initialize raindrops
    initRain();

    // Main loop
    while (running) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {
                    drawRain = !drawRain; // Toggle rain
                }
            }
        }

        // Clear screen
        // ...

        // Update raindrops
        updateRain();

        // Draw map
        drawMap(renderer, map, mapWidth, mapHeight, posX, posY, dirX, dirY, drawMapEnabled);

        // Present renderer
        // ...
    }

    // Free resources
    freeTextures();
    // ...

    return 0;
}

