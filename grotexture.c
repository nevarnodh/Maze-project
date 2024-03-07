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
    if (floorTexture != NULL) {
        for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; ++y) {
            double rayDirX0 = dirX - dirY;
            double rayDirY0 = dirY + dirX;
            double rayDirX1 = dirX + dirY;
            double rayDirY1 = dirY - dirX;

            int p = y - SCREEN_HEIGHT / 2;
            double posZ = 0.5 * SCREEN_HEIGHT;

            double rowDistance = posZ / p;

            double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
            double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

            double floorX = posX + rowDistance * rayDirX0;
            double floorY = posY + rowDistance * rayDirY0;

            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                int cellX = (int)(floorX);
                int cellY = (int)(floorY);

                int tx = (int)(floorTextureWidth * (floorX - cellX)) & (floorTextureWidth - 1);
                int ty = (int)(floorTextureHeight * (floorY - cellY)) & (floorTextureHeight - 1);

                floorX += floorStepX;
                floorY += floorStepY;

                Uint32 color = getPixel(floorTexture, tx, ty);
                SDL_SetRenderDrawColor(renderer, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, 0xFF);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    // Draw the ceiling texture
    if (ceilingTexture != NULL) {
        for (int y = 0; y < SCREEN_HEIGHT / 2; ++y) {
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                Uint32 color = getPixel(ceilingTexture, x % ceilingTextureWidth, y % ceilingTextureHeight);
                SDL_SetRenderDrawColor(renderer, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, 0xFF);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    // Draw the player's line of sight
    double planeX = 0.0;
    double planeY = 0.66; // The 2D raycaster version of camera plane
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

    drawLine(renderer, SCREEN_WIDTH / 2, drawStart, SCREEN_WIDTH / 2, drawEnd, BLUE);
}

// Load textures
void loadTextures() {
    wallTexture = loadTexture(renderer, "wall_texture.png");
    floorTexture = loadTexture(renderer, "floor_texture.png");
    ceilingTexture = loadTexture(renderer, "ceiling_texture.png");
}

// Free textures
void freeTextures() {
    if (wallTexture != NULL) {
        SDL_DestroyTexture(wallTexture);
    }
    if (floorTexture != NULL) {
        SDL_DestroyTexture(floorTexture);
    }
    if (ceilingTexture != NULL) {
        SDL_DestroyTexture(ceilingTexture);
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

    return 0;
}

