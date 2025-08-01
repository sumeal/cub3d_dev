#!/bin/bash

echo "Setting up cub3D project..."

# Install dependencies
echo "Installing dependencies..."
sudo apt-get update
sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev

# Clone and build MLX
if [ ! -d "mlx_linux" ]; then
    echo "Cloning MLX library..."
    git clone https://github.com/42Paris/minilibx-linux.git mlx_linux
fi

cd mlx_linux
echo "Building MLX library..."
make
cd ..

echo "Setup complete! You can now build cub3D with 'make'"
echo "Run the game with: ./cub3D maps/test.cub"
echo ""
echo "Controls:"
echo "  WASD - Move around"
echo "  Left/Right arrows - Look around"
echo "  ESC - Exit"
