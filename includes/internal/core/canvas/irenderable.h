#pragma once
#include "core/nuvio_namespaces.h"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <cstdint>
#include <vector>

NUVIO_CANVAS_NAMESPACE_BEGIN

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
  virtual ~Irenderable() = default;
  RenderableType type;
};

NUVIO_CANVAS_NAMESPACE_END
