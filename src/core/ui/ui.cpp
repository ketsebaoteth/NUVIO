#include "core/ui/ui.h"
#include "core/ui/components/registery.h"
#include "core/window/window_manager.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui.h"

NUVIO_NAMESPACE_BEGIN

void UIManager::init() {
  IMGUI_CHECKVERSION();
  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  m_ui_scaler_factor = 1.3f;
  m_dpi_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(monitor);
  m_dpi_scale *= m_ui_scaler_factor;
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  // Optional: tweak style for multi-viewports
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  // scale imgui based on monitor dpi
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

void UIManager::render() const {
  for (const auto &comp : mComponents) {
      comp->Render();
  }
}

void UIManager::begin_frame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Fullscreen dockspace window
  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                  ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |=
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  ImGui::Begin("DockSpace", nullptr, window_flags);
  ImGui::PopStyleVar(2);

  // Dockspace ID
  ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
}

void UIManager::end_frame() {
  ImGui::End();
  ImGui::Render();

  // Clear the framebuffer
  glViewport(0, 0, gWindowManager.get_size().x, gWindowManager.get_size().y);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background color
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // Handle multiple OS windows
  ImGuiIO &io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
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

void UIManager::Shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

UIManager gUIManager;

NUVIO_NAMESPACE_END
