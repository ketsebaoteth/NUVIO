#pragma once
#include <string>
#include <glad/glad.h>
#include "core/nuvio_namespaces.h"

NUVIO_CANVAS_NAMESPACE_BEGIN

class shader{
public:
  GLuint ID;

  shader(const std::string& vertexPath, const std::string& fragmentPath );
  shader();
  void use() const {glUseProgram(ID);}
  void destroy();
  
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;

private:
  static std::string loadFile(const std::string& path);
  GLuint compileShader(GLenum type, const std::string& src);
};

NUVIO_CANVAS_NAMESPACE_END
