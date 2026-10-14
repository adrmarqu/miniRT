# miniRT

A ray tracing engine written in C using MLX42 and the Phong reflection model, developed as part of the 42 curriculum.

## Requirements

### macOS
Install dependencies via Homebrew:
```bash
brew install cmake glfw
```

### Linux (Ubuntu / Debian)
Install dependencies via apt:
```bash
sudo apt update
sudo apt install build-essential cmake libglfw3-dev libglfw3 xorg-dev libx11-dev
```

### Linux (Arch)
Install dependencies via pacman:
```bash
sudo pacman -S cmake glfw-x11
```

## Compilation

Build the executable:
```bash
make
```

Remove object files:
```bash
make clean
```

Remove object files, MLX42 build artifacts, and the binary:
```bash
make fclean
```

Recompile the entire project:
```bash
make re
```

## Execution

Run the program with a scene file:
```bash
./miniRT <path_to_scene.rt>
```

Examples:
```bash
./miniRT scenes/subject.rt
./miniRT scenes/TwoBalls.rt
./miniRT scenes/Room.rt
```

## Controls

- `ESC`: Close the window and exit the program.
- `Window Close Button (X)`: Close the window and exit cleanly.

## Scene Format (.rt)

Scene files use the `.rt` extension. Fields are space-separated:

- Ambient light:
  `A <ratio [0.0, 1.0]> <R,G,B [0, 255]>`
- Camera:
  `C <x,y,z> <dir_x,dir_y,dir_z [-1.0, 1.0]> <fov [0, 180]>`
- Light:
  `L <x,y,z> <brightness [0.0, 1.0]> <R,G,B [0, 255]>`
- Sphere:
  `sp <x,y,z> <diameter> <R,G,B [0, 255]>`
- Plane:
  `pl <x,y,z> <normal_x,normal_y,normal_z [-1.0, 1.0]> <R,G,B [0, 255]>`
- Cylinder:
  `cy <x,y,z> <normal_x,normal_y,normal_z [-1.0, 1.0]> <diameter> <height> <R,G,B [0, 255]>`
- Cube:
  `cu <x,y,z> <normal_x,normal_y,normal_z [-1.0, 1.0]> <side_size> <R,G,B [0, 255]>`
