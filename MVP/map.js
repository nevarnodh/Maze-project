// Define an array to hold wall meshes
const wallMeshes = [];

// Function to create a wall
function createWall(x, y, z) {
    const wallGeometry = new THREE.BoxGeometry(wallWidth, wallHeight, wallDepth);
    const wallMaterial = new THREE.MeshBasicMaterial({ color: 0x808080 });
    const wallMesh = new THREE.Mesh(wallGeometry, wallMaterial);
    wallMesh.position.set(x, y, z);
    scene.add(wallMesh);
    wallMeshes.push(wallMesh);
}

// Function to remove a wall
function removeWall(wallMesh) {
    scene.remove(wallMesh);
    wallMeshes.splice(wallMeshes.indexOf(wallMesh), 1);
}

// Function to handle user interaction
function handleUserInteraction() {
    // Example: Add wall button
    const addWallButton = document.getElementById('addWallButton');
    addWallButton.addEventListener('click', () => {
        const posX = parseFloat(document.getElementById('wallPosX').value);
        const posY = parseFloat(document.getElementById('wallPosY').value);
        const posZ = parseFloat(document.getElementById('wallPosZ').value);
        createWall(posX, posY, posZ);
    });

    // Example: Remove wall button
    const removeWallButton = document.getElementById('removeWallButton');
    removeWallButton.addEventListener('click', () => {
        if (wallMeshes.length > 0) {
            const removedWall = wallMeshes.pop();
            removeWall(removedWall);
        }
    });
}

// Call function to handle user interaction
handleUserInteraction();

