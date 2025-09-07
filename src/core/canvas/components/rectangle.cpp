#include "core/canvas/components/rectangle.h"
#include "core/canvas/utils/shape_utils.h"
#include "core/nuvio_namespaces.h"

NUVIO_CANVAS_NAMESPACE_BEGIN

Rectangle::Rectangle(glm::vec2 pos, glm::vec2 size) : mRect{pos,size} {}

Rect Rectangle::get_rect() const {return mRect;}
void Rectangle::set_rect(Rect rect){
  mRect = rect;
}

RenderableType Rectangle::get_type() const {return RenderableType::RECTANGLE;}

RenderData Rectangle::get_render_data() const{
  RenderData data;
  float x = mRect.position.x;
    float y = mRect.position.y;
    float w = mRect.size.x;
    float h = mRect.size.y;

    glm::vec4 vertColor = {1.0f,0.0f,0.0f,1.0f};
    // For example:
    // glm::vec4 vertColor = glm::vec4(1.0, 1.0, 1.0, 1.0);

    // Vertices in CCW order (bottom-left, bottom-right, top-right, top-left)
    data.verticies = {
        // Position                //  UV       // Color
        {{x,     y,     0.0f},   {0.0f, 0.0f}, vertColor}, // bottom-left
        {{x + w, y,     0.0f},   {1.0f, 0.0f}, vertColor}, // bottom-right
        {{x + w, y + h, 0.0f},   {1.0f, 1.0f}, vertColor}, // top-right
        {{x,     y + h, 0.0f},   {0.0f, 1.0f}, vertColor}  // top-left
    };

    // Indices for two triangles
    data.indecies = {
        0, 1, 2,
        2, 3, 0
    };

    data.modalMatrix = glm::mat4(1.0f); // Identity by default (no extra model transform)
    data.textureID = -1; // Or a valid texture ID if you have one
    data.color = vertColor; // Or a global color for the rectangle
  return data;
}

NUVIO_CANVAS_NAMESPACE_END
