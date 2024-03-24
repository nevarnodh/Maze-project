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

// Function to apply settings changes
function applySettings() {
    const resolution = document.getElementById('resolution').value;
    const fullscreen = document.getElementById('fullscreen').checked;

    // Apply resolution settings
    console.log("Resolution set to: " + resolution);

    // Apply fullscreen settings
    if (fullscreen) {
        // Enter fullscreen mode
        console.log("Fullscreen enabled");
    } else {
        // Exit fullscreen mode
        console.log("Fullscreen disabled");
    }
}

// Event listeners for menu buttons
document.getElementById('startButton').addEventListener('click', startGame);
document.getElementById('settingsButton').addEventListener('click', toggleSettingsMenu);
document.getElementById('resolution').addEventListener('change', applySettings);
document.getElementById('fullscreen').addEventListener('change', applySettings);

