#include "core/canvas/utils/shape_utils.h"
#include "imgui.h"

NUVIO_CANVAS_NAMESPACE_BEGIN

Rect::Rect() : position(0, 0), size(0, 0) {};

Rect::Rect(glm::vec2 pos, glm::vec2 s) : position(pos), size(s) {};

std::ostream &operator<<(std::ostream &os, const Rect &r) {
    os << "Rect { "
       << "pos=(" << r.position.x << ", " << r.position.y << "), "
       << "size=(" << r.size.x << ", " << r.size.y << "), "
       << "left=" << r.edge_position(nuvio::canvas::RectSide::LEFT) << ", "
       << "right=" << r.edge_position(nuvio::canvas::RectSide::RIGHT) << ", "
       << "top=" << r.edge_position(nuvio::canvas::RectSide::TOP) << ", "
       << "bottom=" << r.edge_position(nuvio::canvas::RectSide::BOTTOM) << " }";
    return os;
}
void DrawStrokedRectangle(Rect rect) {
    ImDrawList *draw_list = ImGui::GetForegroundDrawList();
    ImVec2 halfedSize = {rect.size.x/2,rect.size.y/2};
    // draw handle
    draw_list->AddRectFilled(ImVec2(rect.position.x - halfedSize.x, rect.position.y - halfedSize.y),
                             ImVec2(rect.position.x + rect.size.x, rect.position.y + rect.size.x),
                             IM_COL32(255, 255, 255, 255), // white fill
                             5.0f                          // optional corner rounding
    );

    // Then: draw blue border
    draw_list->AddRect(ImVec2(rect.position.x - halfedSize.x, rect.position.y - halfedSize.y),
                       ImVec2(rect.position.x + rect.size.x, rect.position.y + rect.size.y), IM_COL32(0, 0, 255, 255), // blue border
                       5.0f, // match corner rounding
                       0,    // flags (0 = all corners)
                       2.0f  // thickness
    );
}

NUVIO_CANVAS_NAMESPACE_END
