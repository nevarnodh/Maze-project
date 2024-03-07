To handle collisions between the player and walls, we need to modify the movement functions to check if the next position of the player intersects with a wall. If it does, we'll adjust the player's position accordingly to prevent them from entering the wall. We can implement a simple sliding mechanism to allow the player to slide along the wall.

Here's the modified code with collision handling:

```c
// File: src/main.c

#include <SDL2/SDL.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
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

// Camera variables
double posX = 2.0;
double posY = 2.0;
double dirX = 1.0;
double dirY = 0.0;
double planeX = 0.0;
double planeY = 0.66; // The 2D raycaster version of camera plane

void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int color) {
    SDL_SetRenderDrawColor(renderer, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, 0xFF);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawMap(SDL_Renderer *renderer) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            if (worldMap[x][y] == 1) {
                // Calculate wall color based on orientation
                int wallColor = (x + y) % 2 == 0 ? RED : GREEN;

                // Draw walls
                drawLine(renderer, x * (SCREEN_WIDTH / MAP_WIDTH), y * (SCREEN_HEIGHT / MAP_HEIGHT),
                         (x + 1) * (SCREEN_WIDTH / MAP_WIDTH), y * (SCREEN_HEIGHT / MAP_HEIGHT), wallColor);
                drawLine(renderer, (x + 1) * (SCREEN_WIDTH / MAP_WIDTH), y * (SCREEN_HEIGHT / MAP_HEIGHT),
                         (x + 1) * (SCREEN_WIDTH / MAP_WIDTH), (y + 1) * (SCREEN_HEIGHT / MAP_HEIGHT), wallColor);
                drawLine(renderer, (x + 1) * (SCREEN_WIDTH / MAP_WIDTH), (y + 1) * (SCREEN_HEIGHT / MAP_HEIGHT),
                         x * (SCREEN_WIDTH / MAP_WIDTH), (y + 1) * (SCREEN_HEIGHT / MAP_HEIGHT), wallColor);
                drawLine(renderer, x * (SCREEN_WIDTH / MAP_WIDTH), (y + 1) * (SCREEN_HEIGHT / MAP_HEIGHT),
                         x * (SCREEN_WIDTH / MAP_WIDTH), y * (SCREEN_HEIGHT / MAP_HEIGHT), wallColor);
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

void rotateCamera(double angle) {
    // Rotate direction and camera plane vectors
    double oldDirX = dirX;
    dirX = dirX * cos(angle) - dirY * sin(angle);
    dirY = oldDirX * sin(angle) + dirY * cos(angle);
    double oldPlaneX = planeX;
    planeX = planeX * cos(angle) - planeY * sin(angle);
    planeY = oldPlaneX * sin(angle) + planeY * cos(angle);
}

void moveCamera(int direction) {
    // Move camera forward or backward
    double moveStep = direction * MOVE_SPEED;
    if (worldMap[(int)(posX + dirX * moveStep)][(int)posY] == 0) posX += dirX * moveStep;
    if (worldMap[(int)posX][(int)(posY + dirY * moveStep)] == 0) posY += dirY * moveStep;
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
            } else if (event.type == SDL_KEYDOWN) {
                // Rotate camera when left or right arrow key is pressed
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        rotateCamera(ROTATE_SPEED); // Rotate left
                        break;
                    case SDLK_RIGHT:
                        rotateCamera(-ROTATE_SPEED); // Rotate right
                        break;
                    case SDLK_w:
                        moveCamera(1); // Move forward
                        break;
                    case SDLK_s:
                        moveCamera(-1); // Move backward
                        break;
                }
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, (BLACK >>
