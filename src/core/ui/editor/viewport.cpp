#include "core/ui/editor/viewport.h"
#include "core/canvas/manager.h"
#include "imgui.h"
#include "glm/glm.hpp"
#include "core/ui/ui.h"
#include "imgui_internal.h"

NUVIO_UI_NAMESPACE_BEGIN

component get_viewport_component() {
    return component{
        "ViewportComponent",
        []() {
            ImGuiWindowFlags flags = ImGuiDockNodeFlags_NoTabBar;
            ImGui::Begin("Viewport",nullptr,flags);

            ImGui::Text("FPS: %.1f",ImGui::GetIO().Framerate);
            void* canvasTexture = reinterpret_cast<void*>(static_cast<intptr_t>(gCanvasManager.Render()));
            auto size = gCanvasManager.GetCanvasSize();
            //center horizontally and verticaly
            ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - size.x) * 0.5f);
            ImGui::SetCursorPosY((ImGui::GetContentRegionAvail().y - size.y) * 0.5f);
            //draw canvas as a image from a frame rendered by the gpu
            ImGui::Image(canvasTexture, ImVec2(static_cast<float>(size.x), static_cast<float>(size.y)), ImVec2(0,1), ImVec2(1,0));
            if(ImGui::IsItemHovered()){
              if(ImGui::IsItemClicked()){
                if(ImGui::IsMouseDragging(ImGuiMouseButton_Left)){
                  // ImVec2 dragDelta = ImGui::GetMouseDragDelta();
                  
                }
              }
            }
            ImGui::End();
        }
    };
}

NUVIO_UI_NAMESPACE_END
