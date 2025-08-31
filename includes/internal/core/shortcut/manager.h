#pragma once
#include "core/nuvio_namespaces.h"
#include <unordered_map>
#include "GLFW/glfw3.h"
#include <vector>
#include <algorithm>

NUVIO_NAMESPACE_BEGIN

struct shortcut{
    int key;
    void(*callback)();
    std::vector<int> modifiers;

    bool operator==(const shortcut& other) const {
        return key == other.key && callback == other.callback && modifiers == other.modifiers;
    }
};

class ShortcutManager {
    public:
        void update();
        void register_shortcut(shortcut _shortcut);
        void unregister_shortcut(shortcut _shortcut);
    private:
        // Input state
        std::vector<shortcut> mShortcuts;
        std::vector<shortcut> handledShortcuts;

};

extern ShortcutManager gShortcutManager;

NUVIO_NAMESPACE_END
