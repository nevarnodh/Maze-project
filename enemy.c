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
SDL_Texture *enemyTexture = NULL; // Added enemy texture
SDL_Renderer *renderer = NULL;

// Enemy structure
typedef struct {
    double posX;
    double posY;
    double health;
} Enemy;

Enemy enemies[10]; // Array of enemies
int numEnemies = 0;

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

    // Draw the enemies
    if (enemyTexture != NULL) {
        for (int i = 0; i < numEnemies; i++) {
            SDL_Rect enemyRect = {(int)(enemies[i].posX), (int)(enemies[i].posY), enemyWidth, enemyHeight};
            SDL_RenderCopy(renderer, enemyTexture, NULL, &enemyRect);
        }
    }

    // Draw the player's line of sight
    // ...
}

// Load textures
void loadTextures() {
    // Load wall, floor, ceiling, weapon, and enemy textures
    // ...
}

// Free textures
void freeTextures() {
    // Free wall, floor, ceiling, weapon, and enemy textures
    // ...
}

// Main function
int main(int argc, char *argv[]) {
    // Initialize SDL and create window/renderer
    // ...

    // Load textures
    loadTextures();

    // Add enemies
    // For demonstration purposes, let's add some enemies with random positions and health
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        enemies[i].posX = (rand() % SCREEN_WIDTH);
        enemies[i].posY = (rand() % SCREEN_HEIGHT);
        enemies[i].health = 100; // Initial health of enemies
        numEnemies++;
    }

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

    return 0;
}

