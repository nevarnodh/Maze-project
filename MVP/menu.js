// Function to toggle visibility of settings menu
function toggleSettingsMenu() {
    const settingsMenu = document.getElementById('settingsMenu');
    settingsMenu.style.display = (settingsMenu.style.display === 'none') ? 'block' : 'none';
}

// Function to start the game
function startGame() {
    // Your game initialization code goes here
    console.log("Game started!");
}

// Event listeners for menu buttons
document.getElementById('startButton').addEventListener('click', startGame);
document.getElementById('settingsButton').addEventListener('click', toggleSettingsMenu);

