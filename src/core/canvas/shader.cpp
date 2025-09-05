#include "core/canvas/shader.h"
#include "core/nuvio_namespaces.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

NUVIO_CANVAS_NAMESPACE_BEGIN
std::string shader::loadFile(const std::string& filePath){
  std::ifstream file(filePath);
  if(!file){
    std::cerr << "Error: coudnt open shader file path: " << filePath << std::endl;
    return "";
  }
  std::stringstream ss;
  ss << file.rdbuf();
  return ss.str();
};

GLuint shader::compileShader(GLenum shaderType, const std::string& src){
  GLuint shader = glCreateShader(shaderType);
  const char* csrc = src.c_str();
  glShaderSource(shader,1,&csrc, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader,GL_COMPILE_STATUS, &success);
  if(!success){
    char infoLog[512];
    glGetShaderInfoLog(shader,512,nullptr,infoLog);
    std::cerr << "ERROR: shader compilation failed: \n" << infoLog << std::endl;
  }
  return shader;
}

shader::shader(const std::string& vertexPath, const std::string& fragmentPath){
  std::string vertexSRC = loadFile(vertexPath);
  std::string fragmentSRC = loadFile(fragmentPath);

  GLuint vertexShader = compileShader(GL_VERTEX_SHADER,vertexSRC);
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSRC);

  ID = glCreateProgram();
  glAttachShader(ID,vertexShader);
  glAttachShader(ID,fragmentShader);
  glLinkProgram(ID);

  GLint success;
  glGetProgramiv(ID,GL_LINK_STATUS, &success);
  if(!success){
    char infoLog[512];
    glGetProgramInfoLog(ID,512,nullptr,infoLog);
    std::cerr << "ERROR: coudnt link program : \n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

shader::shader() : ID(0) {}

void shader::destroy(){
  if(ID) glDeleteProgram(ID);
}

void shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

NUVIO_CANVAS_NAMESPACE_END


