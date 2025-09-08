#include "core/shortcut/manager.h"
#include "GLFW/glfw3.h"
#include "Tracy.hpp"
#include "core/window/window_manager.h"

NUVIO_NAMESPACE_BEGIN

void ShortcutManager::process() {
    ZoneScopedN("ShortcutManager::process");

    for (auto &_shortcut : mShortcuts) {
        bool already_handled =
            (std::find(handledShortcuts.begin(), handledShortcuts.end(), _shortcut) != handledShortcuts.end());

        int state = (_shortcut.type == ShortcutType::Key) ? glfwGetKey(glfwGetCurrentContext(), _shortcut.key)
                                                          : glfwGetMouseButton(glfwGetCurrentContext(), _shortcut.key);

        // Handle shortcuts with NO modifiers: only fire if NO modifiers are pressed
        if (_shortcut.modifiers.empty()) {
            bool noModifiersPressed = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_CONTROL) != GLFW_PRESS &&
                                      glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT_CONTROL) != GLFW_PRESS &&
                                      glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS &&
                                      glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT_SHIFT) != GLFW_PRESS &&
                                      glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_ALT) != GLFW_PRESS &&
                                      glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT_ALT) != GLFW_PRESS;

            if (_shortcut.wantedstate == WantedState::Press) {
                if (noModifiersPressed && state == GLFW_PRESS && !already_handled) {
                    _shortcut.callback();
                    handledShortcuts.push_back(_shortcut);
                }
            } else { // WantedState::Release
                if (noModifiersPressed && state == GLFW_RELEASE && !already_handled) {
                    _shortcut.callback();
                    handledShortcuts.push_back(_shortcut);
                }
            }
        }
        // Handle shortcuts WITH modifiers: only fire if ALL required modifiers are pressed
        else {
            bool modifiersPressed = true;
            for (auto &modifier : _shortcut.modifiers) {
                if (glfwGetKey(glfwGetCurrentContext(), modifier) != GLFW_PRESS) {
                    modifiersPressed = false;
                    break;
                }
            }
            if (_shortcut.wantedstate == WantedState::Press) {
                if (modifiersPressed && state == GLFW_PRESS && !already_handled) {
                    _shortcut.callback();
                    handledShortcuts.push_back(_shortcut);
                }
            } else { // WantedState::Release
                if (modifiersPressed && state == GLFW_RELEASE && !already_handled) {
                    _shortcut.callback();
                    handledShortcuts.push_back(_shortcut);
                }
            }
        }
    }

    // Cleanup handledShortcuts:
    handledShortcuts.erase(std::remove_if(handledShortcuts.begin(), handledShortcuts.end(),
                                          [](const shortcut &sc) {
                                              int state = (sc.type == ShortcutType::Key)
                                                              ? glfwGetKey(glfwGetCurrentContext(), sc.key)
                                                              : glfwGetMouseButton(glfwGetCurrentContext(), sc.key);
                                              if (sc.wantedstate == WantedState::Press) {
                                                  // Remove when released (so can trigger again on next press)
                                                  return state == GLFW_RELEASE;
                                              } else {
                                                  // Remove when PRESSED AGAIN (so can trigger again on next release)
                                                  return state == GLFW_PRESS;
                                              }
                                          }),
                           handledShortcuts.end());
}

void ShortcutManager::register_shortcut(shortcut _shortcut) { mShortcuts.push_back(_shortcut); }

void ShortcutManager::unregister_shortcut(shortcut _shortcut) {
    mShortcuts.erase(std::remove(mShortcuts.begin(), mShortcuts.end(), _shortcut), mShortcuts.end());
}

ShortcutManager gShortcutManager;

NUVIO_NAMESPACE_END
