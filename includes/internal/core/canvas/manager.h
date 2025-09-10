#pragma once
#include "core/canvas/irenderable.h"
#include "core/canvas/shader.h"
#include "core/nuvio_namespaces.h"
#include "core/undo/manager.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include <string>
#include <vector>

NUVIO_CANVAS_NAMESPACE_BEGIN
class Irenderable;
NUVIO_CANVAS_NAMESPACE_END

NUVIO_NAMESPACE_BEGIN

struct MoveData {
    canvas::Irenderable *renderable;
    glm::vec2 oldPos;
    glm::vec2 newPos;
};

// Command to move renderables and support undo/redo
class MoveCommand : public action {
  public:
    MoveCommand(const std::vector<MoveData> &moves) : mMoves(moves) {}

    void undo() override {
        for (const auto &move : mMoves)
            move.renderable->set_position(move.oldPos);
    }
    void execute() override {
        for (const auto &move : mMoves)
            move.renderable->set_position(move.newPos);
    }

  private:
    std::vector<MoveData> mMoves;
};

/**
 * @brief The goal of this class it to abstract canvas management and drawing
 * logic
 */
class CanvasManager {
  public:
    void Init(int width, int height);
    void Shutdown();

    GLuint Render();
    /*
     * updaters
     */
    void updateMouseCollision();
    void updateSelected();
    void AppendSelected();
    void updateOutlineRect();
    void updateHandleRects();
    /**
     * Dragging api
     */
    bool hasDraggingStarted;
    bool mIsResizing = false;
    int mResizingHandleIndex = -1;
    void RegisterMoveStart();
    void RegisterMoveEnd();
    bool isMouseOverHandles();
    /**
     * setters
     */
    void SetCanvasSize(const glm::vec2 &size);
    void SetCanvasPosition(const glm::vec2 &position);
    void SetCanvasBackgroundColor(const glm::vec4 &color);
    void SetMouseDelta(ImVec2 mouseDelta);
    void SetMouseLocation(ImVec2 mouseLocation);
    void AddActiveRenderable(canvas::Irenderable *renderable);
    canvas::Rect NDCRectToCanvasPixelRect(const canvas::Rect &rect, const glm::vec2 &canvasSize);
    /**
     * getters
     */
    glm::vec2 GetCanvasSize();
    glm::vec2 GetCanvasPosition();
    std::vector<canvas::Irenderable *>& GetSelectedRenderables();
    // -- for image exporting --
    std::vector<unsigned char> ReadPixels(int x, int y, int width, int height);
    void WriteImage(std::string &path);

    glm::vec2 NDCToScreen(const glm::vec2 &ndc) const;
    /**
     *
     * canvas layer and renderable insertion
     */
    void AppendLayer(std::vector<nuvio::canvas::Irenderable *> Layer);
    void AppendRenderable(nuvio::canvas::Irenderable *renderable, int index);
    void RemoveRenderable(nuvio::canvas::Irenderable *renderable, int index);
    /**
     * Canvas Drawing Functions
     */
    void DrawHandles();

  private:
    // -- canvas properties --
    glm::vec2 mCanvasPosition;
    glm::vec2 mCanvasSize;
    glm::vec4 mCanvasBackgroundColor;

    static constexpr glm::vec2 mHandleSize  = glm::vec2(10, 10);
    std::vector<canvas::Rect> mHandleRects;

    ImVec2 mMouseDelta;
    ImVec2 mMouseLocation;
    canvas::Rect mHandleRect; // rect used to draw handles
    glm::vec2 mOutlineTopLeftScreen;
    glm::vec2 mOutlineBottomRightScreen;

    std::vector<std::vector<canvas::Irenderable *>> mLayers;
    // -- canvas properties --

    // -- for opengl --
    GLuint mFramebuffer;
    GLuint mFramebufferTexture;
    canvas::shader mShader;
    GLuint mVao;
    GLuint mVbo;
    GLuint mEbo;
    GLuint mCanvasTexture;
    // -- for opengl --

    std::vector<canvas::Irenderable *> mSelectedRenderables;
    bool isPointInRect(nuvio::canvas::Rect &rect, ImVec2 &vec);
    // -- for undo ---
    std::vector<MoveData> mMoveData; // data to store the starting and endin
};

extern CanvasManager gCanvasManager;

NUVIO_NAMESPACE_END
