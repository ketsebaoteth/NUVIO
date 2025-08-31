#include "core/ui/theme/theme.h"

NUVIO_UI_NAMESPACE_BEGIN

ThemeManager gThemeManager;

void ThemeManager::ApplyTheme(std::string name) {
    // Find theme from m_themes
    theme_data& theme = m_themes[name];
    ImGuiStyle& style = ImGui::GetStyle();

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(theme.DefaultFontPath.c_str(), 14.0f); // 18.0f is the font size

    style.Alpha = theme.Alpha;
    style.DisabledAlpha = theme.DisabledAlpha;
    style.WindowPadding = theme.WindowPadding;
    style.WindowRounding = theme.WindowRounding;
    style.WindowBorderSize = theme.WindowBorderSize;
    style.WindowMinSize = theme.WindowMinSize;
    style.WindowTitleAlign = theme.WindowTitleAlign;
    style.WindowMenuButtonPosition = theme.WindowMenuButtonPosition;
    style.ChildRounding = theme.ChildRounding;
    style.ChildBorderSize = theme.ChildBorderSize;
    style.PopupRounding = theme.PopupRounding;
    style.PopupBorderSize = theme.PopupBorderSize;
    style.FramePadding = theme.FramePadding;
    style.FrameRounding = theme.FrameRounding;
    style.FrameBorderSize = theme.FrameBorderSize;
    style.ItemSpacing = theme.ItemSpacing;
    style.ItemInnerSpacing = theme.ItemInnerSpacing;
    style.CellPadding = theme.CellPadding;
    style.IndentSpacing = theme.IndentSpacing;
    style.ColumnsMinSpacing = theme.ColumnsMinSpacing;
    style.ScrollbarSize = theme.ScrollbarSize;
    style.ScrollbarRounding = theme.ScrollbarRounding;
    style.GrabMinSize = theme.GrabMinSize;
    style.GrabRounding = theme.GrabRounding;
    style.TabRounding = theme.TabRounding;
    style.TabBorderSize = theme.TabBorderSize;
    style.ColorButtonPosition = theme.ColorButtonPosition;
    style.ButtonTextAlign = theme.ButtonTextAlign;
    style.SelectableTextAlign = theme.SelectableTextAlign;

    // Set each color individually
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text] = theme.ImGuiCol_Text;
    colors[ImGuiCol_TextDisabled] = theme.ImGuiCol_TextDisabled;
    colors[ImGuiCol_WindowBg] = theme.ImGuiCol_WindowBg;
    colors[ImGuiCol_ChildBg] = theme.ImGuiCol_ChildBg;
    colors[ImGuiCol_PopupBg] = theme.ImGuiCol_PopupBg;
    colors[ImGuiCol_Border] = theme.ImGuiCol_Border;
    colors[ImGuiCol_BorderShadow] = theme.ImGuiCol_BorderShadow;
    colors[ImGuiCol_FrameBg] = theme.ImGuiCol_FrameBg;
    colors[ImGuiCol_FrameBgHovered] = theme.ImGuiCol_FrameBgHovered;
    colors[ImGuiCol_FrameBgActive] = theme.ImGuiCol_FrameBgActive;
    colors[ImGuiCol_TitleBg] = theme.ImGuiCol_TitleBg;
    colors[ImGuiCol_TitleBgActive] = theme.ImGuiCol_TitleBgActive;
    colors[ImGuiCol_TitleBgCollapsed] = theme.ImGuiCol_TitleBgCollapsed;
    colors[ImGuiCol_MenuBarBg] = theme.ImGuiCol_MenuBarBg;
    colors[ImGuiCol_ScrollbarBg] = theme.ImGuiCol_ScrollbarBg;
    colors[ImGuiCol_ScrollbarGrab] = theme.ImGuiCol_ScrollbarGrab;
    colors[ImGuiCol_ScrollbarGrabHovered] = theme.ImGuiCol_ScrollbarGrabHovered;
    colors[ImGuiCol_ScrollbarGrabActive] = theme.ImGuiCol_ScrollbarGrabActive;
    colors[ImGuiCol_CheckMark] = theme.ImGuiCol_CheckMark;
    colors[ImGuiCol_SliderGrab] = theme.ImGuiCol_SliderGrab;
    colors[ImGuiCol_SliderGrabActive] = theme.ImGuiCol_SliderGrabActive;
    colors[ImGuiCol_Button] = theme.ImGuiCol_Button;
    colors[ImGuiCol_ButtonHovered] = theme.ImGuiCol_ButtonHovered;
    colors[ImGuiCol_ButtonActive] = theme.ImGuiCol_ButtonActive;
    colors[ImGuiCol_Header] = theme.ImGuiCol_Header;
    colors[ImGuiCol_HeaderHovered] = theme.ImGuiCol_HeaderHovered;
    colors[ImGuiCol_HeaderActive] = theme.ImGuiCol_HeaderActive;
    colors[ImGuiCol_Separator] = theme.ImGuiCol_Separator;
    colors[ImGuiCol_SeparatorHovered] = theme.ImGuiCol_SeparatorHovered;
    colors[ImGuiCol_SeparatorActive] = theme.ImGuiCol_SeparatorActive;
    colors[ImGuiCol_ResizeGrip] = theme.ImGuiCol_ResizeGrip;
    colors[ImGuiCol_ResizeGripHovered] = theme.ImGuiCol_ResizeGripHovered;
    colors[ImGuiCol_ResizeGripActive] = theme.ImGuiCol_ResizeGripActive;
    colors[ImGuiCol_Tab] = theme.ImGuiCol_Tab;
    colors[ImGuiCol_TabHovered] = theme.ImGuiCol_TabHovered;
    colors[ImGuiCol_TabActive] = theme.ImGuiCol_TabActive;
    colors[ImGuiCol_TabUnfocused] = theme.ImGuiCol_TabUnfocused;
    colors[ImGuiCol_TabUnfocusedActive] = theme.ImGuiCol_TabUnfocusedActive;
    colors[ImGuiCol_PlotLines] = theme.ImGuiCol_PlotLines;
    colors[ImGuiCol_PlotLinesHovered] = theme.ImGuiCol_PlotLinesHovered;
    colors[ImGuiCol_PlotHistogram] = theme.ImGuiCol_PlotHistogram;
    colors[ImGuiCol_PlotHistogramHovered] = theme.ImGuiCol_PlotHistogramHovered;
    colors[ImGuiCol_TableHeaderBg] = theme.ImGuiCol_TableHeaderBg;
    colors[ImGuiCol_TableBorderStrong] = theme.ImGuiCol_TableBorderStrong;
    colors[ImGuiCol_TableBorderLight] = theme.ImGuiCol_TableBorderLight;
    colors[ImGuiCol_TableRowBg] = theme.ImGuiCol_TableRowBg;
    colors[ImGuiCol_TableRowBgAlt] = theme.ImGuiCol_TableRowBgAlt;
    colors[ImGuiCol_TextSelectedBg] = theme.ImGuiCol_TextSelectedBg;
    colors[ImGuiCol_DragDropTarget] = theme.ImGuiCol_DragDropTarget;
    colors[ImGuiCol_NavHighlight] = theme.ImGuiCol_NavHighlight;
    colors[ImGuiCol_NavWindowingHighlight] = theme.ImGuiCol_NavWindowingHighlight;
    colors[ImGuiCol_NavWindowingDimBg] = theme.ImGuiCol_NavWindowingDimBg;
    colors[ImGuiCol_ModalWindowDimBg] = theme.ImGuiCol_ModalWindowDimBg;
    // Add more ImGuiCol_* assignments as needed for your theme_data
}

NUVIO_UI_NAMESPACE_END
