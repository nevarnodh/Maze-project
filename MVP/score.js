// Initialize score
let score = 0;

// Function to update score
function updateScore(points) {
    score += points;
    document.getElementById('score').innerText = "Score: " + score;
}

// Function to handle player reaching the goal
function playerReachedGoal() {
    // Increment score
    updateScore(100);

    // Display victory message or perform other actions
    console.log("Congratulations! You reached the goal!");
}

// Example: Check for player reaching the goal
function checkGoal() {
    // Your code to check if the player has reached the goal
    if (playerReachedGoalConditionMet) {
        playerReachedGoal();
    }
}

// Main game loop (not shown): Call checkGoal() function periodically

// Example: Update score when player collects an item
function playerCollectsItem() {
    // Your code to handle player collecting an item
    console.log("Player collected an item");

    // Increment score
    updateScore(10);
}

