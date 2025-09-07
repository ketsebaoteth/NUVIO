#include "core/canvas/manager.h"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <pstl/glue_algorithm_defs.h>
#include "core/canvas/irenderable.h"
#include "core/canvas/shader.h"

NUVIO_NAMESPACE_BEGIN

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
    //create shader
    mShader = canvas::shader("shaders/default_vertex.glsl","shaders/default_fragment.glsl");
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


}

void CanvasManager::Shutdown() {
    // Unbind everything just in case
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Delete OpenGL resources if they exist
    if (mVao) glDeleteVertexArrays(1, &mVao);
    if (mVbo) glDeleteBuffers(1, &mVbo);
    if (mEbo) glDeleteBuffers(1, &mEbo);
    if (mFramebuffer) glDeleteFramebuffers(1, &mFramebuffer);
    if (mCanvasTexture) glDeleteTextures(1, &mCanvasTexture);
}

GLuint CanvasManager::Render() {
    //rebind since in use
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    glViewport(0,0,static_cast<GLsizei>(mCanvasSize.x),static_cast<GLsizei>(mCanvasSize.y));

    glClearColor(mCanvasBackgroundColor.r,mCanvasBackgroundColor.g,mCanvasBackgroundColor.b,mCanvasBackgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(mShader.ID);
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

void CanvasManager::RemoveRenderable(canvas::Irenderable* renderable, int index){
  auto& vec = mLayers[index];
  vec.erase(
    std::remove(vec.begin(), vec.end(), renderable),
    vec.end()
  );
}


CanvasManager gCanvasManager;


NUVIO_NAMESPACE_END
