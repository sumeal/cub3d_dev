# cub3D - 3D Raycasting Game Engine

A 3D game engine inspired by Wolfenstein 3D, built using raycasting techniques as part of the 42 School curriculum.

## Features

- **Raycasting Engine**: Real-time 3D rendering using 2D raycasting
- **Texture Mapping**: Support for wall textures in XPM format
- **Player Movement**: WASD movement and arrow key rotation
- **Map Parsing**: Custom .cub map format with validation
- **MLX Graphics**: Uses the MiniLibX graphics library

## Controls

- **W, A, S, D**: Move forward, left, backward, right
- **Left/Right Arrow Keys**: Rotate camera
- **ESC**: Exit the game

## Installation

### Prerequisites

Make sure you have the following installed:
- GCC compiler
- X11 development libraries
- Make

On Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

### Building

1. Clone the repository (if not already done)
2. Navigate to the project directory:
   ```bash
   cd cub3d
   ```
3. Build the project:
   ```bash
   make
   ```

This will automatically:
- Download and build the MLX library
- Compile all source files
- Create the `cub3D` executable

## Usage

```bash
./cub3D maps/test.cub
```

## Map Format

Maps use the `.cub` extension and must contain:

### Texture Paths
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
```

### Colors (RGB format)
```
F 220,100,0    # Floor color
C 225,200,200  # Ceiling color
```

### Map Layout
- `1`: Wall
- `0`: Empty space
- `N/S/E/W`: Player starting position and orientation
- ` ` (space): Outside area

Example map:
```
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## Project Structure

```
cub3d/
├── Makefile
├── README.md
├── inc/
│   └── cub3d.h              # Main header file
├── src/
│   ├── main.c               # Program entry point
│   ├── parsing/             # Map and texture parsing
│   ├── raycasting/          # Raycasting engine
│   ├── rendering/           # Graphics rendering
│   ├── game/                # Game loop and input
│   └── utils/               # Utility functions
├── maps/
│   └── test.cub             # Sample map
├── textures/
│   ├── north.xpm            # North wall texture
│   ├── south.xpm            # South wall texture
│   ├── west.xpm             # West wall texture
│   └── east.xpm             # East wall texture
└── mlx_linux/               # MLX library (auto-downloaded)
```

## Technical Details

### Raycasting Algorithm

The engine uses a DDA (Digital Differential Analyzer) algorithm to:
1. Cast rays from the player position for each screen column
2. Calculate wall distances and heights
3. Apply texture mapping
4. Render walls with proper perspective

### Performance

- Real-time rendering at 1024x768 resolution
- Efficient wall collision detection
- Optimized texture sampling

## Cleaning

```bash
make clean     # Remove object files
make fclean    # Remove object files and executable
make re        # Rebuild everything
```

## Common Issues

1. **MLX not found**: Make sure X11 development libraries are installed
2. **Segmentation fault**: Check map format and ensure all required textures exist
3. **Black screen**: Verify texture paths in the .cub file are correct

## Credits

- Based on the cub3D project from 42 School
- Uses raycasting techniques pioneered by id Software (Wolfenstein 3D)
- MLX library by 42 School
