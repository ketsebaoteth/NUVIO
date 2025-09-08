#pragma once
#include "core/canvas/irenderable.h"
#include "core/nuvio_namespaces.h"
#include "core/undo/manager.h"
#include "glm/fwd.hpp"
#include "imgui.h"

NUVIO_CANVAS_NAMESPACE_BEGIN

class Rectangle : public Irenderable {
  public:
    Rectangle(glm::vec2 pos, glm::vec2 size);
    Rect get_rect() const override;
    void set_rect(Rect rect) override;
    void set_position(ImVec2 position) override;
    ImVec2 get_position() override;
    RenderData get_render_data() const override;
    RenderableType get_type() const override;

  private:
    Rect mRect;
};

NUVIO_CANVAS_NAMESPACE_END
