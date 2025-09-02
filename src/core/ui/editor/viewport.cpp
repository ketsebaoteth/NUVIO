#include "core/ui/editor/viewport.h"
#include "core/canvas/manager.h"
#include "imgui.h"
#include "glm/glm.hpp"

NUVIO_UI_NAMESPACE_BEGIN

component get_viewport_component() {
    return component{
        "ViewportComponent",
        []() {
            ImGui::Begin("Viewport");
            void* canvasTexture = reinterpret_cast<void*>(static_cast<intptr_t>(gCanvasManager.Render()));
            auto size = gCanvasManager.GetCanvasSize();
            //center horizontally and verticaly
            ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - size.x) * 0.5f);
            ImGui::SetCursorPosY((ImGui::GetContentRegionAvail().y - size.y) * 0.5f);
            ImGui::Image(canvasTexture, ImVec2(static_cast<float>(size.x), static_cast<float>(size.y)), ImVec2(0,1), ImVec2(1,0));
            ImGui::End();
        }
    };
}

NUVIO_UI_NAMESPACE_END
