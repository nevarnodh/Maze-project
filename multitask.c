To handle multiple events on the same frame, we need to modify the main loop to check for multiple key events simultaneously. Here's how we can modify the code to handle moving in several directions and rotating at the same time:

```c
// Main loop
int running = 1;
while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            const Uint8 *state = SDL_GetKeyboardState(NULL);

            double moveDirection = 0.0;
            double rotateDirection = 0.0;

            if (state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S]) {
                moveDirection = 1.0;
            } else if (!state[SDL_SCANCODE_W] && state[SDL_SCANCODE_S]) {
                moveDirection = -1.0;
            }

            if (state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]) {
                rotateDirection = 1.0;
            } else if (!state[SDL_SCANCODE_A] && state[SDL_SCANCODE_D]) {
                rotateDirection = -1.0;
            }

            // Rotate and move camera
            if (rotateDirection != 0.0) {
                rotateCamera(&dirX
