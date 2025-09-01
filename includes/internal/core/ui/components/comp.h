#pragma once
#include "core/nuvio_namespaces.h"
#include <string>
#include <functional>

NUVIO_UI_NAMESPACE_BEGIN

struct component{
    std::string unique_name;
    std::function<void()> Render;

    bool operator==(const component& other) const {
        return unique_name == other.unique_name;
    }
};

NUVIO_UI_NAMESPACE_END
