#include "core/ui/test.h"
#include "imgui.h"

NUVIO_UI_NAMESPACE_BEGIN
// Test component

component get_test_component(){
return  {
    "TestComponent",
    []() {
        ImGui::Begin("Test Component");
            ImGui::Text("Hello from TestComponent!");
        ImGui::End();
    }
};

}


NUVIO_UI_NAMESPACE_END
