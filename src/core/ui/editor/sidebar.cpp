#include "core/ui/editor/sidebar.h"
#include "core/shortcut/manager.h"
#include "imgui.h"
#include <iostream>

NUVIO_UI_NAMESPACE_BEGIN

component get_sidebar_component() {
    return component{"Sidebar", []() {
        ImGui::Begin("Sidebar");
        auto &selectedRenderables = gCanvasManager.GetSelectedRenderables();
        if (!selectedRenderables.empty()) {
            auto first = selectedRenderables.front();
            std::vector<Property> properties = first->get_properties();

            if (ImGui::BeginTable("PropertiesTable", 2, ImGuiTableFlags_SizingFixedFit)) {
                for (size_t i = 0; i < properties.size(); ++i) {
                    auto &prop = properties[i];
                    ImGui::TableNextRow();

                    // Label column
                    ImGui::TableSetColumnIndex(0);
                    ImGui::TextUnformatted(prop.name.c_str());

                    // Widget column
                    ImGui::TableSetColumnIndex(1);
                    ImGui::SetNextItemWidth(200);

                    switch (prop.type) {
                        case PropertyType::Float:
                            ImGui::DragFloat(("##" + prop.name).c_str(), static_cast<float *>(prop.value), prop.step);
                            if(ImGui::IsItemHovered()) {
                                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
                            }
                            break;
                        case PropertyType::Int:
                            ImGui::DragInt(("##" + prop.name).c_str(), static_cast<int *>(prop.value));
                            break;
                        case PropertyType::Bool:
                            ImGui::Checkbox(("##" + prop.name).c_str(), static_cast<bool *>(prop.value));
                            break;
                        case PropertyType::Color:
                            ImGui::ColorEdit4(("##" + prop.name).c_str(), static_cast<float *>(prop.value));
                            break;
                        case PropertyType::String:
                            ImGui::InputText(("##" + prop.name).c_str(), static_cast<char *>(prop.value), 256);
                            break;
                        default:
                            ImGui::Text("Unknown property type");
                            break;
                    }
                }
                ImGui::EndTable();
            }
        }
        ImGui::End();
    }};
}

NUVIO_UI_NAMESPACE_END