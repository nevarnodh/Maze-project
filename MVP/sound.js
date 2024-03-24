// Initialize audio context
const audioContext = new (window.AudioContext || window.webkitAudioContext)();

// Function to load and play a sound effect
function playSoundEffect(soundFile) {
    // Load sound file
    fetch(soundFile)
        .then(response => response.arrayBuffer())
        .then(buffer => audioContext.decodeAudioData(buffer))
        .then(audioBuffer => {
            // Create audio buffer source
            const source = audioContext.createBufferSource();
            source.buffer = audioBuffer;

            // Connect source to output
            source.connect(audioContext.destination);

            // Play sound effect
            source.start(0);
        })
        .catch(error => console.error("Error loading sound:", error));
}

// Example: Play sound effect when player moves
function movePlayer() {
    // Your player movement code here
    console.log("Player moved");
    
    // Play sound effect
    playSoundEffect('"C:\Users\user\Downloads\Alan Walker - World Of Walker (2021) [24 Bit Hi-Res] FLAC [PMEDIA] ⭐️\01. Time  (Alan Walker Remix).flac"');
}

// Example: Play sound effect when player interacts with something
function playerInteraction() {
    // Your player interaction code here
    console.log("Player interacted");
    
    // Play sound effect
    playSoundEffect('"C:\Users\user\Downloads\Alan Walker - World Of Walker (2021) [24 Bit Hi-Res] FLAC [PMEDIA] ⭐️\01. Time  (Alan Walker Remix).flac"');
}

