#pragma once
#include "core/nuvio_namespaces.h"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <ostream>
#include "imgui.h"

NUVIO_CANVAS_NAMESPACE_BEGIN

enum class RectSide{
  TOP,
  LEFT,
  RIGHT,
  BOTTOM
};

struct Rect{
  glm::vec2 position;
  glm::vec2 size;
  Rect();
  Rect(glm::vec2 pos, glm::vec2 size);
  // returns position of each side
  // to make calculations easier to read use this
  float edge_position(RectSide side)const{
    switch(side){
      case nuvio::canvas::RectSide::LEFT:
        return position.x - (size.x/2);
      case nuvio::canvas::RectSide::RIGHT:
        return position.x + (size.x/2);
      case nuvio::canvas::RectSide::TOP:
        return position.y - (size.y/2);
      case nuvio::canvas::RectSide::BOTTOM:
        return position.y + (size.y/2);
      default:
        return 0.0f;
    }
  };
  
};

std::ostream& operator<<(std::ostream& os, const Rect& r);

void DrawStrokedRectangle(canvas::Rect rect);

NUVIO_CANVAS_NAMESPACE_END
