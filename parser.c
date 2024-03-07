To implement a parser that reads the map from a file, we can define a simple standard where the map file contains characters representing walls and empty spaces. We'll use a ".map" extension for our map files. Here's how we can modify the code:

```c
// File: src/main.c

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
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

void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int color) {
    SDL_SetRenderDrawColor(renderer, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, 0xFF);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawMap(SDL_Renderer *renderer, char **map, int mapWidth, int mapHeight) {
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

void rotateCamera(double *dirX, double *dirY, double rotateAngle) {
    double oldDirX = *dirX;
    *dirX = *dirX * cos(rotateAngle) - *dirY * sin(rotateAngle);
    *dirY = oldDirX * sin(rotateAngle) + *dirY * cos(rotateAngle);
}

void moveCamera(char **map, int mapWidth, int mapHeight, double *posX, double *posY, double *dirX, double *dirY, int direction) {
    double moveStep = direction * MOVE_SPEED;
    int newPosX = *posX + *dirX * moveStep;
    int newPosY = *posY + *dirY * moveStep;
    if (map[(int)newPosX][(int)*posY] != '1') {
        *posX = newPosX;
    }
    if (map[(int)*posX][(int)newPosY] != '1') {
        *posY = newPosY;
    }
}

char **parseMapFile(const char *filename, int *mapWidth, int *mapHeight) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return NULL;
    }

    // Get map dimensions
    fscanf(file, "%d %d", mapWidth, mapHeight);

    // Allocate memory for the map
    char **map = (char **)malloc(sizeof(char *) * (*mapWidth));
    for (int i = 0; i < *mapWidth; i++) {
        map[i] = (char *)malloc(sizeof(char) * (*mapHeight));
    }

    // Read map data from file
    for (int y = 0; y < *mapHeight; y++) {
        for (int x = 0; x < *mapWidth; x++) {
            fscanf(file, " %c", &map[x][y]);
        }
    }

    fclose(file);
    return map;
}

void freeMap(char **map, int mapWidth) {
    for (int i = 0; i < mapWidth; i++) {
        free(map[i]);
    }
    free(map);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

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

    // Parse map file
    int mapWidth, mapHeight;
    char **map = parseMapFile(argv[1], &mapWidth, &mapHeight);
    if (map == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Camera variables
    double posX = 2.0;
    double posY = 2.0;
    double dirX = 1.0;
    double dirY = 0.0;

    // Main loop
    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        rotateCamera(&dirX, &dirY, ROTATE_SPEED);
                        break;
                    case SDLK_RIGHT:
                        rotateCamera(&dirX, &dirY, -ROTATE_SPEED);
                       
