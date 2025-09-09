#pragma once
#include "core/nuvio_namespaces.h"
#include <string>
#include <vector>
#include "core/ui/components/comp.h"
#include <memory>

NUVIO_UI_NAMESPACE_BEGIN

enum class separator_direction{
  UP,
  DOWN,
  NONE
};

struct menu_item {
    std::string title;
    std::string shortcut;
    std::string tooltip_title;
    std::string tooltip_desc;
    separator_direction sd = separator_direction::NONE;
    std::string icon; // icon path relative to /assets/icons/
    std::vector<std::shared_ptr<menu_item>> children;
    void(*on_click)();
    void(*on_hover)();
    // add more event handlers if needed
};

NUVIO_UI_NAMESPACE_END
