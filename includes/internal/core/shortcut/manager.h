#pragma once
#include "GLFW/glfw3.h"
#include "core/nuvio_namespaces.h"
#include <algorithm>
#include <unordered_map>
#include <vector>

NUVIO_NAMESPACE_BEGIN
enum class ShortcutType { Key, MouseButton };
enum class WantedState { Press, Release };

struct shortcut {
  ShortcutType type = ShortcutType::Key;
  WantedState wantedstate = WantedState::Press;
  int key;
  void (*callback)();
  std::vector<int> modifiers;

  bool operator==(const shortcut &other) const {
    return key == other.key && callback == other.callback &&
           modifiers == other.modifiers;
  }
};

class ShortcutManager {
public:
  void process();
  void register_shortcut(shortcut _shortcut);
  void unregister_shortcut(shortcut _shortcut);
  void shutdown();

private:
  // Input state
  std::vector<shortcut> mShortcuts;
  std::vector<shortcut> handledShortcuts;
};

extern ShortcutManager gShortcutManager;

NUVIO_NAMESPACE_END
