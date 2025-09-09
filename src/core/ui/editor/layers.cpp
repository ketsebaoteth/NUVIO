#include "core/ui/editor/sidebar.h"
#include "core/utils/texture.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include "core/window/window_manager.h"
#include "core/ui/ui.h"

NUVIO_UI_NAMESPACE_BEGIN

static int blend_mode = 0;
const char* blend_modes[16] = {
    "Normal", "Multiply", "Screen", "Overlay", "Darken", "Lighten",
    "Color Dodge", "Color Burn", "Hard Light", "Soft Light", "Difference",
    "Exclusion", "Hue", "Saturation", "Color", "Luminosity"
};
static int opacity = 100;

struct IconAsset {
    const char *path;
    glm::ivec2 size = glm::ivec2(24, 24); // Default size
    ImTextureID textureId = NULL;
};

static std::vector<IconAsset> iconAssets = {
    {"./assets/icons/lock.png"},
    {"./assets/icons/move.png"},
};

static bool LockIconsLoaded = false;

static void loadIcons() {
    for (auto &icon : iconAssets) {
        if (!icon.textureId) {
            icon.textureId = LoadTextureFromFile(icon.path,&icon.size.x,&icon.size.y); 
        }
    }
}

static GLFWcursor *hresizeCursor = nullptr;

component get_layers_component() {
    return component{
        "Sidebar",
        [](){
            ImGui::Begin("Layers");
            ImGui::SetNextItemWidth(180);
            ImGui::Combo("##Blending", &blend_mode, blend_modes, IM_ARRAYSIZE(blend_modes));
            ImGui::SameLine();
            ImGui::Text("Opacity:");
            ImGui::SameLine();
            //ImGui::SetNextItemWidth(80);
            ImGui::SetNextItemWidth(80);
            ImGui::DragInt("##Opacity", &opacity, 1, 0, 100, "%d%%");
            if (ImGui::IsItemHovered()) {
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
            }
            ImGui::Separator();
            if (!LockIconsLoaded) {
                loadIcons();
                LockIconsLoaded = true;
            }
            // lock toggles
            ImGui::Text("Lock:");
            ImGui::SameLine();
            for (const auto& icon : iconAssets) {
                if (icon.textureId) {
                    ImGui::ImageButton(icon.path, icon.textureId, ImVec2(24,24));
                    ImGui::SameLine();
                }
            }
            ImGui::NewLine();
            ImGui::Separator();


            ImGui::End();
        }
    };
}
NUVIO_UI_NAMESPACE_END
