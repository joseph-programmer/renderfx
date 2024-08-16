# RenderFX Game Engine - README

## Overview
**RenderFX** is a small, work-in-progress game engine focused on rendering using the Vulkan API. This engine is designed for developers who are interested in learning Vulkan or for those who need a lightweight engine for personal or small-scale projects. The engine is modular, allowing for future extensions and improvements as development continues.

## Features (Current)
- **Vulkan Rendering Backend**: The engine exclusively uses Vulkan for rendering, providing low-level access to GPU features for maximum performance.
- **Cross-Platform Support**: Initial support for Windows and Linux. MacOS support is planned but not yet implemented.
- **Basic Scene Management**: Manage and render simple scenes with static and dynamic objects.
- **Shader Management**: Load and compile GLSL shaders to SPIR-V format.
- **Basic Input Handling**: Support for keyboard and mouse input.
- **Logging System**: Basic logging to track engine states, errors, and performance.

## Installation

### Prerequisites
- **Vulkan SDK**: Ensure the Vulkan SDK is installed on your system. This includes necessary headers, libraries, and tools.
- **CMake**: RenderFX uses CMake for build configuration.
- **A C++17 Compatible Compiler**: RenderFX is written in C++ and requires a C++17 compatible compiler, such as GCC or MSVC.
- **GLFW**: Used for window and input management.

### Building RenderFX

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/RenderFX.git
   cd RenderFX
   ```

2. **Configure the project with CMake**:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. **Build the engine**:
   ```bash
   cmake --build .
   ```

4. **Run the engine**:
   After building, the executable can be found in the `build` directory. Run it to launch the engine.

## Usage

### Running a Sample Scene
To load and run a sample scene:
```bash
./RenderFX path_to_scene_file
```
The engine currently supports a simple scene file format (`.rfxscene`). You can find examples in the `samples` directory.

### Creating a Scene
You can create scenes using the provided `.rfxscene` format. A basic example:
```json
{
    "name": "Test Scene",
    "objects": [
        {
            "name": "Cube",
            "model": "cube.obj",
            "position": [0.0, 0.0, 0.0],
            "rotation": [0.0, 0.0, 0.0],
            "scale": [1.0, 1.0, 1.0]
        }
    ]
}
```

### Logging
By default, logs are generated in the `logs/` directory. You can change the logging level by editing the configuration file `config/logging.json`.

## Contributing
RenderFX is still in active development. Contributions are welcome! Please check the `CONTRIBUTING.md` file for guidelines on how to contribute to the project.

## Roadmap
Planned features include:
- **Advanced Scene Management**: Support for hierarchical scenes and multiple scene nodes.
- **Physics Integration**: Basic physics engine integration.
- **Audio System**: Implementation of a simple audio system.
- **Networking**: Basic networking support for multiplayer games.
- **Scripting**: Integration of a scripting language for gameplay logic.

## License
RenderFX is licensed under the MIT License. See the `LICENSE` file for more details.

## Acknowledgements
- **Vulkan SDK**: For providing the tools and libraries necessary to develop with Vulkan.
- **GLFW**: For cross-platform window and input management.
- **SPIR-V Tools**: For shader compilation and management.

## Contact
For questions or suggestions, please open an issue on the GitHub repository.

---

This document will be updated as the project evolves. Thank you for your interest in RenderFX!
