#include "core/canvas/manager.h"
#include "core/shortcut/registery.h"
#include "GLFW/glfw3.h"
#include "core/shortcut/manager.h"
#include "core/undo/manager.h"
#include "core/window/window_manager.h"
#include "imgui.h"
#include <cstdio>
#include <iostream>

NUVIO_NAMESPACE_BEGIN

std::vector<shortcut> all_shortcuts = {
    // -- save shortcut -- 
    {
        ShortcutType::Key,
        WantedState::Press, // type for this shortcut
        GLFW_KEY_S,
        []() {
            printf("Save triggered \n");
        },
        {GLFW_KEY_LEFT_CONTROL}
    },
    // -- undo shortcut --
    {
        ShortcutType::Key,
        WantedState::Press,
        GLFW_KEY_Z,
        [](){
            gUndoManager.undo_last_action();
        },
        {GLFW_KEY_LEFT_CONTROL}
    },
    // -- redo shortcut --
    {
        ShortcutType::Key,
        WantedState::Press,
        GLFW_KEY_Y,
        [](){
            gUndoManager.redo_last_undo();
        },
        {GLFW_KEY_LEFT_CONTROL}
    },
    // -- close window shortcut --
    {
        ShortcutType::Key,
        WantedState::Press,
        GLFW_KEY_Q,
        [](){
            gWindowManager.request_close();
},
        {GLFW_KEY_LEFT_CONTROL}
    },
    // -- select shortcut --
    {
        ShortcutType::MouseButton,
        WantedState::Press,
        GLFW_MOUSE_BUTTON_LEFT,
        [](){
          gCanvasManager.updateSelected();
        },
        {}
    },
    {
      ShortcutType::MouseButton,
      WantedState::Press,
      GLFW_MOUSE_BUTTON_LEFT,
      [](){
        gCanvasManager.AppendSelected();
      },
      {GLFW_KEY_LEFT_CONTROL}
    },
    {
        ShortcutType::MouseButton,
        WantedState::Release,
        GLFW_MOUSE_BUTTON_LEFT,
        [](){
            ImGui::ResetMouseDragDelta();
        },
        {}
    },
    
};

void register_all_shortcuts(){
    for(auto& sc : all_shortcuts) {
        nuvio::gShortcutManager.register_shortcut(sc);
    }
}

NUVIO_NAMESPACE_END
