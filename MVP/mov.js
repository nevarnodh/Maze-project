// Define constants for movement speed and key codes
const MOVE_SPEED = 0.1;
const KEY_W = 87;
const KEY_A = 65;
const KEY_S = 83;
const KEY_D = 68;
const ARROW_UP = 38;
const ARROW_LEFT = 37;
const ARROW_DOWN = 40;
const ARROW_RIGHT = 39;

// Define player object with initial position
let player = {
    x: 0,
    y: 0
};

// Function to handle keyboard input
function handleKeyPress(e) {
    switch(e.keyCode) {
        case KEY_W:
        case ARROW_UP:
            player.y -= MOVE_SPEED; // Move up
            break;
        case KEY_A:
        case ARROW_LEFT:
            player.x -= MOVE_SPEED; // Move left
            break;
        case KEY_S:
        case ARROW_DOWN:
            player.y += MOVE_SPEED; // Move down
            break;
        case KEY_D:
        case ARROW_RIGHT:
            player.x += MOVE_SPEED; // Move right
            break;
    }
}

// Event listener to capture keyboard input
document.addEventListener("keydown", handleKeyPress);

// Main game loop (not shown): Update game state and render scene

