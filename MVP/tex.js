// Create a scene
const scene = new THREE.Scene();

// Create a camera
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.z = 5;

// Create a renderer
const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

// Create a cube geometry
const geometry = new THREE.BoxGeometry(1, 1, 1);

// Load textures
const textureLoader = new THREE.TextureLoader();
const wallTexture = textureLoader.load('path_to_wall_texture.jpg');

// Create materials with textures
const material = new THREE.MeshBasicMaterial({ map: wallTexture });

// Create a cube mesh with the textured material
const cube = new THREE.Mesh(geometry, material);
scene.add(cube);

// Function to handle window resize
function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}

// Event listener for window resize
window.addEventListener('resize', onWindowResize);

// Main render function
function animate() {
    requestAnimationFrame(animate);

    // Rotate the cube
    cube.rotation.x += 0.01;
    cube.rotation.y += 0.01;

    renderer.render(scene, camera);
}

// Call the main render function
animate();

