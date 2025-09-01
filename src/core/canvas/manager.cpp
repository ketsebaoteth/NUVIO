#include "core/canvas/manager.h"
#include <cassert>
#include <iostream>

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

CanvasManager gCanvasManager;

NUVIO_NAMESPACE_END
