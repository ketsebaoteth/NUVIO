# 🎨 Nuvio — Open Source Photo Editor

> *"Edit without the drama."*

Nuvio is an open‑source photo editor we’re building to be **fast**, **feature‑packed**, and **stable**.  
No random crashes, no “oops, your work is gone” moments — just a tool you can trust to get the job done.

---

## 🚀 What We’re Aiming For

- **Feature‑rich** editing tools for pros and hobbyists alike  
- **Smooth performance** even on big projects  
- **Cross‑platform** so you can work anywhere  
- **Minimal bugs** — stability is a core feature, not an afterthought  
- **Open source** so the community can shape its future  

---

## 🤝 Contributing

Pull requests?  
If it looks good, works good, and doesn’t break stuff — we’ll probably merge it.  
We’re not here to gatekeep, we’re here to build something awesome together.

### 📦 Build on Linux

To build Nuvio on Linux (tested on Fedora), follow these steps:

---

#### 🛠️ 1. Install Dependencies

```bash
sudo dnf install \
  cmake \
  gcc-c++ \
  make \
  mesa-libGL-devel \
  mesa-libGLU-devel \
  libX11-devel \
  libXrandr-devel \
  libXinerama-devel \
  libXcursor-devel \
  libXi-devel \
  wayland-devel \
  wayland-protocols-devel \
  libxkbcommon-devel
```

These packages cover:
- CMake and build tools
- OpenGL headers and libraries
- GLFW’s X11 and Wayland backends

---

#### 🧱 2. Clone the Repository

```bash
git clone --recurse-submodules https://github.com/yourusername/nuvio.git
cd nuvio
```

Make sure to use `--recurse-submodules` to pull in GLFW and other dependencies.

---

#### 🧪 3. Configure the Build

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
```

You can also use `Debug` or `RelWithDebInfo` depending on your needs.

---

#### ⚙️ 4. Build the Project

```bash
cmake --build .
```

This will generate the `NUVIO` binary in your build directory.

---

#### 🚀 5. Run Nuvio

```bash
./NUVIO
```

If you get a permission error:

```bash
chmod +x NUVIO
./NUVIO
```

---

### 🧠 Notes

- If you’re building on a non-Fedora distro, package names may differ (e.g. `apt install libgl1-mesa-dev` on Ubuntu).
- The build system disables strict `-pedantic` warnings for GLAD on Linux to avoid function pointer casting errors.
- CMake places the binary directly in the build directory — no `.exe` extension on Linux.

---

## 📜 License

[MIT License](LICENSE) — because creativity should be free.

---

## ✨ Join the Journey

We’re just getting started.  
Follow along, throw us ideas, or jump in and help make Nuvio the most reliable open‑source photo editor out there.