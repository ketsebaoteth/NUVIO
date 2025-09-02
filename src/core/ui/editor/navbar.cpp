#include "core/ui/editor/navbar.h"
#include "imgui.h"
#include "core/ui/components/registery.h"
#include "core/nuvio_namespaces.h"


NUVIO_UI_NAMESPACE_BEGIN

menu_item gNavbar = {
    "File",
    "Ctrl+N",
    "New File",
    "Create a new file",
    "file_icon.png",
    {
        menu_item{
            "Open",
            "Ctrl+O",
            "Open File",
            "Open an existing file",
            "open_icon.png",
            {},
            []() { /* Open file logic */ },
            []() { /* Show tooltip */ }
        },
        menu_item{
            "Save",
            "Ctrl+S",
            "Save File",
            "Save the current file",
            "save_icon.png",
            {},
            []() { /* Save file logic */ },
            []() { /* Show tooltip */ }
        }
    },
    []() { /* Navbar click logic */ },
    []() { /* Show tooltip */ }
};

void render_navbar(){
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu(gNavbar.title.c_str())) {
            for (const auto& item : gNavbar.children) {
                if (ImGui::MenuItem(item.title.c_str(), item.shortcut.c_str())) {
                    if (item.on_click) item.on_click();
                }
                if (ImGui::IsItemHovered() && item.on_hover) {
                    item.on_hover();
                    ImGui::SetTooltip("%s\n%s", item.tooltip_title.c_str(), item.tooltip_desc.c_str());
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

component get_navbar_component() {
    return component{
        "NavbarComponent",
        []() { 
            render_navbar();
         }
    };
}


NUVIO_UI_NAMESPACE_END
