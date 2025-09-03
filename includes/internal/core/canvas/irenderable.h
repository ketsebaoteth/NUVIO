#include "core/nuvio_namespaces.h"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <cstdint>
#include <vector>

NUVIO_NAMESPACE_BEGIN

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


class Irenderable {
  virtual RenderData getRenderData() const = 0;
  ~Irenderable() = default;
};

NUVIO_NAMESPACE_END
