To add weapon textures, you can follow a similar approach as with the wall, floor, and ceiling textures. Here's how you can modify the code to include weapon textures:

```c
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
SDL_Texture *weaponTexture = NULL; // Added weapon texture
SDL_Renderer *renderer = NULL;

void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int color) {
    SDL_SetRenderDrawColor(renderer, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, 0xFF);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawMap(SDL_Renderer *renderer, char **map, int mapWidth, int mapHeight,
             double posX, double posY, double dirX, double dirY,
             int drawMapEnabled) {
    // Draw the map
    if (drawMapEnabled) {
        for (int x = 0; x < mapWidth; x++) {
            for (int y = 0; y < mapHeight; y++) {
                if (map[x][y] == '1') {
                    drawLine(renderer, x * (SCREEN_WIDTH / mapWidth), y * (SCREEN_HEIGHT / mapHeight),
                             (x + 1) * (SCREEN_WIDTH / mapWidth), y * (SCREEN_HEIGHT / mapHeight), RED);
                    drawLine(renderer, (x + 1) * (SCREEN_WIDTH / mapWidth), y * (SCREEN_HEIGHT / mapHeight),
                             (x + 1) * (SCREEN_WIDTH / mapWidth), (y + 1) * (SCREEN_HEIGHT / mapHeight), RED);
                    drawLine(renderer, (x + 1) * (SCREEN_WIDTH / mapWidth), (y + 1) * (SCREEN_HEIGHT / mapHeight),
                             x * (SCREEN_WIDTH / mapWidth), (y + 1) * (SCREEN_HEIGHT / mapHeight), RED);
                    drawLine(renderer, x * (SCREEN_WIDTH / mapWidth), (y + 1) * (SCREEN_HEIGHT / mapHeight),
                             x * (SCREEN_WIDTH / mapWidth), y * (SCREEN_HEIGHT / mapHeight), RED);
                } else {
                    SDL_SetRenderDrawColor(renderer, (BLACK >> 16) & 0xFF, (BLACK >> 8) & 0xFF, BLACK & 0xFF, 0xFF);
                    SDL_Rect rect = {x * (SCREEN_WIDTH / mapWidth), y * (SCREEN_HEIGHT / mapHeight),
                                     SCREEN_WIDTH / mapWidth, SCREEN_HEIGHT / mapHeight};
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }

    // Draw the ground texture
    // ...

    // Draw the ceiling texture
    // ...

    // Draw the weapon texture
    if (weaponTexture != NULL) {
        SDL_Rect weaponRect = {(SCREEN_WIDTH - weaponWidth) / 2, SCREEN_HEIGHT - weaponHeight, weaponWidth, weaponHeight};
        SDL_RenderCopy(renderer, weaponTexture, NULL, &weaponRect);
    }

    // Draw the player's line of sight
    // ...
}

// Load textures
void loadTextures() {
    wallTexture = loadTexture(renderer, "wall_texture.png");
    floorTexture = loadTexture(renderer, "floor_texture.png");
    ceilingTexture = loadTexture(renderer, "ceiling_texture.png");
    weaponTexture = loadTexture(renderer, "weapon_texture.png"); // Load weapon texture
}

// Free textures
void freeTextures() {
    // Free wall, floor, ceiling textures
    // ...

    if (weaponTexture != NULL) {
        SDL_DestroyTexture(weaponTexture); // Free weapon texture
    }
}

// Main function
int main(int argc, char *argv[]) {
    // Initialize SDL and create window/renderer
    // ...

    // Load textures
    loadTextures();

    // Main loop
    while (running) {
        // Handle events
        // ...

        // Clear screen
        // ...

        // Draw map
        drawMap(renderer, map, mapWidth, mapHeight, posX, posY, dirX, dirY, drawMapEnabled);

        // Present renderer
        // ...
    }

    // Free resources
    freeTextures();
    // ...

    return 0
}

