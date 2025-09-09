#pragma once
#include "core/nuvio_namespaces.h"
#include "core/ui/components/menu_item.h"
#include <memory>


NUVIO_UI_NAMESPACE_BEGIN

void render_navbar();

component get_navbar_component();

extern std::shared_ptr<menu_item> gNavbar;

NUVIO_UI_NAMESPACE_END
