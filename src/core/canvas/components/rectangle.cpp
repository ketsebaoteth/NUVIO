#include "core/canvas/components/rectangle.h"
#include "core/canvas/utils/shape_utils.h"
#include "core/nuvio_namespaces.h"
#include "glm/fwd.hpp"
#include "imgui.h"
#include <iostream>

NUVIO_CANVAS_NAMESPACE_BEGIN

Rectangle::Rectangle(glm::vec2 pos, glm::vec2 size) : mRect{pos,size} {}

void Rectangle::set_rect(Rect rect) {
    mRect = rect;
}
Rect Rectangle::get_rect() const {
    return mRect;
}

void Rectangle::set_position(ImVec2 position) {
  mRect.position = {position.x, position.y};
}

ImVec2 Rectangle::get_position(){
  return {mRect.position.x,mRect.position.y};
}

RenderableType Rectangle::get_type() const {return RenderableType::RECTANGLE;}
 
RenderData Rectangle::get_render_data() const {
  RenderData data;

  // Adjust position to treat mRect.position as the center of the rectangle
  float x = mRect.position.x - mRect.size.x / 2.0f;
  float y = mRect.position.y - mRect.size.y / 2.0f;
  float w = mRect.size.x;
  float h = mRect.size.y;

  glm::vec4 vertColor = {1.0f, 0.0f, 0.0f, 1.0f}; // Red color

  // Vertices in counter-clockwise order: bottom-left, bottom-right, top-right, top-left
  data.verticies = {
    // Position                  // UV Coordinates   // Vertex Color
    {{x,     y,     0.0f},      {0.0f, 0.0f},       vertColor}, // bottom-left
    {{x + w, y,     0.0f},      {1.0f, 0.0f},       vertColor}, // bottom-right
    {{x + w, y + h, 0.0f},      {1.0f, 1.0f},       vertColor}, // top-right
    {{x,     y + h, 0.0f},      {0.0f, 1.0f},       vertColor}  // top-left
  };

  // Indices for two triangles forming the rectangle
  data.indecies = {
    0, 1, 2,
    2, 3, 0
  };

  data.modalMatrix = glm::mat4(1.0f); // Identity matrix (no transformation)
  data.textureID = -1;                // No texture by default
  data.color = vertColor;            // Global color for the rectangle

  return data;
}

NUVIO_CANVAS_NAMESPACE_END
