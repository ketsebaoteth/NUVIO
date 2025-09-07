#include "core/shortcut/registery.h"
#include "GLFW/glfw3.h"
#include "core/undo/manager.h"
#include "core/window/window_manager.h"
#include <cstdio>

NUVIO_NAMESPACE_BEGIN

std::vector<shortcut> all_shortcuts = {
    // -- save shortcut -- 
    // note this dosent do much now its for testing only
    {
        GLFW_KEY_S,
        []() {
           printf("Save triggered \n");
        },
        {GLFW_KEY_LEFT_CONTROL}
    },
    // -- undo shortcut --
    {
        GLFW_KEY_Z,
        [](){
          gUndoManager.undo_last_action();
        },
        {GLFW_KEY_LEFT_CONTROL}
    },
    // -- redo shortcut --
    {
        GLFW_KEY_Y,
        [](){
          gUndoManager.redo_last_undo();
        },
        {GLFW_KEY_LEFT_CONTROL}
    },
    // -- close window shortcut --
    {
      GLFW_KEY_Q,
      [](){
        gWindowManager.destroy_window();
      },
      {GLFW_KEY_LEFT_CONTROL}
    }
};

void register_all_shortcuts(){
    for(auto& sc : all_shortcuts) {
        nuvio::gShortcutManager.register_shortcut(sc);
    }
}

NUVIO_NAMESPACE_END
