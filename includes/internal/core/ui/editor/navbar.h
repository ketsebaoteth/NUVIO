#pragma once
#include "core/nuvio_namespaces.h"
#include "core/ui/components/menu_item.h"
#include <memory>


NUVIO_UI_NAMESPACE_BEGIN

void render_navbar();

std::unique_ptr<component> get_navbar_component();

extern menu_item gNavbar;

NUVIO_UI_NAMESPACE_END
