#pragma once
#include "core/canvas/irenderable.h"
#include "core/nuvio_namespaces.h"
#include "core/canvas/utils/shape_utils.h"
#include "glm/fwd.hpp"

NUVIO_CANVAS_NAMESPACE_BEGIN

class Rectangle : public Irenderable{
public:
  Rectangle(glm::vec2 pos, glm::vec2 size);
  Rect get_rect();
  RenderData get_render_data() const override;
  RenderableType get_type() const override;
private:
  Rect mRect;
};

NUVIO_CANVAS_NAMESPACE_END
