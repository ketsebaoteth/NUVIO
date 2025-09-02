#include "core/ui/editor/sidebar.h"
#include "imgui.h"

NUVIO_UI_NAMESPACE_BEGIN
component get_layers_component() {
    return component{
        "Sidebar",
        [](){
            ImGui::Begin("Layers");
            ImGui::Text("This is layers");
            ImGui::End();
        }
    };
}
NUVIO_UI_NAMESPACE_END
