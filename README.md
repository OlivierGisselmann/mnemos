# Mnemos Engine
A lightweight, cross-platform 3D game engine written in C++, built from the ground up with minimal external dependencies. This project emphasizes low-level systems such as memory management and custom data structures, offering full control and flexibility for systems programming and rendering.

Built from scratch for education, experimentation and portfolio showcase purposes.

---

## Goals
- **Low-Level Focus**: Provide fine-grained control over core systems like memory allocation, data layout, and CPU/GPU communication.
- **Minimal Dependencies**: Avoid bloated third-party libraries to maintain transparency and full understanding of all components.
- **Cross-Platform Support**: Seamlessly build and run on both **Linux** and **Windows**.

## Features
- **Rendering**
  - OpenGL-based real-time 3D renderer
  - Custom shader management system
  - Basic scene graph and render queue support

- **Core Systems**
  - Custom memory allocators (stack, pool, linear)
  - ECS-style (Entity Component System) foundation
  - Modular core engine loop with precise frame timing

- **Math & Utilities**
  - Custom math library (vectors, matrices, transforms)
  - Basic file I/O and logging utilities
  - Platform abstraction layer

- **Platform Support**
  - Windows and Linux(X11) support out of the box
  - No GLFW-like libraries used

---

## Architecture
The engine is modular, with the following high-level subsystems:

```
application/       # Entry point, application framework
engine/
├── core/          # Memory, timing, logging, platform abstraction
├── math/          # Vector, matrix, quaternion, transforms
├── graphics/      # Rendering, shaders, textures, mesh formats
├── systems/       # Scene management, ECS (in progress)
├── platform/      # Platform-specific implementations
```

- **Renderer Abstraction**: Encapsulates OpenGL but designed to support future backends (e.g. Vulkan).
- **Allocator Subsystem**: Provides multiple allocator types for optimal memory usage patterns.
- **Minimal Runtime**: Engine initialization and runtime overhead kept as lean as possible.

---

## Build instructions
### Prerequisites

- C++20-compatible compiler (MSVC, GCC, Clang)
- CMake 3.25+
- OpenGL development libraries
- (Optional) Make/Ninja for faster builds

### Building

You can list available CMake Presets with the following commands
```bash
cmake --list-presets
cmake --build --list-presets
```

#### Windows (Visual Studio)
```bash
git clone https://github.com/OlivierGisselmann/mnemos.git
cd mnemos
cmake --preset debug-msvc OR cmake --preset release-msvc
cmake --build --preset app-debug-msvc OR cmake --build --preset app-release-msvc
```

#### Linux
```bash
git clone https://github.com/OlivierGisselmann/mnemos.git
cd mnemos
cmake --preset debug-ninja OR cmake --preset release-ninja
cmake --build --preset app-debug-ninja OR cmake --build --preset app-release-ninja
```

### Running
Run the generated executable from the `out/` directory:
```bash
./out/application/Game(.exe if on Windows)
```

---

## Notes

- This project is under active development and **not yet production-ready**.
- Contributions, suggestions, and feedback are welcome!

---

## Credits
Here is a list of useful resources I used for this project:

- Game Engine Architecture - Third Edition by Jason Gregory
- Kohi Game Engine series by Travis Vroman