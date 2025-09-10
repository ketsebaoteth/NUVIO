#include "core/canvas/manager.h"
#include "core/canvas/irenderable.h"
#include "core/canvas/shader.h"
#include "core/canvas/utils/shape_utils.h"
#include "core/undo/manager.h"
#include "glm/fwd.hpp"
#include "imgui.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <ostream>

// suppress warrnings from stb_image_write
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

NUVIO_NAMESPACE_BEGIN

void CanvasManager::Init(int width, int height) {
    assert(width > 0 && height > 0 && "Width and Height must be greater than 0");
    mCanvasSize = glm::vec2(static_cast<float>(width), static_cast<float>(height));

    // create frame buffer
    glGenFramebuffers(1, &mFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

    // create canvas texture
    glGenTextures(1, &mCanvasTexture);
    glBindTexture(GL_TEXTURE_2D, mCanvasTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(mCanvasSize.x), static_cast<GLsizei>(mCanvasSize.y), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // attach texture to frame buffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mCanvasTexture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Canvas framebuffer is incomplete!" << std::endl;
    }

    // unbind buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // create shader
    mShader = canvas::shader("shaders/default_vertex.glsl", "shaders/default_fragment.glsl");
    // create vao
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    // create vbo
    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);

    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    // create ebo
    glGenBuffers(1, &mEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
    // You can allocate zero bytes here as a placeholder, e.g.:
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    GLsizei stride = sizeof(canvas::vertex);

    // position (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(canvas::vertex, position));
    glEnableVertexAttribArray(0);

    // uv (location 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(canvas::vertex, uv));
    glEnableVertexAttribArray(1);

    // color (location 2)
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(canvas::vertex, color));
    glEnableVertexAttribArray(2);
}

void CanvasManager::Shutdown() {
    // Unbind everything just in case
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Delete OpenGL resources if they exist
    if (mVao)
        glDeleteVertexArrays(1, &mVao);
    if (mVbo)
        glDeleteBuffers(1, &mVbo);
    if (mEbo)
        glDeleteBuffers(1, &mEbo);
    if (mFramebuffer)
        glDeleteFramebuffers(1, &mFramebuffer);
    if (mCanvasTexture)
        glDeleteTextures(1, &mCanvasTexture);
}

GLuint CanvasManager::Render() {
    // rebind since in use
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    glViewport(0, 0, static_cast<GLsizei>(mCanvasSize.x), static_cast<GLsizei>(mCanvasSize.y));

    glClearColor(mCanvasBackgroundColor.r, mCanvasBackgroundColor.g, mCanvasBackgroundColor.b,
                 mCanvasBackgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(mShader.ID);
    // main rendering
    for (const auto &layer : mLayers) {
        for (const auto &renderable : layer) {
            if (!renderable)
                continue;
            canvas::RenderData data = renderable->get_render_data();
            //
            glBindVertexArray(mVao);
            //
            glBindBuffer(GL_ARRAY_BUFFER, mVbo);
            glBufferData(GL_ARRAY_BUFFER, data.verticies.size() * sizeof(canvas::vertex), data.verticies.data(),
                         GL_DYNAMIC_DRAW);
            // //upload indecies data
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indecies.size() * sizeof(uint32_t), data.indecies.data(),
                         GL_DYNAMIC_DRAW);

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(data.indecies.size()), GL_UNSIGNED_INT, 0);
            //
            glBindVertexArray(0);
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // draw imgui side handles
    if (!mSelectedRenderables.empty()) {
        updateOutlineRect();
        DrawHandles();
    }

    return mCanvasTexture;
}

glm::vec2 CanvasManager::GetCanvasSize() { return mCanvasSize; }

glm::vec2 CanvasManager::GetCanvasPosition() { return mCanvasPosition; }

void CanvasManager::SetCanvasPosition(const glm::vec2 &position) { mCanvasPosition = position; }

void CanvasManager::SetCanvasBackgroundColor(const glm::vec4 &color) { mCanvasBackgroundColor = color; }

void CanvasManager::AppendLayer(std::vector<canvas::Irenderable *> Layer) { mLayers.push_back(Layer); }

void CanvasManager::AppendRenderable(canvas::Irenderable *renderable, int index) {
    mLayers[index].push_back(renderable);
}

void CanvasManager::RemoveRenderable(canvas::Irenderable *renderable, int index) {
    auto &vec = mLayers[index];
    vec.erase(std::remove(vec.begin(), vec.end(), renderable), vec.end());
}

void CanvasManager::SetMouseDelta(ImVec2 mouseDelta) { mMouseDelta = mouseDelta; }

void CanvasManager::SetMouseLocation(ImVec2 mouseLocation) { mMouseLocation = mouseLocation; }

void CanvasManager::AddActiveRenderable(canvas::Irenderable *renderable) {
    // Only add if not already present
    auto it = std::find(mSelectedRenderables.begin(), mSelectedRenderables.end(), renderable);
    if (it == mSelectedRenderables.end()) {
        mSelectedRenderables.push_back(renderable);
    }
}

void CanvasManager::updateOutlineRect() {
    glm::vec2 minXY(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    glm::vec2 maxXY(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());

    bool anySelected = false;
    for (auto &selected : mSelectedRenderables) {
        canvas::Rect selected_rect = selected->get_rect();

        float left = selected_rect.edge_position(canvas::RectSide::LEFT);
        float right = selected_rect.edge_position(canvas::RectSide::RIGHT);
        float top = selected_rect.edge_position(canvas::RectSide::TOP);
        float bottom = selected_rect.edge_position(canvas::RectSide::BOTTOM);

        minXY.x = std::min(minXY.x, left);
        minXY.y = std::min(minXY.y, top);
        maxXY.x = std::max(maxXY.x, right);
        maxXY.y = std::max(maxXY.y, bottom);

        anySelected = true;
    }

    // --- Add margin in NDC units (positive = more space around selection) ---
    float margin = 0.01f; // adjust as needed, e.g. 0.01 ~ 1% of NDC range

    minXY -= glm::vec2(margin, margin);
    maxXY += glm::vec2(margin, margin);

    glm::vec2 center = (minXY + maxXY) * 0.5f;
    glm::vec2 size = maxXY - minXY;

    if (!anySelected) {
        mHandleRect = canvas::Rect({0, 0}, {0, 0});
        return;
    }

    mHandleRect = canvas::Rect(center, size);
}

bool CanvasManager::isMouseOverHandles() {
    int idx = 0;
    for (const auto &rect : mHandleRects) {
        float x = rect.position.x;
        float y = rect.position.y;
        float w = rect.size.x;
        float h = rect.size.y;
        if (mMouseLocation.x >= x && mMouseLocation.x <= x + w && mMouseLocation.y >= y && mMouseLocation.y <= y + h) {
            mIsResizing = true;
            mResizingHandleIndex = idx;
            return true;
        }
        ++idx;
    }
    return false;
}

void CanvasManager::updateSelected() {
    if (isMouseOverHandles()) {
        return;
    }
    mSelectedRenderables.clear();
    for (auto &layers : mLayers) {
        for (auto &renderables : layers) {
            canvas::Rect renderable_rect = renderables->get_rect();
            if (isPointInRect(renderable_rect, mMouseLocation)) {
                AddActiveRenderable(renderables);
            }
        }
    }
}

void CanvasManager::AppendSelected() {
    for (auto &layers : mLayers) {
        for (auto &renderables : layers) {
            canvas::Rect renderable_rect = renderables->get_rect();
            if (isPointInRect(renderable_rect, mMouseLocation)) {
                AddActiveRenderable(renderables);
            }
        }
    }
}

bool CanvasManager::isPointInRect(nuvio::canvas::Rect &rect, ImVec2 &vec) {
    // Helper lambda to convert OpenGL [-1, 1] to pixel space [0, canvas_size]
    auto glToPixelX = [&](float gl_x) { return ((gl_x + 1.0f) * 0.5f) * mCanvasSize.x; };
    auto glToPixelY = [&](float gl_y) { return ((1.0f - gl_y) * 0.5f) * mCanvasSize.y;; };

    // Convert rect edges from OpenGL space to pixel space
    float left_px = glToPixelX(rect.edge_position(nuvio::canvas::RectSide::LEFT));
    float right_px = glToPixelX(rect.edge_position(nuvio::canvas::RectSide::RIGHT));
    float bottom_px = glToPixelY(rect.edge_position(nuvio::canvas::RectSide::TOP));
    float top_px = glToPixelY(rect.edge_position(nuvio::canvas::RectSide::BOTTOM));

    // Check if the point is within the rectangle bounds
    return (vec.x >= left_px && vec.x <= right_px && vec.y >= top_px && vec.y <= bottom_px);
}

glm::vec2 CanvasManager::NDCToScreen(const glm::vec2 &ndc) const {
    // Convert NDC -> canvas-local pixel coords, then offset by canvas position
    return glm::vec2(mCanvasPosition.x + (ndc.x + 1.0f) * 0.5f * mCanvasSize.x,
                  mCanvasPosition.y + (1.0f - (ndc.y + 1.0f) * 0.5f) * mCanvasSize.y);
}

void CanvasManager::updateHandleRects(){
    // Get rect edges in NDC
    float left = mHandleRect.edge_position(canvas::RectSide::LEFT);
    float right = mHandleRect.edge_position(canvas::RectSide::RIGHT);
    float top = mHandleRect.edge_position(canvas::RectSide::BOTTOM);
    float bottom = mHandleRect.edge_position(canvas::RectSide::TOP);

    // Convert corners to absolute screen pixel coords
    mOutlineTopLeftScreen = NDCToScreen(glm::vec2(left, top));
    mOutlineBottomRightScreen = NDCToScreen(glm::vec2(right, bottom));

    mHandleRects.clear();
    // handle positions and sizes relative to canvas
    mHandleRects.insert(mHandleRects.end(), {
    {glm::vec2(mOutlineTopLeftScreen.x - mCanvasPosition.x, mOutlineTopLeftScreen.y - mCanvasPosition.y), mHandleSize},
    {glm::vec2(mOutlineBottomRightScreen.x - mCanvasPosition.x, mOutlineBottomRightScreen.y - mCanvasPosition.y), mHandleSize},
    {glm::vec2(mOutlineTopLeftScreen.x - mCanvasPosition.x, mOutlineBottomRightScreen.y - mCanvasPosition.y), mHandleSize},
    {glm::vec2(mOutlineBottomRightScreen.x - mCanvasPosition.x, mOutlineTopLeftScreen.y - mCanvasPosition.y), mHandleSize}
    });
}

void CanvasManager::DrawHandles() {
    
    updateHandleRects();
    // Draw in outline rectangle
    ImDrawList *draw_list = ImGui::GetForegroundDrawList();
    draw_list->AddRect({mOutlineTopLeftScreen.x, mOutlineTopLeftScreen.y}, {mOutlineBottomRightScreen.x, mOutlineBottomRightScreen.y},
                       IM_COL32(0, 0, 255, 255), 0.0f, 0, 2.0f);

    for(auto &handle : mHandleRects) {
        // make them relative to window cause imgui 
        canvas::DrawStrokedRectangle({handle.position + mCanvasPosition, handle.size});
    }

}

void CanvasManager::updateMouseCollision() {
    if (mIsResizing) {
        if (mSelectedRenderables.empty())
            return;

        auto renderable = mSelectedRenderables[0];
        canvas::Rect rect = renderable->get_rect();

        float half_w = rect.size.x * 0.5f;
        float half_h = rect.size.y * 0.5f;
        glm::vec2 center = rect.position;

        ImVec2 tl = {center.x - half_w, center.y - half_h};
        ImVec2 tr = {center.x + half_w, center.y - half_h};
        ImVec2 bl = {center.x - half_w, center.y + half_h};
        ImVec2 br = {center.x + half_w, center.y + half_h};

        float world_dx = 2.0f * mMouseDelta.x / mCanvasSize.x;
        float world_dy = -2.0f * mMouseDelta.y / mCanvasSize.y;

        ImVec2 moved, fixed;

        switch (mResizingHandleIndex) {
        case 0: // bottom-left moves
            moved = {bl.x + world_dx, bl.y + world_dy};
            fixed = tr;
            break;
        case 1: // top-right moves
            moved = {tr.x + world_dx, tr.y + world_dy};
            fixed = bl;
            break;
        case 2: // top-left moves
            moved = {tl.x + world_dx, tl.y + world_dy};
            fixed = br;
            break;
        case 3: // bottom-right moves
            moved = {br.x + world_dx, br.y + world_dy};
            fixed = tl;
            break;
        default:
            return;
        }

        ImVec2 new_center = {(moved.x + fixed.x) * 0.5f, (moved.y + fixed.y) * 0.5f};
        ImVec2 new_size = {fabsf(moved.x - fixed.x), fabsf(moved.y - fixed.y)};
        renderable->set_rect({{new_center.x, new_center.y}, {new_size.x, new_size.y}});
    } else {
        for (auto &renderables : mSelectedRenderables) {
            canvas::Rect renderable_rect = renderables->get_rect();

            float world_dx = 2.0f * mMouseDelta.x / mCanvasSize.x;
            float world_dy = -2.0f * mMouseDelta.y / mCanvasSize.y;
            renderables->set_rect({{renderable_rect.position.x + world_dx, renderable_rect.position.y + world_dy},
                                   {renderable_rect.size.x, renderable_rect.size.y}});
        }
    }
}

void CanvasManager::RegisterMoveStart() {
    for (auto &selected : mSelectedRenderables) {
        ImVec2 oldPos = selected->get_position();
        mMoveData.push_back(
            {selected, oldPos, oldPos}); // store old pos for now for the new pos till we get the new pos
    }
}

void CanvasManager::RegisterMoveEnd() {
    for (auto &movedata : mMoveData) {
        movedata.newPos = movedata.renderable->get_position();
    }
    // create an undo command
    gUndoManager.add_action(std::make_unique<MoveCommand>(mMoveData));
    mMoveData.clear();
}

std::vector<unsigned char> CanvasManager::ReadPixels(int x, int y, int width, int height) {
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    std::vector<unsigned char> pixels(width * height * 4); // rgba
    glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return pixels;
}

void CanvasManager::WriteImage(std::string &path) {
    mSelectedRenderables.clear();
    std::vector<unsigned char> pixels =
        ReadPixels(0, 0, static_cast<int>(mCanvasSize.x), static_cast<int>(mCanvasSize.y));
    stbi_write_png(path.c_str(), static_cast<int>(mCanvasSize.x), static_cast<int>(mCanvasSize.y), 4, pixels.data(), static_cast<int>(mCanvasSize.x * 4));
}

CanvasManager gCanvasManager;

NUVIO_NAMESPACE_END
