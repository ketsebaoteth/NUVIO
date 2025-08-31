#include "core/ui/test.h"
#include "imgui.h"

NUVIO_UI_NAMESPACE_BEGIN
// Test component

std::unique_ptr<component> get_test_component() {
    return std::make_unique<component>(component{
        "TestComponent",
        []() {
            ImGui::Begin("Test Component");
            ImGui::Text("Hello from TestComponent!");
            ImGui::End();
        }
    });
}


NUVIO_UI_NAMESPACE_END
