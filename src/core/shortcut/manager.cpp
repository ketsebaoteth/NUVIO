#include "core/shortcut/manager.h"
#include "GLFW/glfw3.h"
#include "Tracy.hpp"

NUVIO_NAMESPACE_BEGIN

void ShortcutManager::process() {
  ZoneScopedN("ShortcutManager::process");
  for (auto &_shortcut : mShortcuts) {
    bool modifier_pressed = true;
    for (auto &modifier : _shortcut.modifiers) {
      if (glfwGetKey(glfwGetCurrentContext(), modifier) != GLFW_PRESS) {
        modifier_pressed = false;
        break;
      }
    }
    bool already_handled =
        (std::find(handledShortcuts.begin(), handledShortcuts.end(),
                   _shortcut) != handledShortcuts.end());
    if (_shortcut.type == ShortcutType::Key) {
      if (modifier_pressed &&
          glfwGetKey(glfwGetCurrentContext(), _shortcut.key) == GLFW_PRESS &&
          !already_handled) {
        _shortcut.callback();
        handledShortcuts.push_back(_shortcut);
      }
    } else {
      if (modifier_pressed &&
          glfwGetMouseButton(glfwGetCurrentContext(), _shortcut.key) ==
              GLFW_PRESS &&
          !already_handled) {
        _shortcut.callback();
        handledShortcuts.push_back(_shortcut);
      }
    }
  }
  //handle shortcuts that are completed
  handledShortcuts.erase(
      std::remove_if(
          handledShortcuts.begin(), handledShortcuts.end(),
          [](const shortcut &sc) {
            bool still_pressed = false;
            if (sc.type == ShortcutType::Key) {
              still_pressed =
                  glfwGetKey(glfwGetCurrentContext(), sc.key) == GLFW_PRESS;
            } else {
              still_pressed = glfwGetMouseButton(glfwGetCurrentContext(),
                                                 sc.key) == GLFW_PRESS;
            }
            if (still_pressed) {
              for (auto &mod : sc.modifiers) {
                if (glfwGetKey(glfwGetCurrentContext(), mod) != GLFW_PRESS)
                  return true; // Modifier released
              }
              return false; // All still pressed
            }
            return true; // Key or button released
          }),
      handledShortcuts.end());
}

void ShortcutManager::register_shortcut(shortcut _shortcut) {
  mShortcuts.push_back(_shortcut);
}

void ShortcutManager::unregister_shortcut(shortcut _shortcut) {
  mShortcuts.erase(std::remove(mShortcuts.begin(), mShortcuts.end(), _shortcut),
                   mShortcuts.end());
}

ShortcutManager gShortcutManager;

NUVIO_NAMESPACE_END
