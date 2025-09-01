#pragma once
#include "core/nuvio_namespaces.h"
#include "core/ui/components/menu_item.h"
#include <memory>


NUVIO_UI_NAMESPACE_BEGIN

std::unique_ptr<component> get_viewport_component();

NUVIO_UI_NAMESPACE_END
