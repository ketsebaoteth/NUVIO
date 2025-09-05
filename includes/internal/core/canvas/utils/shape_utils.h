#pragma once
#include "core/nuvio_namespaces.h"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"

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
  // returns position of each side
  // to make calculations easier to read use this
  float edge_position(RectSide side){
    switch(side){
      case nuvio::canvas::RectSide::LEFT:
        return position.x;
      case nuvio::canvas::RectSide::RIGHT:
        return position.x + size.x;
      case nuvio::canvas::RectSide::TOP:
        return position.y;
      case nuvio::canvas::RectSide::BOTTOM:
        return position.y + size.y;
    }
  };
};

NUVIO_CANVAS_NAMESPACE_END
