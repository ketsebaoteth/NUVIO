#include "core/ui/editor/viewport.h"
#include "core/canvas/manager.h"
#include "core/ui/ui.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include <cstdio>

NUVIO_UI_NAMESPACE_BEGIN

component get_viewport_component() {
  return component{"ViewportComponent", []() {
                     ImGuiWindowFlags flags =
                         0; // Use 0 or ImGuiWindowFlags_None unless you
                            // want special behavior
                     ImGui::Begin("Viewport", nullptr, flags);

                     ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
                     void *canvasTexture = reinterpret_cast<void *>(
                         static_cast<intptr_t>(gCanvasManager.Render()));
                     auto size = gCanvasManager.GetCanvasSize();

                     // center horizontally and vertically
                     ImGui::SetCursorPosX(
                         (ImGui::GetContentRegionAvail().x - size.x) * 0.5f);
                     ImGui::SetCursorPosY(
                         (ImGui::GetContentRegionAvail().y - size.y) * 0.5f);

                     // draw canvas as a image from a frame rendered by the gpu
                     ImGui::Image(canvasTexture,
                                  ImVec2(static_cast<float>(size.x),
                                         static_cast<float>(size.y)),
                                  ImVec2(0, 1), ImVec2(1, 0));

                     // Overlay an invisible button on the image for mouse
                     // interaction
                     ImVec2 imagePos = ImGui::GetItemRectMin();
                     ImVec2 imageSize = ImGui::GetItemRectSize();
                     ImVec2 mousePos = ImGui::GetMousePos();
                     ImVec2 relPos = ImVec2(mousePos.x - imagePos.x,
                                            mousePos.y - imagePos.y);

                     gCanvasManager.SetMouseLocation(relPos);

                     ImGui::SetCursorScreenPos(imagePos);
                     ImGui::InvisibleButton("canvas_button", imageSize);

                     if (ImGui::IsItemActive() &&
                         ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                       ImVec2 dragDelta = ImGui::GetMouseDragDelta();
                       gCanvasManager.SetMouseDelta(dragDelta);

                       ImGui::ResetMouseDragDelta();
                     }

                     ImGui::End();
                   }};
}

NUVIO_UI_NAMESPACE_END
