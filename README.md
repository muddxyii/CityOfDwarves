# City of Dwarves

A 2D dwarf-themed city builder game implemented in C++ using SDL2 and GLM libraries.

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Building](#building)
- [Usage](#usage)
- [Controls](#controls)
- [License](#license)

## Description

"City of Dwarves" is a 2D city builder game where players construct and manage their own dwarf civilization. Built using C++ with SDL2 for graphics rendering and GLM for mathematics operations, this game offers a unique blend of strategy and resource management in a charming dwarven setting.

## Features

- 2D graphics rendering using SDL2
- Grid system for building placement
- ~Various dwarven structures (living quarters, workshops, mines, taverns)~ (not yet)
- ~Resource management (population, gold, ore, food)~ (not yet)
- ~Basic AI for dwarf behavior and needs~ (not yet)

## Prerequisites

To build and run this project, you'll need:

- C++20 compatible compiler
- SDL2, SDL2_image libraries
- GLM library
- CMake (version 3.29 or higher)

## Building

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/city-of-dwarves.git
   cd city-of-dwarves
   ```

2. Create a build directory:
   ```
   mkdir build
   cd build
   ```

3. Run CMake and build the project:
   ```
   cmake ..
   make
   ```

## Usage

After building, run the executable from the build directory:

```
./city_of_dwarves
```

## Controls
- WASD or Arrow keys: Scroll map
- ESC: Open/close game ~menu~

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- SDL2 developers
- GLM developers
- [Mixamo](https://www.mixamo.com/#/) for 3D Models & Animations
- [Poly Haven](https://polyhaven.com) for Textures
