#pragma once

#include "core/nuvio_namespaces.h"
#include <string>
#include <vector>

NUVIO_NAMESPACE_BEGIN

struct Project {
    std::string name;
    std::string version;
    std::string description;
    std::string author;
    std::string path;
};

struct Projects {
    std::vector<Project> projects;
};





NUVIO_NAMESPACE_END
