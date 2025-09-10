#pragma once
#include "core/canvas/irenderable.h"
#include "core/nuvio_namespaces.h"
#include "core/undo/manager.h"
#include "glm/fwd.hpp"
#include "imgui.h"


NUVIO_CANVAS_NAMESPACE_BEGIN

class Rectangle : public Irenderable {
  public:
    std::vector<Property> get_properties() override;
    Rectangle(glm::vec2 pos, glm::vec2 size);
    Rect get_rect() const override;
    void set_rect(Rect rect) override;
    void set_position(glm::vec2 position) override;
    glm::vec2& get_position() override;
    RenderData get_render_data() const override;
    RenderableType get_type() const override;

    // --specific to rectangle--
    void set_background_color(glm::vec4 color);
  private:
    Rect mRect;
    glm::vec4 mBackgroundColor;
};

NUVIO_CANVAS_NAMESPACE_END
