#include "core/canvas/manager.h"
#include <cassert>
#include <cstdio>
#include <iostream>

NUVIO_NAMESPACE_BEGIN

GLuint CompileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Optional: error checking
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation error: " << infoLog << std::endl;
    }
    return shader;
}

GLuint CreateShaderProgram(const char* vertSrc, const char* fragSrc) {
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragSrc);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Optional: error checking
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Program linking error: " << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

void CanvasManager::Init(int width, int height) {
    assert(width > 0 && height > 0 && "Width and Height must be greater than 0");
    mCanvasSize = glm::vec2(static_cast<float>(width), static_cast<float>(height));

    //create frame buffer
    glGenFramebuffers(1, &mFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

    //create canvas texture
    glGenTextures(1, &mCanvasTexture);
    glBindTexture(GL_TEXTURE_2D, mCanvasTexture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,static_cast<GLsizei>(mCanvasSize.x),static_cast<GLsizei>(mCanvasSize.y),0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    //attach texture to frame buffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,mCanvasTexture,0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cerr << "Canvas framebuffer is incomplete!" << std::endl;
    }

    //unbind buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //create vao
    glGenVertexArrays(1,&mVao);
    glBindVertexArray(mVao);
    
    //create vbo
    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER,mVbo);

    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
  
    //create ebo
    glGenBuffers(1, &mEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
    // You can allocate zero bytes here as a placeholder, e.g.:
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
    
    GLsizei stride = sizeof(canvas::vertex);
    
    // position (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(canvas::vertex, position));
    glEnableVertexAttribArray(0);

    // uv (location 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(canvas::vertex, uv));
    glEnableVertexAttribArray(1);

    // color (location 2)
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(canvas::vertex, color));
    glEnableVertexAttribArray(2);

    //shaders for testing
    const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec4 inColor;

out vec4 vertColor;

void main() {
    gl_Position = vec4(inPos, 1.0);
    vertColor = inColor;
}
)";

    const char* fragmentShaderSource = R"(
#version 330 core
in vec4 vertColor;
out vec4 FragColor;

void main() {
    FragColor = vertColor;
}
    )";

  mShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
    
}

void CanvasManager::Shutdown() {
    // Cleanup code
}

GLuint CanvasManager::Render() {
    //rebind since in use
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    glViewport(0,0,static_cast<GLsizei>(mCanvasSize.x),static_cast<GLsizei>(mCanvasSize.y));

    glClearColor(mCanvasBackgroundColor.r,mCanvasBackgroundColor.g,mCanvasBackgroundColor.b,mCanvasBackgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(mShaderProgram);
    //main rendering
    for(const auto& layer : mLayers){
      for(const auto& renderable : layer){
        if(!renderable) continue;
          canvas::RenderData data = renderable->get_render_data();
          //
          glBindVertexArray(mVao);
          //
          glBindBuffer(GL_ARRAY_BUFFER, mVbo);
          glBufferData(GL_ARRAY_BUFFER, data.verticies.size() * sizeof(canvas::vertex),data.verticies.data(), GL_DYNAMIC_DRAW );
          // //upload indecies data
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
          glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indecies.size() * sizeof(uint32_t), data.indecies.data(), GL_DYNAMIC_DRAW);
          
          glDrawElements(GL_TRIANGLES, data.indecies.size(), GL_UNSIGNED_INT,0);
          //
          glBindVertexArray(0);

      }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return mCanvasTexture;

}

glm::vec2 CanvasManager::GetCanvasSize(){
    return mCanvasSize;
}

glm::vec2 CanvasManager::GetCanvasPosition(){
    return mCanvasPosition;
}

void CanvasManager::SetCanvasBackgroundColor(const glm::vec4& color){
    mCanvasBackgroundColor = color;
}

void CanvasManager::AppendLayer(std::vector<canvas::Irenderable*> Layer){
  mLayers.push_back(Layer);
}

void CanvasManager::AppendRenderable(canvas::Irenderable* renderable,int index){
 mLayers[index].push_back(renderable); 
}


CanvasManager gCanvasManager;


NUVIO_NAMESPACE_END
