#pragma once

#include "core/ui/components/comp.h"
#include <memory>
#include "core/nuvio_namespaces.h"



NUVIO_UI_NAMESPACE_BEGIN
// Test component
std::unique_ptr<component> get_test_component();

void RenderTestComponent();

NUVIO_UI_NAMESPACE_END


