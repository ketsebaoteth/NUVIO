#pragma once
#include "core/nuvio_namespaces.h"
#include <string>

NUVIO_UI_NAMESPACE_BEGIN

struct component{
    std::string unique_name;
    void (*Render)();

    bool operator==(const component& other) const {
        return unique_name == other.unique_name;
    }
};

NUVIO_UI_NAMESPACE_END
