# Cub3D - Raycasting Game Engine

A 3D game engine inspired by Wolfenstein 3D, built using raycasting techniques.

## Overview

Cub3D is a simple raycasting-based 3D game engine that renders a maze-like environment. The player can move around and look in different directions, with textured walls and basic lighting effects.

## Features

- **Raycasting Engine**: Efficient 3D rendering using 2D raycasting
- **Textured Walls**: Different textures for North, South, East, and West walls
- **Player Movement**: WASD movement with arrow key rotation
- **Map Parsing**: Reads custom .cub map files
- **Collision Detection**: Prevents walking through walls
- **Configurable Colors**: Custom floor and ceiling colors

## Building and Running

### Prerequisites

- GCC compiler
- Make
- X11 development libraries
- MLX library (MiniLibX)

### Setup

1. Run the setup script to install dependencies and MLX:
```bash
chmod +x setup.sh
./setup.sh
```

2. Build the project:
```bash
make
```

3. Run the game with a map file:
```bash
./cub3D maps/test.cub
```

## Controls

- **W/A/S/D**: Move forward/left/backward/right
- **Left/Right Arrow Keys**: Rotate view
- **ESC**: Exit the game

## Map Format

Map files use the `.cub` extension and contain:

### Texture Paths
```
NO ./textures/north.xpm    # North wall texture
SO ./textures/south.xpm    # South wall texture  
WE ./textures/west.xpm     # West wall texture
EA ./textures/east.xpm     # East wall texture
```

### Colors
```
F 220,100,0     # Floor color (RGB)
C 225,200,200   # Ceiling color (RGB)
```

### Map Layout
- `1`: Wall
- `0`: Empty space
- `N/S/E/W`: Player starting position and orientation
- ` ` (space): Void

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
├── inc/
│   └── cub3d.h
├── src/
│   ├── main.c
│   ├── parsing/
│   │   ├── parse_map.c
│   │   ├── parse_textures.c
│   │   └── validation.c
│   ├── raycasting/
│   │   ├── raycasting.c
│   │   ├── dda.c
│   │   └── texture.c
│   ├── rendering/
│   │   ├── rendering.c
│   │   └── draw.c
│   ├── game/
│   │   ├── game_loop.c
│   │   ├── movement.c
│   │   └── input.c
│   └── utils/
│       ├── utils.c
│       ├── cleanup.c
│       └── error.c
├── textures/
│   ├── north.xpm
│   ├── south.xpm
│   ├── west.xpm
│   └── east.xpm
└── maps/
    └── test.cub
```

## Technical Details

### Raycasting Algorithm

The engine uses the DDA (Digital Differential Analyzer) algorithm for raycasting:

1. **Ray Calculation**: For each screen column, calculate ray direction
2. **DDA Traversal**: Step through the map grid until hitting a wall
3. **Distance Calculation**: Calculate perpendicular distance to avoid fisheye effect
4. **Wall Height**: Calculate wall height based on distance
5. **Texture Mapping**: Map wall textures to screen pixels

### Performance

- Optimized for real-time rendering
- Efficient texture mapping
- Minimal memory allocations during runtime

## Troubleshooting

### Common Issues

1. **MLX not found**: Make sure MLX is properly installed in the `mlx_linux` directory
2. **Texture loading failed**: Check that texture files exist and are valid XPM format
3. **Map parsing errors**: Ensure map file follows the correct format
4. **Segmentation fault**: Check that all required textures and colors are defined

### Debug Mode

Compile with debug flags:
```bash
make CFLAGS="-Wall -Wextra -Werror -g -fsanitize=address"
```

## License

This project is part of the 42 School curriculum.

## Credits

- Raycasting technique inspired by Lode Vandevenne's raycasting tutorial
- MLX library by 42 School
- Wolfenstein 3D for inspiration
