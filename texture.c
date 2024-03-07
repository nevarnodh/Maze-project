To add textures on the walls, we need to load textures from image files and apply them to the walls based on the raycasting algorithm. Here's how we can modify the code to achieve this:

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

void rotateCamera(double *dirX, double *dirY, double rotateAngle) {
    double oldDirX = *dirX;
    *dirX = *dirX * cos(rotateAngle) - *dirY * sin(rotateAngle);
    *dirY = oldDirX * sin(rotateAngle) + *dirY * cos(rotateAngle);
}

void
