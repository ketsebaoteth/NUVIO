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
