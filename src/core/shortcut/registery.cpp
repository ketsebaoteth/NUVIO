#include "core/shortcut/registery.h"
#include <cstdio>

NUVIO_NAMESPACE_BEGIN

std::vector<shortcut> all_shortcuts = {
    {
        GLFW_KEY_S,
        []() {
           printf("Save triggered \n");
        },
        {GLFW_KEY_LEFT_CONTROL}
    },
};

void register_all_shortcuts(){
    for(auto& sc : all_shortcuts) {
        nuvio::gShortcutManager.register_shortcut(sc);
    }
}

NUVIO_NAMESPACE_END