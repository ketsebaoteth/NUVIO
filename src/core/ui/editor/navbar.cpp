#include "core/ui/editor/navbar.h"
#include "core/nuvio_namespaces.h"
#include "core/ui/components/menu_item.h"
#include "core/ui/components/registery.h"
#include "imgui.h"

NUVIO_UI_NAMESPACE_BEGIN

menu_item open_file_sub_menu = {"Open",
                                "Ctrl+O",
                                "Open File",
                                "Open an existing file",
                                "open_icon.png",
                                {},
                                []() { /* Open file logic */ },
                                []() { /* Show tooltip */ }};

menu_item save_file_sub_menu = {"Save",
                                "Ctrl+S",
                                "Save File",
                                "Save the current file",
                                "save_icon.png",
                                {},
                                []() { /* Save file logic */ },
                                []() { /* Show tooltip */ }};

menu_item export_png_sub_sub_menu = {"png",
                                     "",
                                     "Export PNG",
                                     "",
                                     "",
                                     {},
                                     []() { /* Save file logic */ },
                                     []() { /* Show tooltip */ }};

menu_item export_jpeg_sub_sub_menu = {"jpeg",
                                      "",
                                      "Export JEPG",
                                      "",
                                      "",
                                      {},
                                      []() { /* Save file logic */ },
                                      []() { /* Show tooltip */ }};

menu_item export_bmp_sub_sub_menu = {"bmp",
                                     "",
                                     "Export BMP",
                                     "",
                                     "",
                                     {},
                                     []() { /* Save file logic */ },
                                     []() { /* Show tooltip */ }};

menu_item export_file_sub_menu = {"Export",
    "CTRL+E",
    "Export File",
    "write image to a file in different formats",
    "",
    {export_png_sub_sub_menu, export_jpeg_sub_sub_menu,
     export_bmp_sub_sub_menu},
    []() { /* Save file logic */ },
    []() { /* Show tooltip */ }

};

menu_item file_menu = {
    "File",
    "Ctrl+N",
    "New File",
    "Create a new file",
    "file_icon.png",
    {open_file_sub_menu, save_file_sub_menu, export_file_sub_menu},
    []() {},
    []() {},
};

menu_item gNavbar = {file_menu};

void draw_subitems(menu_item item) {
  if (ImGui::BeginMenu(item.title.c_str())) {
    for (const auto &subitem : item.children) {
      if (ImGui::MenuItem(subitem.title.c_str(), subitem.shortcut.c_str())) {
        if (subitem.on_click)
          subitem.on_click();
      }
    }
    ImGui::EndMenu();
  }
}

void render_navbar() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu(gNavbar.title.c_str())) {
      for (const auto &item : gNavbar.children) {
        if (item.children.size() != 0) {
          draw_subitems(item);
        } else if (ImGui::MenuItem(item.title.c_str(), item.shortcut.c_str())) {
          if (item.on_click)
            item.on_click();
        }
        if (ImGui::IsItemHovered() && item.on_hover) {
          item.on_hover();
          ImGui::SetTooltip("%s\n%s", item.tooltip_title.c_str(),
                            item.tooltip_desc.c_str());
        }
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}

component get_navbar_component() {
  return component{"NavbarComponent", []() { render_navbar(); }};
}

NUVIO_UI_NAMESPACE_END
