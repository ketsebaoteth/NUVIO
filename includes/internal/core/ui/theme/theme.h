#pragma once
#include "core/nuvio_namespaces.h"
#include <imgui.h>
#include <string>
#include <unordered_map>
#include <vector>

NUVIO_UI_NAMESPACE_BEGIN

struct theme_data {
  // Sharp, dark "shadcn" inspired ImGui style - no rounding, subtle grayscale
  // shades

  // Font
  std::string DefaultFontPath =
      "./assets/fonts/inter/static/Inter_24pt-Regular.ttf";
  float DefaultFontSize = 12.0f;

  // Layout
  float Alpha = 1.0f;
  float DisabledAlpha = 0.4f;
  ImVec2 WindowPadding = ImVec2(12.0f, 12.0f);
  float WindowRounding = 0.0f;
  float WindowBorderSize = 1.0f;
  ImVec2 WindowMinSize = ImVec2(24.0f, 32.0f);
  ImVec2 WindowTitleAlign = ImVec2(0.0f, 0.5f);
  ImGuiDir WindowMenuButtonPosition = ImGuiDir_Right;
  float ChildRounding = 0.0f;
  float ChildBorderSize = 1.0f;
  float PopupRounding = 0.0f;
  float PopupBorderSize = 1.0f;
  ImVec2 FramePadding = ImVec2(10.0f, 4.0f);
  float FrameRounding = 0.0f;
  float FrameBorderSize = 1.0f;
  ImVec2 ItemSpacing = ImVec2(8.0f, 6.0f);
  ImVec2 ItemInnerSpacing = ImVec2(6.0f, 5.0f);
  ImVec2 CellPadding = ImVec2(6.0f, 4.0f);
  float IndentSpacing = 12.0f;
  float ColumnsMinSpacing = 8.0f;
  float ScrollbarSize = 14.0f;
  float ScrollbarRounding = 0.0f;
  float GrabMinSize = 10.0f;
  float GrabRounding = 0.0f;
  float TabRounding = 0.0f;
  float TabBorderSize = 1.0f;
  float TabMinWidthForCloseButton = 0.0f;
  ImGuiDir ColorButtonPosition = ImGuiDir_Right;
  ImVec2 ButtonTextAlign = ImVec2(0.5f, 0.5f);
  ImVec2 SelectableTextAlign = ImVec2(0.0f, 0.5f);

  // Dark gray "shadcn" palette
  ImVec4 ImGuiCol_Text = ImVec4(0.92f, 0.92f, 0.95f, 1.00f);
  ImVec4 ImGuiCol_TextDisabled = ImVec4(0.43f, 0.45f, 0.53f, 1.00f);
  ImVec4 ImGuiCol_WindowBg = ImVec4(0.12f, 0.13f, 0.15f, 1.00f);
  ImVec4 ImGuiCol_ChildBg = ImVec4(0.14f, 0.14f, 0.16f, 1.00f);
  ImVec4 ImGuiCol_PopupBg = ImVec4(0.17f, 0.17f, 0.18f, 0.98f);
  ImVec4 ImGuiCol_Border = ImVec4(0.18f, 0.19f, 0.21f, 1.00f);
  ImVec4 ImGuiCol_BorderShadow = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  ImVec4 ImGuiCol_FrameBg = ImVec4(0.18f, 0.19f, 0.21f, 1.00f);
  ImVec4 ImGuiCol_FrameBgHovered = ImVec4(0.23f, 0.24f, 0.26f, 1.00f);
  ImVec4 ImGuiCol_FrameBgActive = ImVec4(0.22f, 0.23f, 0.26f, 1.00f);
  ImVec4 ImGuiCol_TitleBg = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);
  ImVec4 ImGuiCol_TitleBgActive = ImVec4(0.20f, 0.21f, 0.23f, 1.00f);
  ImVec4 ImGuiCol_TitleBgCollapsed = ImVec4(0.10f, 0.10f, 0.11f, 0.75f);
  ImVec4 ImGuiCol_MenuBarBg = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);
  ImVec4 ImGuiCol_ScrollbarBg = ImVec4(0.13f, 0.13f, 0.14f, 0.54f);
  ImVec4 ImGuiCol_ScrollbarGrab = ImVec4(0.26f, 0.27f, 0.29f, 0.98f);
  ImVec4 ImGuiCol_ScrollbarGrabHovered = ImVec4(0.32f, 0.33f, 0.36f, 0.98f);
  ImVec4 ImGuiCol_ScrollbarGrabActive = ImVec4(0.37f, 0.39f, 0.43f, 0.98f);
  ImVec4 ImGuiCol_CheckMark = ImVec4(0.44f, 0.50f, 0.98f, 1.00f);
  ImVec4 ImGuiCol_SliderGrab = ImVec4(0.44f, 0.50f, 0.98f, 0.60f);
  ImVec4 ImGuiCol_SliderGrabActive = ImVec4(0.44f, 0.50f, 0.98f, 1.00f);
  ImVec4 ImGuiCol_Button = ImVec4(0.18f, 0.19f, 0.21f, 1.00f);
  ImVec4 ImGuiCol_ButtonHovered = ImVec4(0.23f, 0.24f, 0.26f, 1.00f);
  ImVec4 ImGuiCol_ButtonActive = ImVec4(0.22f, 0.23f, 0.26f, 1.00f);
  ImVec4 ImGuiCol_Header = ImVec4(0.18f, 0.19f, 0.21f, 1.00f);
  ImVec4 ImGuiCol_HeaderHovered = ImVec4(0.23f, 0.24f, 0.26f, 1.00f);
  ImVec4 ImGuiCol_HeaderActive = ImVec4(0.22f, 0.23f, 0.26f, 1.00f);
  ImVec4 ImGuiCol_Separator = ImVec4(0.18f, 0.19f, 0.21f, 1.00f);
  ImVec4 ImGuiCol_SeparatorHovered = ImVec4(0.32f, 0.33f, 0.36f, 1.00f);
  ImVec4 ImGuiCol_SeparatorActive = ImVec4(0.44f, 0.50f, 0.98f, 1.00f);
  ImVec4 ImGuiCol_ResizeGrip = ImVec4(0.26f, 0.27f, 0.29f, 0.30f);
  ImVec4 ImGuiCol_ResizeGripHovered = ImVec4(0.32f, 0.33f, 0.36f, 0.50f);
  ImVec4 ImGuiCol_ResizeGripActive = ImVec4(0.44f, 0.50f, 0.98f, 0.70f);
  ImVec4 ImGuiCol_Tab = ImVec4(0.14f, 0.15f, 0.17f, 1.00f);
  ImVec4 ImGuiCol_TabHovered = ImVec4(0.23f, 0.24f, 0.26f, 1.00f);
  ImVec4 ImGuiCol_TabActive = ImVec4(0.20f, 0.21f, 0.23f, 1.00f);
  ImVec4 ImGuiCol_TabUnfocused = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
  ImVec4 ImGuiCol_TabUnfocusedActive = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);
  ImVec4 ImGuiCol_PlotLines = ImVec4(0.53f, 0.53f, 0.53f, 1.00f);
  ImVec4 ImGuiCol_PlotLinesHovered = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
  ImVec4 ImGuiCol_PlotHistogram = ImVec4(0.44f, 0.50f, 0.98f, 1.00f);
  ImVec4 ImGuiCol_PlotHistogramHovered = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
  ImVec4 ImGuiCol_TableHeaderBg = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);
  ImVec4 ImGuiCol_TableBorderStrong = ImVec4(0.18f, 0.19f, 0.21f, 1.00f);
  ImVec4 ImGuiCol_TableBorderLight = ImVec4(0.23f, 0.24f, 0.26f, 1.00f);
  ImVec4 ImGuiCol_TableRowBg = ImVec4(0.12f, 0.13f, 0.15f, 1.00f);
  ImVec4 ImGuiCol_TableRowBgAlt = ImVec4(0.14f, 0.14f, 0.16f, 1.00f);
  ImVec4 ImGuiCol_TextSelectedBg = ImVec4(0.44f, 0.50f, 0.98f, 0.30f);
  ImVec4 ImGuiCol_DragDropTarget = ImVec4(0.44f, 0.50f, 0.98f, 0.90f);
  ImVec4 ImGuiCol_NavHighlight = ImVec4(0.44f, 0.50f, 0.98f, 1.00f);
  ImVec4 ImGuiCol_NavWindowingHighlight = ImVec4(0.44f, 0.50f, 0.98f, 0.70f);
  ImVec4 ImGuiCol_NavWindowingDimBg = ImVec4(0.12f, 0.13f, 0.15f, 0.45f);
  ImVec4 ImGuiCol_ModalWindowDimBg = ImVec4(0.12f, 0.13f, 0.15f, 0.70f);
  ImVec4 ImGuiCol_DockingPreview = ImVec4(0.44f, 0.50f, 0.98f, 0.70f); 
  // This style aims for a modern, sharp, neutral look — no roundness, clear
  // edges, and subtle grayscale contrast.  // clang-format on
};

class ThemeManager {
public:
  ThemeManager() : m_themes{{"Default", theme_data{}}} {}
  ThemeManager(const std::string &name, const theme_data &data)
      : m_themes{{name, data}} {};

  /**
   * Applies the specified theme.
   * @param name The name of the theme to apply.
   */
  void ApplyTheme(std::string name);

  /**
   * Loads a theme from a file.
   * @param file_path The path to the theme file.
   */
  void LoadTheme(const std::string &file_path);

  /**
   * Creates a new theme.
   * @param name The name of the theme to create.
   * @param theme_name The name of the theme to be saved.
   */
  void SaveTheme(const std::string &folder_path,
                 const std::string &theme_name) const;

private:
  std::unordered_map<std::string, theme_data> m_themes;
};

extern ThemeManager gThemeManager;

NUVIO_UI_NAMESPACE_END
