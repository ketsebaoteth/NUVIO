# Nuvio

Nuvio is a fast, crash-resistant raster editor focused on performance, stability, and a highly configurable, tactile UI that feels great to work with. Built for creators who value reliability and a smooth user experience.

---

## 💡 Mission

Nuvio’s mission has evolved:  
**Performance, stability, and a tactile, configurable UI** are our top priorities. We want Nuvio to be a joy to use for creators of all kinds.

---

## 🚀 Building Nuvio

### Supported Platforms

- **Linux (Arch & Arch-based systems)**: Manually tested and building reliably.
- **macOS**: _Not yet tested for build—contributions and reports welcome!_
- **Windows**: Supported—see below for instructions.

### Required Dependencies

If you encounter missing library errors, try installing the dependency manually first.  
Below are the most common installables we've needed on Arch/EndeavourOS. Your system may differ.

<details>
<summary>Common dependencies on Arch/EndeavourOS</summary>

```
sudo pacman -S base-devel cmake git gcc make pkgconf \
libglvnd glew glfw-x11 mesa glm freetype2 libpng \
zlib libjpeg-turbo libtiff libwebp openexr libspng \
gtk3 tracy
```

</details>

> **Tip:** Only install what’s missing. If a dependency is already present, you can skip it.

### Build Instructions (Linux)

```sh
git clone https://github.com/ketsebaoteth/NUVIO.git
cd NUVIO
mkdir build && cd build
cmake ..
cmake --build .
```

---

### 🪟 Building on Windows

Building on Windows is straightforward:

1. Install [CMake](https://cmake.org/download/).
2. Install a C++ distribution (MSVC is recommended, available via Visual Studio).
3. Open a terminal in the repo directory:
    ```sh
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
4. Output binaries will be in the `build` directory.

---

## 📑 Documentation

Nuvio’s docs use [VitePress](https://vitepress.dev/) but are built with [Bun](https://bun.sh/).

To build and view docs locally:

```sh
cd docs
bun install
bun run docs:dev
```

Docs will be served at [http://localhost:5173](http://localhost:5173).

---

## 🔥 Currently Working On

We’re currently working on the **scene graph for the canvas renderer**—this is a backbone for rendering and managing complex layers and objects.

Stay tuned for progress updates!

---

## 📊 Profiling with Tracy

We use the [Tracy Profiler](https://github.com/wolfpld/tracy) for performance analysis.

### Usage

- Tracy integration is located in `profiling/tracy`.
- To use Tracy:
    1. Build Nuvio with profiling enabled (`-DNUVIO_ENABLE_TRACY=ON`).
    2. Run the application.
    3. Start the Tracy client to connect and visualize profiling data.

See profiling/tracy for details.

---

## 💬 Contributing & Feedback

We welcome contributions, bug reports, and feedback.  
Please open an issue or pull request!

---

_Enjoy creating with Nuvio!_
