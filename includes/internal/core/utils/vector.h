#pragma once

#include "core/canvas/utils/shape_utils.h"
#include "imgui.h"
template <typename T> struct vec2 {
  T x, y;
};

bool isPointInRect(nuvio::canvas::Rect &rect, ImVec2 &vec);
