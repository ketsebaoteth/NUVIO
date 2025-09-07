#pragma once
#include "core/nuvio_namespaces.h"
#include "core/undo/manager.h"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <cstdint>
#include <vector>
#include "core/canvas/utils/shape_utils.h"

NUVIO_CANVAS_NAMESPACE_BEGIN
class CanvasManager;
extern CanvasManager gCanvasManager;

struct vertex{
  glm::vec3 position;
  glm::vec2 uv;
  glm::vec4 color;
};

struct RenderData{
  std::vector<vertex> verticies;	
  std::vector<uint32_t> indecies;
  glm::mat4 modalMatrix;
  int textureID;
  glm::vec4 color;
};

enum class RenderableType{
  RECTANGLE
};

class Irenderable {
public:
  virtual RenderableType get_type() const = 0;
  virtual RenderData get_render_data() const = 0;
  virtual Rect get_rect() const = 0;
  virtual void set_rect(Rect rect) = 0;
  virtual ~Irenderable() = default;
  RenderableType type;
};

class AddRenderableAction : public action {
  Irenderable* renderable;
  int layerIndex;
public:
  AddRenderableAction(Irenderable* rend, int idx);
  void execute() override ;

    void undo() override ;

};

NUVIO_CANVAS_NAMESPACE_END
