#include "core/ui/ui.h"
#include "core/ui/components/registery.h"
#include "core/window/window_manager.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui.h"

NUVIO_NAMESPACE_BEGIN

void UIManager::init() {
  IMGUI_CHECKVERSION();
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  m_ui_scaler_factor = 1.3f;
  m_dpi_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(monitor);
  m_dpi_scale *= m_ui_scaler_factor;
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  //scale imgui based on monitor dpi
  io.FontGlobalScale = m_dpi_scale;
  ImGui::GetStyle().ScaleAllSizes(m_dpi_scale);
  (void)io;

  ImGui::StyleColorsDark(); // base style

  GLFWwindow *window = gWindowManager.get_window();
  assert(window && "Window must be initialized before UIManager Initializes");

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330"); // Match your shader version

  nuvio::ui::RegisterAllComponents();
}

void UIManager::render() const{
  for (const auto &comp : mComponents) {
    if (comp.Render) {
      comp.Render();
    }
  }
}

void UIManager::begin_frame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void UIManager::end_frame() {
  ImGui::Render();

  // Clear the framebuffer
  glViewport(0, 0, gWindowManager.get_size().x, gWindowManager.get_size().y);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background color
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::RegisterComponent(const nuvio::ui::component comp) {
  mComponents.push_back(comp);
}

void UIManager::UnregisterComponent(nuvio::ui::component comp) {
  auto it = std::remove_if(mComponents.begin(), mComponents.end(),
                           [&](const nuvio::ui::component &c) {
                             return c.unique_name == comp.unique_name;
                           });
  mComponents.erase(it, mComponents.end());
}

void UIManager::Shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

UIManager gUIManager;

NUVIO_NAMESPACE_END
