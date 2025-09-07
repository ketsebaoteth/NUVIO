#include "core/canvas/manager.h"
#include "core/canvas/irenderable.h"
#include "core/canvas/shader.h"
#include "core/canvas/utils/shape_utils.h"
#include "core/utils/vector.h"
#include "glm/detail/qualifier.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"
#include <cassert>
#include <cstdio>
#include <ios>
#include <iostream>
#include <ostream>
#include <pstl/glue_algorithm_defs.h>

NUVIO_NAMESPACE_BEGIN

void CanvasManager::Init(int width, int height) {
  assert(width > 0 && height > 0 && "Width and Height must be greater than 0");
  mCanvasSize =
      glm::vec2(static_cast<float>(width), static_cast<float>(height));

  // create frame buffer
  glGenFramebuffers(1, &mFramebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

  // create canvas texture
  glGenTextures(1, &mCanvasTexture);
  glBindTexture(GL_TEXTURE_2D, mCanvasTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(mCanvasSize.x),
               static_cast<GLsizei>(mCanvasSize.y), 0, GL_RGBA,
               GL_UNSIGNED_BYTE, nullptr);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // attach texture to frame buffer
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         mCanvasTexture, 0);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "Canvas framebuffer is incomplete!" << std::endl;
  }

  // unbind buffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  // create shader
  mShader = canvas::shader("shaders/default_vertex.glsl",
                           "shaders/default_fragment.glsl");
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride,
                        (void *)offsetof(canvas::vertex, position));
  glEnableVertexAttribArray(0);

  // uv (location 1)
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride,
                        (void *)offsetof(canvas::vertex, uv));
  glEnableVertexAttribArray(1);

  // color (location 2)
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride,
                        (void *)offsetof(canvas::vertex, color));
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
  glViewport(0, 0, static_cast<GLsizei>(mCanvasSize.x),
             static_cast<GLsizei>(mCanvasSize.y));

  glClearColor(mCanvasBackgroundColor.r, mCanvasBackgroundColor.g,
               mCanvasBackgroundColor.b, mCanvasBackgroundColor.a);
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
      glBufferData(GL_ARRAY_BUFFER,
                   data.verticies.size() * sizeof(canvas::vertex),
                   data.verticies.data(), GL_DYNAMIC_DRAW);
      // //upload indecies data
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                   data.indecies.size() * sizeof(uint32_t),
                   data.indecies.data(), GL_DYNAMIC_DRAW);

      glDrawElements(GL_TRIANGLES, data.indecies.size(), GL_UNSIGNED_INT, 0);
      //
      glBindVertexArray(0);
    }
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  return mCanvasTexture;
}

glm::vec2 CanvasManager::GetCanvasSize() { return mCanvasSize; }

glm::vec2 CanvasManager::GetCanvasPosition() { return mCanvasPosition; }

void CanvasManager::SetCanvasPosition(const glm::vec2 &position) {
  mCanvasPosition = position;
}

void CanvasManager::SetCanvasBackgroundColor(const glm::vec4 &color) {
  mCanvasBackgroundColor = color;
}

void CanvasManager::AppendLayer(std::vector<canvas::Irenderable *> Layer) {
  mLayers.push_back(Layer);
}

void CanvasManager::AppendRenderable(canvas::Irenderable *renderable,
                                     int index) {
  mLayers[index].push_back(renderable);
}

void CanvasManager::RemoveRenderable(canvas::Irenderable *renderable,
                                     int index) {
  auto &vec = mLayers[index];
  vec.erase(std::remove(vec.begin(), vec.end(), renderable), vec.end());
}

void CanvasManager::SetMouseDelta(ImVec2 mouseDelta) {
  mMouseDelta = mouseDelta;
}

void CanvasManager::SetMouseLocation(ImVec2 mouseLocation) {
  mMouseLocation = mouseLocation;
  updateMouseCollision();
}

void CanvasManager::AddActiveRenderable(canvas::Irenderable *renderable) {
  mSelectedRenderables.push_back(renderable);
}

void CanvasManager::updateSelected() {
  mSelectedRenderables.clear();
  for (auto &layers : mLayers) {
    for (auto &renderables : layers) {
      canvas::Rect renderable_rect = renderables->get_rect();
      if (isPointInRect(renderable_rect, mMouseLocation)) {
        AddActiveRenderable(renderables);
        // If only one selection allowed, return here
        // return;
      }
    }
  }
}

bool CanvasManager::isPointInRect(nuvio::canvas::Rect &rect, ImVec2 &vec) {
  // Canvas dimensions in pixels
  float canvas_width = mCanvasSize.x;
  float canvas_height = mCanvasSize.y;

  // Helper lambda to convert OpenGL [-1, 1] to pixel space [0, canvas_size]
  auto glToPixelX = [&](float gl_x) {
    return ((gl_x + 1.0f) * 0.5f) * canvas_width;
  };
  auto glToPixelY = [&](float gl_y) {
    return ((1.0f - gl_y) * 0.5f) * canvas_height;
  };

  // Convert rect edges from OpenGL space to pixel space
  float left_px = glToPixelX(rect.edge_position(nuvio::canvas::RectSide::LEFT));
  float right_px =
      glToPixelX(rect.edge_position(nuvio::canvas::RectSide::RIGHT));
  float bottom_px = glToPixelY(rect.edge_position(nuvio::canvas::RectSide::TOP));
  float top_px =
      glToPixelY(rect.edge_position(nuvio::canvas::RectSide::BOTTOM));
 

  // Check if the point is within the rectangle bounds
  return (vec.x >= left_px && vec.x <= right_px && vec.y >= top_px &&
          vec.y <= bottom_px);
}

ImVec2 CanvasManager::NDCToScreen(const ImVec2 &ndc) {
  // Convert NDC -> canvas-local pixel coords, then offset by canvas position
  return ImVec2(mCanvasPosition.x + (ndc.x + 1.0f) * 0.5f * mCanvasSize.x,
                mCanvasPosition.y +
                    (1.0f - (ndc.y + 1.0f) * 0.5f) * mCanvasSize.y);
}

void CanvasManager::updateMouseCollision() {
  for (auto &renderables : mSelectedRenderables) {
    canvas::Rect renderable_rect = renderables->get_rect();
    // 1. Get rect edges in NDC
    float left = renderable_rect.edge_position(canvas::RectSide::LEFT);
    float right = renderable_rect.edge_position(canvas::RectSide::RIGHT);
    float top = renderable_rect.edge_position(canvas::RectSide::TOP);
    float bottom = renderable_rect.edge_position(canvas::RectSide::BOTTOM);

    // 2. Convert corners to absolute screen pixel coords
    ImVec2 top_left_screen = NDCToScreen(ImVec2(left, top));
    ImVec2 bottom_right_screen = NDCToScreen(ImVec2(right, bottom));
    // 3. Draw in ImGui overlay
    ImDrawList *draw_list = ImGui::GetForegroundDrawList();
    draw_list->AddRect({top_left_screen.x-10,top_left_screen.y+10}, {bottom_right_screen.x + 10, bottom_right_screen.y - 10},
                       IM_COL32(0, 0, 255, 255), 0.0f, 0, 2.0f

    );

    // (Your rect move code as before)
    float world_dx = 2.0f * mMouseDelta.x / mCanvasSize.x;
    float world_dy = -2.0f * mMouseDelta.y / mCanvasSize.y;
    canvas::Rect newrect = {{renderable_rect.position.x + world_dx,
                             renderable_rect.position.y + world_dy},
                            {renderable_rect.size.x, renderable_rect.size.y}};
    renderables->set_rect(newrect);
  }
}

CanvasManager gCanvasManager;

NUVIO_NAMESPACE_END
