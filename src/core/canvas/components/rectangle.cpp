#include "core/canvas/components/rectangle.h"
#include "core/nuvio_namespaces.h"

NUVIO_CANVAS_NAMESPACE_BEGIN

Rectangle::Rectangle(glm::vec2 pos, glm::vec2 size) : mRect{pos,size} {}

Rect Rectangle::get_rect(){return mRect;}

RenderData Rectangle::get_render_data() const{
  RenderData data;
  return data;
}

NUVIO_CANVAS_NAMESPACE_END
