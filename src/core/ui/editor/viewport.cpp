#include "core/ui/editor/viewport.h"
#include "imgui.h"

NUVIO_UI_NAMESPACE_BEGIN

std::unique_ptr<component> get_viewport_component() {
    return std::make_unique<component>(component{
        "ViewportComponent",
        []() {
            ImGui::Begin("Viewport");
            ImGui::Text("This is the viewport");
            ImGui::End();
        }
    });
}

NUVIO_UI_NAMESPACE_END
