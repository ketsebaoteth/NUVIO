
# 🧩 UI Component System Overview

NUVIO's UI architecture is built around a modular, value-based component system designed for performance, clarity, and extensibility. Each UI element is encapsulated as a `component` struct, registered explicitly into the `UIManager`, and rendered via ImGui.

## 📦 Component Registration

All core UI components are defined in separate headers and registered through a centralized vector:

```cpp
// Component includes
#include "core/ui/editor/navbar.h"
#include "core/ui/editor/sidebar.h"
#include "core/ui/editor/layers.h"
#include "core/ui/editor/viewport.h"

NUVIO_UI_NAMESPACE_BEGIN

std::vector<component> allComps = {
    ui::get_navbar_component(),
    ui::get_layers_component(),
    ui::get_sidebar_component(),
    ui::get_viewport_component()
};

void RegisterAllComponents() {
    for (auto& comp : allComps) {
        nuvio::gUIManager.RegisterComponent(&comp);
    }
}

NUVIO_UI_NAMESPACE_END
```

This approach ensures predictable initialization and avoids static registration pitfalls. Components are stored by value and passed by pointer during registration to preserve ownership semantics.

## 🧱 Component Definition

Each component is defined as a named renderable unit. Here's an example of the sidebar:

```cpp
#include "core/ui/editor/sidebar.h"
#include "core/shortcut/manager.h"
#include "imgui.h"

NUVIO_UI_NAMESPACE_BEGIN

component get_sidebar_component() {
    return component{
        "Sidebar",
        [](){
            ImGui::Begin("Sidebar");
            ImGui::Text("This is the sidebar");
            ImGui::End();
        }
    };
}

NUVIO_UI_NAMESPACE_END
```

Components encapsulate both identity (`unique_name`) and rendering logic (`Render()` lambda), enabling flexible composition and runtime control.

## 🎛️ UIManager Responsibilities

The `UIManager` orchestrates the lifecycle of all registered components:

```cpp
class UIManager {
public:
    void init();
    void render() const;
    void begin_frame();
    void end_frame();
    void RegisterComponent(nuvio::ui::component* comp);
    void UnregisterComponent(nuvio::ui::component* comp);
    void WriteLayoutConfig();
    void Shutdown();

private:
    std::vector<nuvio::ui::component*> mComponents;
    int m_width, m_height;
    float m_dpi_scale;
    float m_ui_scaler_factor;
    std::string m_ini_path = "nuvio_ui.ini";
};
```

### 🔄 Runtime Behavior

- **RegisterComponent**: Adds a new component to the render list.
- **UnregisterComponent**: Removes a component by matching its `unique_name`.
- **render**: Iterates over all registered components and invokes their `Render()` logic.

```cpp
void UIManager::render() const {
    for (const auto& comp : mComponents) {
        comp->Render();
    }
}

void UIManager::RegisterComponent(nuvio::ui::component* comp) {
    mComponents.push_back(comp);
}

void UIManager::UnregisterComponent(nuvio::ui::component* comp) {
    auto it = std::remove_if(mComponents.begin(), mComponents.end(),
        [&](const nuvio::ui::component* c) {
            return c->unique_name == comp->unique_name;
        });
    mComponents.erase(it, mComponents.end());
}
```


## 🧠 Design Philosophy

- **Explicit registration** promotes clarity and avoids hidden state.  
- **Value-based component storage** improves cache locality and simplifies ownership.  
- **Modular layout** enables plugin-friendly extension and runtime flexibility.  
- **ImGui integration** ensures rapid iteration and visual consistency.

### 🧱 Scope & Structure

This system is intentionally scoped to handle only **root-level UI components**—the major building blocks of the editor such as the **Sidebar**, **Layers Panel**, **Properties Panel**, **File Explorer**, and similar top-level views. Smaller UI elements like buttons, labels, and toggles are expected to be **nested within their respective parent components**, maintaining a clean hierarchy and avoiding unnecessary global registration.

As a result, the `allComps` list is designed to remain compact and maintainable, with an expected ceiling of **30–50 root components**. This keeps the system performant and predictable, while leaving room for future expansion without architectural drift.

---

If you're contributing to NUVIO, this is your gateway to the UI layer. Welcome aboard.
