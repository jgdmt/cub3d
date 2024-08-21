# 🥔 Cub3d - 42Cursus Project

Welcome to **Cub3d**, a 3D game engine built using the raycasting technique, inspired by the classic FPS game Wolfenstein. This project is developed as part of the 42 school curriculum and serves as an introduction to basic 3D rendering principle.

## 🎬 Video
[![Watch the video](https://img.youtube.com/vi/WQD2mrOBF8Y/maxresdefault.jpg)](https://youtu.be/WQD2mrOBF8Y)

## ✨ Project Overview

### 📚 Features

- **Raycasting Engine**: Implements a 2.5D raycasting engin to render a 3D environment from a 2D map.
- **Movement and Rotation**: Basic player movement and rotation.
- **Textures**: Support for textured walls for each cardinal point.
- **Collision Detection**: Simple collision detection to prevent the player walking through walls.

### 🚀 Bonus Features
- **Floor and Ceiling**: Textured floor and ceiling.
- **Enemies**: Animated enemies who follow you.
- **Portals**: Textured blue and orange portals (Valve like), recursive.
- **Gun and portal gun**: Scroll between a gun and a portal gun.
- **Mini-map**: Dynamic minimap that rotates with the player.
- **Health bar**: 100 HP.
- **Multi-map**: Go through different maps without restarting the game, by going through doors.
- **Menu**: Pause menu with `esc`, allows you to change map, to exit and to hide or show the hud.
- **Jump**: Funny jump.
- **Multi-thread**: Speed improvement.
- **Inertia**: Doom-like player inertia.
- **Full mouse integration**: Vertical and horizontal view with the mouse.
- **Resize and Fullscreen**: Dynamic resize with frame border.

## 🛠️ Installation & Compilation Guide

### 📦 Dependencies

Make sure you have the following installed:

- **GCC**: A GNU Compiler for C (version >= 9.3.0).
- **CMake**: MLX dependency.

Clone the project:
```bash
git clone https://github.com/jgdmt/cub3d.git
```

In case your system doesn't have **glfw** installed cmake will detect this and download it for you. You can then run `sudo make install` in the `_deps` directory of glfw.

To compile MLX dependency:
```bash
cd MLX42
cmake -B build # build here refers to the outputfolder.
cmake --build build -j4 # or do make -C build -j4
```

### 🏗️ Compilation

You can compile **Cub3d** using the following commands:

- **`make`**: Compiles the entire project.
- **`make bonus`**: Compiles the bonus.
- **`make clean`**: Removes object files generated during compilation.
- **`make fclean`**: Cleans the project directory by removing executables and object files.
- **`make re`**: Recompiles the entire project from scratch.

```bash
# Compile the project
make

# Clean object files
make clean
```

## 🚀 Usage

After compilation, you can run the **Cub3d** by executing:

```bash
./cub3D [path_of_the_map]
```

You can run the bonuses by executing:
```bash
./potato4D [path_of_the_map1] [path_of_the_map2] ...
```

Maps are included in the project. The following maps work with the mandatory part:
- test_map_old.cub
- giga_copy.cub

The followings maps are recommended to use with the bonus part:
- 1_level.cub
- 2_level.cub
- 3_level.cub

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

🌟 Thank you for checking out **Cub3d**! 🌟 If you have any questions or suggestions, feel free to reach out.
