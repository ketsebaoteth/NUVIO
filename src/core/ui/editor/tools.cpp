#include "core/ui/editor/tools.h"
#include "core/nuvio_namespaces.h"
#include "imgui.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <vector>
#include <string>
#include "glad/glad.h"
#include "core/ui/components/comp.h"
#include <unordered_map>
#include <cstdint> // for intptr_t


NUVIO_UI_NAMESPACE_BEGIN
// --------- ICON LOADING UTILITIES ---------
// Simple OpenGL texture loader using stb_image.h
// (You can replace with your renderer's texture loader if not using OpenGL)

static GLuint LoadTextureFromFile(const char* filename, int* out_width, int* out_height)
{
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return 0;

    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#ifdef GL_UNPACK_ROW_LENGTH
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_width = image_width;
    *out_height = image_height;
    return image_texture;
}

// --------- TOOLBAR STRUCTURE ---------
struct tool {
    std::string path_to_icon;
    std::string tool_name;
    std::string tool_descp;
    ImTextureID texture_id = 0; // Will be set at runtime
};

std::vector<tool> tools = {
    {"./assets/icons/move.png", "Move", "Move tool: Drag to reposition elements."},
    {"./assets/icons/rect-select.png", "Rectangle Select", "Select rectangular regions."},
    {"./assets/icons/lasso-select.png", "Lasso Select", "Select freeform regions."},
    {"./assets/icons/crop.png", "Crop", "Crop the canvas."},
    {"./assets/icons/brush.png", "Brush", "Brush tool: Paint with brush."},
    {"./assets/icons/eyedropper.png", "Eyedropper", "Pick colors from canvas."},
    {"./assets/icons/stamp.png", "Clone Stamp", "Clone stamp tool."},
    {"./assets/icons/polygon.png", "Polygon", "Draw polygons."},
    {"./assets/icons/gradient.png", "Gradient", "Gradient fill tool."},
    {"./assets/icons/bucket.png", "Fill", "Fill with color or pattern."},
    {"./assets/icons/pen.png", "Pen", "Pen tool: Draw paths."},
    {"./assets/icons/text.png", "Text", "Text tool: Add and edit text."},
    {"./assets/icons/eraser.png", "Eraser", "Erase parts of the image."},
    {"./assets/icons/hand.png", "Hand", "Pan/move the canvas view."},
    {"./assets/icons/zoom-in.png", "Zoom In", "Zoom in to mouse location."},
    {"./assets/icons/zoom-out.png","Zoom Out", "Zoom out from mouse location."},
    {"./assets/icons/more.png", "More Tools", "Show more tools."},
};

// Helper to load all tool icons only once
static void LoadAllToolIcons()
{
    static bool loaded = false;
    if (loaded) return;
    loaded = true;

    for (auto& t : tools) {
        int icon_w = 0, icon_h = 0;
        GLuint tex_id = LoadTextureFromFile(t.path_to_icon.c_str(), &icon_w, &icon_h);
        t.texture_id = (ImTextureID)(intptr_t)tex_id;
    }
}

component get_tools_component() {
    return component{
        "ToolsComponent",
        []() {
            LoadAllToolIcons();

            ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar;
            ImGui::Begin("Tools", nullptr, flags);

            // Draw vertical icon toolbar
            for (const auto& t : tools) {
                ImGui::PushID(t.tool_name.c_str());
                if (t.texture_id) {
                    if (ImGui::ImageButton(t.tool_name.c_str(), t.texture_id, ImVec2(28, 28)))
                    {
                        // Handle tool select/click here
                    }
                } else {
                    // Fallback: show a button with tool initial if icon missing
                    ImGui::Button(t.tool_name.substr(0, 1).c_str(), ImVec2(28, 28));
                }
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("%s\n%s", t.tool_name.c_str(), t.tool_descp.c_str());
                ImGui::PopID();
            }

            ImGui::End();
        }
    };
}

NUVIO_UI_NAMESPACE_END


