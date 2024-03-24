let gameOver = false;

// Function to handle game over
function handleGameOver(message) {
    gameOver = true;
    // Display game over message
    document.getElementById('gameOverMessage').innerText = message;
    document.getElementById('gameOverScreen').style.display = 'block';
}

// Example: Function to check if the player has collided with an enemy
function checkCollisionWithEnemy() {
    // Your code to check if the player has collided with an enemy
    if (collisionWithEnemyConditionMet) {
        handleGameOver("You were defeated by an enemy!");
    }
}

// Example: Function to check if the player has reached the goal
function checkGoal() {
    // Your code to check if the player has reached the goal
    if (goalReachedConditionMet) {
        handleGameOver("Congratulations! You reached the goal!");
    }
}

// Main game loop (not shown): Call checkCollisionWithEnemy() and checkGoal() functions periodically

