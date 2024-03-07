nclude <stdio.h>
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
SDL_Texture *raindropTexture = NULL;
SDL_Renderer *renderer = NULL;

// Raindrop structure
typedef struct {
    double x;
    double y;
    double speed;
} Raindrop;

// Array to store raindrops
Raindrop raindrops[100];

// Variable to control rain
int drawRain = 0;

// Shadow casting
int castShadow(int x, int y, char **map) {
    // Check if the position (x, y) is within the map bounds
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
        return 1; // Out of bounds, consider as shadow
    }

    // Check if the position (x, y) contains a wall
    if (map[x][y] == '1') {
        return 1; // Wall, consider as shadow
    }

    return 0; // No shadow
}

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
    // ...

    // Calculate shadow and lighting effects
    double planeX = 0.0;
    double planeY = 0.66;
    double cameraX = 2 * posX / SCREEN_WIDTH - 1;
    double rayDirX = dirX + planeX * cameraX;
    double rayDirY = dirY + planeY * cameraX;
    int mapX = (int)posX;
    int mapY = (int)posY;
    double sideDistX, sideDistY;
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);
    double perpWallDist;
    int stepX, stepY;
    int hit = 0;
    int side;

    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    while (!hit) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (map[mapX][mapY] == '1') hit = 1;
    }

    if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
    else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

    int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

    int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (drawStart < 0) drawStart = 0;
    int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

    // Apply shadows and lighting effects
    for (int x = drawStart; x < drawEnd; x++) {
        double wallX; // Exact position of where the wall was hit
        if (side == 0) wallX = posY + perpWallDist * rayDirY;
        else           wallX = posX + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        // Texture coordinate
        int texX = (int)(wallX * (double)wallTextureWidth);
        if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0)) texX = wallTextureWidth - texX - 1;

        // Calculate darkness based on distance
        double darkness = 1.0 - (perpWallDist / 10.0); // Adjust 10.0 for desired shadow intensity
        if (darkness < 0.0) darkness = 0.0;

        // Get texture color
        Uint32 color = getPixel(wallTexture, texX, x);
        Uint8 r = (color >> 16) & 0xFF;
        Uint8 g = (color >> 8) & 0xFF;
        Uint8 b = color & 0xFF;

        // Apply darkness
        r *= darkness;
        g *= darkness;
        b *= darkness;

        // Render the pixel with shadow and lighting effect
        SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
        SDL_RenderDrawPoint(renderer, x, x);
    }
}

// Load textures
void loadTextures() {
    // Load wall, floor, ceiling, and weapon textures
    // ...

    // Load raindrop texture
    // ...
}

// Free textures
void freeTextures() {
    // Free wall, floor, ceiling, and weapon textures
    // ...
}

// Initialize raindrops
void initRain() {
    // Initialize raindrops
    // ...
}

// Update raindrops
void updateRain() {
    // Update raindrops
    // ...
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
        // ...

        // Clear screen
        // ...

        // Update raindrops
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

