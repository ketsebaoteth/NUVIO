#pragma once
#include "core/nuvio_namespaces.h"
#include "glm/glm.hpp"
#include "glad/glad.h"

NUVIO_NAMESPACE_BEGIN

/**
 * @brief The goal of this class it to abstract canvas management and drawing logic
 */
class CanvasManager {
public:

    void Init(int width, int height);
    void Shutdown();

    GLuint Render();
    /**
     * setters
     */
    void SetCanvasSize(const glm::vec2& size);
    void SetCanvasPosition(const glm::vec2& position);
    void SetCanvasBackgroundColor(const glm::vec4& color);
    /**
     * getters
     */
    glm::vec2 GetCanvasSize();
    glm::vec2 GetCanvasPosition();

    /**
     * Canvas Drawing Functions
     */
    void FillPixel(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    void DrawCircle(const glm::vec2& position, float radius, const glm::vec4& color);
    void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec4& color);

private:
    // -- canvas properties --
    glm::vec2 mCanvasPosition;
    glm::vec2 mCanvasSize;
    glm::vec4 mCanvasBackgroundColor;
    // -- canvas properties --


    // -- for opengl --
    GLuint mFramebuffer;
    GLuint mFramebufferTexture;

    GLuint mCanvasTexture;
    // -- for opengl --
    

};

extern CanvasManager gCanvasManager;

NUVIO_NAMESPACE_END
