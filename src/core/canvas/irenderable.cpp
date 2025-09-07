#include "core/canvas/manager.h"
#include "core/canvas/irenderable.h"   // Gets AddRenderableAction, etc.

NUVIO_CANVAS_NAMESPACE_BEGIN

AddRenderableAction::AddRenderableAction(Irenderable* rend, int idx)
    : renderable(rend), layerIndex(idx) {}

void AddRenderableAction::execute() {
  nuvio::gCanvasManager.AppendRenderable(renderable, layerIndex);
}

void AddRenderableAction::undo() {
  nuvio::gCanvasManager.RemoveRenderable(renderable, layerIndex);
}

NUVIO_CANVAS_NAMESPACE_END
