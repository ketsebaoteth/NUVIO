# Contributing to Nuvio

Thank you for your interest in contributing to Nuvio! Whether you're fixing bugs, improving features, or exploring the codebase, this guide will help you get started and understand the repository layout and code conventions.

---

## 🏗️ Codebase Overview

Nuvio is a modular, performance-focused raster editor written primarily in C++. Below you'll find the main directories and their purposes:

### **Directory Structure**

- **src/**  
  Core source files for the editor. Contains logic for canvas, UI, project management, and more.
  - `src/core/canvas/` — Canvas and rendering management.
  - `src/core/ui/` — The UI system and components.
  - `src/core/project/` — Project loading and saving logic.

- **includes/**  
  Header files and external libraries.
  - `includes/internal/` — Project's own internal headers.
      - `core/` — Internal core definitions, e.g. DNA (data) structures, utility headers.
  - `includes/external/` — External dependencies (e.g. ImGui, GLFW, Tracy profiler).

- **profiling/**  
  Tracy profiler integration. See [Profiling with Tracy](readme.md#profiling-with-tracy) for usage.

- **docs/**  
  Documentation, built with VitePress and Bun.

- **build/**  
  Created during the build process; holds compiled binaries.

---

## 🧩 UI Component System

Nuvio's UI is modular, using a value-based component system.  
- Root-level UI components (Sidebar, Layers Panel, Properties Panel, File Explorer, etc.) are explicitly registered in the UI manager.
- Smaller UI elements (buttons, toggles) are nested inside their parent components for clarity and performance.

See [`docs/components.md`](docs/components.md) for a deep dive into the UI architecture and design philosophy.

---

## ✍️ How to Contribute

### 1. **Fork & Clone**

```sh
git clone https://github.com/ketsebaoteth/NUVIO.git
cd NUVIO
```

### 2. **Set Up Dependencies**

See [README.md](README.md) for platform-specific setup.  
If you get build errors about missing libraries, install them as needed (the README lists common dependencies for Arch/EndeavourOS).

### 3. **Build the Project**

- **Linux & Windows:**  
  ```sh
  mkdir build && cd build
  cmake ..
  cmake --build .
  ```
- **Docs:**  
  Requires [Bun](https://bun.sh/).
  ```sh
  cd docs
  bun install
  bun run docs:dev
  ```

### 4. **Code Style & Conventions**

- **C++:**  
  - Follow modern C++ guidelines.
  - Prefer explicit, modular code.
  - Document major functions/classes with comments.
- **UI Components:**  
  - Register root-level components in the UI manager.
  - Keep components value-based and avoid global state.
  - Use ImGui for rendering logic.

### 5. **Making Changes**

- Branch from `main` or the latest stable branch.
- Make atomic commits with clear messages.
- Test your changes (build, run, check for regressions).

### 6. **Pull Requests**

- Open a pull request with a descriptive title and summary.
- If your change touches core UI, briefly explain your approach.
- Link related issues if relevant.

---

## 🗂️ Notable Files

- `CMakeLists.txt` — Main build configuration.
- `Makefile` — Alternate build targets.
- `src/core/ui/ui.cpp` — UI manager and layout logic.
- `includes/internal/core/dna/` — Data models for projects, layers, etc.
- `profiling/tracy/` — Tracy profiler setup.

---

## 💡 Tips & Guidelines

- **Platform Support:**  
  Nuvio builds on Linux and Windows. macOS is not yet tested, but help is welcome!
- **Profiling:**  
  Use Tracy for performance analysis (`-DNUVIO_ENABLE_TRACY=ON`).
- **Documentation:**  
  Docs are in `/docs` (VitePress). Help expand them!

---

## 🙌 Community & Feedback

Questions, suggestions, or big ideas?  
Open an issue, start a discussion, or join a pull request.  
Your feedback helps Nuvio grow!

---

Thank you for improving Nuvio!
