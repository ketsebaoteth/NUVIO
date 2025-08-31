#pragma once
#include "core/nuvio_namespaces.h"
#include "core/shortcut/manager.h"

NUVIO_NAMESPACE_BEGIN

void register_all_shortcuts();

extern std::vector<shortcut> all_shortcuts;

NUVIO_NAMESPACE_END